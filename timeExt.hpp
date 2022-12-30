#ifndef TIMEEXT__HPP
#define TIMEEXT__HPP

#include <time.h>
#include <string>
#include <vector>

std::string getDate()
{
    std::string month, day;
    time_t now = time(0);
    tm *ltm = localtime(&now);

    if (1 + ltm->tm_mon < 10)
        month = '0' + std::to_string(1 + ltm->tm_mon);
    else
        month = std::to_string(1 + ltm->tm_mon);

    if (1 + ltm->tm_mday < 10)
        day = '0' + std::to_string(ltm->tm_mday);
    else
        day = std::to_string(ltm->tm_mday);

    std::string date = std::to_string(1900 + ltm->tm_year) + '-' + month + '-' + day;

    return date;
}

std::string getTime()
{
    std::string hour, minute, second;
    time_t now = time(0);
    tm *ltm = localtime(&now);

    if (ltm->tm_hour < 10)
        hour = '0' + std::to_string(ltm->tm_hour);
    else
        hour = std::to_string(ltm->tm_hour);

    if (ltm->tm_min < 10)
        minute = '0' + std::to_string(ltm->tm_min);
    else
        minute = std::to_string(ltm->tm_min);

    if (ltm->tm_sec < 10)
        second = '0' + std::to_string(ltm->tm_sec);
    else
        second = std::to_string(ltm->tm_sec);

    std::string time = hour + ':' + minute + ':' + second;

    return time;
}

std::string getTimeStamp() // requires: getDate() getTime()
{
    return getDate() + ' ' + getTime();
}

std::vector<std::string> seperateTimeStamp(std::string timeStamp)
{
    std::vector<std::string> seperatedTimeStamp;
    seperatedTimeStamp.push_back(timeStamp.substr(0, timeStamp.find(' ')));
    seperatedTimeStamp.push_back(timeStamp.substr(timeStamp.find(' ') + 1, timeStamp.length() - timeStamp.find(' ')));
    return seperatedTimeStamp;
}

#endif