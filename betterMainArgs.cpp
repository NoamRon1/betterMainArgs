#include "betterMainArgs.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <map>
#include <sstream>

std::string ArgumentCalculator::printUsage(std::vector<Argument> config) {
    std:: ostringstream os;

    size_t flagWidth = 0;
    size_t helpMessageWidth = 0;

    for (const auto& arg: config) {
        flagWidth = std::max(flagWidth, arg.getFlags().length());
        helpMessageWidth = std::max(helpMessageWidth, arg.helpMessage.length());
    }

    flagWidth += 4;
    helpMessageWidth += 4;

    os << "Arguments: " << std::endl;
    for (const auto arg : config) {
        os << "\t" << std::left << std::setw(flagWidth) << arg.getFlags() << std::setw(helpMessageWidth) << arg.helpMessage;
        if (arg.mandatory) {
            os << "[Mandatory]";
        }

        os << std::endl;
    }

    return os.str();
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

            
            if (i+1 < _argc && !std::string(_argv[i+1]).starts_with("-")) {
                used.argument = std::string(_argv[++i]);
            }

            if (used.mandatory && !used.argument.empty()) usedMandatoryCount++;

            usedArguments.push_back(used);
        } catch (std::out_of_range) {
            throw std::runtime_error("Argument " + arg + " does not exists!\n");
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    if (usedMandatoryCount != mandatoryCount) {
        std::vector<Argument> unusedArgs;

        std::vector<Argument>::iterator argIt;

        for (auto arg: config) {
            if (!arg.mandatory) continue;

            argIt = std::find(usedArguments.begin(), usedArguments.end(), arg);
            if (argIt == usedArguments.end() || argIt->argument.empty()) {
                unusedArgs.push_back(arg);
            }
        }

        throw std::runtime_error("Unused " + printUsage(unusedArgs));
    }

    return usedArguments;
}
