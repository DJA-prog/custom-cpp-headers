#ifndef curl__HPP
#define curl__HPP

#include <string>
#include <curl/curl.h>

#pragma once

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

std::string * curl(std::string url)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        return readBuffer;
    }
    return "";
}

/*

#Install header files and library for cURL
sudo aptitude install libcurl4-openssl-dev
#Download sample cpp file
curl -sLO https://gist.github.com/alghanmi/c5d7b761b2c9ab199157/raw/curl_example.cpp
#Compile and run the code
g++ curl_example.cpp -o curl_example -lcurl
./curl_example

*/

#endif