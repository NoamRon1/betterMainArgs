#pragma once
#include <string>
#include <vector>
#include <utility>

struct Argument {
    std::pair<std::string, std::string> argumentNames;
    std::string helpMessage; // for usage print
    bool mandatory = false;
    std::string argument = ""; // for returns;

    std::string getFlags() const {
        return "-" + argumentNames.first + ", --" + argumentNames.second;
    }

    bool operator==(const Argument& other) {
        return argumentNames.first == other.argumentNames.first && argumentNames.second == other.argumentNames.second;
    }
};

class ArgumentCalculator {
public:
    ArgumentCalculator(int argc, char *argv[]): _argv(argv), _argc(argc) {}
    std::vector<Argument> getUsedArguments(std::vector<Argument>);

    std::string printUsage(std::vector<Argument>);
private:
    int _argc;
    char** _argv;
};