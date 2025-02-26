//Azimuth_NewCoord.h
#include <QDebug>
#include <QPointF>
#include <QtMath>
#include <QGeoCoordinate>



QGeoCoordinate NewCoordinate(const QGeoCoordinate &coord,  double azimuth, double distance)
{
    constexpr double earthRadius = 6378137.0; // Радиус Земли в метрах

    double lat0 =coord.latitude();
    double lon0 = coord.longitude();

    double azimuth_rad= qDegreesToRadians(azimuth);
    double Radlat0= qDegreesToRadians((lat0));
     double Radlon0= qDegreesToRadians((lon0));
     double DR= distance/earthRadius;

     double new_lat= asin(sin(Radlat0)*cos(DR)+cos(Radlat0)*sin(DR)+cos(azimuth_rad));
    double new_lon=Radlon0+atan2(sin(azimuth_rad)*sin(DR)*cos(Radlat0), cos(DR)-sin(Radlat0)*sin(new_lat));


    new_lat = qRadiansToDegrees(new_lat);
   new_lon=qRadiansToDegrees(new_lon);

    return QGeoCoordinate(new_lat, new_lon);
}

double calculate_azimuth(const QGeoCoordinate &point1, const QGeoCoordinate &point2)
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

