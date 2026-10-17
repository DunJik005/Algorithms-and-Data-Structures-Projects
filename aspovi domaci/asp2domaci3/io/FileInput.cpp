#include "FileInput.h"
#include <fstream>
#include <sstream>
#include "../errors/InterpreterError.h"

// otvori fajl filename i prekopira sve iz njega u string bafer i smesti to u data atribut
FileInput::FileInput(const std::string& filename) {
    std::ifstream file(filename);
    if (!file)
        throw InterpreterError(InterpreterError::Type::OS, "Cannot open file: " + filename);

    // string stream bafer
    std::ostringstream ss;
    ss << file.rdbuf();
    data = ss.str();
}


std::string FileInput::readAll() {
    return data;
}