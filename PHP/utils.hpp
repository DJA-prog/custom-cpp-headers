#include <string>

// PATHINFO flags
#define PATHINFO_ALL 0          // return whole string
#define PATHINFO_DIRNAME 1      // return from start to last /
#define PATHINFO_BASENAME 2     // return from last / too .*
#define PATHINFO_EXTENSION 3    // return the the last .* if any
#define PATHINFO_FILENAME 4     // return from last / to end of string
#define PATHINFO_PARENTDIR 5    // return from last / to second to last /

std::string pathinfo(std::string path, int flags = PATHINFO_ALL)
{
    int dot_find;
    int path_length = path.length();
    std::string filepath, filename, basename, extention, parent_dir;
    if (path.rfind('.') == std::string::npos)
    {
        dot_find = path_length;
        extention = "";
    }
    else
    {
        dot_find = path.rfind('.');
        extention = path.substr(dot_find + 1, path_length - dot_find - 1);
    }

    if (path.rfind('/') == std::string::npos)
    {
        basename = path.substr(0, dot_find);
        filename = path;
        filepath = ".";
    }
    else
    {
        basename = path.substr(path.rfind('/') + 1, dot_find - path.rfind('/') - 1);
        filename = path.substr(path.rfind('/') + 1, path_length - path.rfind('/') - 1);
        filepath = path.substr(0, path.rfind('/'));
        parent_dir = path.substr(path.rfind('/', path.rfind('/') - 1) + 1, path.rfind('/') - path.rfind('/', path.rfind('/') - 1) - 1);
    }

    switch (flags)
    {
    case 0:
        return path;

    case 1:
        return filepath;

    case 2:
        return basename;

    case 3:
        return extention;

    case 4:
        return filename;

    case 5:
        return parent_dir;

    default:
        return path;
    }
}