#ifndef GENERAL__HPP
#define GENERAL__HPP

#include <string>
#include <stdio.h>

#pragma once

std::string exec(std::string command)
{
    char buffer[128];
    std::string result = "";

    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        return "popen failed!";
    }

    while (!feof(pipe))
    {
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }

    pclose(pipe);
    return result;
}

std::string zeroFill(std::string value, int digits)
{
    std::string val;
    size_t x = digits - value.length();
    for (size_t i = 0; i < x; i++)
    {
        val = '0' + value;
    }
    return val;
}

std::string zeroFill(int value, int digits)
{
    std::string val = std::to_string(value);
    size_t x = digits - val.length();
    for (size_t i = 0; i < x; i++)
    {
        val = '0' + val;
    }
    return val;
}

std::string *split(std::string subject, char delimiter = ',')
{
    size_t n = std::count(subject.begin(), subject.end(), delimiter);
    std::string values[n + 1];

    int pos = 0;
    for (size_t i = 0; i < n + 1; i++)
    {
        values[i] = subject.substr(pos, subject.find(delimiter, pos) - pos);
        pos = subject.find(delimiter, pos) + 1;
    }
}

int arraySize(std::string &arr)
{
    return sizeof(arr) / sizeof(arr[0]);
}

// Comment out for C++ 11

// int arraySize(int (&arr))
// {
//     return sizeof(arr) / sizeof(arr[0]);
// }

#endif