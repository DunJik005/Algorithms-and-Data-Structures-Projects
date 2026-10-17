#include "DateCommand.h"
#include <iostream>
#include <ctime>

void DateCommand::execute(std::unique_ptr<InputBase>) {
    // dobavlja trenutno sistemsko vreme i ispisuje datum u YYYY-MM-DD formatu
    std::time_t t = std::time(nullptr);
    std::tm* tm = std::localtime(&t);
    char buf[11];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", tm);
    std::cout << buf << std::endl;
}