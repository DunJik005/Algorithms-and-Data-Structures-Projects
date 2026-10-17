//
// Created by Dun Jik on 1/7/2026.
//

#ifndef CLI_PHASE1_STDININPUT_H
#define CLI_PHASE1_STDININPUT_H

#include "InputBase.h"

class StdinInput : public InputBase {
public:
    std::string readAll() override;
};

#endif // CLI_PHASE1_STDININPUT_H
