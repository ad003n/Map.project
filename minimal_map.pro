TEMPLATE = app

QT += location\
    positioning \
    testlib

SOURCES +=  maincontroller.cpp \
            maincontroller.h\
            Azimuth_NewCoord.cpp\
            Azimuth_NewCoord.h\






RESOURCES += qml.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/location/minimal_map
INSTALLS += target
