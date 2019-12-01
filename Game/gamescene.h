#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "core/gameobject.h"
#include "tiles/tilebase.h"

#include <memory>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QDebug>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>

namespace Aeta {

/**
 * @brief The GameScene is a custom QGraphicsScene that renders
 * the game map and other graphical elements.
 */
class GameScene : public QGraphicsScene {

    Q_OBJECT

public:

    /**
     * @brief Constructor for the class.
     *
     * @param qt_parent points to the parent object per Qt's parent-child-system.
     * @param mapWidth in tiles for the game map.
     * @param mapHeight in tiles for the game map.
     * @param mapScale is the size in pixels of a single square tile.
     *
     */
    GameScene(QWidget* qt_parent = nullptr,
              int mapWidth = 20,
              int mapHeight = 20,
              int mapScale = 80
            );

    /**
     * @brief Default destructor.
     */
    ~GameScene() override = default;

    /**
     * @brief Default destructor.
     * @return Returns the map size in x and y.
     */
    std::pair<int,int> getSize() const;

    /**
     * @brief Sets the map size to given x and y.
     */
    void setSize(int width, int height);

    /**
     * @brief Sets the single tile pixel scale to given px amount.
     */
    void setScale(int scale);

    /**
     * @brief Resizes the scene to match the private attributes.
     */
    void resize();

    /**
     * @brief Draws a new MapTile object to the scene.
     */
    void drawTile(std::shared_ptr<Course::TileBase> obj);

    /**
     * @brief Removes a MapTile object from the scene.
     */
    void removeItem(std::shared_ptr<Course::GameObject> obj);

    /**
     * @brief Updates a single MapTile object on the scene.
     */
    void updateItem(std::shared_ptr<Course::GameObject> obj);

    /**
     * @brief Draws and stores a single movement highlight rectangle.
     */
    void drawMoveMarker(std::shared_ptr<Course::TileBase> tile);

    /**
     * @brief Removes all movement highlight rectangles.
     */
    void removeMoveMarkers();

    /**
     * @brief Draws and stores a single attack highlight rectangle.
     */
    void drawAttackMarker(std::shared_ptr<Course::TileBase> tile);

    /**
     * @brief Removes all attack highlight rectangles.
     */
    void removeAttackMarkers();

    // Event handlers

    /**
     * @brief Handles clicks on the scene.
     * @param event is the QEvent of the mouseclick
     * @param moveHighlighter tells if the selectedTile highlighter location should be updated
     * @return Returns the ID of the clicked tile to MapWindow
     */
    uint tileClicked(QEvent *event, bool moveHighlighter);

private:

    QGraphicsItem* mapBounds_ = nullptr;
    QGraphicsRectItem* highlightRectangle_ = nullptr;
    std::vector<QGraphicsRectItem*> moveMarkers_ = {};
    std::vector<QGraphicsRectItem*> attackMarkers_ = {};
    int mapWidth_ = 0;
    int mapHeight_ = 0;
    int tileScale_ = 0; // tile pixel size

    // Used to store previously clicked tile's ID in tileClicked
    uint lastTileId_ = 0;

};

} // namespace Aeta

#endif // GAMESCENE_H
