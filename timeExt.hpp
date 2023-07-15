#ifndef TIMEEXT__HPP
#define TIMEEXT__HPP

#include <ctime>
#include <string>
#include <vector>

// YYYY-MM-DD
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

// HH:MM:SS
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

// YYYY-MM-DD HH:MM:SS
std::string getTimeStamp() // requires: getDate() getTime()
{
    return getDate() + ' ' + getTime();
}

std::string getTimeStamp_dash()
{
    std::string result = getDate() + '-' + getTime();
    std::replace(result.begin(), result.end(), ':', '-');
    return result;
}

std::vector<std::string> seperateTimeStamp(std::string timeStamp)
{
    std::vector<std::string> seperatedTimeStamp;
    seperatedTimeStamp.push_back(timeStamp.substr(0, timeStamp.find(' ')));
    seperatedTimeStamp.push_back(timeStamp.substr(timeStamp.find(' ') + 1, timeStamp.length() - timeStamp.find(' ')));
    return seperatedTimeStamp;
}

std::string convertISO8601ToDateTime(const std::string &isoTime)
{
    // Ensure the input string has the correct length
    if (isoTime.length() < 19)
    {
        // Invalid ISO 8601 time string
        std::cerr << "Invalid ISO 8601 Length" << std::endl;
        return "";
    }

    // Extract date components
    int year = std::stoi(isoTime.substr(0, 4));
    int month = std::stoi(isoTime.substr(5, 2));
    int day = std::stoi(isoTime.substr(8, 2));

    // Extract time components
    int hour = std::stoi(isoTime.substr(11, 2));
    int minute = std::stoi(isoTime.substr(14, 2));
    int second = std::stoi(isoTime.substr(17, 2));

    // Format the date and time string
    std::string dateTime = std::to_string(year) + "-" +
                           (month < 10 ? "0" + std::to_string(month) : std::to_string(month)) + "-" +
                           (day < 10 ? "0" + std::to_string(day) : std::to_string(day)) + " " +
                           (hour < 10 ? "0" + std::to_string(hour) : std::to_string(hour)) + ":" +
                           (minute < 10 ? "0" + std::to_string(minute) : std::to_string(minute)) + ":" +
                           (second < 10 ? "0" + std::to_string(second) : std::to_string(second));

    return dateTime;
}

#endif