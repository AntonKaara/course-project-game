#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QDebug>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <memory>

#include "core/gameobject.h"

namespace Aeta {

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene(QWidget* qt_parent = nullptr,
              int mapWidth = 20,
              int mapHeight = 20,
              int mapScale = 80
            );
    ~GameScene() = default;

    void setSize(int width, int height);
    void setScale(int scale);
    void resize();
    std::pair<int,int> getSize() const;
    int getScale() const;
    void drawItem( std::shared_ptr<Course::GameObject> obj);
    void removeItem( std::shared_ptr<Course::GameObject> obj);
    void updateItem( std::shared_ptr<Course::GameObject> obj);

    //virtual bool event(QEvent* event) override;

private:
    QGraphicsItem* mapBounds_;

    int mapWidth_;
    int mapHeight_;
    int mapScale_;

};

} // namespace Aeta
#endif // GAMESCENE_H
