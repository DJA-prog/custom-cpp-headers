# ALPHANUM

Sort Vector v
std::sort(v.begin(), v.end(), doj::alphanum_less<std::string>());

################################

# config.hpp

## Libs
    stdio.h
    string
    fstream
    algorithm

class config
    config(std::string path_to_conf)

## PUBLIC PROPERTIES

#### Create a configuration
void insert(std::string setting, std::string value)
void insert(std::string setting, char &value)
void insert(std::string setting, int value)
void insert(std::string setting, double value)

#### Update existing setting
void updateSetting(std::string setting_old, std::string setting_new)

#### Update existing configuration
void updateValue(std::string setting, std::string value)
void updateValue(std::string setting, int value)

#### Delete existing configuration
void removeSetting(std::string setting)

#### Return whole configuration string
std::string getSettingLine(std::string setting)
std::string getLine(long long pointer_pos, char delimiter = '\n')

#### Get setting value
std::string getValue(std::string setting)
bool getBoolValue(std::string setting)

#### get value from setting line
std::string getLineValue(std::string line)

#### Miscellaneous
void closeConf()

## PRIVATE PROPERTIES:
bool configOpen()

void configClose()

void appendNewLine()

void update(std::string setting, std::string value, int opper = 0)
opper 0: set value
opper 1: set setting
oppen 2: delete setting

################################

# logger.hpp

## Libs
    string
    fstream
    iostream

class Logger
    Logger(std::string path_to_log)

## PUBLIC PROPERTIES

#### Append data to current line
void append(std::string data)
void append(char data)
void appendCode(int code)

#### Miscellaneous
void endLine()
void logClose()

## PRIVATE PROPERTIES
std::string exec(std::string command)
bool log_exists(std::string path)

################################

# sqlwriter.hpp

## Libs
    iostream
    string
    fstream

class SQLWriter
    SQLWriter(std::string path_to_sql, std::string database, std::string* fields, int field_count)

## PUBLIC PROPERTIES

#### append data to row
void appendField(std::string data)
void appendField(char data)
void appendField(int data)
void appendField(unsigned int data)

#### Miscellaneous
void endRow()
void sqlClose()

## PUBLIC PROPERTIES
void endSql()
bool sql_exists(std::string path)

################################

# files.hpp

## Libs
    stdio
    string
    vector
    algorithm
    fstream
    dirent
    sys/stat.h
    time.h

## Functions

#### get list
std::vector<std::string> getFilesList(std::string path)
std::vector<std::string> getDirList(std::string path)

#### get list of files in directory
std::vector<std::string> getDirContentList(std::string path)

#### get list of files in directory with format
std::vector<std::string> getDirFilesListOfFormat(std::string path, std::string format)

#### get size
int getFileSize(std::string path)
int getDirContentSize(std::string path)

#### YYYY-MM-DD HH:MM:SS
std::string getFileLastMod(std::string path)

#### existing
bool file_exists(std::string path)
bool dir_exists(std::string path)

#### count dir content with format
int countFilesOfFormat(std::string path, std::string format)

################################

# general.hpp

## Libs
    string
    stdio.h

## Functions

#### execute system commands and return result
std::string exec(std::string command)

#### fill in zero as prefix
std::string zeroFill(std::string value, int digits)
std::string zeroFill(int value, int digits)

#### split string into string array by delimiter
std::string *split(std::string subject, char delimiter = ',')

#### count number of array elements in string array
int arraySize(std::string &arr)

#### count number of array elements in int array
#### Comment out for C++ 11 but works in 14
int arraySize(int (&arr))

################################

# media.hpp

## Libs
    string
    general.hpp

## Functions

#### get video duration HHH:MM:SS
std::string getVideoDuration(std::string path)

#### get video dimensions (width, height)
int * getVideoDimentions(std::string path)

################################

# filters.hpp

## Libs
    cstring
    string
    algorithm

## Functions

#### file name filters
std::string fileNameFilter(std::string path)
std::string webSaveFileFilter(std::string path)
std::string comicTitleFilter(std::string filename)
std::string comicFilenameFilter(std::string filename)

#### convert
int hexToDec(std::string number)

#### return file path parts
std::string pathinfo(std::url, int file_info)
file_info 0: filepath
file_info 1: filename
file_info 2: basename
file_info 3: extension
file_info 4: parent_dir

#### return source of image tag
std::string imgSrc(std::string htmlTag)

################################

# curl.hpp [TESTING]

## Libs
    string
    curl/curl.h

## Functions

#### used by curl not for user
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)

#### insert url to page and get string of result
std::string * curl(std::string url)
