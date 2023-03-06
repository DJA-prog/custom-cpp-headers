# CSV Class
The CSV class provides a simple interface for reading and writing comma-separated value (CSV) files. It uses the standard C++ libraries iostream, fstream, sstream, and vector.

## Features
- Read CSV files into a two-dimensional vector of string.
- Write a two-dimensional vector of string to a CSV file.
- Update a value in a CSV file at a specified row and column index.
- Find a value in a CSV file and return its row and column index.


## Libraries
The CSV class relies on the following standard libraries:
- iostream: for input/output operations
- fstream: for file input/output operations
- sstream: for string stream operations
- vector: for storing the CSV data in a 2D vector data structure

## Capabilities

### Constructor
- `CSV(std::string filename) : m_filename(filename)`: creates an instance of the config class, and takes the path to the configuration file as an argument. If the file does not exist, the class will create it.

### Reading
- `std::vector<std::vector<std::string>> read()`: The read() function reads the contents of a CSV file and returns a vector of vectors of strings representing the rows and columns in the file.

### Writing
- `void write(std::vector<std::vector<std::string>> &data)`: The write() function takes a vector of vectors of strings and writes it to a CSV file.
- `void update(int row, int col, std::string value)`: The update() function updates the value in a specific cell in the CSV file, given the row and column index and the new value.

### Other
- `void find(std::string value)`: The find() function searches for a specific value in the CSV file and returns its row and column index if found. Otherwise, it prints a message saying the value was not found.
- `void setSkipHeader(bool skip)`: The setSkipHeader() function allows you to skip the header row when reading a CSV file.


## Capabilities Summary
The CSV class provides the following capabilities:
- Read a CSV file into a 2D vector of strings
- Write a 2D vector of strings to a CSV file
- Update a single cell in the CSV file by row and column index
- Find a value in the CSV file and print its row and column index

## How to use in code
To use the CSV class in your C++ code, you will need to include the CSV header file:
~~~~~
#include "CSV.hpp"
~~~~~

Then, you can create a new instance of the CSV class by passing the name of the CSV file as a string to the constructor:
~~~~~
CSV csv("filename.csv");
~~~~~

You can then call the read() method to read the CSV file into a 2D vector of strings:
~~~~~
auto data = csv.read();
~~~~~

To write data to the CSV file, you can create a 2D vector of strings and pass it to the write() method:
~~~~~
std::vector<std::vector<std::string>> data = {
    {"Name", "Age", "City"},
    {"John", "25", "New York"},
    {"Alice", "30", "Los Angeles"}
};
csv.write(data);
~~~~~

To update a cell in the CSV file, you can call the update() method and pass the row index, column index, and new value as parameters:
~~~~~
csv.update(1, 2, "San Francisco");
~~~~~

To find a value in the CSV file, you can call the find() method and pass the value as a parameter:
~~~~~
csv.find("Alice");
~~~~~

This will print the row and column index of the cell containing the value "Alice", or "Value not found" if the value is not in the CSV file.