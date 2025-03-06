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
        anchors.bottomMargin: 15

        Rectangle {
            implicitWidth: 200
            implicitHeight: 30
            color: "transparent"
            TextField {
                id: lanInput
                selectByMouse: true
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                placeholderText: "Введите широту"
                font.pointSize: 10
                color: "black"
                background: Rectangle {
                    color: "#80c0c0c0"
                }
            }
        }

        Rectangle {
            implicitWidth: 200
            implicitHeight: 30
            color: "transparent"
            TextField {
                id: lonInput
                selectByMouse: true
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                placeholderText: "Введите долготу"
                font.pointSize: 10
                color: "black"
                background: Rectangle {
                    color: "#80c0c0c0"
                }
            }
        }

        Button {
            id: btnAddItem
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Добавить маркер"
            background: Rectangle {
                color: "#80ffc0cb"
                radius: 5
            }

            onClicked: {
                var latitude = parseFloat(lanInput.text);
                var longitude = parseFloat(lonInput.text);

                //check
                var isValidLatitude = (latitude >= -90 && latitude <= 90);
                var isValidLongitude = (longitude >= -180 && longitude <= 180);

                if (isValidLatitude && isValidLongitude && markersModel.count < 2) {
                    var markerLabel = markersModel.count === 0 ? "A" : "B";
                    console.log("Adding marker: latitude=" + latitude + ", longitude=" + longitude + ", label=" + markerLabel);
                    markersModel.append({ "latitude": latitude, "longitude": longitude, "markerLabel": markerLabel });
                    coord.push(QtPositioning.coordinate(latitude, longitude));

                    var polylineComponent = Qt.createComponent("qrc:/CustomPolyline.qml");
                    if (polylineComponent.status === Component.Ready) {
                        var polyline = polylineComponent.createObject(mapll, {
                            path: coord
                        });
                        mapll.addMapItem(polyline);
                    }


                    mapll.center = QtPositioning.coordinate(latitude, longitude);
                } else if (markersModel.count >= 2) {
                    console.log("Only two markers can be added.");
                } else {
                    console.log("Error: Invalid coordinates.");
                }
                lanInput.clear();
                lonInput.clear();
            }
        }

        Rectangle {
            implicitWidth: 200
            implicitHeight: 30
            color: "transparent"
            TextField {
                id: stepsInput
                selectByMouse: true
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                placeholderText: "введите длину шага"
                font.pointSize: 10
                color: "black"
                background: Rectangle {
                    color: "#80c0c0c0"
                }
                enabled: markersModel.count >= 2
            }
        }

        Button {
            id: stepsBtn
            anchors.horizontalCenter: parent.horizontalCenter
            text: "принять"
            background: Rectangle {
                color: "#80ffc0cb"
                radius: 5
            }

            onClicked: function() {
                var stepValue = parseFloat(stepsInput.text);
                if (!isNaN(stepValue) && stepValue > 0) {
                    console.log("Step value: " + stepValue);
                    if (markersModel.count === 2) {
                        var startCoord = QtPositioning.coordinate(markersModel.get(0).latitude, markersModel.get(0).longitude);
                        var endCoord = QtPositioning.coordinate(markersModel.get(1).latitude, markersModel.get(1).longitude);

                        console.log("Starting calculation with coordinates:", startCoord, endCoord);

                        // mainController
                        mainController.prCoordinates(startCoord, endCoord, stepValue);

                        // new coordinates from mainController
                        var coordinates = mainController.NCoordinatesFor;
                      //  console.log("***", coordinates);

                        if (coordinates && coordinates.length > 0) {

                            //  markersModel new coord
                            for (var i = 0; i < coordinates.length; ++i) {
                                markersModel.append({
                                    "latitude": coordinates[i].latitude,
                                    "longitude": coordinates[i].longitude,
                                    "markerLabel": " " //+ (markersModel.count + 1)
                                });
                                console.log("Added marker:", coordinates[i].latitude, coordinates[i].longitude);
                            }
                        } else {
                            console.log("No coordinates returned from mainController.");
                        }
                    } else {
                        console.log("Error: Two markers are required to calculate points.");
                    }
                } else {
                    console.log("Error: Invalid step value.");
                }
                stepsInput.clear();
            }
            ///
        }
        ////

    }

    ListModel {
        id: markersModel
    }
}
