#include "core/gameobject.h"
#include "tiles/tilebase.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QDebug>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <memory>

#ifndef GAMESCENE_H
#define GAMESCENE_H

namespace Aeta {

class GameScene : public QGraphicsScene {

    Q_OBJECT

public:

    GameScene(QWidget* qt_parent = nullptr,
              int mapWidth = 20,
              int mapHeight = 20,
              int mapScale = 80
            );

    ~GameScene() override = default;

    std::pair<int,int> getSize() const;
    void setSize(int width, int height);
    void setScale(int scale);
    void resize();
    int getScale() const;
    void drawTile(std::shared_ptr<Course::TileBase> obj);
    void removeItem(std::shared_ptr<Course::GameObject> obj);
    void updateItem(std::shared_ptr<Course::GameObject> obj);

    // Event handlers
    uint tileClicked(QEvent *event, bool moveHighlighter);


private:

    QGraphicsItem* mapBounds_ = nullptr;
    QGraphicsRectItem* highlightRectangle_ = nullptr;
    int mapWidth_ = 0;
    int mapHeight_ = 0;
    int tileScale_ = 0;

    // used to store previously clicked tile's ID in tileClicked
    uint lastTileId_ = 0;

};

} // namespace Aeta

#endif // GAMESCENE_H
