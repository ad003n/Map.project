#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QVector>
#include <QGeoCoordinate>
#include <QPointF>
#include<QVariant>

#include "line_discretization.h"
#include "Azimuth_NewCoord.h"
#include "CoordinateConvert.h"

class MainController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantList new_CoordinatesFor READ getnew_Coordinates NOTIFY new_CoordinatesChanged)

    public:
        explicit MainController(QObject *parent = nullptr);
        QVariantList getnew_Coordinates() const;
        void setnew_Coordinates(const QVector<QGeoCoordinate> &coordinates);
    public slots:
        void processCoordinates(const QGeoCoordinate &startCoord, const QGeoCoordinate &endCoord, double distanse);
    signals:
        void new_CoordinatesChanged();
    private:
        QVector<QGeoCoordinate> newCoords; // Хранит новые координаты
};

#endif // MAINCONTROLLER_H
