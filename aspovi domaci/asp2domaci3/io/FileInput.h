//
// Created by Dun Jik on 1/7/2026.
//

#ifndef CLI_PHASE1_FILEINPUT_H
#define CLI_PHASE1_FILEINPUT_H

#include "InputBase.h"
#include <string>

class FileInput : public InputBase {
public:
    explicit FileInput(const std::string& filename);
    std::string readAll() override;

private:
    std::string data;
};

#endif // CLI_PHASE1_FILEINPUT_H