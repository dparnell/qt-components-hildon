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

#ifndef TIMESELECTOR_P_H
#define TIMESELECTOR_P_H

#include "valueselector_p.h"
#include <QTime>

class TimeSelector : public ValueSelector
{
    Q_OBJECT

    Q_PROPERTY(int minuteStep READ minuteStep WRITE setMinuteStep)
    Q_PROPERTY(QTime currentTime READ currentTime WRITE setCurrentTime)
    Q_PROPERTY(QString currentValueText READ currentValueText NOTIFY selected)

public:
    explicit TimeSelector(QObject *parent = 0);
    ~TimeSelector();

    QTime currentTime() const;
    void setCurrentTime(const QTime &Time);

    int minuteStep() const;
    void setMinuteStep(int step);

    QString currentValueText() const;

signals:
    void selected(const QString &text);

private:
    Q_DISABLE_COPY(TimeSelector)
};

QML_DECLARE_TYPE(TimeSelector)

#endif // TIMESELECTOR_P_H
