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

#ifndef TEXT_P_P_H
#define TEXT_P_P_H

#include "item_p_p.h"
#include "text_p.h"
#include "platformstyle_p.h"

class TextPrivate : public ItemPrivate
{

public:
    TextPrivate(Text *parent) :
        ItemPrivate(parent),
        color(PlatformStyle::defaultTextColor())
    {
    }

    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    static void actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    QDeclarativeListProperty<QObject> data();

    QDeclarativeListProperty<QObject> actions();

    QString text;

    QColor color;

    Q_DECLARE_PUBLIC(Text)
};

#endif // TEXT_P_P_H
