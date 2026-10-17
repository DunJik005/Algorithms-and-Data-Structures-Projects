#include "StdinInput.h"
#include <iostream>
#include <sstream>


// prekopira sve sa std::in u string stream i vrati to
std::string StdinInput::readAll() {
    // string stream bafer
    std::ostringstream drpiIzKonzole;
    drpiIzKonzole << std::cin.rdbuf();
    return drpiIzKonzole.str();
}