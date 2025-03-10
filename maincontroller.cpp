#include "maincontroller.h"
#include <QDebug>
#include <cmath>

MainController::MainController(QObject *parent) :QObject(parent){}


QVariantList MainController::getNewCoordinates() const {
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

void MainController::setNewCoordinates(const QVector<QGeoCoordinate> &coordinates){
     newCoords=coordinates;
     emit newCoordinatesChanged();
}

void MainController::processCoordinates(const QGeoCoordinate &startCoord, const QGeoCoordinate &endCoord, double distance) {
     qDebug() << "Calculating intermediate points between" << startCoord << "and" << endCoord << "with distance" << distance;

     newCoords.clear();

     QPointF start = convertSphericalToCartesian(startCoord);
     QPointF end = convertSphericalToCartesian(endCoord);
     qDebug()<<"start cartesian"<<start;
     qDebug()<<"end cartesian"<<end;
     QVector<QPointF> discretizationPoints = lineDiscretization(start, end, distance);

     if (discretizationPoints.size() <= 2) {
        emit newCoordinatesChanged();
        return;
     }

     double dx=distance*sin(calculateAzimuth(startCoord, endCoord));
     double dy=distance*cos(calculateAzimuth(startCoord, endCoord));
     qDebug()<<"calculate azimuth(startCoord, endCoord)"<<calculateAzimuth(startCoord, endCoord);
     QGeoCoordinate currentCoord = startCoord;

     for (int i = 1; i < discretizationPoints.size() ; ++i) {
        double azimuth = calculateAzimuth(currentCoord, endCoord);

        QGeoCoordinate newCoord = newCoordinate(currentCoord, azimuth, distance);
        newCoords.append(newCoord);
        currentCoord = newCoord;
        qDebug() << "Intermediate coordinate:" << newCoord;
     }
    emit newCoordinatesChanged();
}

