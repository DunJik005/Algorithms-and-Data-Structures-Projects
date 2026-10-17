//
// Created by Dun Jik on 1/7/2026.
//

#ifndef CLI_PHASE1_INTERPRETER_H
#define CLI_PHASE1_INTERPRETER_H

#include <string>

class Interpreter {
public:
    void run();

private:
    void executeLine(const std::string& line);
};

#endif // CLI_PHASE1_INTERPRETER_H
