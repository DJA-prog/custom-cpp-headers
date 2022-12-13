#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
// #include <unistd.h>
// #include <fcntl.h>
#include <time.h>

#pragma once

struct dirent *d;
DIR *dr;

std::vector<std::string> getFilesList(std::string path)
{
    std::vector<std::string> files;
    dr = opendir(path.c_str());
    if (dr != NULL)
    {
        for (d = readdir(dr); d != NULL; d = readdir(dr))
        {
            std::string filename = (std::string)d->d_name;
            if (d->d_type == DT_REG)
                if (filename != "." && filename != "..")
                    files.push_back(filename);
        }
        closedir(dr);
    }
    else
        printf("Error Could not open: %s\n", path.c_str());
    return files;
}

std::vector<std::string> getDirList(std::string path)
{
    std::vector<std::string> files;
    dr = opendir(path.c_str());
    if (dr != NULL)
    {
        for (d = readdir(dr); d != NULL; d = readdir(dr))
        {
            std::string filename = (std::string)d->d_name;
            if (d->d_type == DT_DIR)
                if (filename != "." && filename != "..")
                    files.push_back(filename);
        }
        closedir(dr);
    }
    else
        printf("Error Could not open: %s\n", path.c_str());
    return files;
}

std::vector<std::string> getDirContentList(std::string path)
{
    std::vector<std::string> files;
    dr = opendir(path.c_str());
    if (dr != NULL)
    {
        for (d = readdir(dr); d != NULL; d = readdir(dr))
        {
            std::string filename = (std::string)d->d_name;
            if (filename != "." && filename != "..")
                files.push_back(filename);
        }
        closedir(dr);
    }
    else
        printf("Error Could not open: %s\n", path.c_str());
    return files;
}

int getFileSize(std::string path)
{
    struct stat sb{};
    if (!stat(path.c_str(), &sb))
        return (int) sb.st_size;
    else
        perror("stat");

    return -1;
}

int getDirContentSize(std::string path)
{
    if (path.rfind('/') != path.length() - 1)
        path += '/';
    int contentSize = 0;
    for (std::string file : getDirContentList(path))
    {
        contentSize += getFileSize(path + file);
    }

    return contentSize;
}

// YYYY-MM-DD HH:MM:SS
std::string getFileLastMod(std::string path)
{
    std::string yearStr, monthStr, dayStr, hourStr, minuteStr, secondStr;
    struct stat sb{};
    struct tm *timeinfo;
    if (!stat(path.c_str(), &sb))
    {
        timeinfo = localtime(&sb.st_mtime);
        // return asctime(timeinfo);
        size_t year = timeinfo->tm_year + 1900;
        yearStr = std::to_string(year);
        size_t month = timeinfo->tm_mon + 1;
        if (month < 10)
            monthStr = '0' + std::to_string(month);
        else
            monthStr = std::to_string(month);
        size_t day = timeinfo->tm_mday;
        if (day < 10)
            dayStr = '0' + std::to_string(day);
        else
            dayStr = std::to_string(day);


        size_t hour = timeinfo->tm_hour;
        if (hour < 10)
            hourStr = '0' + std::to_string(hour);
        else
            hourStr = std::to_string(hour);
        size_t minute = timeinfo->tm_min;
        if (minute < 10)
            minuteStr = '0' + std::to_string(minute);
        else
            minuteStr = std::to_string(minute);
        size_t second = timeinfo->tm_sec;
        if (second < 10)
            secondStr = '0' + std::to_string(second);
        else
            secondStr = std::to_string(second);

        return yearStr + '-' + monthStr + '-' + dayStr + ' ' + hourStr + ':' + minuteStr + ':' + secondStr;
    }
    else
        perror("stat");

    return "-1";
}

bool file_exists(std::string path)
{
    std::ifstream myfile;
    myfile.open(path);
    if (myfile)
        return true;
    else
        return false;
}

