#include "TimeCommand.h"
#include <iostream>
#include <ctime>

void TimeCommand::execute(std::unique_ptr<InputBase>) {
    // uzimanje trenutnog sistemskog vremena
    std::time_t t = std::time(nullptr);
    std::tm* tm = std::localtime(&t);

    // formatiranje vremena u HH:MM:SS
    char buf[9];
    std::strftime(buf, sizeof(buf), "%H:%M:%S", tm);
    std::cout << buf << std::endl;
}