#include <QString>
#include <QtTest>

class WorkerBaseTest : public QObject
{
    Q_OBJECT

public:
    WorkerBaseTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
};

WorkerBaseTest::WorkerBaseTest()
{
}

void WorkerBaseTest::initTestCase()
{
}

void WorkerBaseTest::cleanupTestCase()
{
}

void WorkerBaseTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(WorkerBaseTest)

#include "tst_workerbasetest.moc"
