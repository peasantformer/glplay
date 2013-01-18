#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <string>

class FileUtils
{
public:
    static std::string readToString(std::string const& filepath);
};

#endif // FILEUTILS_H
