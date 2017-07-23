#ifndef HUMANDATETIMEPARSER_H
#define HUMANDATETIMEPARSER_H

#include <QDateTime>
#include <QString>
#include <QMap>

class HumanDateTimeParser
{
    public:
        static QDateTime parse(QString humanDateTime, QDateTime base = QDateTime::currentDateTime());

    private:
        enum class ElementType
        {
            // undefined
            Undefined,

            // fix times
            Now, Yesterday, Tomorrow,

            // control
            PlusAlias,

            // ranges
            Next, Last,

            // date parts
            Year, Month, Week, Day, Hour, Minute, Second,

            // weekdays
            Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday,

            // months
            January, Februrary, March, April, May, June, July, August, September, October, November, December
        };

        static QMap<QString, ElementType> elementAliases;
        static QList<QString> dateFormats;
        static QList<QString> timeFormats;
};

#endif // HUMANDATETIMEPARSER_H
