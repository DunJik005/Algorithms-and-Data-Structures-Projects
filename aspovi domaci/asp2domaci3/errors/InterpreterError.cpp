#include "InterpreterError.h"

InterpreterError::InterpreterError(Type type, const std::string& msg)
    : std::runtime_error(msg), type_(type) {}

InterpreterError::Type InterpreterError::type() const {
    return type_;
}

// vraca full poruku za svoju vrstu errora
std::string InterpreterError::fullMessage() const {
    return typeToString(type_) + what();
}

// konvertuje tip errora u string poruku
std::string InterpreterError::typeToString(Type type) {
    switch (type) {
        case Type::Lexical:        return "Lexical error: ";
        case Type::Syntax:         return "Syntax error: ";
        case Type::Semantic:       return "Semantic error: ";
        case Type::Execution:      return "Execution error: ";
        case Type::OS:             return "OS error: ";
        case Type::UnknownCommand: return "Unknown command: ";
        default:                   return "Error: ";
    }
}
