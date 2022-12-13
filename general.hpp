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

std::string zeros(std::string value, int digits)
{
    std::string val;
    size_t x = digits - value.length();
    for (size_t i = 0; i < x; i++)
    {
        val = '0' + value;
    }
    return val;
}

std::string zeros(int value, int digits)
{
    std::string val = std::to_string(value);
    size_t x = digits - val.length();
    for (size_t i = 0; i < x; i++)
    {
        val = '0' + val;
    }
    return val;
}

int arraySize(auto &arr)
{
    return sizeof(arr) / sizeof(arr[0]);
}
