# Configuration 'conf', 'ini'


# config.hpp

### libraries
- stdio
- string
- fstream
- algorithm

### Structure
- class config
- class config // constructor

#### public

1. Configuration file state
- `void stateCheck()`

2. Append setting and value string
- `void insert(std::string setting, std::string value)`

3. Append setting and value character
- `void insert(std::string setting, char value)`

4. Append setting and value integer
- `void insert(std::string setting, int value)`

5. Append setting and value double
- `void insert(std::string setting, double value)`

6. Update setting name string
- `bool updateSetting(std::string setting_old, std::string setting_new)`

7. Update setting value string
- `bool updateValue(std::string setting, std::string value)`

8. Update setting value integer
- `bool updateValue(std::string setting, int value)`

9. Remove setting
- `bool removeSetting(std::string setting)`

10. Get line value
- `std::string getLineValue(std::string line)`

11. Get line
- `std::string getLine(long long pointer_pos, char delimiter = '\n')`

12. Get setting line
- `std::string getSettingLine(std::string setting)`

13. Get setting value string
- `std::string getValue(std::string setting)`

14. Get setting value boolean
- `bool getBoolValue(std::string setting)`

15. Check if setting exists
- `bool setting_exists(std::string setting)`

16. Close configuration
- `void closeConf()`

17. Set debugging
- `void setDebug()`

18. End debugging
- `void endDebug()`

19. Get debugging state
- `bool getDebug()`

#### private
- `std::string config_path;`
- `std::fstream confFile;`
- `long long lineNumber = 0;`
- `bool emptyConfig = false;`
- `bool confDebug = false;`

1. Open configuration file
- `bool configOpen()`

2. Close configuration file
- `void configClose()`

3. Append new line to end of configuration line
- `void appendNewLine()`

4. Update function // opper == 0 updateval; opper == 1 updateSet; opper == 2 deleteSet
- `bool update(std::string setting, std::string value, int opper = 0)`

# config_2.hpp

### libraries
- iosdtream
- fstream
- sstream
- map
- vector
- ctime

### Structure
- class ConfigFile
- ConfigFile(std::string filename) // constructor
- ~ConfigFile() // destructor

#### public

1. Check if file exists
- `bool fileExists(const std::string &filePath)`

2. Save config file
- `bool save()`

3. Check if config section exists
- `bool sectionExists(const std::string &section)`

4. Check if setting exists
- `bool settingExists(std::string section, std::string setting)`

5. Get setting as string
- `std::string getString(const std::string &section, const std::string &setting)`

6. Get setting as integer
- `int getInt(std::string section, std::string option, int defaultValue = 0)`

7. Get setting as float
- `float getFloat(std::string section, std::string option, float defaultValue = 0.0)`

8. Get setting as boolean
- `bool getBool(const std::string &section, const std::string &option)`

9. Update setting
- `bool updateSetting(std::string section, std::string key, std::string value)`

10. Update Section
- `bool updateSection(std::string name, std::map<std::string, std::string> values)`

11. Append Section
- `bool appendSection(std::string name, std::map<std::string, std::string> values)`

12. Insert Option
- `bool insertOption(std::string section, std::string key, std::string value)`

13. Create Section
- `void createSection(std::string sectionName)`

14. Check if Option exists
- `bool optionExists(std::string sectionName, std::string optionName)`

#### private
- `std::string filename;`
- `std::time_t lastRead;`
- `std::map<std::string, std::string> settings;`
- `std::map<std::string, std::map<std::string, std::string>> sections;`
- `std::ifstream file; // Declare file as a member variable`


# config_3.hpp

### libraries

### Structure

#### public

1. 

#### private
