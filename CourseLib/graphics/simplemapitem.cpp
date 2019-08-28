#include "simplemapitem.h"


namespace Course {

std::map<std::string, QColor> SimpleMapItem::c_mapcolors = {};

SimpleMapItem::SimpleMapItem(const std::shared_ptr<Course::GameObject> &obj, int size ):
    m_gameobject(obj), m_scenelocation(m_gameobject->getCoordinate()->asQpoint()), m_size(size)
{
    addNewColor(m_gameobject->getType());
}

QRectF SimpleMapItem::boundingRect() const
{
    return QRectF(m_scenelocation * m_size, m_scenelocation * m_size + QPoint(m_size, m_size));
}

void SimpleMapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(c_mapcolors.at(m_gameobject->getType())));
    if ( m_gameobject->getType() == "" ){

    }
    painter->drawRect(boundingRect());
}

const std::shared_ptr<Course::GameObject> &SimpleMapItem::getBoundObject()
{
    return m_gameobject;
}

void SimpleMapItem::updated()
{
    if ( !m_gameobject ){
        delete this;
    } else {
        update(boundingRect()); // Test if necessary
        m_scenelocation = m_gameobject->getCoordinate()->asQpoint();
    }
}

bool SimpleMapItem::isSameObj(std::shared_ptr<Course::GameObject> obj)
{
    return obj == m_gameobject;
}

int SimpleMapItem::getSize() const
{
    return m_size;
}

void SimpleMapItem::setSize(int size)
{
    m_size = size;
}

void SimpleMapItem::addNewColor(std::string type)
{
    if ( c_mapcolors.find(type) == c_mapcolors.end() ){
        std::size_t hash = std::hash<std::string>{}(type);
        c_mapcolors.insert({type, QColor((hash & 0xFF0000) >> 16, (hash & 0x00FF00 ) >> 8, (hash & 0x0000FF))});

    }
}

}
