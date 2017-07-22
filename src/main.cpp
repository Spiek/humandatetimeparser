#include <QCoreApplication>
#include <QDebug>
#include "humandatetimeparser.h"
#include <QElapsedTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QElapsedTimer timer;
    timer.start();


    for(QString& element : QList<QString>{{"now"},{"10 September 2000"},{"+1 day"},{"+1 week"},{"+1 week 2 days 4 hours 2 seconds"},{"next Thursday"},{"last Monday"}, {"tomorrow"}})
    {
        QElapsedTimer timersub;
        timersub.start();
        QDateTime time = HumanDateTimeParser::parse(element);
        qDebug() << timersub.nsecsElapsed() << element << time;
    }
    qDebug() << "Elapsed:" << timer.nsecsElapsed();


    return a.exec();
}
