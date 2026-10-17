//
// Created by Dun Jik on 1/7/2026.
//

#ifndef CLI_PHASE1_ECHOCOMMAND_H
#define CLI_PHASE1_ECHOCOMMAND_H

#include "../core/Command.h"

class EchoCommand : public Command {
public:
    void execute(std::unique_ptr<InputBase> input) override;
};

#endif // CLI_PHASE1_ECHOCOMMAND_H
