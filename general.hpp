#ifndef GENERAL__HPP
#define GENERAL__HPP

#include <string>
#include <stdio.h>
#include <sstream>

#pragma once

namespace DevGeneral
{

    /* */
    std::string exec(std::string command);
    std::string zeroFill(std::string value, int digits);
    std::string zeroFill(int value, int digits);
    std::string *splitS(const std::string &subject, char delimiter);
    std::vector<std::string> split(const std::string &subject, char delimiter);
    int arraySize(std::string &arr);
    std::string insert_substring_before_extension(std::string path, std::string sub);

    /* Functions */

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

    std::string *splitS(const std::string &subject, char delimiter = ',')
    {
        std::string *result = new std::string[subject.size()];
        int count = 0;
        std::stringstream ss(subject);
        std::string token;
        while (std::getline(ss, token, delimiter))
        {
            result[count] = token;
            count++;
        }
        return result;
    }

    std::vector<std::string> split(const std::string &subject, char delimiter = ',')
    {
        std::vector<std::string> result;
        std::stringstream ss(subject);
        std::string token;
        while (std::getline(ss, token, delimiter))
        {
            result.push_back(token);
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

    std::string insert_substring_before_extension(std::string path, std::string sub)
    {
        // Find the position of the last path separator
        std::size_t last_separator_pos = path.find_last_of("/\\");

        // Find the position of the last dot in the filename
        std::size_t dot_pos = path.find_last_of(".");

        // If there is no dot or the dot comes before the last separator, append the substring to the end
        if (dot_pos == std::string::npos || dot_pos < last_separator_pos)
        {
            path.append(sub);
        }
        else
        { // Insert the substring before the extension
            path.insert(dot_pos, sub);
        }

        return path;
    }
}


#endif
