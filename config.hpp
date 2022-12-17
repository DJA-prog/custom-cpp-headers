/*

FIX: prevent duplicate insert
ADD: emptyConfig flag (check if file is created to add flag and test each time)

*/


#ifndef config__HPP
#define config__HPP

#include <stdio.h>
#include <string>
#include <fstream>
#include <algorithm>

#pragma once

class config
{
public:
    // constructor
    config(std::string path_to_conf)
    {
        config_path = path_to_conf;
        if (!configOpen())
            printf("Unable to open config file");
    }

    void stateCheck()
    {
        printf("Checking config file state\n");
        if (confFile.good())
            printf("Config file is good");
        if (confFile.bad())
            printf("Config file is bad");
        if (confFile.eof())
            printf("Config file is end of file");
        if (confFile.fail())
            printf("Config file failed");
        printf("\n");
    }

    void insert(std::string setting, std::string value)
    {
        appendNewLine();
        confFile << setting << '=' << value;
    }
    void insert(std::string setting, char value)
    {
        appendNewLine();
        confFile << setting << '=' << value;
    }
    void insert(std::string setting, int value)
    {
        appendNewLine();
        confFile << setting << '=' << value;
    }
    void insert(std::string setting, double value)
    {
        appendNewLine();
        confFile << setting << '=' << value;
    }

    bool updateSetting(std::string setting_old, std::string setting_new)
    {
        return update(setting_old, setting_new, 1);
    }

    bool updateValue(std::string setting, std::string value)
    {
        return update(setting, value, 0);
    }

    bool updateValue(std::string setting, int value)
    {
        return update(setting, std::to_string(value), 0);
    }

    bool removeSetting(std::string setting)
    {
        return update(setting, "", 2);
    }

    std::string getLineValue(std::string line)
    {
        if (line.find('=') != std::string::npos)
            return line.substr(line.find('=') + 1, line.length() - line.find('=') - 1);
        return line;
    }

    std::string getLine(long long pointer_pos, char delimiter = '\n')
    {
        if (emptyConfig)
            return "";
        // output line
        std::string returnLine;

        // pointer pos in stream
        long long size = 0;

        // get length of file
        confFile.seekg(0, std::ios::end); // set pointer position to end of file
        long long len = confFile.tellg(); // get pointer position
        
        // exit when pointer position exceeds file length
        if (pointer_pos >= len)
            return "";

        std::cout << "End position: " << len << std::endl;

        // set pointer position to target position
        confFile.seekp(pointer_pos);
        // ignore all characters until delimiter or end of file
        // while (confFile.get() != delimiter);
        charGetLoop:
        if (!confFile.eof()) // not end of file
            if (confFile.get() != delimiter)
                goto charGetLoop;

        std::cout << "passed delimiter loop" << std::endl;
        // get length of target string
        size = (long long)confFile.tellp() - pointer_pos;

        // set pointer position to target position
        confFile.seekp(pointer_pos);

        // storage
        char line[size];

        // write characters from pointer position of length (size) characters to char array line
        confFile.get(line, size);

        // write char array line to string returnLine
        for (long long i = 0; i < size; i++)
            returnLine += line[i];
        
        // write current pointer position to class variable lineNumber
        lineNumber = (long long)confFile.tellp() + 1;
        if (lineNumber >= len)
            lineNumber = -1;

        return returnLine;
    }

    std::string getSettingLine(std::string setting)
    {
        std::string line = "";
        if (emptyConfig)
            return line;

        lineNumber = 0;

        while (lineNumber != -1)
        {
            line = getLine(lineNumber);
            printf("%s\n", line.c_str());
            if (line.find(setting.c_str(), 0, line.find('=')) != std::string::npos)
                break;
            else
                line = "-1";
        }
        return line;
    }

    std::string getValue(std::string setting)
    {
        std::string line = getSettingLine(setting);
        if (line == "" || line.find('=') != std::string::npos)
           return line.substr(line.find('=') + 1, line.length() - line.find('=') - 2);
        return line;
    }

    bool getBoolValue(std::string setting)
    {
        std::string booleanValue = getValue(setting);
        std::transform(booleanValue.begin(), booleanValue.end(), booleanValue.begin(), ::tolower);
        if (booleanValue == "true")
            return true;
        return false;
    }

    bool setting_exists(std::string setting)
    {
        if (emptyConfig)
            return false;
        confFile.seekg(0, confFile.beg);

        std::string line;
        while (getline(confFile, line)) // getline is fstream native
            if (line.find(setting) != std::string::npos)
                return true;

        return false;
    }

    void closeConf()
    {
        configClose();
    }

private:
    std::string config_path;
    std::fstream confFile;
    long long lineNumber = 0;
    bool emptyConfig = false;

    bool configOpen()
    {
        confFile.open(config_path, std::fstream::in | std::fstream::out | std::fstream::app);
        if (confFile.peek() == std::ifstream::traits_type::eof())
            emptyConfig = true;
        return confFile.is_open();
    }

    void configClose()
    {
        confFile.close();
    }

    void appendNewLine()
    {
        if (!emptyConfig)
        {
            confFile.seekg(0, confFile.end);
            confFile.unget();
            if (confFile.get() != '\n')
                confFile.put('\n');
        }
    }

    // opper == 0 updateval; opper == 1 updateSet; opper == 2 deleteSet
    bool update(std::string setting, std::string value, int opper = 0)
    {
        if (opper < 0 || opper > 2)
        {
            printf("Opperation out of range");
            return false;
        }
        configClose();

        bool update_success = true;
        bool update_skip = false;
        std::string line;
        std::string configTemp_path = "./." + config_path.substr(config_path.rfind('/') + 1, config_path.length() - config_path.rfind('/') - 1);
        std::ifstream mainConf(config_path.c_str());

        if (mainConf.is_open())
            if (opper == 1)
                while (getline(mainConf, line))
                    if (line.find(setting) != std::string::npos)
                        update_skip = true;

        if (!update_skip)
        {
            mainConf.seekg(0, confFile.beg);
            std::ofstream confCopy(configTemp_path.c_str());
            if (mainConf && confCopy)
            {
                printf("Ready to copy\n");

                while (getline(mainConf, line))
                {
                    if (line.find(setting.c_str(), 0, line.find('=')) != std::string::npos)
                    {
                        if (opper == 0)
                        {
                            printf("setVal: %s=%s\n", setting.c_str(), value.c_str());
                            confCopy << setting << '=' << value << '\n';
                        }
                        else if (opper == 1)
                        {
                            printf("setSett: %s=%s\n", value.c_str(), getLineValue(line).c_str());
                            confCopy << value << '=' << getLineValue(line) << '\n';
                        }
                        else if (opper == 2)
                        {
                            printf("delSet: %s=%s\n", setting.c_str(), value.c_str());
                        }
                        else
                        {
                            printf("Error: Opperation out of bound\n");
                            confCopy << line << '\n';
                        }
                    }
                    else
                    {
                        printf("stdCpy: %s\n", line.c_str());
                        confCopy << line << '\n';
                    }
                }
                printf("Done!\n");
            }
            else
            {
                printf("Could not open config files: %s; %s", config_path.c_str(), configTemp_path.c_str());
                update_success = false;
            }
            mainConf.close();
            confCopy.close();
            remove(config_path.c_str());
            rename(configTemp_path.c_str(), config_path.c_str());
        }
        else
        {
            mainConf.close();
            printf("Duplicate configuration\n");
            update_success = false;
        }

        configOpen();
        return update_success;
    }
};

#endif