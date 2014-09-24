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

#ifndef TABBAR_P_H
#define TABBAR_P_H

#include "anchors_p.h"
#include <QTabBar>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class TabBarPrivate;

class TabButton : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)

public:
    explicit TabButton(QObject *parent = 0);
    ~TabButton();

    QString text() const;
    void setText(const QString &text);

    QString icon() const;
    void setIcon(const QString &icon);

signals:
    void textChanged();
    void iconChanged();

private:
    QString m_text;
    QString m_icon;

    int m_index;

    friend class TabBar;
    friend class TabBarPrivate;

    Q_DISABLE_COPY(TabButton)
};

class TabBar : public QTabBar, public QDeclarativeParserStatus
{
    Q_OBJECT

    Q_PROPERTY(QWidget* parent READ parentWidget WRITE setParent NOTIFY parentChanged)
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(int width READ width WRITE setFixedWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setFixedHeight NOTIFY heightChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PRIVATE_PROPERTY(TabBar::d_func(), Anchors* anchors READ anchors CONSTANT FINAL)
    Q_PROPERTY(AnchorLine left READ left CONSTANT FINAL)
    Q_PROPERTY(AnchorLine right READ right CONSTANT FINAL)
    Q_PROPERTY(AnchorLine top READ top CONSTANT FINAL)
    Q_PROPERTY(AnchorLine bottom READ bottom CONSTANT FINAL)
    Q_PROPERTY(AnchorLine horizontalCenter READ horizontalCenter CONSTANT FINAL)
    Q_PROPERTY(AnchorLine verticalCenter READ verticalCenter CONSTANT FINAL)
    Q_PRIVATE_PROPERTY(TabBar::d_func(), QDeclarativeListProperty<QObject> data READ data)
    Q_PRIVATE_PROPERTY(TabBar::d_func(), QDeclarativeListProperty<QWidget> children READ children)
    Q_PRIVATE_PROPERTY(TabBar::d_func(), QDeclarativeListProperty<QObject> actions READ actions)
    Q_PRIVATE_PROPERTY(TabBar::d_func(), bool visible READ qmlVisible WRITE setQmlVisible NOTIFY visibleChanged)
    Q_PRIVATE_PROPERTY(TabBar::d_func(), bool focus READ hasFocus WRITE setFocus NOTIFY focusChanged)
    Q_PRIVATE_PROPERTY(TabBar::d_func(), Style* style READ style WRITE setStyle RESET resetStyle)

    Q_INTERFACES(QDeclarativeParserStatus)

    Q_CLASSINFO("DefaultProperty", "data")

public:
    explicit TabBar(QWidget *parent = 0);
    ~TabBar();

    void setX(int x);
    void setY(int y);

    qreal opacity() const;
    void setOpacity(qreal opacity);

    AnchorLine left() const;
    AnchorLine right() const;
    AnchorLine top() const;
    AnchorLine bottom() const;
    AnchorLine horizontalCenter() const;
    AnchorLine verticalCenter() const;

signals:
    void parentChanged();
    void xChanged();
    void yChanged();
    void widthChanged();
    void heightChanged();
    void opacityChanged();
    void visibleChanged();
    void enabledChanged();
    void focusChanged();

protected:
    TabBar(TabBarPrivate &dd, QWidget *parent = 0);

    virtual void changeEvent(QEvent *event);
    virtual void moveEvent(QMoveEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event);
    virtual void focusInEvent(QFocusEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);

    virtual void classBegin();
    virtual void componentComplete();

    QScopedPointer<TabBarPrivate> d_ptr;

    Q_DECLARE_PRIVATE(TabBar)
    
    Q_PRIVATE_SLOT(d_func(), void _q_onStyleChanged())

private:
    Q_DISABLE_COPY(TabBar)
};

QML_DECLARE_TYPE(TabButton)
QML_DECLARE_TYPE(TabBar)

#endif // TabBar_P_H
