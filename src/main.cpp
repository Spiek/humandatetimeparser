#include <QCoreApplication>
#include <QDebug>
#include "humandatetimeparser.h"
#include <QElapsedTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	// init human date time parser
    HumanDateTimeParser::parse("next day");

    QElapsedTimer timer;
    timer.start();

    qint64 elaspedSum = 0;
    for(QString& element : QList<QString>{{"next day"}, {"now"},{"10 September 2000"},{"+1 day"},{"+1 week"},{"+1 week +2 days +4 hours +2 seconds"},{"next Thursday"},{"last Monday"}, {"tomorrow"}})
    {
        QElapsedTimer timersub;
        timersub.start();
        QDateTime time = HumanDateTimeParser::parse(element);
        qint64 elasped = timersub.nsecsElapsed();
        elaspedSum += elasped;
        qDebug("%7lld %s %s", timersub.nsecsElapsed(), qPrintable(time.toString("yyyy-MM-dd hh:mm:ss")), qPrintable(element));
    }
    qDebug("%7lld Elapsed", elaspedSum);


    return a.exec();
}
