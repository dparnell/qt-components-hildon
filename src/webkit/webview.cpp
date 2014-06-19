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
#include <QMoveEvent>
#include <QResizeEvent>
#include <QActionGroup>
#include <QAbstractKineticScroller>

WebView::WebView(QWidget *parent) :
    QWebView(parent),
    d_ptr(new WebViewPrivate(this))
{
    Q_D(WebView);

    d->suppressor = new WebViewSelectionSuppressor(this);

    this->setTextSelectionEnabled(false);
    this->connect(this, SIGNAL(loadStarted()), this, SLOT(_q_onLoadStarted()));
    this->connect(this, SIGNAL(loadFinished(bool)), this, SLOT(_q_onLoadFinished(bool)));
    this->connect(this, SIGNAL(loadProgress(int)), this, SLOT(_q_onLoadProgress(int)));
}

WebView::WebView(WebViewPrivate &dd, QWidget *parent) :
    QWebView(parent),
    d_ptr(&dd)
{
    this->setTextSelectionEnabled(false);
    this->connect(this, SIGNAL(loadStarted()), this, SLOT(_q_onLoadStarted()));
    this->connect(this, SIGNAL(loadFinished(bool)), this, SLOT(_q_onLoadFinished(bool)));
    this->connect(this, SIGNAL(loadProgress(int)), this, SLOT(_q_onLoadProgress(int)));
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

    if (enabled = this->textSelectionEnabled()) {
        return;
    }

    if (enabled) {
        d->suppressor->disable();
    }
    else {
        d->suppressor->enable();
    }

    this->property("kineticScroller").value<QAbstractKineticScroller*>()->setEnabled(!enabled);

    emit textSelectionEnabledChanged();
}

int WebView::progress() const {
    Q_D(const WebView);

    return d->progress;
}

WebView::Status WebView::status() const {
    Q_D(const WebView);

    return d->status;
}

void WebView::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
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
}

void WebViewPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (WebView *view = qobject_cast<WebView*>(list->object)) {
        view->d_func()->dataList.append(obj);
    }
}

void WebViewPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (WebView *view = qobject_cast<WebView*>(list->object)) {
        view->d_func()->actionList.append(obj);

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

QDeclarativeListProperty<QObject> WebViewPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, WebViewPrivate::data_append);
}

QDeclarativeListProperty<QObject> WebViewPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, WebViewPrivate::actions_append);
}

void WebViewPrivate::_q_onLoadStarted() {
    Q_Q(WebView);

    status = WebView::Loading;
    emit q->statusChanged();
}

void WebViewPrivate::_q_onLoadFinished(bool ok) {
    Q_Q(WebView);

    status = ok ? WebView::Finished : WebView::Error;
    emit q->statusChanged();
}

void WebViewPrivate::_q_onLoadProgress(int p) {
    Q_Q(WebView);

    progress = p;
    emit q->progressChanged();
}

#include "moc_webview_p.cpp"
