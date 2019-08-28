#ifndef SIMPLEMAPITEM_HH
#define SIMPLEMAPITEM_HH

#include <QGraphicsItem>
#include <QPainter>

#include <memory>
#include <map>

#include "core/gameobject.h"

namespace Course {

class SimpleMapItem : public QGraphicsItem
{
public:
    SimpleMapItem(const std::shared_ptr<Course::GameObject> &obj, int size);
    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    const std::shared_ptr<Course::GameObject> &getBoundObject();
    void updated();
    bool isSameObj(std::shared_ptr<Course::GameObject> obj);

    int getSize() const;
    void setSize(int size);

private:
    const std::shared_ptr<Course::GameObject> m_gameobject;
    QPoint m_scenelocation;
    int m_size;

    static std::map<std::string, QColor> c_mapcolors;
    static void addNewColor(std::string type);
};
}
#endif // SIMPLEMAPITEM_HH
