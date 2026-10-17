#include "TouchCommand.h"
#include <fstream>
#include <iostream>
#include "../errors/InterpreterError.h"

TouchCommand::TouchCommand(std::string filename) : filename(std::move(filename)) {}

void TouchCommand::execute(std::unique_ptr<InputBase>) {
    // proverava da li fajl vec postoji
    std::ifstream test(filename);
    if (test)
        throw InterpreterError(InterpreterError::Type::Semantic, "File already exists");

    // pokusava da kreira novi fajl
    std::ofstream file(filename);
    if (!file)
        throw InterpreterError(InterpreterError::Type::OS, "File error");

    std::cout << "File successfully created" << '\n';
}