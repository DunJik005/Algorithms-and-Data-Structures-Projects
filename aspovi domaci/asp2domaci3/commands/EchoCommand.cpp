#include "EchoCommand.h"
#include <iostream>

void EchoCommand::execute(std::unique_ptr<InputBase> input) {
    // ispisuje sav ulaz (string, fajl ili stdin) na standardni izlaz
    std::cout << input->readAll() << '\n';
}