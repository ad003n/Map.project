#ifndef COORDINATECONVERTER_H
#define OORDINATECONVERTER_H
#include <QDebug>
#include <QPointF>
#include <QtMath>
#include <QGeoCoordinate>

inline QPointF convertSphericalToCartesian(const QGeoCoordinate &latlong)
{

constexpr double earthRadius = 6378137.0;
    double lat = qDegreesToRadians (latlong.latitude());
    double lon = qDegreesToRadians (latlong.longitude());
//    qDebug()<<"lat______"<<lat;
  //   qDebug()<<"lon______"<<lon;
    double c_x = earthRadius * qCos(lat)*qCos(lon);
    double c_y = earthRadius * qCos(lat)*qSin(lon);
//coordinate.append(QPoint(c_x, c_y));
//
  // return coordinate;
return QPointF(c_x, c_y);
}



inline QGeoCoordinate convertToGeo(const QGeoCoordinate &coord,  double dx, double dy)
{
    constexpr double earthRadius = 6378137.0; // Радиус Земли в метрах

    // Перевод широты и долготы в радианы
    double latRad = qDegreesToRadians(coord.latitude());
// double lonRad = qDegreesToRadians(coord.longitude());
    // Смещение в градусах

    double dLat = ((dy) / earthRadius) * (180.0 / M_PI);

    double dLon = ((dx) / (earthRadius * qCos(latRad))) * (180.0 / M_PI);

//qDebug()<<"                 "<<dLat<<"---"<<dLon;

    return QGeoCoordinate(coord.latitude() + dLat, coord.longitude() + dLon);
}




#endif
