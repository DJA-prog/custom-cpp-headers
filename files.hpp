#ifndef FILES__HPP
#define FILES__HPP

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
#include <cmath>

#pragma once

struct dirent *d;
DIR *dr;

// Only list files in path
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

// Only list directories in path
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

// List all files in path
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

// List all files in path with given extension
std::vector<std::string> getDirFilesListOfFormat(std::string path, std::string format)
{
    std::vector<std::string> files;
    dr = opendir(path.c_str());
    if (dr != NULL)
    {
        for (d = readdir(dr); d != NULL; d = readdir(dr))
        {
            std::string filename = (std::string)d->d_name;
            if (filename != "." && filename != ".." && filename.find('.') != 0 && d->d_type == DT_REG)
                if (filename.substr(filename.rfind('.') + 1, filename.length() - filename.rfind('.') - 1) == format)
                    files.push_back(filename);
        }
        closedir(dr);
    }
    else
        printf("Error Could not open: %s\n", path.c_str());
    return files;
}

// return bytes size of file
int getFileSize(std::string path)
{
    struct stat sb{};
    if (!stat(path.c_str(), &sb))
        return (int) sb.st_size;
    else
        perror("stat");

    return -1;
}

// return bytes size of all files in path
int getDirContentSize(const std::string path)
{
    
    int contentSize = 0;
    for (std::string file : getDirContentList(path))
    {
    	if (path.rfind('/') != path.length() - 1)
        	contentSize += getFileSize(path + '/' + file);
        else
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

// returns the number of days since the specified mod date
int getDaysLastMod(std::string path)
{
    struct stat sb{};
    struct tm *timeinfo;

    time_t now = time(0);
    struct tm *currentTime = localtime(&now);
    int today = currentTime->tm_mday + round((currentTime->tm_mon + 1) * 30.4375) + round((currentTime->tm_year + 1900) * 365.25);

    if (!stat(path.c_str(), &sb))
    {
        timeinfo = localtime(&sb.st_mtime);
        int days = timeinfo->tm_mday + round((timeinfo->tm_mon + 1) * 30.4375) + round((timeinfo->tm_year + 1900) * 365.25);

        return today - days;
    }
    else
        perror("stat");

    return -1;
}

// return true if file exists
bool file_exists(std::string path)
{
    struct stat sb;
    if (stat(path.c_str(), &sb) == 0 && !(sb.st_mode & S_IFDIR))
        return true;

    return false;
}

// return true if directory exists
bool dir_exists(std::string& path)
{
    struct stat sb;
    if (stat(path.c_str(), &sb) == 0)
        return true;

    return false;
}

// create directory returns 0 if successful
int makeDir(std::string path)
{
    if(!dir_exists(path))
    {
        int status = mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); // gives read, write, and execute permissions to the owner, the group and others
        if (status == 0)
        	return 0;
       	else
       		return status;
    }
    else
        return 1;
}

// remove all directories in path
int removeDirInPath(std::string path)
{
    std::vector<std::string> dirList = getDirList(path);
    for (std::string dir : dirList)
        std::remove((path + "/" + dir).c_str());
    return 0;
}

// count all files in path with the given extension
int countFilesOfFormat(std::string path, std::string format)
{
    size_t filesOfFormat = 0;
    struct dirent *d;
    DIR *dr;
    dr = opendir(path.c_str());
    if (dr != NULL)
    {
        for (d = readdir(dr); d != NULL; d = readdir(dr))
        {
            std::string filename = (std::string)d->d_name;
            if (filename != "." && filename != ".." && filename.find('.') != 0 && d->d_type == DT_REG)
                if (filename.substr(filename.rfind('.') + 1, filename.length() - filename.rfind('.') - 1) == format)
                    filesOfFormat++;
        }
        closedir(dr);
    }
    else
        printf("Can't open %s\n", path.c_str());
    return filesOfFormat;
}

#endif
