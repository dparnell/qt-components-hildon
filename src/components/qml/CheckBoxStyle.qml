/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 1.0

/*!
    \class CheckBoxStyle
    \brief Provides styling properties for CheckBox.
    
    \ingroup components
    
    The CheckBoxStyle component can be used to provide custom styling for a CheckBox.
    
    \sa CheckBox
*/
ButtonStyle {
    backgroundChecked: background
    iconWidth: 38
    iconHeight: 38
    paddingLeft: platformStyle.paddingLarge
}
