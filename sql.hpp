#ifndef SQLWRITER__HPP
#define SQLWRITER__HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept> // for exceptions

class SQLWriter
{
public:
    SQLWriter(std::string sqlFileName, std::string database, std::vector<std::string> fields)
    {
        sqlFile = sqlFileName;
        if (sql_exists(sqlFile))
            throw std::runtime_error("sql file already exists");
        sql_file.open(sqlFile, std::fstream::out);
        if (!sql_file.is_open())
            throw std::runtime_error("Could not create/open sql file: " + sqlFile);
        sql_file << "INSERT INTO `" << database << "` (";
        int fieldC = 0;
        for (std::string x : fields)
        {
            if (fieldC == 0)
            {
                sql_file << '`' << x << '`';
            }
            else
            {
                sql_file << ",`" << x << '`';
            }
            fieldC++;
        }
        sql_file << ")\nVALUES" << '\n';
    }

    template <typename T>
    void appendField(T data)
    {
        if (newLine)
        {
            sql_file << "(\'" << data << '\'';
        }
        else
        {
            sql_file << ",\'" << data << '\'';
        }
        newLine = false;
    }

    void appendRow(const std::vector<std::string> &row)
    {
        if (newLine)
        {
            sql_file << "(";
        }
        else
        {
            sql_file << ",";
        }
        for (size_t i = 0; i < row.size(); i++)
        {
            sql_file << "'" << row[i] << "'";
            if (i != row.size() - 1)
            {
                sql_file << ",";
            }
        }
        sql_file << ")," << std::endl;
        newLine = false;
    }

    void endRow()
    {
        sql_file << ")," << '\n';
        newLine = true;
    }

    void endSql()
    {
        sql_file << ");";
        sqlEnded = true;
    }

    void sqlClose()
    {
        if (!sqlEnded)
            endSql();
        sql_file.close();
    }

private:
    std::string sqlFile;
    bool newLine = true, sqlEnded = false;
    std::fstream sql_file;
    bool sql_exists(std::string path)
    {
        std::ifstream myfile(path);
        return myfile.good();
    }
};

#endif