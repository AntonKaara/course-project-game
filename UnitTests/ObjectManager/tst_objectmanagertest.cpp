#include "../../Course/CourseLib/interfaces/iobjectmanager.h"
#include "../../Course/CourseLib/interfaces/igameeventhandler.h"
#include "../../Course/CourseLib/core/gameobject.h"
#include "../../Course/CourseLib/core/coordinate.h"
#include "../../Course/CourseLib/core/placeablegameobject.h"
#include "../../Course/CourseLib/core/basicresources.h"
#include "../../Course/CourseLib/core/resourcemaps.h"
#include "../../Course/CourseLib/tiles/tilebase.h"
#include "../../Course/CourseLib/workers/workerbase.h"
#include "../../Course/CourseLib/buildings/buildingbase.h"

#include "../../Game/unitbase.h"
#include "../../Game/objectmanager.hh"
#include "../../Game/gameeventhandler.hh"

#include <QtTest>

class ObjectManagerTest : public QObject {
    Q_OBJECT

public:

    ObjectManagerTest();
    ~ObjectManagerTest();

private:

    std::shared_ptr<Aeta::ObjectManager> objectManager = nullptr;
    std::shared_ptr<Aeta::GameEventHandler> gameEventHandler = nullptr;
    std::shared_ptr<Aeta::Player> player = nullptr;


private slots:

    /**
     * @brief addTilesGetTilesTest tests the result of addTiles method.
     * @note it is mandatory to use getAllTiles method in this to access
     * the tiles_ but as it is just a plain return method it doesn't
     * require actual testing.
     */
    void addTilesTest();

    /**
     * @brief getTileWithCoordinateTest tests the getTile method's return
     * value validity when calling it with coordinate parameter.
     */
    void getTileCoordinateTest();

    /**
     * @brief getTileWithIdTest tests the getTile method's return
     * value validity when calling it with ID parameter.
     */
    void getTileIdTest();

    /**
     * @brief removeTileTest test tile removal from the tiles_
     * vector.
     * @note it is mandatory to use getAllTiles method in this to access
     * the tiles_ but as it is just a plain return method it doesn't
     * require actual testing.
     */
    void removeTileTest();

    /**
     * @brief addBuildingTest tests the result of addTiles method.
     * @note it is mandatory to use getAllBuildings method in this
     * to access the buildings_ but as it is just a plain return method
     * it doesn't require actual testing.
     */
    void addBuildingTest();

    /**
     * @brief getBuildingTest tests the getBuilding method's return
     * value validity when calling it with coordinate parameter.
     */
    void getBuildingCoordinateTest();

    /**
     * @brief getBuildingWithIdTest tests the getBuilding method's
     * return value validity when calling it with ID parameter.
     */
    void getBuildingIdTest();

    /**
     * @brief getBuildingsTest tests return value validity when
     * specifying a vector of coordinates as a parameter.
     */
    void getBuildingsTest();

    /**
     * @brief removeBuildingsTest tests removal of individual
     * buildings.
     * @note it is mandatory to use getAllBuildings method in this
     * to access the buildings_ but as it is just a plain return method
     * it doesn't require actual testing.
     */
    void removeBuildingTest();


    /**
     * @brief addUnitTest tests the result validity of adding an unit.
     * @note it is mandatory to use getAllUnits method in this to
     * access the units_ but as it is just a plain return method it
     * doesn't require actual testing.
     */
    void addUnitTest();

    /**
     * @brief getUnitCoordinateTest tests the getUnit method's return
     * value validity when calling it with coordinate parameter.
     */
    void getUnitCoordinateTest();

    /**
     * @brief getUnitIdTest test the getUnit method's return value
     * validity when calling it with ID parameter.
     */
    void getUnitIdTest();

    /**
     * @brief getUnitsTest tests the getUnits method's return value
     * validity when giving it a vector of unit corresponding
     * coordinates as a parameter.
     */
    void getUnitsTest();

    /**
     * @brief removeUnitTest tests the removal of individual units.
     * @note it is mandatory to use getAllUnits method in this to
     * access the units_ but as it is just a plain return method it
     * doesn't require actual testing.
     */
    void removeUnitTest();


};

ObjectManagerTest::ObjectManagerTest() {

}

ObjectManagerTest::~ObjectManagerTest() {

}

void ObjectManagerTest::addTilesTest() {

    objectManager = std::make_shared<Aeta::ObjectManager>();
    gameEventHandler = std::make_shared<Aeta::GameEventHandler>();

    std::shared_ptr<Course::TileBase> testTile = std::make_shared<
            Course::TileBase>(Course::Coordinate(1,1), gameEventHandler, objectManager);
    std::vector<std::shared_ptr<Course::TileBase>> testTiles = {testTile};

    objectManager->addTiles(testTiles);

    QCOMPARE(objectManager->getAllTiles(), testTiles);


}

void ObjectManagerTest::getTileCoordinateTest() {

    objectManager = std::make_shared<Aeta::ObjectManager>();
    gameEventHandler = std::make_shared<Aeta::GameEventHandler>();

    std::shared_ptr<Course::TileBase> testTile = std::make_shared<
            Course::TileBase>(Course::Coordinate(1,1), gameEventHandler, objectManager);
    std::vector<std::shared_ptr<Course::TileBase>> testTiles = {testTile};

    objectManager->addTiles(testTiles);

    Course::Coordinate coord = Course::Coordinate(1,1);

    QCOMPARE(objectManager->getTile(coord), testTile);

}

void ObjectManagerTest::getTileIdTest() {

    objectManager = std::make_shared<Aeta::ObjectManager>();
    gameEventHandler = std::make_shared<Aeta::GameEventHandler>();

    std::shared_ptr<Course::TileBase> testTile = std::make_shared<
            Course::TileBase>(Course::Coordinate(1,1),
                              gameEventHandler, objectManager);
    std::vector<std::shared_ptr<Course::TileBase>> testTiles = {testTile};

    objectManager->addTiles(testTiles);

    Course::ObjectId tileId = testTile->ID;

    QCOMPARE(objectManager->getTile(tileId), testTile);

}

void ObjectManagerTest::removeTileTest() {

    objectManager = std::make_shared<Aeta::ObjectManager>();
    gameEventHandler = std::make_shared<Aeta::GameEventHandler>();

    std::shared_ptr<Course::TileBase> testTile = std::make_shared<
            Course::TileBase>(Course::Coordinate(1,1),
                              gameEventHandler, objectManager);
    std::vector<std::shared_ptr<Course::TileBase>> testTiles = {testTile};

    objectManager->addTiles(testTiles);

    objectManager->removeTile(testTile);

    std::vector<std::shared_ptr<Course::TileBase>> expectedVector = {};

    QCOMPARE(objectManager->getAllTiles(),
             expectedVector);

}

void ObjectManagerTest::addBuildingTest() {

    objectManager = std::make_shared<Aeta::ObjectManager>();
    gameEventHandler = std::make_shared<Aeta::GameEventHandler>();
    std::vector<std::shared_ptr<Course::GameObject>> objects = {};
    player = std::make_shared<Aeta::Player>("", objects);

    std::shared_ptr<Course::BuildingBase> testBuilding =
            std::make_shared<Course::BuildingBase>(gameEventHandler,
                                                   objectManager,
                                                   player);
    objectManager->addBuilding(testBuilding);

    QCOMPARE(objectManager->getAllBuildings(), {testBuilding});

}

void ObjectManagerTest::getBuildingCoordinateTest() {

    objectManager = std::make_shared<Aeta::ObjectManager>();
    gameEventHandler = std::make_shared<Aeta::GameEventHandler>();

    std::vector<std::shared_ptr<Course::GameObject>> objects = {};
    player = std::make_shared<Aeta::Player>("", objects);

    std::shared_ptr<Course::BuildingBase> testBuilding =
            std::make_shared<Course::BuildingBase>(gameEventHandler,
                                                   objectManager,
                                                   player);
    testBuilding->setCoordinate(Course::Coordinate(1,1));

    objectManager->addBuilding(testBuilding);

    QCOMPARE(objectManager->getBuilding(Course::Coordinate(1,1)),
             testBuilding);

}

void ObjectManagerTest::getBuildingIdTest() {


    objectManager = std::make_shared<Aeta::ObjectManager>();
    gameEventHandler = std::make_shared<Aeta::GameEventHandler>();

    std::vector<std::shared_ptr<Course::GameObject>> objects = {};
    player = std::make_shared<Aeta::Player>("", objects);

    std::shared_ptr<Course::BuildingBase> testBuilding =
            std::make_shared<Course::BuildingBase>(gameEventHandler,
                                                   objectManager,
                                                   player);
    testBuilding->setCoordinate(Course::Coordinate(1,1));

    objectManager->addBuilding(testBuilding);

    Course::ObjectId id = testBuilding->ID;

    QCOMPARE(objectManager->getBuilding(id), testBuilding);

}

void ObjectManagerTest::getBuildingsTest() {

    objectManager = std::make_shared<Aeta::ObjectManager>();
    gameEventHandler = std::make_shared<Aeta::GameEventHandler>();

    std::vector<std::shared_ptr<Course::GameObject>> objects = {};
    player = std::make_shared<Aeta::Player>("", objects);

    std::shared_ptr<Course::BuildingBase> testBuilding =
            std::make_shared<Course::BuildingBase>(gameEventHandler,
                                                   objectManager,
                                                   player);
    testBuilding->setCoordinate(Course::Coordinate(1,1));

    objectManager->addBuilding(testBuilding);

    QCOMPARE(objectManager->getBuildings({Course::Coordinate(1,1)}),
             {testBuilding});

}

void ObjectManagerTest::removeBuildingTest() {

    objectManager = std::make_shared<Aeta::ObjectManager>();
    gameEventHandler = std::make_shared<Aeta::GameEventHandler>();

    std::vector<std::shared_ptr<Course::GameObject>> objects = {};
    player = std::make_shared<Aeta::Player>("", objects);

    std::shared_ptr<Course::BuildingBase> testBuilding =
            std::make_shared<Course::BuildingBase>(gameEventHandler,
                                                   objectManager,
                                                   player);
    testBuilding->setCoordinate(Course::Coordinate(1,1));

    objectManager->addBuilding(testBuilding);

    objectManager->removeBuilding(testBuilding);

    std::vector<std::shared_ptr<Course::BuildingBase>> expectedVector = {};


    QCOMPARE(objectManager->getAllBuildings(), expectedVector);


}

void ObjectManagerTest::addUnitTest() {

    objectManager = std::make_shared<Aeta::ObjectManager>();
    gameEventHandler = std::make_shared<Aeta::GameEventHandler>();

    std::vector<std::shared_ptr<Course::GameObject>> objects = {};
    player = std::make_shared<Aeta::Player>("", objects);

    std::shared_ptr<Aeta::UnitBase> testUnit =
            std::make_shared<Aeta::UnitBase>(gameEventHandler,
                                             objectManager,
                                             player);
    objectManager->addUnit(testUnit);

    QCOMPARE(objectManager->getAllUnits(), {testUnit});

}

void ObjectManagerTest::getUnitCoordinateTest() {

    objectManager = std::make_shared<Aeta::ObjectManager>();
    gameEventHandler = std::make_shared<Aeta::GameEventHandler>();

    std::vector<std::shared_ptr<Course::GameObject>> objects = {};
    player = std::make_shared<Aeta::Player>("", objects);

    std::shared_ptr<Aeta::UnitBase> testUnit =
            std::make_shared<Aeta::UnitBase>(gameEventHandler,
                                             objectManager,
                                             player);
    testUnit->setCoordinate(Course::Coordinate(1,1));

    objectManager->addUnit(testUnit);

    QCOMPARE(objectManager->getUnit(Course::Coordinate(1,1)),
             testUnit);

}

void ObjectManagerTest::getUnitIdTest() {

    objectManager = std::make_shared<Aeta::ObjectManager>();
    gameEventHandler = std::make_shared<Aeta::GameEventHandler>();

    std::vector<std::shared_ptr<Course::GameObject>> objects = {};
    player = std::make_shared<Aeta::Player>("", objects);

    std::shared_ptr<Aeta::UnitBase> testUnit =
            std::make_shared<Aeta::UnitBase>(gameEventHandler,
                                                   objectManager,
                                                   player);
    testUnit->setCoordinate(Course::Coordinate(1,1));

    objectManager->addUnit(testUnit);

    Course::ObjectId id = testUnit->ID;

    QCOMPARE(objectManager->getUnit(id), testUnit);

}

void ObjectManagerTest::getUnitsTest() {

    objectManager = std::make_shared<Aeta::ObjectManager>();
    gameEventHandler = std::make_shared<Aeta::GameEventHandler>();

    std::vector<std::shared_ptr<Course::GameObject>> objects = {};
    player = std::make_shared<Aeta::Player>("", objects);

    std::shared_ptr<Aeta::UnitBase> testUnit =
            std::make_shared<Aeta::UnitBase>(gameEventHandler,
                                                   objectManager,
                                                   player);
    testUnit->setCoordinate(Course::Coordinate(1,1));

    objectManager->addUnit(testUnit);

    QCOMPARE(objectManager->getUnits({Course::Coordinate(1,1)}),
             {testUnit});

}

void ObjectManagerTest::removeUnitTest() {

    objectManager = std::make_shared<Aeta::ObjectManager>();
    gameEventHandler = std::make_shared<Aeta::GameEventHandler>();

    std::vector<std::shared_ptr<Course::GameObject>> objects = {};
    player = std::make_shared<Aeta::Player>("", objects);

    std::shared_ptr<Aeta::UnitBase> testUnit =
            std::make_shared<Aeta::UnitBase>(gameEventHandler,
                                                   objectManager,
                                                   player);
    objectManager->addUnit(testUnit);
    objectManager->removeUnit(testUnit);

    std::vector<std::shared_ptr<Aeta::UnitBase>> expectedVector = {};


    QCOMPARE(objectManager->getAllUnits(), expectedVector);



}




QTEST_APPLESS_MAIN(ObjectManagerTest)

#include "tst_objectmanagertest.moc"
