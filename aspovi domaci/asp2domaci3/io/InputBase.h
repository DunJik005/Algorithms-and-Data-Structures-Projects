//
// Created by Dun Jik on 1/7/2026.
//

#ifndef CLI_PHASE1_INPUTBASE_H
#define CLI_PHASE1_INPUTBASE_H

#include <string>

class InputBase {
public:
    virtual ~InputBase() = default;
    virtual std::string readAll() = 0;
};

#endif