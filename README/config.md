# Config Class
The config class is a C++ class that allows you to easily read, write, update and delete key-value pairs in a configuration file. The configuration file format is a simple text file, with each line representing a key-value pair. The class has been designed to be easy to use, and requires only basic C++ knowledge to get started.

## Libraries Used
- stdio.h
- string
- fstream
- algorithm

## Capabilities
The config class provides the following capabilities:

### Constructor
- `config(std::string path_to_conf)`: creates an instance of the config class, and takes the path to the configuration file as an argument. If the file does not exist, the class will create it.

### Insertion
- `void insert(std::string setting, std::string value)`: inserts a new key-value pair into the configuration file.
- `void insert(std::string setting, char value)`: overloads the above function to allow inserting character values.
- `void insert(std::string setting, int value)`: overloads the above function to allow inserting integer values.
- `void insert(std::string setting, double value)`: overloads the above function to allow inserting double values.

### Updating
- `bool updateSetting(std::string setting_old, std::string setting_new)`: updates the name of an existing key.
- `bool updateValue(std::string setting, std::string value)`: updates the value of an existing key.
- `bool updateValue(std::string setting, int value)`: overloads the above function to allow updating integer values.

### Deletion
- `bool removeSetting(std::string setting)`: removes an existing key-value pair.

### Retrieval
- `std::string getValue(std::string setting)`: retrieves the value of a key-value pair.
- `std::string getSettingLine(std::string setting)`: retrieves the entire line containing the specified key-value pair.
- `std::string getLine(long long pointer_pos, char delimiter = '\n')`: retrieves a line of text from the configuration file based on a given pointer position and delimiter.
- `std::string getLineValue(std::string line)`: retrieves the value from a given line.

### Other
- `void stateCheck()`: checks the state of the configuration file, e.g. if it is good or bad.

## Capabilities Summary
The config class allows you to perform various operations on a configuration file, including:
- Opening and reading from a configuration file
- Checking the state of the configuration file
- Inserting a new setting with its corresponding value
- Updating an existing setting name or value
- Removing an existing setting
- Retrieving the line number of a setting
- Retrieving the value of a setting

## How to use in code
Here are some examples of how to use the config class in your code:

~~~~~
#include "config.hpp"
#include <iostream>

int main() {
    config myConfig("config.cfg");

    // Insert a new setting
    myConfig.insert("Setting1", "Value1");

    // Update an existing setting's value
    myConfig.updateValue("Setting1", "NewValue1");

    // Remove an existing setting
    myConfig.removeSetting("Setting1");

    // Get the value of a setting
    std::string value = myConfig.getValue("Setting1");

    // Check the state of the config file
    myConfig.stateCheck();

    return 0;
}
~~~~~

In this example, the config class is used to open a configuration file called config.cfg. It then inserts a new setting called "Setting1" with the value "Value1". Next, it updates the value of "Setting1" to "NewValue1" and then removes the "Setting1" setting entirely. Finally, it retrieves the value of "Setting1" and checks the state of the configuration file.
