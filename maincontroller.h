#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QVector>
#include <QGeoCoordinate>
#include <QPointF>
#include<QVariant>

#include "linediscretization.h"
#include "azimuthnewcoord.h"
#include "coordinateconvert.h"

class MainController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantList NewCoordinatesFor READ getNewCoordinates NOTIFY newCoordinatesChanged)

    public:
        explicit MainController(QObject *parent = nullptr);
        QVariantList getNewCoordinates() const;
        void setNewCoordinates(const QVector<QGeoCoordinate> &coordinates);
    public slots:
        void processCoordinates(const QGeoCoordinate &startCoord, const QGeoCoordinate &endCoord, double distanse);
    signals:
        void newCoordinatesChanged();
    private:
        QVector<QGeoCoordinate> newCoords; // Хранит новые координаты
};

#endif // MAINCONTROLLER_H
