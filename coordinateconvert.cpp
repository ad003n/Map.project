#include"coordinateconvert.h"
#include <QtMath>

constexpr double EARTH_RADIUS_METERS_MAJOR = 6371000.0; // Большая полуось (м)
constexpr double EARTH_RADIUS_MINOR = 6356752.314245; // Малая полуось (м)
constexpr double FLATTENING = (EARTH_RADIUS_METERS_MAJOR - EARTH_RADIUS_MINOR) / EARTH_RADIUS_METERS_MAJOR;
constexpr double f = 1.0 / 298.257223563; // Сжатие Земли (WGS-84)
constexpr double e2 = 2 * f - f * f; // Квадрат эксцентриситета

constexpr double kA = EARTH_RADIUS_METERS_MAJOR;
constexpr double kF = f; // Сжатие WGS-84
constexpr double kB = (1 - kF) * kA;
constexpr double kEpsilon = 1e-12;       // Точность вычислений

// Функция для вычисления расстояния по методу Винсенти
double vincentyDistance(const QGeoCoordinate& coord1, const QGeoCoordinate& coord2) {
    double lat1 = qDegreesToRadians(coord1.latitude());
    double lon1 = qDegreesToRadians(coord1.longitude());
    double lat2 = qDegreesToRadians(coord2.latitude());
    double lon2 = qDegreesToRadians(coord2.longitude());

    double L = lon2 - lon1;
    double U1 = atan((1 - kF) * tan(lat1));
    double U2 = atan((1 - kF) * tan(lat2));
    double sinU1 = sin(U1), cosU1 = cos(U1);
    double sinU2 = sin(U2), cosU2 = cos(U2);

    double lambda = L, lambdaPrev;
    double sinLambda, cosLambda, sinSigma, cosSigma, sigma, sinAlpha, cosSqAlpha, cos2SigmaM;
    int iterLimit = 100;

    do {
        sinLambda = sin(lambda);
        cosLambda = cos(lambda);
        sinSigma = sqrt((cosU2 * sinLambda) * (cosU2 * sinLambda) +
                        (cosU1 * sinU2 - sinU1 * cosU2 * cosLambda) * (cosU1 * sinU2 - sinU1 * cosU2 * cosLambda));

        if (sinSigma == 0) return 0; // Совпадающие точки

        cosSigma = sinU1 * sinU2 + cosU1 * cosU2 * cosLambda;
        sigma = atan2(sinSigma, cosSigma);
        sinAlpha = cosU1 * cosU2 * sinLambda / sinSigma;
        cosSqAlpha = 1 - sinAlpha * sinAlpha;
        cos2SigmaM = cosSigma - 2 * sinU1 * sinU2 / cosSqAlpha;
        if (std::isnan(cos2SigmaM)) cos2SigmaM = 0; // Для экваториальных линий

        double C = kF / 16 * cosSqAlpha * (4 + kF * (4 - 3 * cosSqAlpha));
        lambdaPrev = lambda;
        lambda = L + (1 - C) * kF * sinAlpha * (sigma + C * sinSigma * (cos2SigmaM + C * cosSigma * (-1 + 2 * cos2SigmaM * cos2SigmaM)));
    } while (fabs(lambda - lambdaPrev) > kEpsilon && --iterLimit > 0);

    if (iterLimit == 0) return std::numeric_limits<double>::quiet_NaN(); // Не сошлось

    double uSq = cosSqAlpha * (kA * kA - kB * kB) / (kB * kB);
    double A = 1 + uSq / 16384 * (4096 + uSq * (-768 + uSq * (320 - 175 * uSq)));
    double B = uSq / 1024 * (256 + uSq * (-128 + uSq * (74 - 47 * uSq)));
    double deltaSigma = B * sinSigma * (cos2SigmaM + B / 4 * (cosSigma * (-1 + 2 * cos2SigmaM * cos2SigmaM) -
                                                              B / 6 * cos2SigmaM * (-3 + 4 * sinSigma * sinSigma) * (-3 + 4 * cos2SigmaM * cos2SigmaM)));

    return kB * A * (sigma - deltaSigma);
}

QPointF geoToCartesian(const QGeoCoordinate& geo, const QGeoCoordinate& origin)
{
    double lat1 = qDegreesToRadians(origin.latitude());
    double lon1 = qDegreesToRadians(origin.longitude());
    double lat2 = qDegreesToRadians(geo.latitude());
    double lon2 = qDegreesToRadians(geo.longitude());

    double x = EARTH_RADIUS_METERS_MAJOR * (lon2 - lon1) * cos(lat1);
    double y = EARTH_RADIUS_METERS_MAJOR * (lat2 - lat1);
    return QPointF(x, y);
}

static QGeoCoordinate cartesianToGeo(const QPointF& cart, const QGeoCoordinate& origin)
{
    double lat1 = qDegreesToRadians(origin.latitude());
    double lon1 = qDegreesToRadians(origin.longitude());

    double sin_lat1 = sin(lat1);
    double cos_lat1 = cos(lat1);
    double N = EARTH_RADIUS_METERS_MAJOR / sqrt(1 - FLATTENING * (2 - FLATTENING) * sin_lat1 * sin_lat1);

    // Переводим декартовы смещения в географические координаты
    double dLat = cart.y() / (N + cart.y());
    double dLon = cart.x() / ((N + cart.x()) * cos_lat1);

    // Итоговые координаты
    double lat2 = lat1 + dLat;
    double lon2 = lon1 + dLon;

    return QGeoCoordinate(lat2 * 180.0 / M_PI, lon2 * 180.0 / M_PI);
}



