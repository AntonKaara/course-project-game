#include "../../Course/CourseLib/interfaces/iobjectmanager.h"
#include "../../Course/CourseLib/core/gameobject.h"
#include "../../Course/CourseLib/core/coordinate.h"
#include "../../Course/CourseLib/core/placeablegameobject.h"
#include "../../Course/CourseLib/core/basicresources.h"
#include "../../Course/CourseLib/core/resourcemaps.h"
#include "../../Course/CourseLib/tiles/tilebase.h"
#include "../../Course/CourseLib/workers/workerbase.h"

#include "../../Game/unitbase.h"

#include <QtTest>

class ObjectManagerTest : public QObject {
    Q_OBJECT

public:

    ObjectManagerTest();
    ~ObjectManagerTest();

private slots:

    void addTilesTest();

};

ObjectManagerTest::ObjectManagerTest() {

}

ObjectManagerTest::~ObjectManagerTest() {

}

void ObjectManagerTest::addTilesTest() {

}

QTEST_APPLESS_MAIN(ObjectManagerTest)

#include "tst_objectmanagertest.moc"
