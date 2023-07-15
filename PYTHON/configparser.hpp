#include <iostream>
#include <fstream>
#include <map>
#include <sstream>

class ConfigParser
{
private:
    std::string filename;
    std::map<std::string, std::map<std::string, std::string>> sections;

public:
    ConfigParser(std::string filename) : filename(filename)
    {
        parseFile();
    }

    void parseFile()
    {
        std::ifstream file(filename);
        std::string line;
        std::string currentSection;
        while (std::getline(file, line))
        {
            if (line[0] == '[' && line[line.length() - 1] == ']')
            {
                currentSection = line.substr(1, line.length() - 2);
                sections[currentSection] = std::map<std::string, std::string>();
            }
            else if (line.find("=") != std::string::npos)
            {
                int split = line.find("=");
                std::string key = line.substr(0, split);
                std::string value = line.substr(split + 1);
                sections[currentSection][key] = value;
            }
        }
        file.close();
    }

    std::string getValue(std::string section, std::string key, std::string defaultValue = "")
    {
        if (sections.count(section) > 0 && sections[section].count(key) > 0)
        {
            return sections[section][key];
        }
        return defaultValue;
    }

    void setValue(std::string section, std::string key, std::string value)
    {
        sections[section][key] = value;
    }

    void save()
    {
        std::ofstream file(filename);
        for (const auto &section : sections)
        {
            file << "[" << section.first << "]" << std::endl;
            for (const auto &keyValuePair : section.second)
            {
                file << keyValuePair.first << "=" << keyValuePair.second << std::endl;
            }
        }
        file.close();
    }
};

int main()
{
    ConfigParser config("config.ini");

    // Read values from the config file
    std::string username = config.getValue("User", "Username", "default_user");
    std::string password = config.getValue("User", "Password", "default_password");
    std::string port = config.getValue("Server", "Port", "8080");

    std::cout << "Username: " << username << std::endl;
    std::cout << "Password: " << password << std::endl;
    std::cout << "Port: " << port << std::endl;

    // Update values in the config file
    config.setValue("User", "Username", "new_username");
    config.setValue("User", "Password", "new_password");
    config.setValue("Server", "Port", "9090");

    // Save the changes to the config file
    config.save();

    return 0;
}
