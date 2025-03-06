#include "maincontroller.h"


MainController::MainController(QObject *parent) :QObject(parent){}

//QVector<QGeoCoordinate>MainController ::getNCoordinates()
//const{return newCoords;}



QVariantList MainController::getNCoordinates() const {
     qDebug() << "getNCoordinatesForQML called";
    QVariantList coordList;
    for (const QGeoCoordinate &coord : newCoords) {
        QVariantMap coordMap;
        coordMap["latitude"] = coord.latitude();
        coordMap["longitude"] = coord.longitude();
        coordList.append(coordMap);
    }
   // qDebug() << "Returning coordinates:" << coordList;
    return coordList;
}




void MainController::setNCoordinates(const QVector<QGeoCoordinate> &coordinates){
    qDebug()<<"--------";
    newCoords=coordinates;

    emit NCoordinatesChanged();
    qDebug()<<"newCoord (setNcoord)"<<newCoords;
}

void MainController::prCoordinates(const QGeoCoordinate &startCoord, const QGeoCoordinate &endCoord, double distance) {
    qDebug() << "Calculating intermediate points between" << startCoord << "and" << endCoord << "with distance" << distance;

    newCoords.clear();

    QPointF start = convertSphericalToCartesian(startCoord);
    QPointF end = convertSphericalToCartesian(endCoord);
qDebug()<<"start cartesian"<<start;
qDebug()<<"end cartesian"<<end;
    QVector<QPointF> discretizationPoints = lineDiscretization(start, end, distance);

    if (discretizationPoints.size() <= 2) {
        emit NCoordinatesChanged();
        return;
    }

 //   double dx = discretizationPoints[1].x() - discretizationPoints[0].x();
  //  double dy = discretizationPoints[1].y() - discretizationPoints[0].y();

   double dx=distance*sin(calculate_azimuth(startCoord, endCoord));
    double dy=distance*cos(calculate_azimuth(startCoord, endCoord));
    qDebug()<<"calculate_azimuth(startCoord, endCoord)______________"<<calculate_azimuth(startCoord, endCoord);
    QGeoCoordinate currentCoord = startCoord;
    for (int i = 1; i < discretizationPoints.size() ; ++i) {
        double azimuth = calculate_azimuth(currentCoord, endCoord); // Используйте endCoord для расчета
        qDebug()<<"calculate_azimuth______________"<<azimuth;

        QGeoCoordinate newCoord = NewCoordinate(currentCoord, azimuth, distance);
        newCoords.append(newCoord);
        currentCoord = newCoord;
         qDebug() << "Intermediate coordinate:" << newCoord;
    }
    /*for (int i = 1; i < discretizationPoints.size() - 1; ++i) {
        QGeoCoordinate newCoord = convertToGeo(currentCoord, dx, dy);

        double azimuth = calculate_azimuth(currentCoord, newCoord);
       qDebug()<<"calculate_azimuth______________"<<azimuth;


    newCoord = NewCoordinate(currentCoord, static_cast<double>(azimuth), distance);

        newCoords.append(newCoord);
        currentCoord = newCoord;

    //    qDebug() << "----:" << newCoord;
    }*/

    emit NCoordinatesChanged();
   // qDebug() << "---------" << newCoords.size() << "coordinates";
}

///////////

