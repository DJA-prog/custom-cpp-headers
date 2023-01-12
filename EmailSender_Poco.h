/*
// LINUX INSTALLS:
sudo sh -c "echo deb http://repo.poco.ws/debian stable main > /etc/apt/sources.list.d/poco.list"
wget -O - http://repo.poco.ws/debian/apt-key.asc | sudo apt-key add -
sudo apt update
sudo apt install libpoco-dev


// HOW TO COMPILE THIS CODE
g++ -std=c++11 -o myprogram myprogram.cpp -lPocoNet -lPocoFoundation -lPocoUtil
*/

#ifndef EMAIL_SENDER_H
#define EMAIL_SENDER_H

#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/SMTPClientSession.h>
#include <Poco/Net/NetException.h>
#include <iostream>

class EmailSender
{
public:
    /**
     * Send an email using Poco::Net::SMTPClientSession
     * @param from Sender email address
     * @param to Receiver email address
     * @param subject Email subject
     * @param message Email message body
     */
    static void sendEmail(const std::string &from, const std::string &to,
                          const std::string &subject, const std::string &message);
};

void EmailSender::sendEmail(const std::string &from, const std::string &to,
                            const std::string &subject, const std::string &message)
{
    try
    {
        Poco::Net::MailMessage msg;
        msg.setSender(from);
        msg.addRecipient(Poco::Net::MailRecipient(Poco::Net::MailRecipient::PRIMARY_RECIPIENT, to));
        msg.setSubject(subject);
        msg.setContent(message);
        Poco::Net::SMTPClientSession smtp("smtp.gmail.com");
        smtp.login("username", "password"); // login with your gmail username and password
        smtp.sendMessage(msg);
    }
    catch (Poco::Exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

#endif

/*
// HOW TO USE THIS CODE:

#include "EmailSender_Poco.h"

std::string from = "sender@gmail.com";
std::string to = "receiver@example.com";
std::string subject = "example subject";
std::string message = "example message";

EmailSender::sendEmail(from, to, subject, message);


*/