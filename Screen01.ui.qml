import QtQuick
import QtQuick.Controls
import QTBettingApp 1.0
import QtQuick3D 6.2
import FlowView 1.0
import QtCore 6.2

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.height
    color: "#616161"

    border.color: "#787777"

    Frame {
        id: frame
        y: 104
        width: 532
        height: 277
        opacity: 1
        focusPolicy: Qt.NoFocus
        transformOrigin: Item.Center
        font.family: "Verdana"
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        clip: false
        font.bold: false

        Label {
            id: label
            x: 144
            y: 0
            text: qsTr("Obstawianie zakładów")
            font.pointSize: 15
            font.family: "Verdana"
        }

        Button {
            id: button
            x: 215
            y: 204
            text: qsTr("Obstaw")
            font.bold: false
            highlighted: false
            flat: false
        }

        TextField {
            id: numberField
            x: 195
            y: 59
            horizontalAlignment: Text.AlignHCenter
            placeholderText: qsTr("Podaj kwotę")
        }
    }
}
