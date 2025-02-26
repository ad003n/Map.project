
#include <QtTest/QtTest>
#include "CoordinateConvert.h"

class TestCoordinateConvert : public QObject {
    Q_OBJECT

private slots:
    void testToCartesian();
    void testToGeo();
};

// Тест 1:
void TestCoordinateConvert::testToCartesian() {
    QGeoCoordinate latlong(55.7558, 37.6173);
    QPointF cartesian = convertSphericalToCartesian(latlong);

    qDebug() << "Cartesian:" << cartesian;

}

// Тест 2:
void TestCoordinateConvert::testToGeo() {
     QGeoCoordinate coord(55.7558, 37.6173);
  //  QGeoCoordinate coord(2840377.0, 2190000.0);
    QGeoCoordinate newCoord = convertToGeo(coord, 10000, 10000);

    qDebug() << "New Geo Coordinate:" << newCoord;
}


QTEST_MAIN(TestCoordinateConvert)
#include "CoordinateConvertTest.moc"
