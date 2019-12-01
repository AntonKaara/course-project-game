QT += testlib
QT -= gui
QT += widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += c++14

TEMPLATE = app

SOURCES += \
tst_objectmanagertest.cpp \
../../Course/CourseLib/core/gameobject.cpp \
../../Course/CourseLib/core/coordinate.cpp \
../../Course/CourseLib/core/placeablegameobject.cpp \
../../Course/CourseLib/core/basicresources.cpp \
../../Course/CourseLib/core/playerbase.cpp \
../../Course/CourseLib/tiles/tilebase.cpp \
../../Course/CourseLib/workers/workerbase.cpp \
../../Course/CourseLib/buildings/buildingbase.cpp \
../../Game/unitbase.cpp \
../../Game/objectmanager.cpp \
../../Game/gameeventhandler.cpp \
../../Game/player.cpp \

HEADERS += \
../../Course/CourseLib/interfaces/iobjectmanager.h \
../../Course/CourseLib/interfaces/igameeventhandler.h \
../../Course/CourseLib/core/gameobject.h \
../../Course/CourseLib/core/coordinate.h \
../../Course/CourseLib/core/placeablegameobject.h \
../../Course/CourseLib/core/basicresources.h \
../../Course/CourseLib/core/resourcemaps.h \
../../Course/CourseLib/core/playerbase.h \
../../Course/CourseLib/tiles/tilebase.h \
../../Course/CourseLib/workers/workerbase.h \
../../Course/CourseLib/buildings/buildingbase.h \
../../Game/unitbase.h \
../../Game/objectmanager.hh \
../../Game/gameeventhandler.hh \
../../Game/player.hh \

INCLUDEPATH += \
../../Course/CourseLib/ \
../../Game/ \

