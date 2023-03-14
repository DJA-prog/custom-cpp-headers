#ifndef CURL_WRAPPER_TOR_H
#define CURL_WRAPPER_TOR_H

#include <curl/curl.h>
#include <string>

class CurlWrapper
{
public:
    CurlWrapper()
    {
        curl_global_init(CURL_GLOBAL_ALL);
        curl_ = curl_easy_init();
        curl_easy_setopt(curl_, CURLOPT_PROXY, "socks5://127.0.0.1:9050");
        curl_easy_setopt(curl_, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
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