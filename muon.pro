TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    muon.cpp \
    point.cpp \
    pixel.cpp \
    detector.cpp \
    layer.cpp \
    kit.cpp \
    surface.cpp \
    event.cpp \
    res.cpp \
    equipment.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    muon.h \
    point.h \
    pixel.h \
    detector.h \
    layer.h \
    !_All_include.h \
    kit.h \
    surface.h \
    event.h \
    res.h \
    equipment.h

