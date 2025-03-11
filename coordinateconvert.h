#ifndef COORDINATECONVERTER_H
#define OORDINATECONVERTER_H

#include <QPointF>
#include <QGeoCoordinate>
double vincentyDistance(const QGeoCoordinate& coord1, const QGeoCoordinate& coord2);
QPointF geoToCartesian(const QGeoCoordinate& geo, const QGeoCoordinate& origin);
static QGeoCoordinate cartesianToGeo(const QPointF& cart, const QGeoCoordinate& origin);
//
#endif
