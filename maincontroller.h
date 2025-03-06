#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QVector>
#include <QGeoCoordinate>
#include <QPointF>

#include "line_discretization.h"
#include "Azimuth_NewCoord.h"
#include "CoordinateConvert.h"

class MainController : public QObject {
    Q_OBJECT
   /* Q_PROPERTY(
        QVector<QGeoCoordinate> NCoordinates
        READ getNCoordinates
        WRITE setNCoordinates
        NOTIFY NCoordinatesChanged)*/
    Q_PROPERTY(QVariantList NCoordinatesFor READ getNCoordinates NOTIFY NCoordinatesChanged)


public:
    explicit MainController(QObject *parent = nullptr);
//    ~MainController() = default;
QVariantList getNCoordinates() const;
   // QVector<QGeoCoordinate> getNCoordinates() const;
    void setNCoordinates(const QVector<QGeoCoordinate> &coordinates); // Добавляем метод для установки координат
 public slots:
    void prCoordinates(const QGeoCoordinate &startCoord, const QGeoCoordinate &endCoord, double distanse);
//

signals:
   // void NCoordinatesChanged(const QVector <QGeoCoordinate> &coordinates);
  void NCoordinatesChanged();
private:
    QVector<QGeoCoordinate> newCoords; // Хранит новые координаты

};

#endif // MAINCONTROLLER_H
