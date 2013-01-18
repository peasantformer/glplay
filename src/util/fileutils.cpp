#include "fileutils.h"

#include <fstream>
#include <streambuf>
#include <iostream>

std::string FileUtils::readToString(const std::string &filepath)
{
    std::ifstream t(filepath);

    if (!t.is_open()) {
        std::cout << "Error opening " << filepath << "\n";
        return "";
    }

    std::string str;

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)),
                std::istreambuf_iterator<char>());

    return str;
}


