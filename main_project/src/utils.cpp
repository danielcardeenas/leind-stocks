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

// Adds number of months to current date
struct tm* utils::addMonths(struct tm* date, int months)
{
    struct tm* newDate = date;
    const time_t ONE_MONTH = 24 * 60 * 60 * 30 ;

    // Seconds since start of epoch
    time_t date_seconds = mktime(newDate) + (months * ONE_MONTH) ;

    // Use localtime because mktime converts to UTC so may change date
    *newDate = *localtime(&date_seconds);

    return newDate;
}

std::string utils::buildMajorHoldersQuery(std::string stockSymbol)
{
    std::string query = "https://api.import.io/store/connector/b4c82ce2-a2de-4460-9c98-74f214d2bb46/_query?input=webpage/url:https%3A%2F%2Ffinance.yahoo.com%2Fq%2Fmh%3Fs%3D"
    + stockSymbol + "&&_apikey=506841ffeb29443699a16cfc39f7de4553744839a0d2766b1bc06bc73f091186389edc8f697c1b8b0f9e29437c6c55344b84300b84ae94ab1a62e892a20e165b68f0e9de7708acfa79f768f79bd3756e";

    return query;
}
