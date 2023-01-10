/*
// HOW TO COMPILE THIS CODE
g++ -o main main.cpp curl_wrapper.cpp -lcurl
*/

#ifndef GITHUB_API_H
#define GITHUB_API_H

#include <curl/curl.h>
#include <string>

class GithubApi
{
public:
    GithubApi();
    bool retrieveData(const std::string &url, const std::string &token, std::string &response);

private:
    CURL *curl_;
    static size_t writeCallback(char *data, size_t size, size_t nmemb, void *userdata);
};

GithubApi::GithubApi() : curl_(curl_easy_init()) {}

bool GithubApi::retrieveData(const std::string &url, const std::string &token, std::string &response)
{
    if (!curl_)
    {
        return false;
    }
    curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_, CURLOPT_USERAGENT, "MyApp/1.0");
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, ("Authorization: token " + token).c_str());
    curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl_);
    if (res != CURLE_OK)
    {
        return false;
    }
    return true;
}

size_t GithubApi::writeCallback(char *data, size_t size, size_t nmemb, void *userdata)
{
    size_t realsize = size * nmemb;
    std::string *response = static_cast<std::string *>(userdata);
    response->append(data, realsize);
    return realsize;
}

#endif

/*
// HOW TO USE THIS CODE:

#include "GithubApi_Token.h"

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

*/