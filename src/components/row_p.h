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

#ifndef ROW_P_H
#define ROW_P_H

#include "item_p.h"

class RowPrivate;

class Row : public Item
{
    Q_OBJECT

    Q_PROPERTY(int spacing READ spacing WRITE setSpacing NOTIFY spacingChanged)

public:
    explicit Row(QWidget *parent = 0);
    ~Row();

    int spacing() const;
    void setSpacing(int spacing);

signals:
    void spacingChanged();

private:
    Row(RowPrivate &dd, QWidget *parent = 0);

    void componentComplete();

    Q_DISABLE_COPY(Row)
    Q_DECLARE_PRIVATE(Row)
};

QML_DECLARE_TYPE(Row)

#endif // ROW_P_H
