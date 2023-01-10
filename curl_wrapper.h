/*
// HOW TO COMPILE THIS CODE
g++ -o main main.cpp curl_wrapper.cpp -lcurl
*/

#ifndef CURL_WRAPPER_H
#define CURL_WRAPPER_H

#include <iostream>
#include <curl/curl.h>

class CurlWrapper
{
public:
    CurlWrapper()
    {
        curl_global_init(CURL_GLOBAL_ALL);
        curl_ = curl_easy_init();
    }
    ~CurlWrapper()
    {
        curl_easy_cleanup(curl_);
        curl_global_cleanup();
    }

    std::string fetchUrl(const std::string &url)
    {
        std::string response;
        if (curl_)
        {
            curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, &CurlWrapper::writeCallback);
            curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response);
            CURLcode res = curl_easy_perform(curl_);
            if (res != CURLE_OK)
            {
                std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
            }
        }
        return response;
    }

private:
    CURL *curl_;

    static size_t writeCallback(char *ptr, size_t size, size_t nmemb, void *userdata)
    {
        std::string *response = static_cast<std::string *>(userdata);
        response->append(ptr, size * nmemb);
        return size * nmemb;
    }
};

#endif

/*
// HOW TO USE THIS CODE:

#include "curl_wrapper.h"

int main() {
    CurlWrapper curl;
    std::string response = curl.fetchUrl("https://www.example.com");
    std::cout << response << std::endl;
    return 0;
}

*/