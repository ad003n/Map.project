TEMPLATE = app

QT += location\
    positioning \
    testlib

SOURCES +=  main.cpp\
            maincontroller.cpp \
            Azimuth_NewCoord.h\
            line_discretization.h\
            CoordinateConvert.h\


HEADERS+=maincontroller.h\



RESOURCES += qml.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/location/minimal_map
INSTALLS += target
