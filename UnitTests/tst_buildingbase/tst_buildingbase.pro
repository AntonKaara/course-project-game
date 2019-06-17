QT       += testlib

QT       -= gui

TARGET = tst_buildingbasetest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


HEADERS += \
    ../../BGBase/source/gameobject.h \
    ../../BGBase/source/coordinate.h \
    ../../BGBase/source/playerbase.h \
    ../../source/buildings/buildingbase.h \
    ../../source/workers/workerbase.h \
    ../../source/tiles/tilebase.h \
    ../../source/placeablegameobject.h

SOURCES += \
    ../../BGBase/source/gameobject.cpp \
    ../../BGBase/source/coordinate.cpp \
    ../../BGBase/source/playerbase.cpp \
    ../../source/buildings/buildingbase.cpp \
    ../../source/workers/workerbase.cpp \
    ../../source/tiles/tilebase.cpp \
    ../../source/placeablegameobject.cpp \
        tst_buildingbasetest.cpp
