### I do not claim ownership of files in the downloaded directory.

# ALPHANUM.hpp

## Libs
    cassert
    functional
    string
    sstream
    cctype
    iostream
    typeinfo

## Functions
// std::vector<std::string> v;
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

#### Print config stream state
stateCheck()

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

#### get value from setting line
std::string getLineValue(std::string line)

#### Return whole configuration string
std::string getLine(long long pointer_pos, char delimiter = '\n')
std::string getSettingLine(std::string setting)

#### Get setting value
std::string getValue(std::string setting)
bool getBoolValue(std::string setting)

#### Miscellaneous
bool setting_exists(std::string setting)
void closeConf()

#### Debug
void setDebug()
void endDebug()
bool getDebug()

## PRIVATE PROPERTIES:
bool configOpen()

void configClose()

void appendNewLine()

void update(std::string setting, std::string value, int opper = 0)
opper 0: set value
opper 1: set setting
oppen 2: delete setting

################################

# csv.hpp

## Libs
    iostream
    fstream
    sstream
    vector

class csv
    CSV(std::string filename) : m_filename(filename) {}

## PUBLIC PROPERTIES
void setSkipHeader(bool skip)

#### Function to read the CSV file
std::vector<std::vector<std::string>> read()

#### Function to write to the CSV file
void write(std::vector<std::vector<std::string>> &data)

#### Function to update the CSV file
void update(int row, int col, std::string value)

#### Function to find the CSV file
void find(std::string value)

## PRIVATE PROPERTIES
std::string m_filename;
bool hasHeader = true;

################################

# curl.hpp [TESTING]

## Compile
g++ curl_example.cpp -o curl_example -lcurl

## Libs
    string
    curl/curl.h

## Functions

#### best use (readBuffer is global variable)
std::string readBuffer;
curl(std::string url)

#### insert url to page and get string of result
std::string * curl(std::string url)

#### used by curl not for user
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)

################################

# curl_wrapper.h

## Libs
    iostream
    curl/curl.h

class CurlWrapper
    CurlWrapper()
    ~CurlWrapper()

## PUBLIC PROPERTIES
std::string fetchUrl(const std::string &url)

## PRIVATE PROPERTIES
CURL *curl_;
static size_t writeCallback(char *ptr, size_t size, size_t nmemb, void *userdata)

## COMPILE
g++ -o main main.cpp curl_wrapper.cpp -lcurl

## USAGE
\#include "curl_wrapper.h"

int main() {
    CurlWrapper curl;
    std::string response = curl.fetchUrl("https://www.example.com");
    std::cout << response << std::endl;
    return 0;
}

################################

# EmailSender.h

## Libs
    string
    curl/curl.h

class EmailSender

## PUBLIC PROPERTIES
static void sendEmail(const std::string &from, const std::string &to, const std::string &subject, const std::string &message);

## COMPILE
g++ -o main main.cpp curl_wrapper.cpp -lcurl

## USAGE
\#include "EmailSender.h"

std::string from = "sender@example.com";
std::string to = "receiver@example.com";
std::string subject = "example subject";
std::string message = "example message";

EmailSender::sendEmail(from, to, subject, message);

################################

# EmailSender_Poco.h

## Libs
    Poco/Net/MailMessage.h
    Poco/Net/MailRecipient.h
    Poco/Net/SMTPClientSession.h
    Poco/Net/NetException.h
    iostream

class EmailSender
## PUBLIC PROPERTIES
static void sendEmail(const std::string &from, const std::string &to, const std::string &subject, const std::string &message);

## COMPILE
g++ -std=c++11 -o myprogram myprogram.cpp -lPocoNet -lPocoFoundation -lPocoUtil

## USAGE
\#include "EmailSender_Poco.h"

std::string from = "sender@gmail.com";
std::string to = "receiver@example.com";
std::string subject = "example subject";
std::string message = "example message";

EmailSender::sendEmail(from, to, subject, message);

## LINUX INSTALL
sudo sh -c "echo deb http://repo.poco.ws/debian stable main > /etc/apt/sources.list.d/poco.list"
wget -O - http://repo.poco.ws/debian/apt-key.asc | sudo apt-key add -
sudo apt update
sudo apt install libpoco-dev

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
    cmath

struct dirent *d;
DIR *dr;

## Functions

#### get list
std::vector<std::string> getFilesList(std::string path)
std::vector<std::string> getDirList(std::string path)

#### get list of files in directory
std::vector<std::string> getDirContentList(std::string path)

#### get list of files in directory with format
std::vector<std::string> getDirFilesListOfFormat(std::string path, std::string format)

#### get size (size depend ont individual OS)
int getFileSize(std::string path)
int getDirContentSize(std::string path)

#### YYYY-MM-DD HH:MM:SS
std::string getFileLastMod(std::string path)

#### Miscellaneous
int getDaysLastMod(std::string path)
int makeDir(std::string path) // gives read, write, and execute permissions to the owner, the group and others

#### existing
bool file_exists(std::string path)
bool dir_exists(std::string path)

#### count dir content with format
int countFilesOfFormat(std::string path, std::string format)

################################

# filters.hpp

## Libs
    cstring
    string
    algorithm
    regex

## Functions

#### file name filters
std::string fileNameFilter(std::string path)
std::string webSaveFileFilter(std::string path)
std::string comicTitleFilter(std::string filename)
std::string comicFilenameFilter(std::string filename)

#### general string filters
std::string removeNonNumericCharacters(std::string str)

#### convert
int hexToDec(std::string number)

#### return file path parts
std::string pathinfo(std::url, int file_info)
file_info 0: filepath
file_info 1: filename
file_info 2: basename
file_info 3: extension
file_info 4: parent_dir

#### Miscellaneous
std::string urlUnReplace(std::string url)
std::string addEscapeCharacters(std::string input)
std::string imgSrc(std::string htmlTag)

################################

# ftp_download.h

## Libs
    string
    curl/curl.h

class Ftp
    Ftp()
    ~Ftp()

## PUBLIC PROPERTIES
bool checkFileExists(const std::string &url, const std::string &username, const std::string &password)
bool download(const std::string &url, const std::string &username, const std::string &password, const std::string &filepath)

## PRIVATE PROPERTIES
size_t Ftp::write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)

## COMPILE
g++ -o main main.cpp curl_wrapper.cpp -lcurl

## USAGE
\#include "ftp_download.h"

int main(){
    Ftp ftp;
    if (ftp.download("ftp://ftp.example.com/report.txt","username","password","/path/to/save/report.txt"))
        printf("Downloaded successfully\n");
    else
        printf("Failed to download\n");
    return 0;
}

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
std::string* split(const std::string& subject, char delimiter = ',')

#### count number of array elements in string array
int arraySize(std::string &arr)

#### count number of array elements in int array
##### Comment out for C++ 11 but works in 14
int arraySize(int (&arr))

################################

# GithubApi.h

## Libs
    string
    curl/curl.h

class GithubApi
    GithubApi()

## PUBLIC PROPERTIES
bool retrieveData(const std::string &url, const std::string &username, const std::string &password, std::string &response);

## PRIVATE PROPERTIES
CURL *curl_;
static size_t writeCallback(char *data, size_t size, size_t nmemb, void *userdata);

## COMPILE
g++ -o main main.cpp -lcurl

## USAGE
\#include "GithubApi.h"

int main() {
    std::string token = "<YOUR_PRIVATE_TOKEN>";
    std::string url = "https://api.github.com/users/<USERNAME>";
    std::string response;

    GithubApi api;
    bool success = api.retrieveData(url, token, response);

    if (success) {
        // Do something with the response
        std::cout << response << std::endl;
    } else {
        // Handle the error
        std::cout << "Request failed" << std::endl;
    }
    return 0;
}

################################

# GithubApi_Token.h

## Libs
    string
    curl/curl.h

class GithubApi
    GithubApi()

## PUBLIC PROPERTIES
bool retrieveData(const std::string &url, const std::string &token, std::string &response);

## PRIVATE PROPERTIES
CURL *curl_;
static size_t writeCallback(char *data, size_t size, size_t nmemb, void *userdata);

## COMPILE
g++ -o main main.cpp -lcurl

## USAGE
\#include "GithubApi_Token.h"

int main() {
    std::string token = "<YOUR_PRIVATE_TOKEN>";
    std::string url = "https://api.github.com/users/<USERNAME>";
    std::string response;

    GithubApi api;
    bool success = api.retrieveData(url, token, response);

    if (success) {
        // Do something with the response
        std::cout << response << std::endl;
    } else {
        // Handle the error
        std::cout << "Request failed" << std::endl;
    }
    return 0;
}

################################

# GitHubDownloader.h

## Libs
    string
    fstream
    curl/curl.h

class GitHubDownloader

## PUBLIC PROPERTIES
static std::string downloadFile(const std::string &url, const std::string &filename);

## COMPILE
g++ -o main main.cpp -lcurl

## USAGE
\#include "GitHubDownloader.h"

std::string url = "https://api.github.com/repos/OWNER/REPO/contents/path/to/file?access_token=YOUR_TOKEN";
std::string filename = "path/to/save/file/on/disk.extension"
std::string error = GitHubDownloader::downloadFile(url, filename);
if (error.empty()) {
    // success
} else {
    // an error occurred, error message is in the 'error' variable
}

################################

# logger.hpp

## Libs
    string
    fstream
    iostream

class Logger
    Logger(std::string path_to_log)

## PUBLIC PROPERTIES
std::string logFile;

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

# media.hpp

## Libs
    string
    general.hpp

## Functions
std::string command = "";

#### get video duration HHH:MM:SS
std::string getVideoDuration(std::string path)

#### get video dimensions (width, height)
int * getVideoDimentions(std::string path)

################################

# network.hpp

## Libs
    iostream
    string
    boost/asio.hpp
    arpa/inet.h
    sys/socket.h
    netdb.h
    cstring

## FUNCTIONS
std::string get_ip_from_hostname(const std::string &hostname)
bool is_host_online(const char *hostname)

## COMPILE
g++ -std=c++11 -o myprogram myprogram.cpp -std=c++11 -lboost_system -lpthread

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

## PRIVATE PROPERTIES
bool newLine = true;
std::fstream sql_file;
void endSql()
bool sql_exists(std::string path)

## Known ISSUES
file does not end on a ; but ,

################################

# ssh_wrapper.h

## Libs
    iostream
    libssh/libssh.h

class SshWrapper
    SshWrapper() : session_(ssh_new())
    ~SshWrapper()

## PUBLIC PROPERTIES
bool connect(const std::string &hostname)
bool auth(const std::string &username, const std::string &password)
bool runCommand(const std::string &command)

## PRIVATE PROPERTIES
ssh_session session_;

## LINUX INSTALL
sudo apt install libssh-dev

## COMPILE
g++ -o main main.cpp ssh_wrapper.cpp -lssh

## USAGE
\#include "ssh_wrapper.h"

int main() {
    SshWrapper ssh;
    if (!ssh.connect("example.com"))
        return -1;
    if (!ssh.auth("username", "password"))
        return -1;
    if (!ssh.runCommand("ls -l"))
        return -1;
    return 0;
}

################################

# Time.h

## Libs
    iostream
    string
    sstream
    curl/curl.h

class Time
    Time()
    ~Time()

## PUBLIC PROPERTIES
std::string get_time()
std::string get_date()
std::string get_timestamp()

## PRIVATE PROPERTIES
std::string time_str;
std::string date_str;
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)

## COMPILE
g++ -o main main.cpp curl_wrapper.cpp -lcurl

## USAGE
\#include "Time.h"

int main() {
    Time t;
    std::cout << "Time: " << t.get_time() << std::endl;
    std::cout << "Date: " << t.get_date() << std::endl;
    std::cout << "Timestamp: " << t.get_timestamp() << std::endl;
    return 0;
}

################################

# Time_boost.h

## Libs
    iostream
    iomanip
    chrono
    ctime
    boost/asio.hpp

class Time
    Time()
    ~Time()

## PUBLIC PROPERTIES
std::string get_time()
std::string get_date()
std::string get_timestamp()

## PRIVATE PROPERTIES
std::string time_str;
std::string date_str;

## COMPILE

## USAGE

################################


# timeExt.hpp

## Libs
  time.h
  string
  vector

## Functions

#### get date YYYY-MM-DD
std::string getDate()

#### get time HH:MM:SS
std::string getTime()

#### get timestamp "YYYY-MM-DD HH:MM:SS"
std::string getTimeStamp()

#### seperate timeStamp "YYYY-MM-DD" "HH:MM:SS" (splits string in two by first space)
std::vector<std::string> seperateTimeStamp(std::string timeStamp)

################################

# CMAKE
using curl lib: -lcurl
using mariadb lib: -std=c++11 -lmariadbcpp
