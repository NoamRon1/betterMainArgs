#include "betterMainArgs.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    BetterMainArguments::ArgumentProcessor::ArgumentList config = { // vector
        { // Argument
            {"h", "help"}, // pair of strings
            "prints this message",
            false
        },
        {
            {"v", ""},
            "prints the version",
            false
        },
        {
            {"o", "output"},
            "sets the output filename",
            true
        },
        {
            {"", "input"},
            "sets the input filename",
            true
        }
    };
    
    BetterMainArguments::ArgumentProcessor ac(argc, argv);

    auto used = ac.getUsedArguments(config);

    std::cout << "Recognized Arguments:" << std::endl;
    for (const auto& arg : used.usedArguments) {
        std::cout << arg.getFlags() << ": " << arg.argument << std::endl;
    }

    std::cout << "Unrecognized Arguments:" << std::endl;
    for (const auto& arg : used.unrecognizedArguments) {
        std::cout << arg << std::endl;
    }
    
    return 0;
}