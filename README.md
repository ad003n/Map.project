# Map.project
# Приложение для работы с картографическими маршрутами

## Описание приложения
Десктопное приложение с графическим интерфейсом для проектирования и редактирования маршрутов на карте. Позволяет:
- Добавлять стартовую (А) и конечную (B) точки маршрута
- Автоматически генерировать промежуточные маркеры с заданным шагом
- Перемещать любые маркеры для изменения маршрута
- Визуализировать траекторию в виде полилинии
- Преобразовывать дополнительные маркеры в основные при взаимодействии
- Работать с географическими координатами (широта/долгота)

## Структура проекта и функции

### Основные модули C++
| Файл | Описание |
|------|----------|
| **`azimuthnewcoord.cpp`** | Вычисление азимута и генерация новых координат |
| **`coordinateconvert.cpp`** | Преобразование координат и расчёт расстояний |
| **`linediscretization.cpp`** | Дискретизация линии на отрезки заданной длины |
| **`maincontroller.cpp`** | Центральный контроллер логики приложения |
| **`main.cpp`** | Точка входа и инициализация приложения |

### QML-компоненты
| Файл | Назначение |
|------|------------|
| **`main.qml`** | Главный интерфейс: карта, управление, визуализация |
| **`CustomPolyline.qml`** | Компонент для отрисовки линии маршрута |

### Ключевые функции
1. **Преобразование координат**:
   - `geoToCartesian()`: Географические → Декартовы координаты
   - `cartesianToGeo()`: Декартовы → Географические координаты
   - `vincentyDistance()`: Точное расстояние между точками (алгоритм Винсенти)

2. **Расчёт маршрута**:
   - `calculateAzimuth()`: Определение направления между точками
   - `newCoordinate()`: Генерация новой точки по азимуту и расстоянию
   - `lineDiscretization()`: Разбиение маршрута на сегменты

3. **Управление логикой**:
   - `processCoordinates()`: Основной метод генерации промежуточных точек
   - `getNewCoordinates()`: Подготовка данных для QML-интерфейса

4. **Интерфейс пользователя**:
   - Drag-and-drop перемещение маркеров
   - Автоматическое обновление полилинии
   - Динамическое преобразование серых маркеров в основные
   - Интерактивные элементы управления

