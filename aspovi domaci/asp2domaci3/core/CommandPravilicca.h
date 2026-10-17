//
// Created by Dun Jik on 1/7/2026.
//

#ifndef CLI_PHASE1_COMMANDPRAVILICCA_H
#define CLI_PHASE1_COMMANDPRAVILICCA_H

#include <memory>
#include <vector>
#include <string>
#include "Command.h"

class CommandPravilicca {
public:
    static std::unique_ptr<Command> create(const std::vector<std::string>& tokens);
};

#endif