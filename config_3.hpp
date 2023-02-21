/*
This code is reading the config file line by line and storing the values in the memory, but it doesn't handle the case when the config file is changed while the program is running. To fix this, you could add a check to re-read the file if it has been modified since the last time it was read.
*/

#include <iostream>
#include <fstream>
#include <time.h>

class Config
{
private:
    std::string filename;
    std::time_t lastRead;
    std::map<std::string, std::string> settings;
    std::map<std::string, std::map<std::string, std::string>> sections;

    void readFile()
    {
        std::ifstream file(filename);
        std::string line;
        std::string currentSection;
        while (std::getline(file, line))
        {
            if (line[0] == '[')
            {
                currentSection = line.substr(1, line.length() - 2);
                sections[currentSection] = std::map<std::string, std::string>();
            }
            else if (line.find("=") != std::string::npos)
            {
                int split = line.find("=");
                std::string key = line.substr(0, split);
                std::string value = line.substr(split + 1);
                if (currentSection.empty())
                {
                    settings[key] = value;
                }
                else
                {
                    sections[currentSection][key] = value;
                }
            }
        }
        file.close();
        lastRead = std::time(nullptr);
    }

public:
    Config(std::string filename) : filename(filename)
    {
        readFile();
    }

    std::string getSetting(std::string key)
    {
        std::time_t currentTime = std::time(nullptr);
        struct stat attrib;
        stat(filename.c_str(), &attrib);
        if (currentTime - lastRead > attrib.st_mtime)
        {
            readFile();
        }
        return settings[key];
    }

    std::map<std::string, std::string> getSection(std::string key)
    {
        std::time_t currentTime = std::time(nullptr);
        struct stat attrib;
        stat(filename.c_str(), &attrib);
        if (currentTime - lastRead > attrib.st_mtime)
        {
            readFile();
        }
        return sections[key];
    }

    void updateSetting(std::string key, std::string value)
    {
        settings[key] = value;
        save();
    }

    void updateSection(std::string key, std::map<std::string, std::string> values)
    {
        sections[key] = values;
        save();
    }

    void save()
    {
        std::ofstream file(filename);
        for (const auto &[key, value] : settings)
        {
            file << key << "=" << value << std::endl;
        }
        for (const auto &[key, value] : sections)
        {
            file << "[" << key << "]" << std::endl;
            for (const auto &[skey, svalue] : value)
            {
                file << skey << "=" << svalue << std::endl;
            }
        }
        file.close();
    }
};
