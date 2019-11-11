#ifndef MAPWINDOW_HH
#define MAPWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include <map>

//#include "interfaces/igameeventhandler.h"
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

    void setGEHandler(std::shared_ptr<Course::iGameEventHandler> nHandler);
    void setSize(int width, int height);
    void setScale(int scale);
    void resize();
    void drawItem( std::shared_ptr<Course::GameObject> obj);
    void removeItem( std::shared_ptr<Course::GameObject> obj);
    void updateItem( std::shared_ptr<Course::GameObject> obj);


    void generateMap();


private:
    Ui::MapWindow* ui_;
    std::shared_ptr<Course::iGameEventHandler> gameEventHandler_ = nullptr;
    std::shared_ptr<Course::iObjectManager> objectManager_ = nullptr;
    std::shared_ptr<Course::SimpleGameScene> m_simplescene = nullptr;

    int mapsizeX_ = 20;
    int mapsizeY_ = 20;


};

#endif // MapWINDOW_HH

