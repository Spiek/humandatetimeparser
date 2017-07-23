#ifndef HDTPSETTINGS_CPP
#define HDTPSETTINGS_CPP

#include "humandatetimeparser.h"

QList<QString> HumanDateTimeParser::dateFormats = {
    // english formats
    {"yyyy-MM-dd"},
    {"yy-MM-dd"},
    {"MM-dd"},

    // german formats
    {"dd.MM.yyyy"},
    {"dd.MM.yy"},
    {"dd.MM"},
};

QList<QString> HumanDateTimeParser::timeFormats = {
    // 24-h formats
    {"hh:mm"},
    {"hh:mm:ss"},

    // 24-h formats (simplified)
    {"h:m:s"},
    {"h:m"},
};

QMap<QString, HumanDateTimeParser::ElementType> HumanDateTimeParser::elementAliases = {
    // english
    {"now",         HumanDateTimeParser::ElementType::Now},
    {"yesterday",   HumanDateTimeParser::ElementType::Yesterday},
    {"tomorrow",    HumanDateTimeParser::ElementType::Tomorrow},
    {"in",          HumanDateTimeParser::ElementType::Skip},
    {"next",        HumanDateTimeParser::ElementType::Next},
    {"last",        HumanDateTimeParser::ElementType::Last},

    {"year",        HumanDateTimeParser::ElementType::Year},
    {"years",       HumanDateTimeParser::ElementType::Year},
    {"month",       HumanDateTimeParser::ElementType::Month},
    {"months",      HumanDateTimeParser::ElementType::Month},
    {"week",        HumanDateTimeParser::ElementType::Week},
    {"weeks",       HumanDateTimeParser::ElementType::Week},
    {"day",         HumanDateTimeParser::ElementType::Day},
    {"days",        HumanDateTimeParser::ElementType::Day},
    {"hour",        HumanDateTimeParser::ElementType::Hour},
    {"hours",       HumanDateTimeParser::ElementType::Hour},
    {"minute",      HumanDateTimeParser::ElementType::Minute},
    {"minutes",     HumanDateTimeParser::ElementType::Minute},
    {"second",      HumanDateTimeParser::ElementType::Second},
    {"seconds",     HumanDateTimeParser::ElementType::Second},

    {"monday",      HumanDateTimeParser::ElementType::Monday},
    {"tuesday",     HumanDateTimeParser::ElementType::Tuesday},
    {"wednesday",   HumanDateTimeParser::ElementType::Wednesday},
    {"thursday",    HumanDateTimeParser::ElementType::Thursday},
    {"friday",      HumanDateTimeParser::ElementType::Friday},
    {"saturday",    HumanDateTimeParser::ElementType::Saturday},
    {"sunday",      HumanDateTimeParser::ElementType::Sunday},

    {"january",     HumanDateTimeParser::ElementType::January},
    {"februrary",   HumanDateTimeParser::ElementType::Februrary},
    {"march",       HumanDateTimeParser::ElementType::March},
    {"april",       HumanDateTimeParser::ElementType::April},
    {"may",         HumanDateTimeParser::ElementType::May},
    {"june",        HumanDateTimeParser::ElementType::June},
    {"july",        HumanDateTimeParser::ElementType::July},
    {"august",      HumanDateTimeParser::ElementType::August},
    {"september",   HumanDateTimeParser::ElementType::September},
    {"october",     HumanDateTimeParser::ElementType::October},
    {"november",    HumanDateTimeParser::ElementType::November},
    {"december",    HumanDateTimeParser::ElementType::December}
};

#endif // HDTPSETTINGS_CPP
