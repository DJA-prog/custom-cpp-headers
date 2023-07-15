# Comma-Separated Values

# csv.hpp

### libraries
- iostream
- fstream
- sstream
- vector
- utility

### Structure
- class CSV
- CSV(std::string filename) // constructor

#### public

1. Set flag to skip first row / header line
-  `void setSkipHeader(bool skip)`

2. Read whole CSV file content into 2D string array
-  `std::vector<std::vector<std::string>> read()`

3. Write whole CSV file content as 2D string array
- `void write(std::vector<std::vector<std::string>> &data)`

4. Update specified cell
-  `void update(int row, int col, std::string value)`

5. Search CSV file content for specified value
- `std::pair<int, int> find(std::string value)`

#### private
- std::string m_filename;
- bool hasHeader = true;

# csv2.hpp

### libraries
- iostream
- fstream
- sstream
- vector

### Structure
- class CSV
- CSV() // constructor

#### public

1. Set filename
- `void setFilename(const std::string &filename)`

2. Set flag to skip first row / header line
- `void setSkipHeader(bool skip)`

3. Read whole CSV file content into 2D string array
- `std::vector<std::vector<std::string>> read()`

4. Write whole CSV file content as 2D string array
- `void write(const std::vector<std::vector<std::string>> &data)`

#### private
- std::string m_filename;
- bool hasHeader = true;

# csv3.hpp

### libraries
- iostream
- fstream
- sstream
- vector
- utility

### Structure
- class CSV
- CSV() // constructor


#### public

1. Set filename
- `void setFilename(const std::string &filename)`

2. Set flag to skip first row / header line
- `void setSkipHeader(bool skip)`

3. Read whole CSV file content into 2D string array
- `std::vector<std::vector<std::string>> read()`

4. Write whole CSV file content as 2D string array
- `void write(const std::vector<std::vector<std::string>> &data)`

5. Update specified cell
- `void update(int row, int col, std::string value)`

6. Search CSV file content for specified value
- `std::pair<int, int> find(std::string value)`

#### private
- std::string m_filename;
- bool hasHeader = true;