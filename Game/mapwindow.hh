#include "graphics/simplegamescene.h"
#include "core/coordinate.h"

#include "gamescene.h"
#include "gameeventhandler.hh"
#include "objectmanager.hh"
#include "player.hh"
#include "mainmenu.hh"

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
    ~MapWindow();

    void setSize(int width, int height);
    void setScale(int scale);
    void resize();
    void drawTile( std::shared_ptr<Course::TileBase> obj);
    void removeItem( std::shared_ptr<Course::GameObject> obj);
    void updateItem( std::shared_ptr<Course::GameObject> obj);

    void generateMap();
    void drawMap();

    void initializePlayer1();
    void initializePlayer2();

    void buildOnTile();
    void endTurn();

    bool eventFilter(QObject *object, QEvent *event);
    void updateUI();

public slots:

    void setPlayerName(const QString &name, const int &playerNumber);

private slots:

    void on_zoomInButton_clicked();
    void on_zoomOutButton_clicked();
    void on_confirmBuildButton_clicked();
    void on_buildPanelButton_clicked();
    void on_endTurnButton_clicked();

    void resizeEvent(QResizeEvent *event);

    void on_buildList_itemDoubleClicked(QListWidgetItem *item);


private:
    void addPixmaps();

    Ui::MapWindow* ui_;
    std::shared_ptr<GameScene> scene_ = nullptr;
    std::shared_ptr<GameEventHandler> gameEventHandler_ = nullptr;
    std::shared_ptr<ObjectManager> objectManager_ = nullptr;
    std::shared_ptr<MainMenu> mainMenu_ = nullptr;

    std::map<std::string, QPixmap> pixmaps_ = {};

    int mapsizeX_ = 20; // Tile count
    int mapsizeY_ = 20;
    int mapScale_ = 60; // Tile pixmap size in px
    int zoomLevel_ = 0; // Normal view = 0

    int turn_ = 1;
    uint selectedTileID_ = 0;

    // Attributes for storing players' information

    std::shared_ptr<Player> playerInTurn_ = nullptr;
    std::string player1Name_ = "Player 1";
    std::string player2Name_ = "Player 2";

    std::vector<std::shared_ptr<Player>> players_ = {};

    // Attributes for defining the maps size and scale

    int selectedMapSize = 1;
    const int MAP_SIZE_SMALL = 10;
    const int MAP_SIZE_MEDIUM = 20;
    const int MAP_SIZE_LARGE = 40;
    const int MAP_SIZE_ULTRA_LARGE = 60;

};

} // namespace Aeta

#endif // MapWINDOW_HH

