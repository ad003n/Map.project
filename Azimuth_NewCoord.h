//Azimuth_NewCoord.h
#ifndef AZIMUTH_NEWCOORD_H
#define AZIMUTH_NEWCOORD_H
#include <QGeoCoordinate>

 QGeoCoordinate NewCoordinate(const QGeoCoordinate &coord, double azimuth, double distance);
 double Calculate_azimuth(const QGeoCoordinate &point1, const QGeoCoordinate &point2);

#endif//AZIMUTH_NEWCOORD_H
