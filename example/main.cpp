#include <QCoreApplication>
#include <QDebug>
#include "humandatetimeparser.h"

#define PrettyPrint(a,datetime) qDebug("%s %s", qPrintable(HumanDateTimeParser::parse(a, currentDateTime).toString("yyyy-MM-dd hh:mm:ss")), a)

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // get current time
    QDateTime currentDateTime = QDateTime::currentDateTime();

    PrettyPrint("now", currentDateTime);
    PrettyPrint("yesterday", currentDateTime);
    PrettyPrint("tomorrow", currentDateTime);

    // week related
    PrettyPrint("week", currentDateTime);
    PrettyPrint("-1 week", currentDateTime);
    PrettyPrint("1 week", currentDateTime);
    PrettyPrint("last week", currentDateTime);
    PrettyPrint("next saturday", currentDateTime);
    PrettyPrint("last Thursday", currentDateTime);

    // relative
    PrettyPrint("day", currentDateTime);
    PrettyPrint("1 year", currentDateTime);
    PrettyPrint("+1 month", currentDateTime);
    PrettyPrint("-1 day", currentDateTime);
    PrettyPrint("next year", currentDateTime);

    // fix
    PrettyPrint("10 September 2000", currentDateTime);
    PrettyPrint("10.05.2017", currentDateTime);
    PrettyPrint("2017-05-10 14:04", currentDateTime);

    // chain
    PrettyPrint("2017-05-10 14:04 +2 days +2 seconds 12:04", currentDateTime);
    PrettyPrint("1 day +1 week +2 days +4 hours +2 seconds", currentDateTime);

    return a.exec();
}
