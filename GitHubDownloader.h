/*
// HOW TO COMPILE THIS CODE
g++ -o main main.cpp curl_wrapper.cpp -lcurl
*/

#ifndef GITHUB_DOWNLOADER_H
#define GITHUB_DOWNLOADER_H

#include <string>
#include <curl/curl.h>
#include <fstream>

class GitHubDownloader
{
public:
    /**
     * Download file from GitHub API
     * @param url URL to download file from
     * @param filename Filename to save the downloaded file
     * @return Empty string if success, otherwise error message
     */
    static std::string downloadFile(const std::string &url, const std::string &filename);
};

std::string GitHubDownloader::downloadFile(const std::string &url, const std::string &filename)
{
    CURL *curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        std::ofstream outfile(filename);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &outfile);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            return curl_easy_strerror(res);
        }
        curl_easy_cleanup(curl);
    }
    return "";
}

#endif

/*
// HOW TO USE THIS CODE:

#include "GitHubDownloader.h"

std::string url = "https://api.github.com/repos/OWNER/REPO/contents/path/to/file?access_token=YOUR_TOKEN";
std::string filename = "path/to/save/file/on/disk.extension"
std::string error = GitHubDownloader::downloadFile(url, filename);
if (error.empty()) {
    // success
} else {
    // an error occurred, error message is in the 'error' variable
}


*/