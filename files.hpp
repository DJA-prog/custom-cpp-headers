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
#include <iomanip>

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

int getFileSize(std::string path)
{
    struct stat sb{};
    if (!stat(path.c_str(), &sb))
        return (int) sb.st_size;
    else
        perror("stat");

    return -1;
}

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
std::string getFileCreationDate(const std::string &filePath)
{
    struct stat attr;
    if (stat(filePath.c_str(), &attr) == 0)
    {
        std::tm *time = std::gmtime(&attr.st_ctime);
        std::ostringstream ss;
        ss << std::put_time(time, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
    else
    {
        throw std::runtime_error("Unable to get file creation date for file " + filePath);
    }
}

// YYYY-MM-DD HH:MM:SS
std::string getFileLastMod(std::string path)
{
    struct stat sb;
    if (!stat(path.c_str(), &sb))
    {
        auto *timeinfo = localtime(&sb.st_mtime);
        std::ostringstream ss;
        ss << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
    else
    {
        perror("stat");
        return "-1";
    }
}

int getDaysLastMod(std::string path)
{
    struct stat sb;
    if (!stat(path.c_str(), &sb))
    {
        std::time_t now = std::time(nullptr);
        std::tm *currentTime = std::localtime(&now);
        std::tm *fileModTime = std::localtime(&sb.st_mtime);
        auto currentDay = currentTime->tm_mday + currentTime->tm_mon * 30 + currentTime->tm_year * 365;
        auto fileModDay = fileModTime->tm_mday + fileModTime->tm_mon * 30 + fileModTime->tm_year * 365;
        return currentDay - fileModDay;
    }
    else
    {
        perror("stat");
        return -1;
    }
}

bool file_exists(std::string path)
{
    struct stat sb;
    if (stat(path.c_str(), &sb) == 0 && !(sb.st_mode & S_IFDIR))
        return true;

    return false;
}

bool dir_exists(std::string& path)
{
    struct stat sb;
    if (stat(path.c_str(), &sb) == 0)
        return true;

    return false;
}

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

// bool remove_directory_recursive(const std::string &dir_path_str)
// {
//     std::filesystem::path dir_path(dir_path_str);
//     try
//     {
//         std::filesystem::remove_all(dir_path);
//         return true;
//     }
//     catch (const std::filesystem::filesystem_error &e)
//     {
//         std::cerr << e.what() << std::endl;
//     }
//     return false;
// }

bool copyFile(const std::string &src_path, const std::string &dst_path)
{
    std::ifstream src(src_path, std::ios::binary);
    std::ofstream dst(dst_path, std::ios::binary);
    if (!src.is_open() || !dst.is_open())
    {
        return false;
    }
    dst << src.rdbuf();
    src.close();
    dst.close();
    return true;
}

bool moveFile(const std::string &src_path, const std::string &dst_path)
{
    if (rename(src_path.c_str(), dst_path.c_str()) == 0)
        return true;
    return false;
}

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
