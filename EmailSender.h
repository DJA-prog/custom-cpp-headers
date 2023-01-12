/*
// HOW TO COMPILE THIS CODE
g++ -o main main.cpp curl_wrapper.cpp -lcurl
*/

#ifndef EMAIL_SENDER_H
#define EMAIL_SENDER_H

#include <curl/curl.h>
#include <string>

class EmailSender
{
public:
    /**
     * Send an email using SMTP
     * @param from Sender email address
     * @param to Receiver email address
     * @param subject Email subject
     * @param message Email message body
     */
    static void sendEmail(const std::string &from, const std::string &to, const std::string &subject, const std::string &message);
};

void EmailSender::sendEmail(const std::string &from, const std::string &to, const std::string &subject, const std::string &message)
{
    CURL *curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.example.com");
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, from.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, to.c_str());

        struct curl_slist *recipient = NULL;
        recipient = curl_slist_append(recipient, to.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipient);

        std::string email = "Subject: " + subject + "\r\n\r\n" + message;
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, email.c_str());

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        }
        curl_slist_free_all(recipient);
        curl_easy_cleanup(curl);
    }
}
#endif

/*
// HOW TO USE THIS CODE:

#include "EmailSender.h"

std::string from = "sender@example.com";
std::string to = "receiver@example.com";
std::string subject = "example subject";
std::string message = "example message";

EmailSender::sendEmail(from, to, subject, message);


*/