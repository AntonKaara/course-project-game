TEMPLATE = lib

CONFIG += c++14 staticlib

HEADERS += \
    buildings/buildingbase.h \
    buildings/farm.h \
    buildings/headquarters.h \
    buildings/outpost.h \
    exceptions/baseexception.h \
    exceptions/keyerror.h \
    exceptions/expiredpointer.h \
    exceptions/resourceerror.h \
    exceptions/ownerconflict.h \
    exceptions/nospace.h \
    interfaces/iobjectmanager.h \
    interfaces/igameeventhandler.h \
    tiles/grassland.h \
    tiles/forest.h \
    tiles/tilebase.h \
    workers/basicworker.h \
    workers/workerbase.h \
    core/basicresources.h \
    core/placeablegameobject.h \
    core/worldgenerator.h \
    core/coordinate.h \
    core/playerbase.h \
    core/gameobject.h


SOURCES += \
    buildings/buildingbase.cpp \
    buildings/headquarters.cpp \
    buildings/outpost.cpp \
    buildings/farm.cpp \
    tiles/grassland.cpp \
    tiles/forest.cpp \
    tiles/tilebase.cpp \
    workers/basicworker.cpp \
    workers/workerbase.cpp \
    core/placeablegameobject.cpp \
    core/worldgenerator.cpp \
    core/coordinate.cpp \
    core/playerbase.cpp \
    core/gameobject.cpp
