#include "maincontroller.h"
#include <QDebug>
#include <cmath>

MainController::MainController(QObject *parent) :QObject(parent){}


QVariantList MainController::getnew_Coordinates() const {
     qDebug() << "getnew_CoordinatesForQML called";
     QVariantList coordList;
     for (const QGeoCoordinate &coord : newCoords) {
        QVariantMap coordMap;
        coordMap["latitude"] = coord.latitude();
        coordMap["longitude"] = coord.longitude();
        coordList.append(coordMap);
     }
    return coordList;
}

void MainController::setnew_Coordinates(const QVector<QGeoCoordinate> &coordinates){
     newCoords=coordinates;
     emit new_CoordinatesChanged();
}

void MainController::processCoordinates(const QGeoCoordinate &startCoord, const QGeoCoordinate &endCoord, double distance) {
     qDebug() << "Calculating intermediate points between" << startCoord << "and" << endCoord << "with distance" << distance;

     newCoords.clear();

     QPointF start = ConvertSphericalToCartesian(startCoord);
     QPointF end = ConvertSphericalToCartesian(endCoord);
     qDebug()<<"start cartesian"<<start;
     qDebug()<<"end cartesian"<<end;
     QVector<QPointF> discretizationPoints = LineDiscretization(start, end, distance);

     if (discretizationPoints.size() <= 2) {
        emit new_CoordinatesChanged();
        return;
     }

     double dx=distance*sin(Calculate_azimuth(startCoord, endCoord));
     double dy=distance*cos(Calculate_azimuth(startCoord, endCoord));
     qDebug()<<"calculate_azimuth(startCoord, endCoord)"<<Calculate_azimuth(startCoord, endCoord);
     QGeoCoordinate currentCoord = startCoord;

     for (int i = 1; i < discretizationPoints.size() ; ++i) {
        double azimuth = Calculate_azimuth(currentCoord, endCoord);

        QGeoCoordinate newCoord = NewCoordinate(currentCoord, azimuth, distance);
        newCoords.append(newCoord);
        currentCoord = newCoord;
        qDebug() << "Intermediate coordinate:" << newCoord;
     }
    emit new_CoordinatesChanged();
}

