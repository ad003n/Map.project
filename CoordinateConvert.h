
#include <QDebug>
#include <QPointF>
#include <QtMath>
#include <QGeoCoordinate>

QPointF convertSphericalToCartesian(const QGeoCoordinate &latlong)
{

constexpr double earthRadius = 6378137.0;
    double lat = qDegreesToRadians (latlong.latitude());
    double lon = qDegreesToRadians (latlong.longitude());
    double c_x = earthRadius * qCos(lat)*qCos(lon);
    double c_y = earthRadius * qCos(lat)*qSin(lon);
//coordinate.append(QPoint(c_x, c_y));
//
  // return coordinate;
return QPointF(c_x, c_y);
}




QGeoCoordinate convertToGeo(const QGeoCoordinate &coord,  double dx, double dy)
{
    constexpr double earthRadius = 6378137.0; // Радиус Земли в метрах

    // Перевод широты и долготы в радианы
    double latRad = qDegreesToRadians(coord.latitude());
    double lonRad = qDegreesToRadians(coord.longitude());

    // Смещение в градусах
    double dLat = (dy / earthRadius) * (180.0 / M_PI);
    double dLon = (dx / (earthRadius * qCos(latRad))) * (180.0 / M_PI);

    return QGeoCoordinate(coord.latitude() + dLat, coord.longitude() + dLon);
}




