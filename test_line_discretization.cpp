#include <QtTest/QtTest>
#include "line_discretization.h"

class TestLineDiscretization : public QObject {
    Q_OBJECT

private slots:
    void testDiscretization();
    void testZeroLengthSegment();
    void testSegmentStepLargerThanLength();
};

// Тест 1: Обычная дискретизация отрезка
void TestLineDiscretization::testDiscretization() {
    QPointF start(0, 0);
    QPointF end(0, 5);
    double step = 1.0;

    QVector<QPointF> result = lineDiscretization(start, end, step);///

    QCOMPARE(result.first(), start);  // Первая точка должна совпадать с начальной
    QCOMPARE(result.last(), end);     // Последняя точка должна совпадать с конечной
    QVERIFY(result.size() > 2);       // Должно быть больше двух точек


    // Проверяем, что расстояния между точками соответствуют шагу
    for (int i = 1; i < result.size(); ++i) {
        double dist = QLineF(result[i - 1], result[i]).length();
        QVERIFY(qAbs(dist - step) < 0.01 || i == result.size() - 1);  // Последняя точка может быть ближе
    }
}

// Тест 2: Разбиение нулевого отрезка (точка == точке)
void TestLineDiscretization::testZeroLengthSegment() {
    QPointF point(5, 5);
    double step = 1.0;

    QVector<QPointF> result = lineDiscretization(point, point, step);

    QCOMPARE(result.size(), 1);  // Должна остаться одна точка
    QCOMPARE(result.first(), point);
}

// Тест 3: Если шаг больше длины отрезка, должны быть только начало и конец
void TestLineDiscretization::testSegmentStepLargerThanLength() {
    QPointF start(0, 0);
    QPointF end(3, 3);
    double step = 10.0;

    QVector<QPointF> result = lineDiscretization(start, end, step);

    QCOMPARE(result.size(), 2);
    QCOMPARE(result.first(), start);
    QCOMPARE(result.last(), end);
}

// Регистрация тестового класса
QTEST_MAIN(TestLineDiscretization)
#include "test_line_discretization.moc"
