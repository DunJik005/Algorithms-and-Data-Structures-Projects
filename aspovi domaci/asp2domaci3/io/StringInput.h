//
// Created by Dun Jik on 1/7/2026.
//

#ifndef CLI_PHASE1_STRINGINPUT_H
#define CLI_PHASE1_STRINGINPUT_H

#include "InputBase.h"
#include <string>

class StringInput : public InputBase {
public:
    explicit StringInput(std::string data);
    std::string readAll() override;

private:
    std::string data;
};

#endif // CLI_PHASE1_STRINGINPUT_H