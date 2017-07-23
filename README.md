# Qt HumanDateTimeParser

A easy to use Qt library which converts human datetime inputs to QDateTime like [strtotime](http://php.net/manual/en/function.strtotime.php) in php.

----------

### Possible Formats 

The following primary formats are possible ([] = optional; {} = manditory):

Function | Description | Example
:-------- | :-------  | :-------
[+][digit] {Janary, February... December} [Year]|Date with month name|10 December 2017
+[digit] {Year, Month, Week, Day, Hour, Minute, Second}|Relative Date/Timepart|+2 hours
[digit] {Year, Month, Week, Day, Hour, Minute, Second}|Absolut Date/Timepart|2 hours
{next\|last} {Year, Month, Week, Day, Hour, Minute, Second, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday, January, Februrary, March, April, May, June, July, August, September, October, November, December}|Next or last occurrence of ...|next Month
yesterday\|tomorrow|Start of yesterday or tomorrow|yesterday
dd.mm.yyyy\|yyyy-mm-dd...|Fix DateTime|2014-05-01

##### Note: all formats are also useable in a chain!


### Example

Here an example (which is also available in the [repo](https://github.com/Spiek/humandatetimeparser/blob/master/example/main.cpp)):

```c++
#include <QCoreApplication>
#include <QDebug>
#include "humandatetimeparser.h"

#define PrettyPrint(a,datetime) \
    qDebug("%s %s", \
            qPrintable(HumanDateTimeParser::parse(a, currentDateTime).toString("yyyy-MM-dd hh:mm:ss")), a)

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // get current time
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // day related
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

    // relative dates/times
    PrettyPrint("day", currentDateTime);
    PrettyPrint("1 year", currentDateTime);
    PrettyPrint("+1 month", currentDateTime);
    PrettyPrint("-1 day", currentDateTime);
    PrettyPrint("next year", currentDateTime);

    // fix dates/times
    PrettyPrint("10 September 2000", currentDateTime);
    PrettyPrint("10.05.2017", currentDateTime);
    PrettyPrint("2017-05-10 14:04", currentDateTime);

    // multiple commands in a chain
    PrettyPrint("2017-05-10 14:04 +2 days +2 seconds 12:04", currentDateTime);
    PrettyPrint("1 day +1 week +2 days +4 hours +2 seconds", currentDateTime);

    return a.exec();
}
```
Prints following results:
Date | Time | String
:-------- | :------- | :-------
2017-07-23|19:10:28|now
2017-07-22|00:00:00|yesterday
2017-07-24|00:00:00|tomorrow
2017-07-17|00:00:00|week
2017-07-16|19:10:28|-1 week
2017-07-24|00:00:00|1 week
2017-07-10|00:00:00|last week
2017-07-29|00:00:00|next saturday
2017-07-20|00:00:00|last Thursday
2017-07-01|00:00:00|day
2001-01-01|00:00:00|1 year
2017-08-23|19:10:28|+1 month
2017-07-22|19:10:28|-1 day
2018-01-01|00:00:00|next year
2000-09-10|00:00:00|10 September 2000
2017-05-10|19:10:28|10.05.2017
2017-05-10|14:04:28|2017-05-10 14:04
2017-05-12|12:04:30|2017-05-10 14:04 +2 days +2 seconds 12:04
2017-07-10|04:00:02|1 day +1 week +2 days +4 hours +2 seconds

### Licence
The [humandatetimeparser licence](https://github.com/Spiek/humandatetimeparser/blob/master/LICENCE) is a modified version of the [LGPL](http://www.gnu.org/licenses/lgpl.html) licence, with a static linking exception.
