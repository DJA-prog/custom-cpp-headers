#ifndef SQLWRITER__HPP
#define SQLWRITER__HPP

#include <iostream>
#include <string>
#include <fstream>

#pragma once

class SQLWriter{ // require: none

    public:
        std::string sqlFile;
        SQLWriter(std::string path_to_sql, std::string database, std::string* fields, int field_count)
        {
            sqlFile = path_to_sql;
            if (sqlFile.rfind('.') == std::string::npos)
            {
                sqlFile += ".log";
            }
            int append_name = 1;
            std::string testname = "";
            if (sql_exists(sqlFile))
            {
                do
                {
                    testname = std::to_string(append_name) + '_' + sqlFile;
                    append_name++;
                } while (sql_exists(testname));
                sqlFile = testname;
            }
            
            sql_file.open(sqlFile, std::fstream::in | std::fstream::out | std::fstream::app);
            if (!sql_file.is_open())
                std::cout << "Could not create / open sql file: " + sqlFile << std::endl;
            sql_file << "INSERT INTO `" << database << "` (";
            // int field_count = sizeof(*fields)/sizeof(*(fields + 0));
            // std::cout << field_count << std::endl;
            for (size_t i = 0 ; i < field_count; i++)
            {
                if (i == 0)
                {
                    sql_file << '`' << *(fields + i) << '`';
                }
                else
                {
                    sql_file << ",`" << *(fields + i) << '`';
                }
            }
            sql_file << ")\nVALUES" << std::endl;
        }

        void appendField(std::string data)
        {
            if (newLine)
            {
                sql_file << "(\"" << data << '\"';
            }
            else{
                sql_file << ",\"" << data << '\"';
            }
            newLine = false;
        }  

        void appendField(char data)
        {
            if (newLine)
            {
                sql_file << "(\"" << data << '\"';
            }
            else{
                sql_file << ",\"" << data << '\"';
            }
            newLine = false;
        } 

        void appendField(int data)
        {
            if (newLine)
            {
                sql_file << "(\"" << data << '\"';
            }
            else{
                sql_file << ",\"" << data << '\"';
            }
            newLine = false;
        }

        void appendField(unsigned int data)
        {
            if (newLine)
            {
                sql_file << "(\"" << data << '\"';
            }
            else{
                sql_file << ",\"" << data << '\"';
            }
            newLine = false;
        }

        void endRow()
        {
            sql_file << ")," << std::endl;
            newLine = true;
        }

        void sqlClose()
        {
            endSql();
            sql_file.close();
        }

    private:
        bool newLine = true;
        std::fstream sql_file;

        void endSql()
        {
            sql_file.seekg(0, sql_file.end);
            while (true)
            {
                sql_file.unget();
                size_t chr = sql_file.get();
                // std::cout << chr << std::endl;
                sql_file.unget();
                if ((char) chr == ',')
                {
                    sql_file.put(';');
                    break;
                }
            }
        }

        bool sql_exists(std::string path)
        {
            struct stat sb;
            if (stat(path.c_str(), &sb) == 0 && !(sb.st_mode & S_IFDIR))
                return true;

            return false;
        }

};

#endif