QT += testlib
QT -= gui
QT += widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
tst_objectmanagertest.cpp \
../../Course/CourseLib/core/gameobject.cpp \
../../Course/CourseLib/core/coordinate.cpp \
../../Course/CourseLib/core/placeablegameobject.cpp \
../../Course/CourseLib/core/basicresources.cpp \
../../Course/CourseLib/tiles/tilebase.cpp \
../../Course/CourseLib/workers/workerbase.cpp \
../../Game/unitbase.cpp \

HEADERS += \
../../Course/CourseLib/interfaces/iobjectmanager.h \
../../Course/CourseLib/core/gameobject.h \
../../Course/CourseLib/core/coordinate.h \
../../Course/CourseLib/core/placeablegameobject.h \
../../Course/CourseLib/core/basicresources.h \
../../Course/CourseLib/core/resourcemaps.h \
../../Course/CourseLib/tiles/tilebase.h \
../../Course/CourseLib/workers/workerbase.h \
../../Game/unitbase.h \

INCLUDEPATH += \
../../Course/CourseLib/ \
../../Game/ \

