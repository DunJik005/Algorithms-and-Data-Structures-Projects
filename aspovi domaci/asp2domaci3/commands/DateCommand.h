//
// Created by Dun Jik on 1/7/2026.
//

#ifndef CLI_PHASE1_DATECOMMAND_H
#define CLI_PHASE1_DATECOMMAND_H

#include "../core/Command.h"

class DateCommand : public Command {
public:
    void execute(std::unique_ptr<InputBase>) override;
    bool needsArgument() const override { return false; }
};

#endif // CLI_PHASE1_DATECOMMAND_H
