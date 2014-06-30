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

#ifndef BUTTONROW_P_P_H
#define BUTTONROW_P_P_H

#include "item_p_p.h"
#include "buttonrow_p.h"
#include <QButtonGroup>

class ButtonRowPrivate : public ItemPrivate
{

public:
    ButtonRowPrivate(ButtonRow *parent) :
        ItemPrivate(parent),
        group(0)
    {}

    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    static void children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget);

    QDeclarativeListProperty<QObject> data();

    QDeclarativeListProperty<QWidget> children();

    void updateStyleSheets();

    void componentComplete();

    QButtonGroup *group;

    Q_DECLARE_PUBLIC(ButtonRow)
};

#endif // BUTTONROW_P_P_H
