#ifndef CSV_HPP
#define CSV_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility> // for std::pair

class CSV
{
public:
    CSV(std::string filename) : m_filename(filename) {}

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

        long rows = data.size();

        for (long i = 0; i < rows; i++)
        {
            auto &row = data[i];
            long cells = row.size();
            for (long j = 0; j < cells; j++)
            {
                auto &cell = row[j];
                file << cell;
                if (j < cells - 1)
                    file << ',';
            }
            if (i < rows - 1)
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
    std::pair<int, int> find(std::string value)
    {
        std::vector<std::vector<std::string>> data = read();
        for (unsigned int i = 0; i < data.size(); i++)
        {
            for (unsigned int j = 0; j < data[i].size(); j++)
            {
                if (data[i][j] == value)
                {
                    return std::make_pair(i, j);
                }
            }
        }
        return std::make_pair(-1, -1); // Value not found
    }

private:
    std::string m_filename;
    bool hasHeader = true;
};

#endif
