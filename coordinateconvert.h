#ifndef COORDINATECONVERTER_H
#define OORDINATECONVERTER_H

#include <QPointF>
#include <QGeoCoordinate>

QPointF convertSphericalToCartesian(const QGeoCoordinate &latlong);
 QGeoCoordinate convertToGeo(const QGeoCoordinate &coord,  double dx, double dy);
#endif
