#ifndef COORDINATECONVERTER_H
#define OORDINATECONVERTER_H

#include <QPointF>
#include <QGeoCoordinate>

QPointF ConvertSphericalToCartesian(const QGeoCoordinate &latlong);
 QGeoCoordinate ConvertToGeo(const QGeoCoordinate &coord,  double dx, double dy);
#endif
