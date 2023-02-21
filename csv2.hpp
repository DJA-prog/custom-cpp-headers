/*
Ment for small csv files

Note:
it ignores the first row (header)

*/

#ifndef CSV_HPP
#define CSV_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class CSV
{
public:
    CSV() {}

    void setFilename(const std::string &filename)
    {
        m_filename = filename;
    }

    void setSkipHeader(bool skip)
    {
        hasHeader = skip;
    }

    void write(const std::vector<std::vector<std::string>> &data)
    {
        std::ofstream file(m_filename);
        for (const auto &row : data)
        {
            for (size_t i = 0; i < row.size(); ++i)
            {
                file << row[i];
                if (i < row.size() - 1)
                {
                    file << ",";
                }
            }
            file << "\n";
        }
    }

    std::vector<std::vector<std::string>> read()
    {
        std::vector<std::vector<std::string>> data;
        std::ifstream file(m_filename);
        if (file.is_open())
        {
            std::string line;
            while (std::getline(file, line))
            {
                std::vector<std::string> row;
                std::istringstream iss(line);
                std::string val;
                while (std::getline(iss, val, ','))
                {
                    row.push_back(val);
                }
                data.push_back(row);
            }
            file.close();
        }
        return data;
    }

private:
    std::string m_filename;
    bool hasHeader = true;
};

#endif
