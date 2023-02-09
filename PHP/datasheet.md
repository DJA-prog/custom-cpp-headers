# This contatins a list of files in the directory and provide a list of their fucntions.

####################
# utils.hpp

## Libs
    string

## Functions

#### std::string pathinfo(std::string $path, int $flags = PATHINFO_ALL)
Flags:
    PATHINFO_ALL 0          // return whole string
    PATHINFO_DIRNAME 1      // return from start to last /
    PATHINFO_BASENAME 2     // return from last / too .*
    PATHINFO_EXTENSION 3    // return the the last .* if any
    PATHINFO_FILENAME 4     // return from last / to end of string
    PATHINFO_PARENTDIR 5    // return from last / to second to last /