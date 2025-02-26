/*import QtQuick 2.0
import QtQuick.Window 2.0
import QtLocation 5.6
import QtPositioning 5.6
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

// editor component

Item {
    id: inputCoord
    signal CoordAdd (double latitude, double longitude)
    property alias LatInput: lat
    property alias LongInput: lon
    width: 200
    height: 100
Column{
    TextInput{
        id:lat
        width: parent.width
        placeholderText: labelText+"***"
    }
    TextInput{
        id:lon
        width: parent.width
        placeholderText: labelText+"***"
    }
    Button{
        width: parent.width
        text: "ok"+ labelText
        onClicked: {
            let latitude parseFloat(lat.text);
           let longitude parseFloat(lon.text);
            if(!isNan(latitude) && !isNan (longitude)){
                inputCoord.coorAdd(latitude, longitude);
            }
            else {
                console.log ("error")
                lat.text=" ";
                lon.text=" ";
            }
        }
    }
}
}




/*
Rectangle {
    id: root
    color: mapll.panelColor
    height: 60

    property alias textColor: edtText.color
    signal newMessage(string msg)

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10

        TextField {
            id: edtText
            selectByMouse: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
            placeholderText: "Write a message..."
            font.pointSize: 10
            color: "black"
            background: Rectangle {
                color: root.color
            }
        }

        Button {
            id: btnAddItem
            Layout.alignment: Qt.AlignVCenter
            text: "+"

            onClicked: {
                newMessage(edtText.text);
                edtText.clear();
            }
        }
    }
}
*/
