/*
// HOW TO COMPILE THIS CODE
g++ -o main main.cpp curl_wrapper.cpp -lcurl
*/

#ifndef FTP_H
#define FTP_H

#include <curl/curl.h>
#include <string>

class Ftp
{
    public:
        Ftp() {}
        ~Ftp() {}

        bool checkFileExists(const std::string &url, const std::string &username, const std::string &password)
        {
            CURL *curl;
            CURLcode res;

            curl = curl_easy_init();
            if (curl)
            {
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_USERNAME, username.c_str());
                curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
                curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
                res = curl_easy_perform(curl);

                if (res != CURLE_OK)
                {
                    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                    return false;
                }

                long http_code = 0;
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

                /* always cleanup */
                curl_easy_cleanup(curl);
                if (http_code == 404)
                {
                    return false;
                }
            }
            return true;
        }

        bool download(const std::string &url, const std::string &username, const std::string &password, const std::string &filepath)
        {
            if (!checkFileExists(url, username, password))
            {
                printf("File not found on server\n");
                return false;
            }
            CURL *curl;
            CURLcode res;

            curl = curl_easy_init();
            if (curl)
            {
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_USERNAME, username.c_str());
                curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, fopen(filepath.c_str(), "wb"));
                res = curl_easy_perform(curl);
                /* check for errors */
                if (res != CURLE_OK)
                {
                    fprintf(stderr, "curl_easy_perform() failed: %s\n",
                            curl_easy_strerror(res));
                    return false;
                }
                /* always cleanup */
                curl_easy_cleanup(curl);
            }
            return true;
        }

    private:
        size_t Ftp::write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
        {
            size_t written = fwrite(ptr, size, nmemb, stream);
            return written;
        }
};


#endif

/*
// HOW TO USE THIS CODE:

#include "ftp_download.h"

int main(){
    Ftp ftp;
    if (ftp.download("ftp://ftp.example.com/report.txt","username","password","/path/to/save/report.txt"))
        printf("Downloaded successfully\n");
    else
        printf("Failed to download\n");
    return 0;
}


*/