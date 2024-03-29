#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <ctime>

class ConfigFile
{
private:
    std::string filename;
    std::time_t lastRead;
    std::map<std::string, std::string> settings;
    std::map<std::string, std::map<std::string, std::string>> sections;
    std::ifstream file; // Declare file as a member variable

public:
    ConfigFile(std::string filename)
    {
        this->filename = filename;
        file.open(filename); // Open the file
        if (file.is_open())
        {
            std::string line;
            std::string currentSection = "";
            while (std::getline(file, line))
            {
                // Check if line is a section header
                if (line[0] == '[')
                {
                    currentSection = line.substr(1, line.size() - 2);
                }
                else if (line.find("=") != std::string::npos)
                {
                    std::string key = line.substr(0, line.find("="));
                    std::string value = line.substr(line.find("=") + 1);
                    sections[currentSection][key] = value;
                }
            }
            file.close();
        }
    }

    ~ConfigFile()
    {
        // No need to check if the file is open here
        file.close();
    }

    bool fileExists(const std::string &filePath)
    {
        std::ifstream file(filePath);
        return file.good();
    }

    bool save()
    {
        std::ofstream file(filename);
        if (file.is_open())
        {
            for (auto &section : sections)
            {
                file << "[" << section.first << "]" << std::endl;
                for (auto &setting : section.second)
                {
                    file << setting.first << "=" << setting.second << std::endl;
                }
            }
            if (file.fail())
            {
                std::cout << "Error: Failed to write to file " << filename << "." << std::endl;
                return false;
            }
            file.close();
            return true;
        }
        else
        {
            std::cerr << "Unable to open file " << filename << " for saving" << std::endl;
            return false;
        }
    }

    bool sectionExists(const std::string &section)
    {
        return sections.count(section) != 0;
    }

    bool settingExists(std::string section, std::string setting)
    {
        if (sectionExists(section))
        {
            return sections[section].find(setting) != sections[section].end();
        }
        return false;
    }

    std::string getString(const std::string &section, const std::string &setting)
    {
        // Check if the section exists
        if (sections.count(section) == 0)
        {
            std::cout << "Error: Section '" << section << "' does not exist" << std::endl;
            return "";
        }

        // Check if the setting exists
        if (sections[section].count(setting) == 0)
        {
            std::cout << "Error: Setting '" << setting << "' does not exist in section '" << section << "'" << std::endl;
            return "";
        }

        // Return the value of the setting
        return sections[section][setting];
    }

    int getInt(std::string section, std::string option, int defaultValue = 0)
    {
        try
        {
            return std::stoi(getString(section, option));
        }
        catch (std::exception &e)
        {
            return defaultValue;
        }
    }

    float getFloat(std::string section, std::string option, float defaultValue = 0.0)
    {
        try
        {
            return std::stof(getString(section, option));
        }
        catch (std::exception &e)
        {
            return defaultValue;
        }
    }

    bool getBool(const std::string &section, const std::string &option)
    {
        std::string value = getString(section, option);
        std::istringstream iss(value);
        bool b;
        iss >> std::boolalpha >> b;
        return b;
    }

    bool updateSetting(std::string section, std::string key, std::string value)
    {
        if (!sectionExists(section))
            return false;
        sections[section][key] = value;
        save();
        // Check if the file was saved correctly
        std::ifstream file(filename);
        if (file.good())
        {
            file.close(); // Close the file
            return true;
        }
        else
        {
            std::cout << "Error: Could not save changes to file" << std::endl;
            return false;
        }
    }

    // continued from here

    bool updateSection(std::string name, std::map<std::string, std::string> values)
    {
        if (!sectionExists(name))
            return false;
        sections[name] = values;
        save();
        // Check if the file was saved correctly
        std::ifstream file(filename);
        if (file.good())
        {
            file.close(); // Close the file
            return true;
        }
        else
        {
            std::cout << "Error: Could not save changes to file" << std::endl;
            return false;
        }
    }

    bool appendSection(std::string name, std::map<std::string, std::string> values)
    {
        if (sectionExists(name))
            return false;
        sections[name] = values;
        save();
        // Check if the file was saved correctly
        std::ifstream file(filename);
        if (file.good())
        {
            file.close(); // Close the file
            return true;
        }
        else
        {
            std::cout << "Error: Could not save changes to file" << std::endl;
            return false;
        }
    }

    bool insertOption(std::string section, std::string key, std::string value)
    {
        if (!sectionExists(section))
            return false;
        sections[section][key] = value;
        save();
        // Check if the file was saved correctly
        std::ifstream file(filename);
        if (file.good())
        {
            file.close(); // Close the file
            return true;
        }
        else
        {
            std::cout << "Error: Could not save changes to file" << std::endl;
            return false;
        }
    }

    void createSection(std::string sectionName)
    {
        if (!sectionExists(sectionName))
        {
            std::ofstream file(filename, std::ios::app);
            if (file.good())
            {
                file << "[" << sectionName << "]" << std::endl;
                file.close();
            }
            else
            {
                std::cout << "Error creating section " << sectionName << std::endl;
            }
        }
    }

    // Helper function to check if a section exists
    // bool sectionExists(std::string sectionName)
    // {
    //     for (auto &line : fileContent)
    //     {
    //         if (line.find("[" + sectionName + "]") != std::string::npos)
    //         {
    //             return true;
    //         }
    //     }
    //     return false;
    // }

    // Helper function to check if an option exists in a specific section
    bool optionExists(std::string sectionName, std::string optionName)
    {
        bool sectionFound = false;
        file.open(filename); // Open the file
        if (file.is_open())
        {
            std::string line;
            while (std::getline(file, line))
            {
                if (line.find("[" + sectionName + "]") != std::string::npos)
                {
                    sectionFound = true;
                }
                else if (sectionFound && line.find(optionName) != std::string::npos)
                {
                    file.close(); // Close the file
                    return true;
                }
            }
            file.close(); // Close the file
        }
        return false;
    }
};
