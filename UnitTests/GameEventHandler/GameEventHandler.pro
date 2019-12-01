QT += testlib
QT -= gui
QT += widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += c++14

TEMPLATE = app

SOURCES += \
tst_gameeventhandlertest.cpp \
../../Course/CourseLib/core/basicresources.cpp \
../../Course/CourseLib/core/playerbase.cpp \
../../Game/gameeventhandler.cpp \
../../Game/player.cpp \


HEADERS += \
../../Course/CourseLib/interfaces/igameeventhandler.h \
../../Course/CourseLib/core/basicresources.h \
../../Course/CourseLib/core/playerbase.h \
../../Game/gameeventhandler.hh \
../../Game/player.hh \

INCLUDEPATH += \
../../Course/CourseLib/ \
../../Game/ \

