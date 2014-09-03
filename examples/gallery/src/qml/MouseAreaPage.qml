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

import org.hildon.components 1.0

Page {
    id: root

    windowTitle: qsTr("MouseArea")

    Column {
        id: column

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            margins: 10
        }

        ValueButton {
            id: selector

            text: qsTr("Drag axis")
            valueText: "XAxis"
            selector: ListSelector {
                model: [ "XAxis", "YAxis", "XandYAxis" ]
                currentIndex: 2
                onSelected: mouseArea.drag.axis = currentValueText
            }
        }
    }

    Label {
        id: label

        y: 100
        width: 200
        height: 40
        color: platformStyle.activeTextColor
        font.bold: true
        font.pixelSize: 32
        text: qsTr("Drag me")
    }

    MouseArea {
        id: mouseArea

        anchors {
            fill: parent
            topMargin: 100
        }
        drag.target: label
        drag.axis: "XAxis"
    }
}
