#include "azimuthnewcoord.h"
#include <QtMath>

QGeoCoordinate NewCoordinate(const QGeoCoordinate &coord, double azimuth, double distance)
{
    constexpr double earthRadius = 6378137.0;
    double lat0 =coord.latitude();
    double lon0 = coord.longitude();
    double azimuth_rad= qDegreesToRadians(azimuth);
    double radlat0= qDegreesToRadians((lat0));
    double radlon0= qDegreesToRadians((lon0));
    double dR= distance/earthRadius;

    double new_lat = asin(sin(radlat0) * cos(dR) + cos(radlat0) * sin(dR) * cos(azimuth_rad));
    double new_lon=radlon0+atan2(sin(azimuth_rad)*sin(dR)*cos(radlat0), cos(dR)-sin(radlat0)*sin(new_lat));

    new_lat = qRadiansToDegrees(new_lat);
    new_lon=qRadiansToDegrees(new_lon);
    return QGeoCoordinate(new_lat, new_lon);
}

double Calculate_azimuth(const QGeoCoordinate &point1, const QGeoCoordinate &point2)
{

    double lat1=point1.latitude();
    double lon1=point1.longitude();
    double lat2=point2.latitude();
    double lon2=point2.longitude();


   double lat1_rad = qDegreesToRadians(lat1);
   double lon1_rad = qDegreesToRadians(lon1);
   double lat2_rad = qDegreesToRadians(lat2);
   double lon2_rad = qDegreesToRadians(lon2);

    double d_lon = lon2_rad - lon1_rad;
    double a_x = sin(d_lon)*cos(lat2_rad);
    double a_y= cos(lat1_rad)*sin(lat2_rad)-(sin(lat1_rad)*cos(lat2_rad)*cos(d_lon));
    double azimuth = atan2(a_x, a_y);

    azimuth= qRadiansToDegrees(azimuth);
    azimuth = fmod((azimuth+360), 360);
    return azimuth;
}

