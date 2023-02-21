This repository contains the headers I have created as a developer for C++ on a Debian Machine.

## AIM:
To create headers and functions with similar functions used in other programming languages such as PHP, as it is much easier then to transition into C++.

### Contributers:

## Users:
You can just clone the repo into your projects directory and direct the compiler (CMake) or the includes to the specific header file, and start using them.
$ git clone https://github.com/DJA-prog/custom-cpp-headers.git

## Usage:
There are short implementation examples and dependant Libraries in the header files. Note that most headers a a single file type.
For a complete overview of the headers and their content refer to the datasheet.md in each directory.

## Known issues:
Some headers are using the .hpp extention even though it is a .h header for C.

# Addtional Libs for Linux (required for some libraries)
## Boost Libs
$ sudo apt install libboost-all-dev

## Curl lib
$ sudo apt install libcurlpp-dev

## SSH libs
$ sudo apt install libssh-dev