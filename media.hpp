#ifndef media__HPP
#define media__HPP

#include <string>

#include "general.hpp"

#pragma once

std::string command = "";

std::string getVideoDuration(std::string path)
{
    command = "ffprobe -i \'" + path + "\' -v quiet -show_entries format=duration -hide_banner -of default=noprint_wrappers=1:nokey=1";
    
    int duration = stoi(exec(command));
    int hours = duration / 3600;
    int minutes = (duration - (hours * 3600)) / 60;
    int seconds = duration % 60;
    std::string duration_str = zeros(hours, 2) + ':' + zeros(minutes, 2) + ':' + zeros(seconds, 2);
    return duration_str;
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

#endif