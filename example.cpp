#include "betterMainArgs.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    std::vector<Argument> config = { // vector
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
    
    ArgumentCalculator ac(argc, argv);

    auto used = ac.getUsedArguments(config);

    for (auto arg : used) {
        std::cout << arg.getFlags() << ": " << arg.argument << std::endl;
    }
    
    return 0;
}