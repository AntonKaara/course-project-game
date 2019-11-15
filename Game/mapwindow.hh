#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <map>

#include "gamescene.h"
#include "gameeventhandler.hh"
#include "objectmanager.hh"
#include "graphics/simplegamescene.h"
#include "player.hh"

#ifndef MAPWINDOW_HH
#define MAPWINDOW_HH



namespace Ui {
class MapWindow;
}

namespace Aeta {

class MapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapWindow(QWidget *parent = nullptr);
    ~MapWindow();

    void setSize(int width, int height);
    void setScale(int scale);
    void resize();
    void drawItem( std::shared_ptr<Course::GameObject> obj);
    void removeItem( std::shared_ptr<Course::GameObject> obj);
    void updateItem( std::shared_ptr<Course::GameObject> obj);

    void mouseWheelEventHandler(QGraphicsSceneWheelEvent* mouseWheelEvent);

    void generateMap();
    void drawMap();
    void initializeStart(std::string playerName);


private slots:
    void on_zoomInButton_clicked();
    void on_zoomOutButton_clicked();

private:
    Ui::MapWindow* ui_;
    std::shared_ptr<Course::iGameEventHandler> gameEventHandler_ = nullptr;
    std::shared_ptr<Course::iObjectManager> objectManager_ = nullptr;
    std::shared_ptr<Aeta::GameScene> scene_ = nullptr;

    int mapsizeX_ = 10; // Tile count
    int mapsizeY_ = 10;
    int mapScale_ = 60; // Tile pixmap size in px
    int zoomLevel_ = 0; // Normal view = 0

    std::vector<std::shared_ptr<Player>> players_ = {};

    std::string player1Name_ = "Unnamed";
    std::string player2Name_ = "Unnamed2";

    int selectedMapSize = 1;
    const int MAP_SIZE_SMALL = 10;
    const int MAP_SIZE_MEDIUM = 20;
    const int MAP_SIZE_LARGE = 40;
    const int MAP_SIZE_ULTRA_LARGE = 60;

};
} // namespace Aeta
#endif // MapWINDOW_HH

