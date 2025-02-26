

import QtQuick 2.0
import QtQuick.Window 2.0
import QtLocation 5.6
import QtPositioning 5.6
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Window {
    width: 512
    height: 512
    visible: true

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    property var coord: []
    Map {
        id: mapll
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(59.91, 10.75) // Oslo
        zoomLevel: 14

        MapItemView {
            id: mapItemView
            model: markersModel


            delegate: MapQuickItem {
                coordinate: QtPositioning.coordinate(model.latitude, model.longitude)
                anchorPoint.x: circle.width / 2
                anchorPoint.y: circle.height / 2
                sourceItem: Rectangle {
                    id: circle
                    width: 20
                    height: 20
                    radius: width / 2 // Makes it a circle
                    color: "red"
                    Text {
                        id: textMarker
                        anchors.centerIn: parent
                        text: model.markerLabel // marker
                    }
                    border.color: "darkred"
                    border.width: 2
                }
            }
        }
    }

    ColumnLayout {
        id: loColumn
        anchors.bottom: parent.bottom
        anchors.right: parent.right
      //anchors.top: parent.verticalCenter

       // anchors.margins: 10
        anchors.bottomMargin: 15
       // anchors.verticalCenter: parent.verticalCenter

        Rectangle {
            implicitWidth: 200
            implicitHeight: 30
            color: "transparent"
            TextField {
                id: lanInput
                selectByMouse: true

                        anchors.verticalCenter: parent.verticalCenter //
                        anchors.horizontalCenter: parent.horizontalCenter //


                placeholderText: "Введите широту."
                font.pointSize: 10
                color: "black"
                background: Rectangle {
                    color: "#80c0c0c0"//"transparent"//'#800000FF'
                }

            }
        }

        Rectangle {
            implicitWidth: 200
            implicitHeight: 30
            color:"transparent"
            TextField {
                id: lonInput
                selectByMouse: true
                anchors.verticalCenter: parent.verticalCenter //
                anchors.horizontalCenter: parent.horizontalCenter //
                placeholderText: "Введите долготу."
                font.pointSize: 10
                color: "black"
                background: Rectangle {
                    color: "#80c0c0c0"

                }
            }
        }

        Button {
            id: btnAddItem

            anchors.horizontalCenter: parent.horizontalCenter //
            text: "Добавить маркер"
            background: Rectangle {
                color: "#80ffc0cb"
                radius: 5
            }

            onClicked: {
                var latitude = parseFloat(lanInput.text);
                var longitude = parseFloat(lonInput.text);


                // check
                var isValidLatitude = (latitude >= -90 && latitude <= 90);
                var isValidLongitude = (longitude >= -180 && longitude <= 180);

                if (isValidLatitude && isValidLongitude && markersModel.count < 2) {//if 2
                    var markerLabel = markersModel.count === 0 ? "A" : "B";
                    console.log("Добавление маркера: широта=" + latitude + ", долгота=" + longitude + ", метка=" + markerLabel);
                    markersModel.append({ "latitude": latitude, "longitude": longitude, "markerLabel": markerLabel });
                    //
                 //
                    coord.push(QtPositioning.coordinate(latitude,longitude));
                    var polylineComponent = Qt.createComponent("qrc:/CustomPolyline.qml");
                        if (polylineComponent.status === Component.Ready) {
                            console.log("!!!!!")
                            var polyline = polylineComponent.createObject(mapll, {
                                path: coord
                            });
                        }
                        mapll.addMapItem(polyline);


                    //
                    lanInput.placeholderText= "Введите широту."
                     lonInput.placeholderText= "Введите долготу"
                    lanInput.color="black"
                    lonInput.color="black"
                    // centr coord
                    mapll.center = QtPositioning.coordinate(latitude, longitude);

                }
 //   else if (markersModel.count == 2){lineab.visible=true}
                else if (markersModel.count >= 2) {
                    console.log("Можно добавить только два маркера.");
                    lanInput.placeholderText= "только два маркера"
                     lonInput.placeholderText= " только два маркера"
                    lanInput.color="red"
                    lonInput.color="red"
                 //   lanInput.clear();
                 //   lonInput.clear();
                } else {
                    console.log("Ошибка: неправильные координаты");
                   lanInput.placeholderText= "неправильные координаты"
                    lonInput.placeholderText= "неправильные координаты"
                    lanInput.color="red"
                    lonInput.color="red"
                   // lanInput.clear();
                    //lonInput.clear();
                }
              lanInput.clear();
               lonInput.clear();
            }
        }
    }

    ListModel {
        id: markersModel
    }

}
