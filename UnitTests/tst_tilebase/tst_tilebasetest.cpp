#include <QString>
#include <QtTest>

class TilebaseTest : public QObject
{
    Q_OBJECT

public:
    TilebaseTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

};

TilebaseTest::TilebaseTest()
{
}

void TilebaseTest::initTestCase()
{
}

void TilebaseTest::cleanupTestCase()
{
}

QTEST_APPLESS_MAIN(TilebaseTest)

#include "tst_tilebasetest.moc"
