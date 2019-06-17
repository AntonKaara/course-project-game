    TEMPLATE = lib

CONFIG += c++14

INCLUDEPATH +=  BGBase/source

HEADERS += \
    buildings/buildingbase.h \
    buildings/farm.h \
    buildings/headquarters.h \
    buildings/outpost.h \
    exceptions/resourceerror.h \
    exceptions/ownerconflict.h \
    interfaces/iobjectmanager.h \
    interfaces/igameeventhandler.h \
    tiles/grassland.h \
    tiles/forest.h \
    tiles/tilebase.h \
    workers/basicworker.h \
    workers/workerbase.h \
    basicresources.h \
    placeablegameobject.h \
    worldgenerator.h



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
    placeablegameobject.cpp \
    worldgenerator.cpp
