#include <QString>
#include <QtTest>

class BuildingBaseTest : public QObject
{
    Q_OBJECT

public:
    BuildingBaseTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
};

BuildingBaseTest::BuildingBaseTest()
{
}

void BuildingBaseTest::initTestCase()
{
}

void BuildingBaseTest::cleanupTestCase()
{
}

void BuildingBaseTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(BuildingBaseTest)

#include "tst_buildingbasetest.moc"
