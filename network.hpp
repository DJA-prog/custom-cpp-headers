/*
// HOW TO COMPILE THIS CODE
g++ -std=c++11 -o myprogram myprogram.cpp -std=c++11 -lboost_system -lpthread

*/

#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <netdb.h>
#include <cstring>

std::string get_ip_from_hostname(const std::string &hostname)
{
    addrinfo hints;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    addrinfo *res;
    int status = getaddrinfo(hostname.c_str(), NULL, &hints, &res);
    if (status != 0)
    {
        std::cout << "Error: " << gai_strerror(status) << std::endl;
        return "";
    }

    char ip[INET_ADDRSTRLEN];
    std::string ip_address;
    for (addrinfo *p = res; p != NULL; p = p->ai_next)
    {
        inet_ntop(AF_INET, &(((sockaddr_in *)p->ai_addr)->sin_addr), ip, INET_ADDRSTRLEN);
        ip_address = ip;
    }
    freeaddrinfo(res); // free the linked list
    return ip_address;
}

bool is_host_online(const char *hostname)
{
    struct addrinfo hints;
    struct addrinfo *result;

    std::memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME;

    int status = getaddrinfo(hostname, NULL, &hints, &result);
    if (status != 0)
    {
        std::cout << "Error: " << gai_strerror(status) << std::endl;
        return false;
    }

    freeaddrinfo(result);
    return true;
}

#endif