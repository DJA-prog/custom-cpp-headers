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

std::string* split(const std::string& subject, char delimiter = ',') {
    std::string* result = new std::string[subject.size()];
    int count = 0;
    std::stringstream ss(subject);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        result[count] = token;
        count++;
    }
    return result;
}

/*
std::string* result = split("hello,world,goodbye", ',');
int size = sizeof(result) / sizeof(result[0]);
for (int i = 0; i < size; i++) {
    std::cout << result[i] << std::endl;
}
*/

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
