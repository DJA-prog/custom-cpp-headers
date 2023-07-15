/*
// HOW TO COMPILE THIS CODE
g++ -o main main.cpp curl_wrapper.cpp -lcurl
*/

#ifndef TIME_H
#define TIME_H

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <sstream>

class Time
{
public:
    Time()
    {
        CURL *curl = curl_easy_init();
        if (curl)
        {
            std::stringstream out;
            curl_easy_setopt(curl, CURLOPT_URL, "time1.google.com");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
            CURLcode res = curl_easy_perform(curl);

            if (res != CURLE_OK)
            {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            }
            else
            {
                std::string data = out.str();
                std::size_t found_time = data.find("time");
                std::size_t found_date = data.find("date");
                if (found_time != std::string::npos && found_date != std::string::npos)
                {
                    time_str = data.substr(found_time + 7, 8);
                    date_str = data.substr(found_date + 6, 10);
                }
            }
            curl_easy_cleanup(curl);
        }
    }
    ~Time()
    {

    }
    std::string get_time()
    {
        return time_str;
    }

    std::string get_date()
    {
        return date_str;
    }

    std::string get_timestamp()
    {
        return date_str + ' ' + time_str;
    }

    std::string get_timestamp_dash()
    {
        return date_str + '-' + time_str;
    }

private:
    static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
    {
        std::string data((const char *)ptr, (size_t)size * nmemb);
        *((std::stringstream *)stream) << data << std::endl;
        return size * nmemb;
    }
    std::string time_str;
    std::string date_str;
};

#endif

/*
// HOW TO USE THIS CODE:

#include "Time.h"

int main() {
    Time t;
    std::cout << "Time: " << t.get_time() << std::endl;
    std::cout << "Date: " << t.get_date() << std::endl;
    std::cout << "Timestamp: " << t.get_timestamp() << std::endl;
    return 0;
}


*/