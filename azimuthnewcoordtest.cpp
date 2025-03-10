//Azimuth_NewCoord.cpp
#include <QtTest/QtTest>
#include "Azimuth_NewCoord.h"

class TestFunctions : public QObject {
    Q_OBJECT

private slots:
    void testToAzimuth();
    void testToNewCoord();
};

void TestFunctions::testToNewCoord() {
    QGeoCoordinate coord(0, 0);
     double azimuth = 129;
    double distance = 10000000;
    QGeoCoordinate NewCoord= NewCoordinate(coord, azimuth, distance);
    qDebug() << "new coord:" << NewCoord;
}



void TestFunctions::testToAzimuth() {
    QGeoCoordinate point1(30, 0);
    QGeoCoordinate point2(30, 120);
   double Azimuth = calculate_azimuth(point1, point2);
    qDebug() << "Azimuth:" << Azimuth;
}

QTEST_MAIN(TestFunctions)
#include "Azimuth_NewCoord.moc"
