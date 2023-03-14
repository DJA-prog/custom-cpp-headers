#ifndef TOR_MANAGE_HPP
#define TOR_MANAGE_HPP

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <memory>
#include <thread>
#include <chrono>
#include "tor.h"

using namespace std::chrono_literals;

// Custom error class for libtor errors
class TorError : public std::runtime_error
{
public:
    TorError(const std::string &message) : std::runtime_error(message) {}
};

// Wrapper class for managing a Tor process
class TorProcess
{
public:
    // Constructor initializes and starts a Tor process
    TorProcess()
    {
        // Initialize Tor process
        torProcess_ = tor_init(0);

        // Start Tor process
        int rc = tor_run(torProcess_, nullptr);
        if (rc != 0)
        {
            throw TorError("Failed to start Tor process: " + std::string(tor_strerror(rc)));
        }

        // Wait for Tor process to fully initialize
        std::this_thread::sleep_for(2s);

        std::cout << "Tor process started successfully\n";
    }

    // Destructor stops and frees the Tor process
    ~TorProcess()
    {
        // Stop Tor process
        int rc = tor_stop(torProcess_);
        if (rc != 0)
        {
            std::cerr << "Failed to stop Tor process: " << tor_strerror(rc) << std::endl;
        }

        // Free Tor process
        tor_free(torProcess_);

        std::cout << "Tor process stopped successfully\n";
    }

    // Getter for Tor control port number
    uint16_t getControlPort() const
    {
        return tor_get_control_port(torProcess_);
    }

private:
    tor_t *torProcess_;
};

#endif

/*
int main()
{
    try
    {
        // Start Tor process
        TorProcess torProcess;

        // Fetch a URL through Tor
        CurlWrapper curl;
        std::string url = "http://check.torproject.org/";
        curl_easy_setopt(curl.getHandle(), CURLOPT_PROXY, "socks5h://127.0.0.1:9050"); // use Tor SOCKS5 proxy
        std::string response = curl.fetchUrl(url);
        std::cout << response << std::endl;
    }
    catch (const TorError &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
*/