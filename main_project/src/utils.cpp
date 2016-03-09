//
// Created by leind on 08/03/16.
//

#include "utils.h"

double utils::diferentialIncrease(double past, double current)
{
    return ((current - past) / past) * 100;
}

struct tm* utils::getNow()
{
    time_t t = time(0);   // get time now
    return localtime(&t);
}

std::string utils::dateToString(struct tm* date)
{
    int year = (date->tm_year + 1900);
    int month = (date->tm_mon + 1);
    int day = date->tm_mday;

    std::string result = "";
    result = result + std::to_string(year);
    result = result + "-";
    result = result + std::to_string(month);
    result = result + "-";
    result = result + std::to_string(day);

    return result;
}

// Adds number of days to current date
struct tm* utils::addDays(struct tm* date, int days)
{
    struct tm* newDate = date;
    const time_t ONE_DAY = 24 * 60 * 60 ;

    // Seconds since start of epoch
    time_t date_seconds = mktime(newDate) + (days * ONE_DAY) ;

    // Use localtime because mktime converts to UTC so may change date
    *newDate = *localtime(&date_seconds);

    return newDate;
}
