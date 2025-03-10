#include"coordinateconvert.h"
#include <QtMath>

 QPointF convertSphericalToCartesian(const QGeoCoordinate &latlong)
{
    constexpr double earthRadius = 6378137.0;
    double lat = qDegreesToRadians (latlong.latitude());
    double lon = qDegreesToRadians (latlong.longitude());
    double cX = earthRadius * qSin(lat)*qCos(lon);
    double cY = earthRadius * qSin(lat)*qSin(lon);
    return QPointF(cX, cY);
}

 QGeoCoordinate convertToGeo(const QGeoCoordinate &coord,  double dx, double dy)
{
    constexpr double earthRadius = 6378137.0;
    double latRad = qDegreesToRadians(coord.latitude());
    double dLat = ((dy) / earthRadius) * (180.0 / M_PI);
    double dLon = ((dx) / (earthRadius * qCos(latRad))) * (180.0 / M_PI);
    return QGeoCoordinate(coord.latitude() + dLat, coord.longitude() + dLon);
}
