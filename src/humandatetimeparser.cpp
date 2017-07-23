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
        bool relativeTime = isInt && (element.at(0) == '+' || element.at(0) == '-');
        bool relativeTimeReset = true;
        if(isInt) {
            if(dateTimeParts.isEmpty()) return QDateTime();
            element = dateTimeParts.takeFirst();
        }

        // try to get element type
        ElementType type = elementAliases.value(element, ElementType::Undefined);

        // parse: Date/Time Formats (begin with integer!)
        if(type == ElementType::Undefined && element.begin()->isDigit()) {
            bool timeFormat = element.contains(":");
            for(QString& format : timeFormat ? HumanDateTimeParser::timeFormats : HumanDateTimeParser::dateFormats) {
                // parse: Time Format
                if(timeFormat) {
                    QTime time = QTime::fromString(element, format);
                    if(!time.isNull()) {
                        base.setTime(time);
                        break;
                    }
                }

                // parse: Date Format
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

        // Parse Error
        if(type == ElementType::Undefined || (type == ElementType::Skip && dateTimeParts.isEmpty())) return QDateTime();

        // parse: Now
        if(type == ElementType::Now) return QDateTime::currentDateTime();

        // skip entry (without error!)
        if(type == ElementType::Skip) continue;

        // parse: next|last {Element}
        if((type == ElementType::Next || type == ElementType::Last) && !dateTimeParts.isEmpty()) {
            isInt = true;
            relativeTimeReset = false;
            intNumber = type == ElementType::Next ? 1 : -1;
            type = elementAliases.value(dateTimeParts.takeFirst(), ElementType::Undefined);
        }

        // parse: [1|-1] {Monday,Tuesday...}
        if(type >= ElementType::Monday && type <= ElementType::Sunday) {
            int dayOfWeekCurrent = base.date().dayOfWeek();
            int dayOfWeekTarget = ((int)type - (int)ElementType::Monday) + 1;
            int daysToTarget = intNumber == 0 ? dayOfWeekTarget - dayOfWeekCurrent :
                               intNumber  > 0 ? (7 - dayOfWeekCurrent) + dayOfWeekTarget :
                               intNumber  < 0 ? -(qMax(dayOfWeekCurrent, dayOfWeekTarget) - qMin(dayOfWeekCurrent, dayOfWeekTarget) ?: 7) : 0;
            base = base.addDays(daysToTarget);
            base.setTime(QTime());
            continue;
        }

        // parse: [+][day] {Januar,Febrary...} [Year]
        if(type >= ElementType::January && type <= ElementType::December) {
            int day = isInt ? intNumber : 1;
            int month = ((int)type - (int)ElementType::January) + 1;
            int year = dateTimeParts.isEmpty() || !dateTimeParts.first().at(0).isDigit() ? 0 : dateTimeParts.first().toInt(&isInt);
            if(year && isInt) {
                if(year < 100) year += 2000;
                dateTimeParts.takeFirst();
            }
            base.setDate(QDate(year && isInt ? year : base.date().year(), month, day));
            base.setTime(QTime());
            continue;
        }

        // parse: [+|-][offset] {Day,Week...}
        if(isInt && type >= ElementType::Year && type <= ElementType::Second)
        {
            // parse datetime types
            if(type == ElementType::Week) {
                base = base.addDays(intNumber * 7);
            } else if(relativeTime || !relativeTimeReset) {
                if(type == ElementType::Year)   base = base.addYears(intNumber);
                if(type == ElementType::Month)  base = base.addMonths(intNumber);
                if(type == ElementType::Day)    base = base.addDays(intNumber);
                if(type == ElementType::Hour)   base = base.addSecs(intNumber * 3600);
                if(type == ElementType::Minute) base = base.addSecs(intNumber * 60);
                if(type == ElementType::Second) base = base.addSecs(intNumber);
            } else if(relativeTimeReset) {
                if(type == ElementType::Year)   base = QDateTime(QDate(intNumber < 100 ? 2000 + intNumber : intNumber, 1, 1), QTime());
                if(type == ElementType::Month)  base = QDateTime(QDate(base.date().year(), intNumber, 1), QTime());
                if(type == ElementType::Day)    base = QDateTime(QDate(base.date().year(), base.date().month(), intNumber), QTime());
                if(type == ElementType::Hour)   base.setTime(QTime(intNumber, 0, 0));
                if(type == ElementType::Minute) base.setTime(QTime(base.time().hour(), intNumber, 0));
                if(type == ElementType::Second) base.setTime(QTime(base.time().hour(), base.time().minute(), intNumber));
            }
            if(!relativeTimeReset) {
                if(type == ElementType::Year)   base = QDateTime(QDate(base.date().year(), 1, 1), QTime());
                if(type == ElementType::Month)  base = QDateTime(QDate(base.date().year(), base.date().month(), 1), QTime());
                if(type == ElementType::Day)    base = QDateTime(QDate(base.date().year(), base.date().month(), base.date().day()), QTime());
                if(type == ElementType::Hour)   base.setTime(QTime(base.time().hour(), 0, 0));
                if(type == ElementType::Minute) base.setTime(QTime(base.time().hour(), base.time().minute(), 0));
            }
            continue;
        }

        // parse: tomorrow|yesterday
        if(type == ElementType::Yesterday || type == ElementType::Tomorrow) {
            base = base.addDays(type == ElementType::Yesterday ? -1 : 1);
            base.setTime(QTime());
            continue;
        }

        // otherwise we have an error
        return QDateTime();
    }

    // error occours
    return base;
}
