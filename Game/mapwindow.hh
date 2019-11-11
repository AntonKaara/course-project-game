#ifndef MAPWINDOW_HH
#define MAPWINDOW_HH

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

namespace Ui {
class MapWindow;
}

class MapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapWindow(QWidget *parent = nullptr);
    ~MapWindow();

    void setSize(int width, int height);
    void setScale(double scale);
    void resize();
    void drawItem( std::shared_ptr<Course::GameObject> obj);
    void removeItem( std::shared_ptr<Course::GameObject> obj);
    void updateItem( std::shared_ptr<Course::GameObject> obj);

    void generateMap();
    void drawMap(double scale);

private slots:
    void on_zoomInButton_clicked();
    void on_zoomOutButton_clicked();

private:
    Ui::MapWindow* ui_;
    std::shared_ptr<Course::iGameEventHandler> gameEventHandler_ = nullptr;
    std::shared_ptr<Course::iObjectManager> objectManager_ = nullptr;
    std::shared_ptr<Aeta::GameScene> scene_ = nullptr;

    int mapsizeX_ = 50;
    int mapsizeY_ = 50;
    int mapScale_ = 1;

    int selectedMapSize = 1;
    const int MAP_SIZE_MEDIUM = 20;

};

#endif // MapWINDOW_HH

