/*

FIX: update cause extra lines at end of file

*/


#ifndef CONFIG__HPP
#define CONFIG__HPP

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
        if (!setting_exists(setting))
        {
            appendNewLine();
            confFile.clear();
            confFile << setting << '=' << value;
            emptyConfig = false;
        }
        else
            printf("Duplicate setting\n");
    }
    void insert(std::string setting, char value)
    {
        if (!setting_exists(setting))
        {
            appendNewLine();
            confFile.clear();
            confFile << setting << '=' << value;
            emptyConfig = false;
        }
        else
            printf("Duplicate setting\n");
    }
    void insert(std::string setting, int value)
    {
        if (!setting_exists(setting))
        {
            appendNewLine();
            confFile.clear();
            confFile << setting << '=' << value;
            emptyConfig = false;
        }
        else
            printf("Duplicate setting\n");
    }
    void insert(std::string setting, double value)
    {
        if (!setting_exists(setting))
        {
            appendNewLine();
            confFile.clear();
            confFile << setting << '=' << value;
            emptyConfig = false;
        }
        else
            printf("Duplicate setting\n");
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

        // length of extract line
        long long size = 0;

        // get length of file
        confFile.seekg(0, std::fstream::end); // set pointer position to end of file
        long long len = confFile.tellg(); // get file length (1 - last character)

        // exit when pointer position exceeds file length
        if (pointer_pos > len)
            return "";

        // set pointer position to target position
        confFile.seekp(pointer_pos);
        // ignore all characters until delimiter or end of file
        // while (confFile.get() != delimiter);
        charGetLoop:
        if (!confFile.eof()) // not end of file
            if (confFile.get() != delimiter)
                goto charGetLoop;

        // get length of target string
        if (confFile.eof())
            size = len - pointer_pos + 1;
        else
            size = (long long)confFile.tellp() - pointer_pos;

        // set pointer position to target position
        confFile.clear();
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
            if (lineNumber <= 0) // prevent infinite loop
                break;
            if (line.find(setting.c_str(), 0, line.find('=')) != std::string::npos)
                break;
            else
                line = "-1";
        }
        return line;
    }
    std::string getValue(std::string setting)
    {
        if (setting_exists(setting))
        {
            std::string line = getSettingLine(setting);

            if (line == "" || line.find('=') != std::string::npos)
                return line.substr(line.find('=') + 1, line.length() - line.find('=') - 2);
            return line;
        }
        return "";
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

    void setDebug()
    {
        confDebug = true;
    }
    void endDebug()
    {
        confDebug = false;
    }
    bool getDebug()
    {
        return confDebug;
    }

private:
    std::string config_path;
    std::fstream confFile;
    long long lineNumber = 0;
    bool emptyConfig = false;
    bool confDebug = false;

    bool configOpen()
    {
        confFile.open(config_path, std::fstream::in | std::fstream::out | std::fstream::app);
        if (confFile.peek() == std::ifstream::traits_type::eof())
        {
            emptyConfig = true;
            confFile.clear();
        }
            
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
            confFile.clear();
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
        // close config file before updating
        configClose();

        bool update_success = true;
        bool update_skip = false;
        std::string line;
        std::string configTemp_path = "./." + config_path.substr(config_path.rfind('/') + 1, config_path.length() - config_path.rfind('/') - 1);
        std::ifstream mainConf(config_path.c_str());

        // check if update needs to skip
        if (mainConf.is_open() && opper != 1)
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
                if (confDebug)
                    printf("Ready to copy\n");

                while (getline(mainConf, line))
                {
                    if (line.find(setting.c_str(), 0, line.find('=')) != std::string::npos)
                    {
                        if (opper == 0)
                        {
                            if (confDebug)
                                printf("setVal: %s=%s\n", setting.c_str(), value.c_str());
                            confCopy << setting << '=' << value;
                        }
                        else if (opper == 1)
                        {
                            std::string val = getLineValue(line);
                            if (confDebug)
                                printf("setSett: %s=%s\n", value.c_str(), val.c_str());
                            confCopy << value << '=' << val;
                        }
                        else if (opper == 2)
                        {
                            if (confDebug)
                                printf("delSet: %s=%s\n", setting.c_str(), value.c_str());
                        }
                        else
                        {
                            printf("Error: Opperation out of bound\n");
                            confCopy << line;
                        }
                    }
                    else
                    {
                        if (confDebug)
                            printf("stdCpy: %s\n", line.c_str());
                        confCopy << line;
                    }
                    confCopy << '\n';
                }
                if (confDebug)
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