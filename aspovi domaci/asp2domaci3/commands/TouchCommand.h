//
// Created by Dun Jik on 1/7/2026.
//

#ifndef CLI_PHASE1_TOUCHCOMMAND_H
#define CLI_PHASE1_TOUCHCOMMAND_H

#include "../core/Command.h"
#include <string>

class TouchCommand : public Command {
public:
    explicit TouchCommand(std::string filename);

    void execute(std::unique_ptr<InputBase>) override;
    bool needsArgument() const override { return false; }

private:
    std::string filename;
};

#endif // CLI_PHASE1_TOUCHCOMMAND_H
