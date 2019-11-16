#include "core/gameobject.h"
#include <QPainter>
#include <QGraphicsItem>
#include <map>
#include <string>
#include <QSize>

#ifndef MAPITEM_H
#define MAPITEM_H

namespace Aeta {

class MapItem  : public QGraphicsItem {

public:

    MapItem(const std::shared_ptr<Course::GameObject> &obj, int size);

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

    const std::shared_ptr<Course::GameObject> &getBoundObject();

    /**
     * @brief updateLoc moves the item if the position has changed.
     */
    void updateLoc();

    /**
     * @brief checks if this instance has obj as bound obj.
     * @param obj to compare to.
     * @return True: if obj is pointing to the same object as this item.
     * False otherwise.
     */
    bool isSameObj(std::shared_ptr<Course::GameObject> obj);

    /**
     * @brief getSize
     * @return size of the object in pixels.
     * @post Exception guarantee: No-throw
     */
    int getSize() const;

    /**
     * @brief setSize
     * @param size of the object in pixels.
     * @pre 0 < size <= 500
     * @post Exception guarantee: No-throw
     */
    void setSize(int size);

    void addMapItemPictures();

private:
    /**
     * @brief addMapItemPicture is a helper function to add a
     * corresponding picture representing the MapItem to the picturemap
     * whenever constructing a new MapItem.
     */

    std::shared_ptr<Course::GameObject> gameObject_;
    QPoint sceneLocation_;
    QSize objectSize_;
    int tileScale_ = 60;
    std::map<std::string, QPixmap> mapItemPictures_ = {};

};

} // namespace Aeta



#endif // MAPITEM_H
