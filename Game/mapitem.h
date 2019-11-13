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

    // dunno if needed
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

private:

    std::shared_ptr<Course::GameObject> gameObject_;
    QPoint sceneLocation_;
    QSize objectSize_;
    int tileScale_ = 60;
    static std::map<std::string, QPixmap> mapItemPictures_;

    /**
     * @brief addMapItemPicture is a helper function to add a
     * corresponding picture representing the MapItem to the picturemap
     * whenever constructing a new MapItem.
     */

    void addMapItemPicture(std::string mapItemType);

};

} // namespace Aeta



#endif // MAPITEM_H
