#ifndef logger__HPP
#define logger__HPP

#include <string>
#include <fstream>
#include <iostream>

#pragma once

class Logger{ // require: none

    public:
        std::string logFile;
        Logger(std::string logFileName, std::string title)
        {
            logFile = logFileName;
            if (logFile.rfind('.') == std::string::npos)
            {
                logFile += ".log";
            }
            int append_name = 1;
            std::string testname = "";
            if (log_exists(logFile))
            {
                do
                {
                    testname = logFile + '.' + std::to_string(append_name);
                    append_name++;
                } while (log_exists(testname));
                logFile = testname;
            }
            
            
            log_file.open(logFile, std::fstream::app);
            if (!log_file.is_open())
                std::cout << "Could not create / open log file: " + logFile << std::endl;
            log_file << "Log: " << title << std::endl << "Date: " << exec("date") << std::endl;
        }

        void append(std::string data)
        {
            log_file << data;
        }  
        void append(char data)
        {
            log_file << data;
        } 

        void appendCode(int code)
        {
            if (code == 0)
            {
                log_file << "[ SUCCESS ]";
            }
            else
            {
                log_file << "[ FAILED ] code: " << code;
            }
            
        }

        void endLine()
        {
            log_file << std::endl;
        }

        void logClose()
        {
            log_file.close();
        }

    private:
        std::string exec(std::string command) {
        char buffer[128];
        std::string result = "";

        FILE* pipe = popen(command.c_str(), "r");
        if (!pipe) {
            return "popen failed!";
        }

        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }

        pclose(pipe);
        return result;
        }

        std::fstream log_file;
        bool log_exists(std::string path)
        {
            std::fstream myfile;
            myfile.open(path, std::ios::in);
            if (myfile.is_open())
            {
                myfile.close();
                return true;
            }
            return false;    
        }

};

#endif