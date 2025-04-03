#ifndef FILTERS__HPP
#define FILTERS__HPP

#include <cstring>
#include <string>
#include <algorithm>
#include <regex>
#include <sstream>
#include <vector>

#pragma once

namespace DevFilters
{
    /* String */
    std::string htmlEntityToChar(const std::string &input);
    std::string removeNonNumericCharacters(std::string str);
    std::string fileNameFilter(std::string path);
    std::string webSaveFileFilter(std::string path);
    std::string comicTitleFilter(std::string filename);
    std::string comicFilenameFilter(std::string filename);
    std::string urlUnReplace(std::string url);
    std::string pathinfo(std::string url, int file_info);
    std::string imgSrc(std::string htmlTag);
    std::string addEscapeCharacters(std::string input);
    std::string compact_list(const std::vector<float> &nums);
    std::vector<std::string> unique_values(const std::vector<std::string> &v1, const std::vector<std::string> &v2);
    std::string removeWhitespace(const std::string &str);

    /* Integer */
    int hexToDec(std::string number);
    
    /* Bool */
    bool isValidURL(const std::string& url);

    /* Functions */

    std::string htmlEntityToChar(const std::string &input)
    {
        static const std::map<std::string, std::string> entityMap = {
            {"&amp;", "&"},
            {"&lt;", "<"},
            {"&gt;", ">"},
            {"&quot;", "\""},
            {"&apos;", "'"},
            {"&#039;", "'"},
            {"&nbsp;", " "},
            {"&period;", "."},
            // Add more HTML entities and their replacements here
        };

        std::string output = input;

        // Replace each HTML entity with its corresponding character
        for (const auto &entry : entityMap)
        {
            size_t pos = output.find(entry.first);
            while (pos != std::string::npos)
            {
                output.replace(pos, entry.first.length(), entry.second);
                pos = output.find(entry.first, pos + 1);
            }
        }

        return output;
    }

    std::string removeNonNumericCharacters(std::string str)
    {
        const std::regex pattern("[^0-9]");
        return regex_replace(str, pattern, "");
    }

    std::string fileNameFilter(std::string path)
    {
    fileNameFilterTop:
        // remove spaces from the beginning
        while (!path.empty() && path[0] == ' ')
            path = path.substr(1, path.length() - 1);

        // remove spaces from the end
        while (!path.empty() && path[path.length() - 1] == ' ')
            path = path.substr(0, path.length() - 1);

        // remove dash from the beginning
        while (!path.empty() && path[0] == '-')
            path = path.substr(1, path.length() - 1);

        // remove dash from the end
        while (!path.empty() && path[path.length() - 1] == '-')
            path = path.substr(0, path.length() - 1);

        // remove single quotes and double quotes
        path.erase(std::remove_if(path.begin(), path.end(),
                                  [](char c)
                                  { return c == '\'' || c == '"'; }),
                   path.end());

        // repeat from the beginning if spaces or dash are at the beginning or end
        if (!path.empty() && (path[path.length() - 1] == ' ' || path[0] == '-' || path[0] == ' '))
            goto fileNameFilterTop;

        return path;
    }

    std::string webSaveFileFilter(std::string path)
    {
        if (path.rfind("_files") != std::string::npos)
            return fileNameFilter(path.substr(0, path.rfind('_')));

        if (path.rfind(".html") != std::string::npos)
            return fileNameFilter(path.substr(0, path.rfind('.')));

        return fileNameFilter(path);
    }

    std::string comicTitleFilter(std::string filename)
    {
        int limitCounter = 0;
        while (filename.find('[') != std::string::npos)
        {
            int SquareBracketStart = filename.find('[');
            int SquareBracketEnd = filename.find(']');
            if (SquareBracketEnd == std::string::npos)
            {
                break;
            }
            else
            {
                if (SquareBracketStart == 0)
                    filename = filename.substr(SquareBracketEnd + 1, filename.length() - SquareBracketEnd - 1);
                else
                    filename = filename.substr(0, SquareBracketStart) + filename.substr(SquareBracketEnd + 1, filename.length() - SquareBracketEnd - 1);
            }
            if (limitCounter > 10)
            {
                break;
            }
            limitCounter++;
        }

        std::replace(filename.begin(), filename.end(), '\'', '_');

        return webSaveFileFilter(filename);
    }

    std::string comicFilenameFilter(std::string filename)
    {
        filename = webSaveFileFilter(filename);
        std::replace(filename.begin(), filename.end(), '\'', '_');

        if (filename.find("[Eng]"))
            filename = filename.substr(0, filename.find("[Eng]") - 1) + filename.substr(filename.find("[Eng]") + 5, filename.length() - filename.find("[Eng]") - 5);

        return filename;
    }

    int hexToDec(std::string number)
    {
        int len = number.length();
        char num[len + 1];
        std::strcpy(num, number.c_str());
        int base = 1;
        int temp = 0;
        for (int i = len - 1; i >= 0; i--)
        {
            if (num[i] >= '0' && num[i] <= '9')
            {
                temp += (num[i] - 48) * base;
                base = base * 16;
            }
            else if (num[i] >= 'A' && num[i] <= 'F')
            {
                temp += (num[i] - 55) * base;
                base = base * 16;
            }
        }
        return temp;
    }

    std::string urlUnReplace(std::string url)
    {
        while (url.find('%') != std::string::npos)
        {
            int percentage = url.find('%');
            int percentageVal = hexToDec(url.substr(percentage + 1, 2));
            char replacement = char(percentageVal);
            if (percentage == std::string::npos)
                return url;
            if (percentage == 0)
                url = replacement + url.substr(3, url.length() - 3);
            else
                url = url.substr(0, percentage) + replacement + url.substr(percentage + 3, url.length() - percentage - 3);
        }
        std::string find = "&amp;";
        int findLen = find.length();
        while (url.find(find) != std::string::npos)
        {
            int percentage = url.find(find);
            char replacement = '&';
            if (percentage == std::string::npos)
                return url;
            if (percentage == 0)
                url = replacement + url.substr(findLen, url.length() - findLen);
            else
                url = url.substr(0, percentage) + replacement + url.substr(percentage + findLen, url.length() - percentage - findLen);
        }

        return url;
    }

    // 0:filepath ; 1:filename ; 2:basename ; 3: file_extention ; 4: parent_directory
    std::string pathinfo(std::string url, int file_info)
    {
        int dot_find;
        int url_length = url.length();
        std::string filepath, filename, basename, extention, parent_dir;
        if (url.rfind('.') == std::string::npos)
        {
            dot_find = url_length;
            extention = "";
        }
        else
        {
            dot_find = url.rfind('.');
            extention = url.substr(dot_find + 1, url_length - dot_find - 1);
        }

        if (url.rfind('/') == std::string::npos)
        {
            basename = url.substr(0, dot_find);
            filename = url;
            filepath = ".";
        }
        else
        {
            basename = url.substr(url.rfind('/') + 1, dot_find - url.rfind('/') - 1);
            filename = url.substr(url.rfind('/') + 1, url_length - url.rfind('/') - 1);
            filepath = url.substr(0, url.rfind('/'));
            parent_dir = url.substr(url.rfind('/', url.rfind('/') - 1) + 1, url.rfind('/') - url.rfind('/', url.rfind('/') - 1) - 1);
        }

        switch (file_info)
        {
        case 0:
            return filepath;
            break;

        case 1:
            return filename;
            break;

        case 2:
            return basename;
            break;

        case 3:
            return extention;
            break;

        default:
            return parent_dir;
            break;
        }
    }

    std::string imgSrc(std::string htmlTag)
    {
        return htmlTag.substr(htmlTag.find("src") + 5, (htmlTag.find('"', htmlTag.find("src") + 5)) - (htmlTag.find("src") + 5));
    }

    std::string addEscapeCharacters(std::string input)
    {
        std::string output = "";
        for (int i = 0; i < input.length(); i++)
        {
            char c = input[i];
            if (c == '\'' || c == '\"' || c == '`')
            {
                output += "\\";
            }
            output += c;
        }
        return output;
    }

    std::string compact_list(const std::vector<float> &nums)
    {
        std::stringstream ss;
        std::string result;
        bool in_range = false;
        float prev = -1.0;
        for (float num : nums)
        {
            if (prev != -1.0 && num != prev + 1.0)
            {
                if (in_range)
                {
                    ss << prev << ", ";
                    in_range = false;
                }
                ss << num << ", ";
            }
            else
            {
                if (!in_range)
                {
                    ss << prev << "-";
                    in_range = true;
                }
            }
            prev = num;
        }
        if (in_range)
        {
            ss << prev;
        }
        else
        {
            ss.seekp(-2, ss.cur);
            ss << " ";
        }
        result = ss.str();
        return result;
    }

    /*
    Use:
        std::vector<int> nums = { 236, 237, 238, 239, 240, 243, 244, 245, 246 };
        std::cout << compact_list(nums) << std::endl; // Output: 236-240, 243-246
    */

    // The unique_values function takes two string vectors v1 and v2, and returns a new vector containing all the unique values in v1 (i.e., values that are not present in v2).
    std::vector<std::string> unique_values(const std::vector<std::string> &v1, const std::vector<std::string> &v2)
    {
        std::vector<std::string> result;
        for (const std::string &s : v1)
        {
            if (std::find(v2.begin(), v2.end(), s) == v2.end())
            {
                result.push_back(s);
            }
        }
        return result;
    }

    // remove leading and trailing whitespace
    std::string removeWhitespace(const std::string &str)
    {
        // Find the first non-whitespace character from the beginning
        size_t start = str.find_first_not_of(" \t\r\n");

        // If the string is all whitespace, return an empty string
        if (start == std::string::npos)
        {
            return "";
        }

        // Find the last non-whitespace character from the end
        size_t end = str.find_last_not_of(" \t\r\n");

        // Extract the trimmed substring
        return str.substr(start, end - start + 1);
    }

    bool isValidURL(const std::string& url) {
        // Define a regex pattern for a basic URL validation
        const std::regex urlPattern(R"((http|https):\/\/([\w.-]+)\.([a-z]{2,6})([\w.,@?^=%&:/~+#-]*[\w@?^=%&/~+#-])?)");

        // Use regex_match to validate the URL
        return std::regex_match(url, urlPattern);
    }
}


#endif
