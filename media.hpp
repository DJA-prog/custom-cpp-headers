#ifndef MEDIA__HPP
#define MEDIA__HPP

#include <string>

#include "general.hpp"

#pragma once

std::string command = "";

// HH:MM:SS
std::string getVideoDuration(std::string path)
{
    command = "ffprobe -i \'" + path + "\' -v quiet -show_entries format=duration -hide_banner -of default=noprint_wrappers=1:nokey=1";
    
    int duration = stoi(exec(command));
    int hours = duration / 3600;
    int minutes = (duration - (hours * 3600)) / 60;
    int seconds = duration % 60;
    std::string duration_str = zeroFill(hours, 2) + ':' + zeroFill(minutes, 2) + ':' + zeroFill(seconds, 2);
    return duration_str;
}

int getVideoLength(std::string path)
{
    command = "ffprobe -i \'" + path + "\' -v quiet -show_entries format=duration -hide_banner -of default=noprint_wrappers=1:nokey=1";
    return stoi(exec(command));
}

int * getVideoDimentions(std::string path)
{
    static int vidDimentions[2];

    command = "ffprobe -i \'" + path + "\' -v error -select_streams v:0 -show_entries stream=height -of csv=s=x:p=0";
    vidDimentions[0] = stoi(exec(command));

    command = "ffprobe -i \'" + path + "\' -v error -select_streams v:0 -show_entries stream=width -of csv=s=x:p=0";
    vidDimentions[1] = stoi(exec(command));

    return vidDimentions;
}

/*
USAGE:
    int* videoDim = getVideoDimentions(videoPath);
    //use the array
    delete [] videoDim; // free the memory after using
*/

// bool is_empty(std::ifstream &pFile)
// {
//     return pFile.peek() == std::ifstream::traits_type::eof();
// }

#endif