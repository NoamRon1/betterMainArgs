#pragma once
#include <string>
#include <vector>
#include <utility>

namespace BetterMainArguments {
    struct ArgumentInstance {
        std::pair<std::string, std::string> argumentNames;
        std::string helpMessage; // for usage print
        bool mandatory = false;
        std::string argument; // for returns

        std::string getFlags() const {
            if (argumentNames.second.empty()) return "-" + argumentNames.first;
            if (argumentNames.first.empty()) return "--" + argumentNames.second;

            return "-" + argumentNames.first + ", --" + argumentNames.second;
        }

        bool operator==(const ArgumentInstance& other) const {
            return argumentNames.first == other.argumentNames.first && argumentNames.second == other.argumentNames.second;
        }
    };

    struct ProcessedArgumentInstance {
        std::vector<ArgumentInstance> usedArguments;
        std::vector<std::string> unrecognizedArguments;
    };

    class ArgumentProcessor {
    public:
        using Argument = ArgumentInstance;
        using ArgumentList = std::vector<Argument>;
        using ProcessedArgument = ProcessedArgumentInstance;

    public:
        ArgumentProcessor(const int argc, char *argv[]): _argc(argc), _argv(argv) {}
        ProcessedArgument getUsedArguments(const ArgumentList&) const;

        static std::string printUsage(const ArgumentList&);
    private:
        int _argc;
        char** _argv;
    };
}