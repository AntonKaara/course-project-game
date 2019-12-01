#include "../../Course/CourseLib/core/playerbase.h"
#include "../../Course/CourseLib/interfaces/igameeventhandler.h"
#include "../../Course/CourseLib/core/playerbase.h"
#include "../../Course/CourseLib/core/resourcemaps.h"
#include "../../Course/CourseLib/core/basicresources.h"

#include "../../Game/gameeventhandler.hh"
#include "../../Game/player.hh"
#include "../../Game/resources.hh"

#include <QtTest>

class GameEventHandlerTest : public QObject {
    Q_OBJECT

public:
    GameEventHandlerTest();
    ~GameEventHandlerTest();

private:

    std::shared_ptr<Aeta::GameEventHandler> gameEventHandler = nullptr;
    std::shared_ptr<Aeta::Player> player = nullptr;

private slots:

    /**
     * @brief modifyResourcesIntTest tests the result of resource
     * modifying method of GameEventHandler. This is for the method
     * which adds integer-type maps into a single sum-map which is
     * added to the player's resources.
     */
    void modifyResourcesIntTest();

    /**
     * @brief modifyResourcesDoubleTest tests the result of resource
     * modifying method of GameEventHandler. This is for the method
     * which adds double-type maps into a single sum-map which is
     * added to the player's resources.
     */
    void modifyResourcesDoubleTest();

    /**
     * @brief modifyResourceTest tests the result of modifying a single
     * resource item in player's resources.
     */
    void modifyResourceTest();

};

GameEventHandlerTest::GameEventHandlerTest() {

}

GameEventHandlerTest::~GameEventHandlerTest() {

}

void GameEventHandlerTest::modifyResourcesIntTest() {

    gameEventHandler = std::make_shared<Aeta::GameEventHandler>();
    std::vector<std::shared_ptr<Course::GameObject>> testObjs = {};
    player = std::make_shared<Aeta::Player>("Test", testObjs);
    player->setResources(Aeta::PLAYER_STARTING_RESOURCES);

    Course::ResourceMap testMapToAdd = {
        {Course::BasicResource::MONEY, 10},
        {Course::BasicResource::FOOD, 10},
        {Course::BasicResource::WOOD, 10},
        {Course::BasicResource::STONE, 10},
        {Course::BasicResource::ORE, 10}
    };

    Course::ResourceMap expectedResult = {
        {Course::BasicResource::MONEY, 285},
        {Course::BasicResource::FOOD, 60},
        {Course::BasicResource::WOOD, 130},
        {Course::BasicResource::STONE, 60},
        {Course::BasicResource::ORE, 12}
    };

    gameEventHandler->modifyResources(player, testMapToAdd);

    QCOMPARE(player->getResources(), expectedResult);

}

void GameEventHandlerTest::modifyResourcesDoubleTest() {

    gameEventHandler = std::make_shared<Aeta::GameEventHandler>();
    std::vector<std::shared_ptr<Course::GameObject>> testObjs = {};
    player = std::make_shared<Aeta::Player>("Test", testObjs);
    player->setResources(Aeta::PLAYER_STARTING_RESOURCES);

    Course::ResourceMapDouble testMapToAdd = {
        {Course::BasicResource::MONEY, 10.5},
        {Course::BasicResource::FOOD, 10.5},
        {Course::BasicResource::WOOD, 10.5},
        {Course::BasicResource::STONE, 10.5},
        {Course::BasicResource::ORE, 10.5}
    };

    Course::ResourceMapDouble expectedResult = {
        {Course::BasicResource::MONEY, 285.5},
        {Course::BasicResource::FOOD, 60.5},
        {Course::BasicResource::WOOD, 130.5},
        {Course::BasicResource::STONE, 60.5},
        {Course::BasicResource::ORE, 12.5}
    };

    gameEventHandler->modifyResources(player, testMapToAdd);

    QCOMPARE(player->getResourcesDouble(), expectedResult);

}

void GameEventHandlerTest::modifyResourceTest() {

    gameEventHandler = std::make_shared<Aeta::GameEventHandler>();
    std::vector<std::shared_ptr<Course::GameObject>> testObjs = {};
    player = std::make_shared<Aeta::Player>("Test", testObjs);
    player->setResources(Aeta::PLAYER_STARTING_RESOURCES);

    gameEventHandler->modifyResource(player, Course::BasicResource::WOOD, 1);

    Course::ResourceMap expectedResult = {
        {Course::BasicResource::MONEY, 275},
        {Course::BasicResource::FOOD, 50},
        {Course::BasicResource::WOOD, 121},
        {Course::BasicResource::STONE, 50},
        {Course::BasicResource::ORE, 2}
    };

    QCOMPARE(player->getResources(), expectedResult);
}

QTEST_APPLESS_MAIN(GameEventHandlerTest)

#include "tst_gameeventhandlertest.moc"
