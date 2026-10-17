//
// Created by Dun Jik on 1/7/2026.
//

#ifndef CLI_PHASE1_COMMAND_H
#define CLI_PHASE1_COMMAND_H

#include <memory>
#include "../io/InputBase.h"

class Command {
public:
    virtual ~Command() = default;

    virtual bool needsArgument() const { return true; }
    virtual void execute(std::unique_ptr<InputBase> input) = 0;
    virtual std::size_t inputTokenIndex() const { return 1; }
};

#endif // CLI_PHASE1_COMMAND_H
