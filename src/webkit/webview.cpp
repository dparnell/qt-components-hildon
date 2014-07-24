/*
 * Copyright (C) 2014 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 3, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "webview_p.h"
#include "webview_p_p.h"
#include "webhistory_p.h"
#include "websettings_p.h"
#include <QMoveEvent>
#include <QResizeEvent>
#include <QActionGroup>
#include <QWebFrame>
#include <QScrollBar>
#include <QAbstractKineticScroller>
#include <QGraphicsOpacityEffect>
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QDeclarativeComponent>
#include <QDeclarativeInfo>

WebView::WebView(QWidget *parent) :
    QWebView(parent),
    d_ptr(new WebViewPrivate(this))
{
    Q_D(WebView);

    d->suppressor = new WebViewSelectionSuppressor(this);

    if (QDeclarativeEngine *engine = qmlEngine(this)) {
        this->page()->setNetworkAccessManager(engine->networkAccessManager());
    }

    this->connect(this->page(), SIGNAL(linkClicked(QUrl)), this, SIGNAL(linkClicked(QUrl)));
    this->connect(this->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(_q_onJavaScriptWindowObjectCleared()));
    this->connect(this, SIGNAL(titleChanged(QString)), this, SIGNAL(titleChanged()));
    this->connect(this, SIGNAL(urlChanged(QUrl)), this, SIGNAL(urlChanged()));
    this->connect(this, SIGNAL(loadStarted()), this, SLOT(_q_onLoadStarted()));
    this->connect(this, SIGNAL(loadFinished(bool)), this, SLOT(_q_onLoadFinished(bool)));
    this->connect(this, SIGNAL(loadProgress(int)), this, SLOT(_q_onLoadProgress(int)));
    this->connect(this, SIGNAL(statusBarMessage(QString)), this, SLOT(_q_onStatusBarMessage(QString)));
}

WebView::WebView(WebViewPrivate &dd, QWidget *parent) :
    QWebView(parent),
    d_ptr(&dd)
{
    Q_D(WebView);

    d->suppressor = new WebViewSelectionSuppressor(this);

    if (QDeclarativeEngine *engine = qmlEngine(this)) {
        this->page()->setNetworkAccessManager(engine->networkAccessManager());
    }

    this->connect(this->page(), SIGNAL(linkClicked(QUrl)), this, SIGNAL(linkClicked(QUrl)));
    this->connect(this->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(_q_onJavaScriptWindowObjectCleared()));
    this->connect(this, SIGNAL(titleChanged(QString)), this, SIGNAL(titleChanged()));
    this->connect(this, SIGNAL(urlChanged(QUrl)), this, SIGNAL(urlChanged()));
    this->connect(this, SIGNAL(loadStarted()), this, SLOT(_q_onLoadStarted()));
    this->connect(this, SIGNAL(loadFinished(bool)), this, SLOT(_q_onLoadFinished(bool)));
    this->connect(this, SIGNAL(loadProgress(int)), this, SLOT(_q_onLoadProgress(int)));
    this->connect(this, SIGNAL(statusBarMessage(QString)), this, SLOT(_q_onStatusBarMessage(QString)));
}

WebView::~WebView() {}

void WebView::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void WebView::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

qreal WebView::opacity() const {
    if (QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect())) {
        return effect->opacity();
    }

    return 1.0;
}

void WebView::setOpacity(qreal opacity) {
    QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect());

    if (!effect) {
        effect = new QGraphicsOpacityEffect(this);
        this->setGraphicsEffect(effect);
    }

    if (opacity != effect->opacity()) {
        effect->setOpacity(opacity);
        emit opacityChanged();
    }
}

AnchorLine WebView::left() const {
    Q_D(const WebView);

    return d->left;
}

AnchorLine WebView::right() const {
    Q_D(const WebView);

    return d->right;
}

AnchorLine WebView::top() const {
    Q_D(const WebView);

    return d->top;
}

AnchorLine WebView::bottom() const {
    Q_D(const WebView);

    return d->bottom;
}

AnchorLine WebView::horizontalCenter() const {
    Q_D(const WebView);

    return d->horizontalCenter;
}

AnchorLine WebView::verticalCenter() const {
    Q_D(const WebView);

    return d->verticalCenter;
}

QString WebView::iconSource() const {
    return this->icon().name();
}

bool WebView::textSelectionEnabled() const {
    Q_D(const WebView);

    return !d->suppressor->isEnabled();
}

void WebView::setTextSelectionEnabled(bool enabled) {
    Q_D(WebView);

    if (enabled == this->textSelectionEnabled()) {
        return;
    }

    if (enabled) {
        d->suppressor->disable();
    }
    else {
        d->suppressor->enable();
    }

    d->kineticScroller->setEnabled(!enabled);

    emit textSelectionEnabledChanged();
}

QWebPage::LinkDelegationPolicy WebView::linkDelegationPolicy() const {
    return this->page() ? this->page()->linkDelegationPolicy() : QWebPage::DontDelegateLinks;
}

void WebView::setLinkDelegationPolicy(QWebPage::LinkDelegationPolicy policy) {
    if ((policy != this->linkDelegationPolicy()) && (this->page())) {
        this->page()->setLinkDelegationPolicy(policy);
        emit linkDelegationPolicyChanged();
    }
}

bool WebView::moving() const {
    Q_D(const WebView);

    switch (d->kineticScroller->state()) {
    case QAbstractKineticScroller::Pushing:
    case QAbstractKineticScroller::AutoScrolling:
        return true;
    default:
        return false;
    }
}

bool WebView::atXBeginning() const {
    if (this->page()) {
        return this->page()->mainFrame()->scrollBarValue(Qt::Horizontal) == this->page()->mainFrame()->scrollBarMinimum(Qt::Horizontal);
    }

    return false;
}

bool WebView::atXEnd() const {
    if (this->page()) {
        return this->page()->mainFrame()->scrollBarValue(Qt::Horizontal) == this->page()->mainFrame()->scrollBarMaximum(Qt::Horizontal);
    }

    return false;
}

bool WebView::atYBeginning() const {
    if (this->page()) {
        return this->page()->mainFrame()->scrollBarValue(Qt::Vertical) == this->page()->mainFrame()->scrollBarMinimum(Qt::Vertical);
    }

    return false;
}

bool WebView::atYEnd() const {
    if (this->page()) {
        return this->page()->mainFrame()->scrollBarValue(Qt::Vertical) == this->page()->mainFrame()->scrollBarMaximum(Qt::Vertical);
    }

    return false;
}

int WebView::contentX() const {
    if (this->page()) {
        return this->page()->mainFrame()->scrollBarValue(Qt::Horizontal);
    }

    return 0;
}

void WebView::setContentX(int x) {
    if (this->page()) {
        this->page()->mainFrame()->setScrollBarValue(Qt::Horizontal, x);
    }
}

int WebView::contentY() const {
    if (this->page()) {
        return this->page()->mainFrame()->scrollBarValue(Qt::Vertical);
    }

    return 0;
}

void WebView::setContentY(int y) {
    if (this->page()) {
        this->page()->mainFrame()->setScrollBarValue(Qt::Vertical, y);
    }
}

qreal WebView::flickDeceleration() const {
    Q_D(const WebView);

    return d->kineticScroller->decelerationFactor();
}

void WebView::setFlickDeceleration(qreal deceleration) {
    if (deceleration != this->flickDeceleration()) {
        Q_D(WebView);
        d->kineticScroller->setDecelerationFactor(deceleration);
        emit flickDecelerationChanged();
    }
}

qreal WebView::maximumFlickVelocity() const {
    Q_D(const WebView);

    return d->kineticScroller->maximumVelocity();
}

void WebView::setMaximumFlickVelocity(qreal maximum) {
    if (maximum != this->maximumFlickVelocity()) {
        Q_D(WebView);
        d->kineticScroller->setMaximumVelocity(maximum);
        emit maximumFlickVelocityChanged();
    }
}

int WebView::progress() const {
    Q_D(const WebView);

    return d->progress;
}

WebView::Status WebView::status() const {
    Q_D(const WebView);

    return d->status;
}

QString WebView::statusText() const {
    Q_D(const WebView);

    return d->statusText;
}

QDeclarativeComponent* WebView::newWindowComponent() const {
    Q_D(const WebView);

    return d->windowComponent;
}

void WebView::setNewWindowComponent(QDeclarativeComponent *component) {
    if (component != this->newWindowComponent()) {
        Q_D(WebView);
        d->windowComponent = component;
        emit newWindowComponentChanged();
    }
}

QWidget* WebView::newWindowParent() const {
    Q_D(const WebView);

    return d->windowParent;
}

void WebView::setNewWindowParent(QWidget *parent) {
    if (parent != this->newWindowParent()) {
        Q_D(WebView);
        d->windowParent = parent;
        emit newWindowParentChanged();
    }
}

bool WebView::findText(const QString &text) {
    return QWebView::findText(text, QWebPage::FindWrapsAroundDocument);
}

QWebView* WebView::createWindow(QWebPage::WebWindowType type) {
    Q_UNUSED(type);
    Q_D(WebView);

    if (!d->windowComponent) {
        return 0;
    }

    QWebView *view = 0;
    QDeclarativeContext *creationContext = d->windowComponent->creationContext();
    QDeclarativeContext *context = new QDeclarativeContext(creationContext ? creationContext : qmlContext(this));

    if (QObject *obj = d->windowComponent->create(context)) {
        if (QWidget *widget = qobject_cast<QWidget*>(obj)) {
            view = qobject_cast<QWebView*>(widget);

            if (!view) {
                foreach (QObject *ch, widget->children()) {
                    view = qobject_cast<QWebView*>(ch);

                    if (view) {
                        break;
                    }
                }
            }

            if (view) {
                widget->setParent(d->windowParent);
            }
            else {
                qmlInfo(this) << tr("No WebView found in window component");
                delete widget;
                delete context;
            }
        }
        else {
            qmlInfo(this) << tr("Window component is not a visual item");
            delete obj;
            delete context;
        }
    }
    else {
        delete context;
    }

    return view;
}

void WebView::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    case QEvent::EnabledChange:
        emit enabledChanged();
        break;
    default:
        break;
    }

    QWebView::changeEvent(event);
}

void WebView::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QWebView::moveEvent(event);
}

void WebView::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QWebView::resizeEvent(event);
}

void WebView::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QWebView::showEvent(event);
}

void WebView::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QWebView::hideEvent(event);
}

void WebView::focusInEvent(QFocusEvent *event) {
    emit focusChanged();
    QWebView::focusInEvent(event);
}

void WebView::focusOutEvent(QFocusEvent *event) {
    emit focusChanged();
    QWebView::focusOutEvent(event);
}

void WebView::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_C:
        if (event->modifiers() & Qt::ControlModifier) {
            this->triggerPageAction(QWebPage::Copy);
            event->accept();
            return;
        }

        break;
    case Qt::Key_X:
        if (event->modifiers() & Qt::ControlModifier) {
            this->triggerPageAction(QWebPage::Cut);
            event->accept();
            return;
        }

        break;
    case Qt::Key_V:
        if (event->modifiers() & Qt::ControlModifier) {
            this->triggerPageAction(QWebPage::Paste);
            event->accept();
            return;
        }

        break;
    default:
        break;
    }

    QWebView::keyPressEvent(event);
}

void WebView::classBegin() {}

void WebView::componentComplete() {
    Q_D(WebView);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    if (d->qmlVisible()) {
        this->show();
    }

    foreach (QObject *obj, d->jsObjectList) {
        this->page()->mainFrame()->addToJavaScriptWindowObject(obj->objectName(), obj);
    }
}

void WebViewPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (WebView *view = qobject_cast<WebView*>(list->object)) {
        view->d_func()->dataList.append(obj);

        if (obj->isWidgetType()) {
            view->d_func()->childrenList.append(qobject_cast<QWidget*>(obj));
        }
    }
}

void WebViewPrivate::children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget) {
    if (!widget) {
        return;
    }

    if (WebView *view = qobject_cast<WebView*>(list->object)) {
        view->d_func()->childrenList.append(widget);
        view->d_func()->dataList.append(widget);
    }
}

void WebViewPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (WebView *view = qobject_cast<WebView*>(list->object)) {
        view->d_func()->actionList.append(obj);
        view->d_func()->dataList.append(obj);

        if (!view->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            view->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            view->addActions(group->actions());
        }
    }
}

void WebViewPrivate::jsobjects_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (WebView *view = qobject_cast<WebView*>(list->object)) {
        view->d_func()->jsObjectList.append(obj);
        view->d_func()->dataList.append(obj);

        if (view->d_func()->complete) {
            view->page()->mainFrame()->addToJavaScriptWindowObject(obj->objectName(), obj);
        }
    }
}

QDeclarativeListProperty<QObject> WebViewPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, WebViewPrivate::data_append);
}

QDeclarativeListProperty<QWidget> WebViewPrivate::children() {
    return QDeclarativeListProperty<QWidget>(q_func(), 0, WebViewPrivate::children_append);
}

QDeclarativeListProperty<QObject> WebViewPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, WebViewPrivate::actions_append);
}

QDeclarativeListProperty<QObject> WebViewPrivate::jsObjects() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, WebViewPrivate::jsobjects_append);
}

WebHistory* WebViewPrivate::history() {
    Q_Q(WebView);

    if (!webHistory) {
        webHistory = new WebHistory(q->history(), q);
    }

    return webHistory;
}

WebSettings* WebViewPrivate::settings() {
    Q_Q(WebView);

    if (!webSettings) {
        webSettings = new WebSettings(q->settings(), q);
    }

    return webSettings;
}

void WebViewPrivate::_q_onLoadStarted() {
    Q_Q(WebView);

    status = WebView::Loading;
    emit q->statusChanged();
    emit q->urlChanged();
    emit q->titleChanged();
}

void WebViewPrivate::_q_onLoadFinished(bool ok) {
    Q_Q(WebView);

    status = ok ? WebView::Ready : WebView::Error;
    emit q->statusChanged();
    emit q->urlChanged();
    emit q->titleChanged();
}

void WebViewPrivate::_q_onLoadProgress(int p) {
    Q_Q(WebView);

    progress = p;
    emit q->progressChanged();
}

void WebViewPrivate::_q_onStatusBarMessage(const QString &message) {
    if (message != statusText) {
        statusText = message;
        Q_Q(WebView);
        emit q->statusTextChanged();
    }
}

void WebViewPrivate::_q_onJavaScriptWindowObjectCleared() {
    Q_Q(WebView);

    foreach (QObject *obj, jsObjectList) {
        q->page()->mainFrame()->addToJavaScriptWindowObject(obj->objectName(), obj);
    }
}

#include "moc_webview_p.cpp"
