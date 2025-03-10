#include"CoordinateConvert.h"
#include <QtMath>

 QPointF ConvertSphericalToCartesian(const QGeoCoordinate &latlong)
{
    constexpr double earthRadius = 6378137.0;
    double lat = qDegreesToRadians (latlong.latitude());
    double lon = qDegreesToRadians (latlong.longitude());
    double c_x = earthRadius * qSin(lat)*qCos(lon);
    double c_y = earthRadius * qSin(lat)*qSin(lon);
    return QPointF(c_x, c_y);
}

 QGeoCoordinate ConvertToGeo(const QGeoCoordinate &coord,  double dx, double dy)
{
    constexpr double earthRadius = 6378137.0;
    double latRad = qDegreesToRadians(coord.latitude());
    double dLat = ((dy) / earthRadius) * (180.0 / M_PI);
    double dLon = ((dx) / (earthRadius * qCos(latRad))) * (180.0 / M_PI);
    return QGeoCoordinate(coord.latitude() + dLat, coord.longitude() + dLon);
}
