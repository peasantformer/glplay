#ifndef OPTIONPARSER_H
#define OPTIONPARSER_H

#include <ezOptionParser.hpp>

#include <string>

class OptionParser
{
public:
    OptionParser(int argc, char ** argv);

    bool parse();

    std::string const& getWorkingDirectory() const;
    int getWidth() const;
    int getHeight() const;

private:
    void printHelp();

    ez::ezOptionParser opt;
    std::vector<std::string> badOptions;
    std::vector<std::string> badArgs;

    int argc;
    char ** argv;

    std::string workingDirectory;
    int width;
    int height;
};

#endif // OPTIONPARSER_H
