#include "graphics/simplegamescene.h"
#include "core/coordinate.h"

#include "gamescene.h"
#include "gameeventhandler.hh"
#include "objectmanager.hh"
#include "player.hh"
#include "mainmenu.hh"
#include "welcome.h"
#include "headquarters.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QListWidget>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <map>
#include <QObject>

#ifndef MAPWINDOW_HH
#define MAPWINDOW_HH

namespace Ui {

class MapWindow;

}

namespace Aeta {

class MapWindow : public QMainWindow {

    Q_OBJECT

public:

    explicit MapWindow(QWidget *parent = nullptr);
    ~MapWindow() override;

    // Scene

    void setSize(int width, int height);
    void setScale(int scale);
    void drawTile(std::shared_ptr<Course::TileBase> obj);
    void removeItem(std::shared_ptr<Course::GameObject> obj);

    // Map generation

    void addPixmaps();
    void generateMap();
    void drawMap();
    void initializePlayer1();
    void initializePlayer2();

    // Map view

    void centerViewtoHQ();

    // Buildings

    void buildOnTile();
    void demolishBuilding(std::shared_ptr<Course::BuildingBase> building,
                          std::shared_ptr<Course::TileBase> tile);

    // Units

    void recruitUnit();
    bool moveUnit(const std::shared_ptr<Course::TileBase> &tile);
    void cutForest(const std::shared_ptr<Course::TileBase> &tile);
    bool attackHQ(const std::shared_ptr<Course::TileBase> &tile, const std::shared_ptr<UnitBase> &attacker);

    // Other mechanics

    void endTurn();
    void addProduction();
    void updateUI();

    // Events

    bool eventFilter(QObject *object, QEvent *event) override;

public slots:

    // Signals from main menu

    void setPlayerName(const QString &name, const int &playerNumber);
    void setMapSize(const int &sizeX, const int &sizeY);

private slots:

    // Buttons and other clickables

    void on_zoomInButton_clicked();
    void on_zoomOutButton_clicked();
    void on_confirmBuildButton_clicked();
    void on_buildPanelButton_clicked();
    void on_endTurnButton_clicked();
    void on_buildList_itemDoubleClicked(QListWidgetItem *item);
    void on_unitTextBox_editingFinished();
    void on_moveButton_clicked();
    void on_recruitButton_clicked();
    void on_confirmRecruitButton_clicked();
    void on_recruitList_doubleClicked(const QModelIndex &index);

    // Events

    void resizeEvent(QResizeEvent *event) override;

private:

    Ui::MapWindow* ui_;
    std::shared_ptr<GameScene> scene_ = nullptr;
    std::shared_ptr<GameEventHandler> gameEventHandler_ = nullptr;
    std::shared_ptr<ObjectManager> objectManager_ = nullptr;
    std::shared_ptr<MainMenu> mainMenu_ = nullptr;
    std::shared_ptr<Welcome> welcomeDialog_ = nullptr;

    std::map<std::string, QPixmap> pixmaps_ = {};

    int mapsizeX_ = 20; // Tile count
    int mapsizeY_ = 20;
    int mapScale_ = 60; // Tile pixmap size in px
    int zoomLevel_ = 0; // Normal view = 0

    int turn_ = 1; // Turn for playerInTurn pointer
    int turnCount_ = 1; // Turn for UI
    bool moveMode_ = false;

    // Important GameObjects

    std::shared_ptr<Course::TileBase> selectedTile_ = nullptr;
    std::shared_ptr<UnitBase> selectedUnit_ = nullptr;
    std::shared_ptr<Headquarters> player1HQ_ = nullptr;
    std::shared_ptr<Headquarters> player2HQ_ = nullptr;

    // Attributes for storing players' information

    std::shared_ptr<Player> playerInTurn_ = nullptr;
    QString player1UiName_ = "Unnamed";
    QString player2UiName_ = "Unnamed2";

    std::vector<std::shared_ptr<Player>> players_ = {};
    std::vector<std::shared_ptr<Course::TileBase>> tilesToGiveBack_ = {};

    // Attributes for defining the maps size and scale

    int selectedMapSize = 1;
    const int MAP_SIZE_SMALL = 10;
    const int MAP_SIZE_MEDIUM = 20;
    const int MAP_SIZE_LARGE = 40;
    const int MAP_SIZE_ULTRA_LARGE = 60;

};

} // namespace Aeta

#endif // MapWINDOW_HH

