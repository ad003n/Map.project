#include "azimuthnewcoord.h"
#include <QtMath>

QGeoCoordinate newCoordinate(const QGeoCoordinate &coord, double azimuth, double distance)
{
    constexpr double earthRadius = 6378137.0;
    double lat0 =coord.latitude();
    double lon0 = coord.longitude();
    double azimuthRad= qDegreesToRadians(azimuth);
    double radlat0= qDegreesToRadians((lat0));
    double radlon0= qDegreesToRadians((lon0));
    double dR= distance/earthRadius;

    double newLat = asin(sin(radlat0) * cos(dR) + cos(radlat0) * sin(dR) * cos(azimuthRad));
    double newLon=radlon0+atan2(sin(azimuthRad)*sin(dR)*cos(radlat0), cos(dR)-sin(radlat0)*sin(newLat));

    newLat = qRadiansToDegrees(newLat);
    newLon=qRadiansToDegrees(newLon);
    return QGeoCoordinate(newLat, newLon);
}

double calculateAzimuth(const QGeoCoordinate &point1, const QGeoCoordinate &point2)
{

    double lat1=point1.latitude();
    double lon1=point1.longitude();
    double lat2=point2.latitude();
    double lon2=point2.longitude();


   double lat1Rad = qDegreesToRadians(lat1);
   double lon1Rad = qDegreesToRadians(lon1);
   double lat2Rad = qDegreesToRadians(lat2);
   double lon2Rad = qDegreesToRadians(lon2);

    double dlon = lon2Rad - lon1Rad;
    double aX = sin(dlon)*cos(lat2Rad);
    double aY= cos(lat1Rad)*sin(lat2Rad)-(sin(lat1Rad)*cos(lat2Rad)*cos(dlon));
    double azimuth = atan2(aX, aY);

    azimuth= qRadiansToDegrees(azimuth);
    azimuth = fmod((azimuth+360), 360);
    return azimuth;
}

