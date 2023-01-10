/*
// LINUX INSTALLS:
sudo apt install libssh-dev

// HOW TO COMPILE THIS CODE
g++ -o main main.cpp ssh_wrapper.cpp -lssh
*/

#ifndef SSH_WRAPPER_H
#define SSH_WRAPPER_H

#include <iostream>
#include <libssh/libssh.h>

class SshWrapper
{
public:
    SshWrapper() : session_(ssh_new())
    {
    }
    ~SshWrapper()
    {
        ssh_disconnect(session_);
        ssh_free(session_);
    }

    bool connect(const std::string &hostname)
    {
        ssh_options_set(session_, SSH_OPTIONS_HOST, hostname.c_str());
        int rc = ssh_connect(session_);
        if (rc != SSH_OK)
        {
            std::cerr << "Error connecting to server: " << ssh_get_error(session_) << std::endl;
            return false;
        }
        return true;
    }

    bool auth(const std::string &username, const std::string &password)
    {
        int rc = ssh_userauth_password(session_, username.c_str(), password.c_str());
        if (rc != SSH_AUTH_SUCCESS)
        {
            std::cerr << "Error authenticating with password: " << ssh_get_error(session_) << std::endl;
            return false;
        }
        return true;
    }

    bool runCommand(const std::string &command)
    {
        ssh_channel channel = ssh_channel_new(session_);
        if (channel == NULL)
        {
            std::cerr << "Error creating channel: " << ssh_get_error(session_) << std::endl;
            return false;
        }
        int rc = ssh_channel_open_session(channel);
        if (rc != SSH_OK)
        {
            std::cerr << "Error opening channel: " << ssh_get_error(session_) << std::endl;
            ssh_channel_free(channel);
            return false;
        }
        rc = ssh_channel_request_exec(channel, command.c_str());
        if (rc != SSH_OK)
        {
            std::cerr << "Error executing command: " << ssh_get_error(session_) << std::endl;
            ssh_channel_close(channel);
            ssh_channel_free(channel);
            return false;
        }

        char buffer[256];
        int nbytes;
        while ((nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0)) > 0)
        {
            std::cout << buffer;
        }
        ssh_channel_send_eof(channel);
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        return true;
    }

private:
    ssh_session session_;
};

#endif

/*
// HOW TO USE THIS CODE:

#include "ssh_wrapper.h"

int main() {
    SshWrapper ssh;
    if (!ssh.connect("example.com"))
        return -1;
    if (!ssh.auth("username", "password"))
        return -1;
    if (!ssh.runCommand("ls -l"))
        return -1;
    return 0;
}


*/