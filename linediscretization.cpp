#include "linediscretization.h"

#include <QLineF>
#include <QDebug>
#include <cmath>

 QVector<QPointF> lineDiscretization(const QPointF &start, const QPointF &end, double distance) {
    QVector<QPointF> points;


    if (distance <= 0) {
        qWarning() << "Шаг должен быть > 0";
        return points;
    }


    QLineF line(start, end);
    double length = line.length();
    qDebug() << " length: " << length;

    if (length == 0) {
        points.append(start);
        return points;
    }


    if (length < distance) {
        points.append(start);
        points.append(end);
        qDebug() << "Points when length < distance:" << points;
        return points;
    }

    int numPoints = static_cast<int>(length / distance);
    double dx = ((end.x() - start.x()) / length * distance);
    double dy = ((end.y() - start.y()) / length * distance);


    qDebug()<<"dx "<<dx;
    qDebug()<<"dy "<<dy;
    qDebug()<<"number of points "<<numPoints;


    for (int i = 0; i < numPoints-1; ++i) {
        double x = start.x() + i * dx;
        double y = start.y() + i * dy;
        QPointF point(x, y);
        points.append(point);
        }

    if (points.isEmpty() || points.last() != end) {
        points.append(end);
    }

    return points;
}
