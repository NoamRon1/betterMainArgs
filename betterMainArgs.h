#pragma once
#include <string>
#include <vector>
#include <utility>

namespace BetterMainArguments {
    struct Argument {
        std::pair<std::string, std::string> argumentNames;
        std::string helpMessage; // for usage print
        bool mandatory = false;
        std::string argument = ""; // for returns

        std::string getFlags() const {
            if (argumentNames.second.empty()) return "-" + argumentNames.first;
            if (argumentNames.first.empty()) return "--" + argumentNames.second;

            return "-" + argumentNames.first + ", --" + argumentNames.second;
        }

        bool operator==(const Argument& other) {
            return argumentNames.first == other.argumentNames.first && argumentNames.second == other.argumentNames.second;
        }
    };

    class ArgumentProcessor {
    public:
        ArgumentProcessor(int argc, char *argv[]): _argv(argv), _argc(argc) {}
        std::vector<Argument> getUsedArguments(std::vector<Argument>);

        std::string printUsage(std::vector<Argument>);
    private:
        int _argc;
        char** _argv;
    };
}