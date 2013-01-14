#include "optionparser.h"

OptionParser::OptionParser(int argc, char **argv)
    : workingDirectory(".")
    , width(640)
    , height(480)
    , argc(argc)
    , argv(argv)
{
    opt.overview = "PeasantFormer";
    opt.syntax = (std::string) argv[0] + " [OPTIONS]";

    opt.add(".",1,1,0,"Selects working resources directory","-w","--working-directory");
    opt.add("640x480",0,2,'x',"Window resolution","-r","--resolution");
    opt.add("",0,0,0,"Prints this help message","-h","--help");
}

bool OptionParser::parse()
{
    opt.parse(argc,const_cast<const char**>(argv));

    if (!opt.gotRequired(badOptions)) {
        for (int i = 0; i < badOptions.size(); i++) {
            std::cout << "ERROR: Missing rquired option: " << badOptions[i] << ".\n\n";
        }
        printHelp();
        return false;
    }

    if (!opt.gotExpected(badOptions)) {
        for (int i = 0; i < badOptions.size(); i++) {
            std::cout << "ERROR: Missing argument for option: " << badOptions[i] << ".\n\n";
        }
        printHelp();
        return false;
    }

    if (opt.isSet("-h")) {
        printHelp();
        exit(0);
    }

    std::vector<int> ints;
    opt.get("-r")->getInts(ints);

    width = ints[0];
    height = ints[1];

    if (width <= 0 || height <= 0) {
        std::cout << "Incorrect resolution: " << width << "x" << height << "\n";
        return false;
    }

    opt.get("-w")->getString(workingDirectory);

    return true;
}

const std::string &OptionParser::getWorkingDirectory() const
{
    return workingDirectory;
}

int OptionParser::getWidth() const
{
    return width;
}

int OptionParser::getHeight() const
{
    return height;
}

void OptionParser::printHelp()
{
    std::string helpMessage;
    opt.getUsage(helpMessage);
    std::cout << helpMessage;
}
