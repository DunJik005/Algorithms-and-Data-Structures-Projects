//
// Created by Dun Jik on 1/7/2026.
//

#ifndef CLI_PHASE1_WCCOMMAND_H
#define CLI_PHASE1_WCCOMMAND_H

#include "../core/Command.h"

class WcCommand : public Command {
public:
    enum class Mode { Words, Chars };

    explicit WcCommand(Mode mode);

    bool needsArgument() const override { return true; }
    std::size_t inputTokenIndex() const override { return 2; }

    void execute(std::unique_ptr<InputBase> input) override;

private:
    Mode mode;
};


#endif // CLI_PHASE1_WCCOMMAND_H
