#include "humandatetimeparser.h"

QDateTime HumanDateTimeParser::parse(QString humanDateTime, QDateTime base)
{
    // sanitize dateTime
    humanDateTime = humanDateTime.toLower();

    QStringList dateTimeParts = humanDateTime.split(' ', QString::SkipEmptyParts);
    while(!dateTimeParts.isEmpty()) {
        // simplify
        QString element = dateTimeParts.takeFirst();

        // parse: number(s)
        bool isInt;
        int intNumber = element.toInt(&isInt);
        if(isInt) {
            if(dateTimeParts.isEmpty()) return QDateTime();
            element = dateTimeParts.takeFirst();
        }

        // try to get element type
        ElementType type = elementAliases.value(element, ElementType::Undefined);

        // parse: Date/Time Formats (begin with integer!)
        if(type == ElementType::Undefined && *element.begin() >= 48 && *element.begin() <= 57) {
            // parse: TimeFormat
            bool timeFormat = element.contains(":");
            for(QString& format : timeFormat ? HumanDateTimeParser::timeFormats : HumanDateTimeParser::dateFormats) {
                if(timeFormat) {
                    QTime time = QTime::fromString(element, format);
                    if(!time.isNull()) {
                        base.setTime(time);
                        break;
                    }
                }
                else {
                    QDate date = QDate::fromString(element, format);
                    if(!date.isNull()) {
                        base.setDate(date);
                        break;
                    }
                }
            }
            continue;
        }
        if(type == ElementType::Undefined || (type == ElementType::Skip && dateTimeParts.isEmpty())) return QDateTime();
        if(type == ElementType::Now) return QDateTime::currentDateTime();
        if(type == ElementType::Skip) continue;

        // parse: \d+ {MONTH} [{Year}]
        if(isInt && type >= ElementType::January && type <= ElementType::December) {
            int year = dateTimeParts.isEmpty() ? 0 : dateTimeParts.first().toInt(&isInt);
            if(isInt && year < 100) year += 2000;
            base.setDate(QDate(isInt ? year : base.date().year(), ((int)type - (int)ElementType::January) + 1, intNumber));
            if(isInt) dateTimeParts.takeFirst();
        }

        // parse: [+|-][offset] [Day,Week...]
        else if(isInt && type >= ElementType::Year && type <= ElementType::Second) {
            if(type == ElementType::Year)   base = base.addYears(intNumber);
            if(type == ElementType::Month)  base = base.addMonths(intNumber);
            if(type == ElementType::Week)   base = base.addDays(intNumber * 7);
            if(type == ElementType::Day)    base = base.addDays(intNumber);
            if(type == ElementType::Hour)   base = base.addSecs(intNumber * 3600);
            if(type == ElementType::Minute) base = base.addSecs(intNumber * 60);
            if(type == ElementType::Second) base = base.addSecs(intNumber);
        }

        // parse: next|last [Weekday]
        else if((type == ElementType::Next || type == ElementType::Last) && !dateTimeParts.isEmpty()) {
            ElementType typeSub = elementAliases.value(dateTimeParts.takeFirst(), ElementType::Undefined);
            if(typeSub == ElementType::Undefined || typeSub < ElementType::Monday || typeSub > ElementType::Sunday) return QDateTime();

            int dayOfWeekCurrent = base.date().dayOfWeek();
            int dayOfWeekTarget = ((int)typeSub - (int)ElementType::Monday) + 1;
            int daysToTarget = type == ElementType::Next ?
                                     (7 - dayOfWeekCurrent) + dayOfWeekTarget :
                                    -(qMax(dayOfWeekCurrent, dayOfWeekTarget) - qMin(dayOfWeekCurrent, dayOfWeekTarget) ?: 7);
            base = base.addDays(daysToTarget);
        }

        // parse: tomorrow|yesterday
        else if(type == ElementType::Yesterday || type == ElementType::Tomorrow) {
            base = base.addDays(type == ElementType::Yesterday ? -1 : 1);
        }

        // otherwise we have an error
        else return QDateTime();
    }

    // error occours
    return base;
}
