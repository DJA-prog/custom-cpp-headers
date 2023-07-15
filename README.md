# Custom C++ Headers

This repository contains a collection of custom C++ headers created by a developer for C++ on a Debian machine. These headers provide additional functionality and utilities for your C++ projects.

## Aim

The aim of this project is to create headers and functions with similar functionality used in other programming languages such as PHP. This makes it easier to transition into C++ for developers familiar with those languages.

## Contributors

- [DJA-prog](https://github.com/DJA-prog)

## Users

To use the custom headers in your C++ projects, you can follow these steps:

1. Clone the repository to your local machine:
``` 
   git clone https://github.com/DJA-prog/custom-cpp-headers.git
``` 
2. Copy the desired headers into your project's directory.

3. Include the headers in your C++ code using the #include directive:
```
    #include "custom_header.hpp"
```
4. Build and compile your C++ project with the necessary flags to link the custom headers.

## Usage
There are short implementation examples and dependent libraries in the header files. Note that most headers are of a single file type. For a complete overview of the headers and their content, refer to the datasheet.md in each directory.

## Known Issues
- Some headers use the .hpp extension even though they are .h headers for C.

## Additional Libraries for Linux (required for some headers)
- Boost Libraries: `sudo apt install libboost-all-dev`
- Curl Library: `sudo apt install libcurlpp-dev`
- SSH Libraries: `sudo apt install libssh-dev`

## License
This repository is licensed under the MIT License.

