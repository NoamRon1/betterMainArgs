#include "betterMainArgs.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <map>

void ArgumentCalculator::printUsage(std::vector<Argument> config) {
    size_t flagWidth = 0;
    size_t helpMessageWidth = 0;

    for (const auto& arg: config) {
        flagWidth = std::max(flagWidth, arg.getFlags().length());
        helpMessageWidth = std::max(helpMessageWidth, arg.helpMessage.length());
    }

    flagWidth += 4;
    helpMessageWidth += 4;

    std::cout << "Arguments: " << std::endl;
    for (const auto arg : config) {
        std::cout << "\t" << std::left << std::setw(flagWidth) << arg.getFlags() << std::setw(helpMessageWidth) << arg.helpMessage;
        if (arg.mandatory) {
            std::cout << "[Mandatory]";
        }

        std::cout << std::endl;
    }
}

std::vector<Argument> ArgumentCalculator::getUsedArguments(std::vector<Argument> config) {
    // converts the vector to a hashmap for faster lookup
    std::map<std::string, Argument> possibleArguments;
    int mandatoryCount = 0;

    for (auto arg : config) {
        if (arg.mandatory) mandatoryCount++;

        possibleArguments.insert({"-" + arg.argumentNames.first, arg});
        possibleArguments.insert({"--" + arg.argumentNames.second, arg});
    }

    std::vector<Argument> usedArguments;
    int usedMandatoryCount = 0;

    for (int i = 1; i < _argc; i++) {
        std::string arg = _argv[i];
        if (!arg.starts_with("-")) continue;
        
        try {
            Argument used = possibleArguments.at(arg);

            if (used.mandatory) usedMandatoryCount++;
            
            if (i+1 < _argc && !std::string(_argv[i+1]).starts_with("-")) {
                used.argument = std::string(_argv[++i]);
            }

            usedArguments.push_back(used);
        } catch (std::out_of_range) {
            throw std::runtime_error("Argument " + arg + " does not exists!\n");
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    if (usedMandatoryCount != mandatoryCount) {
        std::vector<Argument> unusedArgs;
        
        for (auto arg: config) {
            if (arg.mandatory && std::find(usedArguments.begin(), usedArguments.end(), arg) == usedArguments.end()) {
                unusedArgs.push_back(arg);
            }
        }

        std::cerr << "Unused Arguments:" << std::endl;
        printUsage(unusedArgs);
    }

    return usedArguments;
}
