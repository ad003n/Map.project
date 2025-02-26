import QtQuick 2.0
import QtQuick.Window 2.0
import QtLocation 5.6
import QtPositioning 5.6

import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Rectangle{
    implicitWidth: 200
    implicitHeight: 40
    color:"transparent"
    TextField {
        id: edtText1
        selectByMouse: true
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignVCenter
      //  placeholderText: "write a coordinate."
        font.pointSize: 10
        color: "black"
        background: Rectangle {
            color:"transparent"
        }
    }

}

