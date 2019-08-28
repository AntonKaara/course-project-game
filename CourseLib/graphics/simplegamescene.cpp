#include "simplegamescene.h"
#include "simplemapitem.h"

#include <QEvent>
#include <QGraphicsSceneMouseEvent>

#include <math.h>

namespace Course {


SimpleGameScene::SimpleGameScene(QWidget* parent,
                                 int width,
                                 int height,
                                 int scale):
    QGraphicsScene(parent),
    m_mapBoundRect(nullptr),
    m_width(width),
    m_height(height),
    m_scale(scale)
{
    resize();
}

SimpleGameScene::~SimpleGameScene()
{
}

void SimpleGameScene::setSize(int width, int height)
{
    if ( width > SCENE_WIDTH_LIMITS.first && width < SCENE_WIDTH_LIMITS.second )
    {
        m_width = width;
    }
    if ( height > SCENE_HEIGHT_LIMITS.first && height < SCENE_HEIGHT_LIMITS.second )
    {
        m_height = height;
    }
    resize();
}

void SimpleGameScene::setScale(int scale)
{
    if ( scale > SCENE_SCALE_LIMITS.first && scale < SCENE_SCALE_LIMITS.second )
    {
        m_scale = scale;
    }
}

void SimpleGameScene::resize()
{
    if ( m_mapBoundRect != nullptr ){
        QGraphicsScene::removeItem(m_mapBoundRect);
    }

    // Calculates rect with middle at (0,0).
    // Basically left upper corner coords and then width and height
    QRect rect = QRect( m_width * m_scale / - 2, m_height * m_scale / -2,
                        m_width * m_scale - 1, m_height * m_scale - 1 );

    addRect(rect, QPen(Qt::black));
    setSceneRect(rect);
    m_mapBoundRect = itemAt(rect.topLeft(), QTransform());
}

int SimpleGameScene::getScale() const
{
    return m_scale;
}

std::pair<int, int> SimpleGameScene::getSize() const
{
    return {m_width, m_height};
}

void SimpleGameScene::updateItem(std::shared_ptr<Course::GameObject> obj)
{
    QList<QGraphicsItem*> items_list = items(obj->getCoordinate()->asQpoint());
    if ( items_list.size() == 1 ){
        qDebug() << "Nothing to be updated at the location pointed by given obj.";
    } else {
        for ( auto item : items_list ){
            static_cast<SimpleMapItem*>(item)->updated();
        }
    }
}

bool SimpleGameScene::event(QEvent *event)
{
    if(event->type() == QEvent::GraphicsSceneMousePress)
    {
        QGraphicsSceneMouseEvent* mouse_event =
                dynamic_cast<QGraphicsSceneMouseEvent*>(event);

        if ( sceneRect().contains(mouse_event->scenePos())){

            QPointF point = mouse_event->scenePos() / m_scale;

            point.rx() = floor(point.rx());
            point.ry() = floor(point.ry());

            QGraphicsItem* pressed = itemAt(point * m_scale, QTransform());

            if ( pressed == m_mapBoundRect ){
                qDebug() << "Click on map area.";
            }else{
                qDebug() << "ObjID: " <<
                            static_cast<Course::SimpleMapItem*>(pressed)
                            ->getBoundObject()->ID  << " pressed.";
                return true;
            }

        }
    }

    return false;
}


void SimpleGameScene::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    QList<QGraphicsItem*> items_list = items(obj->getCoordinate()->asQpoint());
    if ( items_list.size() == 1 ){
        qDebug() << "Nothing to be removed at the location pointed by given obj.";
    } else {
        for ( auto item : items_list ){
            SimpleMapItem* mapitem = static_cast<SimpleMapItem*>(item);
            if ( mapitem->isSameObj(obj) ){
                delete mapitem;
            }
        }
    }
}

void SimpleGameScene::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    SimpleMapItem* nItem = new SimpleMapItem(obj, m_scale);
    addItem(nItem);
}

}
