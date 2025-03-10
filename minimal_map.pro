TEMPLATE = app

QT += location\
    positioning \
    testlib

SOURCES +=  main.cpp\
            maincontroller.cpp \
            azimuthnewcoord.cpp\
            linediscretization.cpp\
            coordinateconvert.cpp\

HEADERS+=   maincontroller.h\
            azimuthnewcoord.h\
            linediscretization.h\
            coordinateconvert.h\



RESOURCES += qml.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/location/minimal_map
INSTALLS += target
