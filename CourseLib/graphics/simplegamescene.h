#ifndef SIMPLEGAMESCENE_H
#define SIMPLEGAMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

#include <map>
#include <memory>

#include "core/gameobject.h"

namespace Course {

const std::pair<int, int> SCENE_WIDTH_LIMITS = {1, 100};
const std::pair<int, int> SCENE_HEIGHT_LIMITS = {1, 100};
const std::pair<int, int> SCENE_SCALE_LIMITS = {1, 500};

class SimpleGameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    SimpleGameScene(QWidget* qt_parent = nullptr,
                    int width = 10,
                    int height = 10,
                    int scale = 50
            );
    ~SimpleGameScene();

    void setSize(int width, int height);
    void setScale(int scale);
    void resize();

    int getScale() const;
    std::pair<int,int> getSize() const;

    void drawItem( std::shared_ptr<Course::GameObject> obj);
    void removeItem( std::shared_ptr<Course::GameObject> obj);
    void updateItem( std::shared_ptr<Course::GameObject> obj);

    bool event(QEvent* event) override;

private:
    QGraphicsItem* m_mapBoundRect;
    int m_width;
    int m_height;
    int m_scale;
};
}

#endif // SIMPLEGAMESCENE_H

