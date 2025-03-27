

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
    property int draggedMarkerIndex: -1
    property bool isDraggingMarker: false
    property var polyline: null
    property var polyline2: null

    property int draggedGrayMarkerIndex: -1
    property bool isDraggingGrayMarker: false
    property ListModel grayMarkersModel: ListModel {}
    property bool showGrayMarkers: false

    Map {
        id: mapll
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(59.91, 10.75)
        zoomLevel: 14

        MapItemView {
            model: grayMarkersModel
            delegate: MapQuickItem {
                coordinate: QtPositioning.coordinate(model.latitude, model.longitude)
                anchorPoint.x: grayCircle.width / 2
                anchorPoint.y: grayCircle.height / 2
                visible: showGrayMarkers
                sourceItem: Rectangle {
                    id: grayCircle
                    width: 10
                    height: 10
                    radius: width / 2
                    color: "#80800000"
                    border.color: "#80680000"
                    border.width: 2
                }
            }
        }
        MapItemView {
            model: markersModel

            delegate: MapQuickItem {
                coordinate: QtPositioning.coordinate(model.latitude, model.longitude)
                anchorPoint.x: circle.width / 2
                anchorPoint.y: circle.height / 2
                sourceItem: Rectangle {
                    id: circle
                    width: model.markerSize || 20
                    height: model.markerSize || 20
                    radius: width / 2
                    color: model.markerColor || "red"
                    Drag.active: dragArea.drag.active
                    Text {
                        anchors.centerIn: parent
                        text: model.markerLabel || ""
                    }
                    border.color: model.borderColor || "darkred"
                    border.width: 2

                }
            }
        }
    }

    function createPolyline(path, color) {
        var polylineComponent = Qt.createComponent("qrc:/CustomPolyline.qml");
        if (polylineComponent.status === Component.Ready) {
            var polyline = polylineComponent.createObject(mapll, {
                path: path,
            });
            mapll.addMapItem(polyline);
            return polyline;
        }
        return null;
    }

    function updatePolylines() {
        if (polyline) {
            polyline.destroy();
            polyline = null;
        }
        if (polyline2) {
            polyline2.destroy();
            polyline2 = null;
        }

        var path = [];
        for (var i = 0; i < markersModel.count; i++) {
            var marker = markersModel.get(i);
            path.push(QtPositioning.coordinate(marker.latitude, marker.longitude));
        }

        if (showGrayMarkers) {
            polyline2 = createPolyline(path);
        } else if (markersModel.count === 2) {
            polyline = createPolyline(path);
        }
    }

    function updateGrayMarkers() {
        grayMarkersModel.clear();
        for (var i = 0; i < markersModel.count - 1; i++) {
            var first = markersModel.get(i);
            var second = markersModel.get(i + 1);
            grayMarkersModel.append({
                "latitude": (first.latitude + second.latitude) / 2,
                "longitude": (first.longitude + second.longitude) / 2
            });
        }
    }

    function restart(){
          markersModel.clear();
          grayMarkersModel.clear();
          showGrayMarkers = false;

           //  mapll.center = QtPositioning.coordinate(59.91, 10.75);
           //  mapll.zoomLevel = 14;

             updatePolylines();
             updateGrayMarkers();

             lanInput.clear();
             lonInput.clear();
             stepsInput.clear();
      }

    MouseArea {
        id: dragArea
        anchors.fill: parent
        propagateComposedEvents: true

        onPressed: {
            var markerIndex = -1;
            var grayMarkerIndex = -1;

            if (showGrayMarkers) {
                for (var j = 0; j < grayMarkersModel.count; j++) {
                    var grayMarkerCoord = grayMarkersModel.get(j);
                    var grayMarkerPos = mapll.fromCoordinate(QtPositioning.coordinate(
                        grayMarkerCoord.latitude, grayMarkerCoord.longitude));
                    if (Math.abs(mouse.x - grayMarkerPos.x) <= 5 && Math.abs(mouse.y - grayMarkerPos.y) <= 5) {
                        grayMarkerIndex = j;
                        break;
                    }
                }

                if (grayMarkerIndex !== -1) {
                    draggedGrayMarkerIndex = grayMarkerIndex;
                    isDraggingGrayMarker = true;

                    var grayLat = grayMarkersModel.get(grayMarkerIndex).latitude;
                    var grayLon = grayMarkersModel.get(grayMarkerIndex).longitude;

                    grayMarkersModel.remove(grayMarkerIndex);
                    var insertIndex = grayMarkerIndex + 1;
                    markersModel.insert(insertIndex, {
                        "latitude": grayLat,
                        "longitude": grayLon,
                        "markerLabel": " ",
                        "markerColor": "#80990000",
                        "borderColor": "#80880000",
                        "markerSize": 15
                    });

                    draggedMarkerIndex = insertIndex;
                    isDraggingMarker = true;
                    isDraggingGrayMarker = false;

                    updateGrayMarkers();
                    updatePolylines();
                    return;
                }
            }

            for (var i = 0; i < markersModel.count; i++) {
                var markerCoord = markersModel.get(i);
                var markerPos = mapll.fromCoordinate(QtPositioning.coordinate(
                    markerCoord.latitude, markerCoord.longitude));
                if (Math.abs(mouse.x - markerPos.x) <= 10 && Math.abs(mouse.y - markerPos.y) <= 10) {
                    markerIndex = i;
                    break;
                }
            }

            if (markerIndex !== -1) {
                draggedMarkerIndex = markerIndex;
                isDraggingMarker = true;

                markersModel.setProperty(markerIndex, "markerColor", "#80FF0000");
                markersModel.setProperty(markerIndex, "borderColor", "#C0FF0000");
            } else {
                mouse.accepted = false;
            }
        }

        onPositionChanged: {
            if (isDraggingMarker && draggedMarkerIndex !== -1) {
                var newCoord = mapll.toCoordinate(Qt.point(mouse.x, mouse.y));
                markersModel.setProperty(draggedMarkerIndex, "latitude", newCoord.latitude);
                markersModel.setProperty(draggedMarkerIndex, "longitude", newCoord.longitude);
                updatePolylines();
                if (showGrayMarkers) updateGrayMarkers();
            } else {
                mouse.accepted = false;
            }
        }

        onReleased: {
            if (isDraggingMarker && draggedMarkerIndex !== -1) {
                if (markersModel.get(draggedMarkerIndex).markerColor === "#80990000") {
                    markersModel.setProperty(draggedMarkerIndex, "markerColor", "red");
                    markersModel.setProperty(draggedMarkerIndex, "borderColor", "darkred");
                    markersModel.setProperty(draggedMarkerIndex, "markerSize", 20);
                } else {
                    markersModel.setProperty(draggedMarkerIndex, "markerColor", "red");
                    markersModel.setProperty(draggedMarkerIndex, "borderColor", "darkred");
                }

                draggedMarkerIndex = -1;
                isDraggingMarker = false;
            }
            if (isDraggingGrayMarker && draggedGrayMarkerIndex !== -1) {
                draggedGrayMarkerIndex = -1;
                isDraggingGrayMarker = false;
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
                color:black
                background:
                    Rectangle {
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
                background:
                    Rectangle {
                    color: "#80c0c0c0"
                }
            }
        }

        Button {
            id: btnAddItem
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Добавить маркер"
            background:
                Rectangle {
                color:btnAddItem.hovered ? "#c0ffc0cb" : "#80ffc0cb"// "#80ffc0cb";
                radius: 5 }
            onClicked: {
                var latitude = parseFloat(lanInput.text);
                var longitude = parseFloat(lonInput.text);

                if (latitude >= -90 && latitude <= 90 &&
                        longitude >= -180 && longitude <= 180 &&markersModel.count < 2) {

                    var markerLabel = markersModel.count === 0 ? "A" : "B";
                    console.log("Adding marker: latitude="+ latitude+", longitude=" +longitude+", label="+markerLabel);
                    markersModel.append({
                        "latitude": latitude,
                        "longitude": longitude,
                        "markerLabel": markerLabel,
                        "markerColor": "red",
                        "borderColor": "darkred",
                        "markerSize": 20
                    });

                    mapll.center = QtPositioning.coordinate(latitude, longitude);

                    if (markersModel.count === 2) {
                        updatePolylines();
                    }
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
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                placeholderText: "введите длину шага"
                font.pointSize: 10
                color: black
                background:
                    Rectangle {
                    color: "#80c0c0c0"
                }
                enabled: markersModel.count >= 2
            }
        }

        Button {
            id: stepsBtn
            anchors.horizontalCenter: parent.horizontalCenter
            text: "принять"
            background:
                Rectangle {
                //color: "#80ffc0cb";
                  color:stepsBtn.hovered ? "#c0ffc0cb" : "#80ffc0cb"
                radius: 5 }
            onClicked: function() {
                var stepValue = parseFloat(stepsInput.text);
                if (!isNaN(stepValue) && stepValue > 0){
                    console.log("Step value: "+stepValue)
                }

                if ( markersModel.count === 2) {

                    var startCoord = QtPositioning.coordinate(markersModel.get(0).latitude, markersModel.get(0).longitude);
                    var endCoord = QtPositioning.coordinate(markersModel.get(1).latitude, markersModel.get(1).longitude);
                    console.log("Starting calculation with coordinates:", startCoord,endCoord);

                    mainController.processCoordinates(startCoord, endCoord, stepValue);
                    var coordinates = mainController.NewCoordinatesFor;

                    if (coordinates && coordinates.length > 0) {
                        var markerBLat = markersModel.get(1).latitude;
                        var markerBLon = markersModel.get(1).longitude;

                        markersModel.remove(1);

                        for (var i = 0; i < coordinates.length; i++) {
                            markersModel.append({
                                "latitude": coordinates[i].latitude,
                                "longitude": coordinates[i].longitude,
                                "markerLabel": " ",
                                "markerColor": "red",
                                "borderColor": "darkred",
                                "markerSize": 20
                            });
                        }

                        markersModel.append({
                            "latitude": markerBLat,
                            "longitude": markerBLon,
                            "markerLabel": "B",
                            "markerColor": "red",
                            "borderColor": "darkred",
                            "markerSize": 20
                        });

                        showGrayMarkers = true;
                        updatePolylines();
                        updateGrayMarkers();
                    }

                    else {
                                    console.log("No intermediate coordinates received");
                                }
                            } else {
                                console.log("Need exactly 2 markers to process, current count: " + markersModel.count);
                            }

                stepsInput.clear();
            }
        }
        Button
               {
                   id:btnRestart
                   text: "restart"
                   background:
                       Rectangle {
                       //color: "#a0b4bbff";
                       color:btnRestart.hovered ? "#d0b4bbff" : "#a0b4bbff"
                       radius: 5 }
                   anchors.horizontalCenter: parent.horizontalCenter
                   onClicked: {restart();}
               }
    }

    ListModel {
        id: markersModel
    }

    Component.onCompleted: {
        updateGrayMarkers();
    }
}
