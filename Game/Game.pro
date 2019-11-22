TEMPLATE = app
TARGET = TheGame

QT += core gui widgets

CONFIG += c++14

SOURCES += \
    archery.cpp \
    cavalry.cpp \
    farm.cpp \
    foresttile.cpp \
    gamescene.cpp \
    grasstile.cpp \
    headquarters.cpp \
    infantry.cpp \
    lake.cpp \
    lumbermill.cpp \
    main.cpp \
    mapitem.cpp \
    mapwindow.cc \
    gameeventhandler.cpp \
    mine.cpp \
    mountain.cpp \
    outpost.cpp \
    player.cpp \
    mainmenu.cpp \
    objectmanager.cpp \
    swamp.cpp \
    unitbase.cpp \
    welcome.cpp

HEADERS += \
    archery.h \
    cavalry.h \
    farm.h \
    foresttile.h \
    gamescene.h \
    grasstile.h \
    headquarters.h \
    infantry.h \
    lake.h \
    lumbermill.h \
    mapitem.h \
    mapwindow.hh \
    gameeventhandler.hh \
    mine.h \
    mountain.h \
    outpost.h \
    player.hh \
    resources.hh \
    mainmenu.hh \
    objectmanager.hh \
    swamp.h \
    unitbase.h \
    welcome.h

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib

DEPENDPATH += \
    $$PWD/../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a

FORMS += \
    mapwindow.ui \
    mainmenu.ui \
    welcome.ui

RESOURCES += \
    pictures.qrc
