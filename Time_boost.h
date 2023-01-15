#ifndef TIME_BOOST__H
#define TIME_BOOST__H

#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <boost/asio.hpp>

class Time
{
public:
    Time()
    {
        boost::asio::io_service io_service;
        boost::asio::ip::udp::resolver resolver(io_service);
        boost::asio::ip::udp::endpoint endpoint = *resolver.resolve(boost::asio::ip::udp::v4(), "pool.ntp.org", "ntp").begin();

        boost::asio::ip::udp::socket socket(io_service);
        socket.open(boost::asio::ip::udp::v4());
        socket.send_to(boost::asio::buffer("\x1b", 1), endpoint);

        boost::array<char, 48> recv_buf;
        boost::asio::ip::udp::endpoint sender_endpoint;
        size_t len = socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);

        std::string data(recv_buf.begin(), recv_buf.begin() + len);
        auto secs_since_1900 = static_cast<uint32_t>((unsigned char)data[40] << 24 | (unsigned char)data[41] << 16 | (unsigned char)data[42] << 8 | (unsigned char)data[43]);
        auto now = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        auto secs_since_1970 = now - 2208988800;
        auto time = std::chrono::system_clock::from_time_t(secs_since_1970 - secs_since_1900);
        std::time_t t = std::chrono::system_clock::to_time_t(time);

        std::stringstream stream;
        stream << std::put_time(std::localtime(&t), "%H:%M:%S");
        time_str = stream.str();
        stream.str("");
        stream << std::put_time(std::localtime(&t), "%Y-%m-%d");
        date_str = stream.str();
    }
    ~Time()
    {}
    std::string get_time()
    {
        return time_str;
    }
    std::string get_date()
    {
        return time_str;
    }
    std::string get_timestamp()
    {
        return date_str + " " + time_str;
    }

private:
    std::string time_str;
    std::string date_str;
};

#endif
