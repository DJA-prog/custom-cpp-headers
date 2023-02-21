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
#include <vector>

    class CSV
{
public:
    CSV() {}

    void setFilename(std::string filename)
    {
        m_filename = filename;
    }

    void setSkipHeader(bool skip)
    {
        hasHeader = skip;
    }

    // Function to read the CSV file
    std::vector<std::vector<std::string>> read()
    {
        std::vector<std::vector<std::string>> data;
        std::string line;
        std::ifstream file(m_filename);

        while (std::getline(file, line))
        {
            std::vector<std::string> row;
            std::stringstream ss(line);
            std::string cell;

            while (std::getline(ss, cell, ','))
            {
                row.push_back(cell);
            }

            if (hasHeader)
            {
                hasHeader = false;
                continue;
            }

            data.push_back(row);
        }

        return data;
    }

    // Function to write to the CSV file
    void write(std::vector<std::vector<std::string>> &data)
    {
        std::ofstream file(m_filename);

        for (auto &row : data)
        {
            for (unsigned int i = 0; i < row.size(); i++)
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

    // Function to update the CSV file
    void update(int row, int col, std::string value)
    {
        std::vector<std::vector<std::string>> data = read();
        data[row][col] = value;
        write(data);
    }

    // Function to find the CSV file
    void find(std::string value)
    {
        std::vector<std::vector<std::string>> data = read();
        for (unsigned int i = 0; i < data.size(); i++)
        {
            for (unsigned int j = 0; j < data[i].size(); j++)
            {
                if (data[i][j] == value)
                {
                    std::cout << "Found at row: " << i << ", col: " << j << std::endl;
                    return;
                }
            }
        }
        std::cout << "Value not found" << std::endl;
    }

private:
    std::string m_filename;
    bool hasHeader = true;
};

#endif