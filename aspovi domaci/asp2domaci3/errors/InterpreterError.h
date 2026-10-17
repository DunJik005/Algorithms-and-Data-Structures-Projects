#ifndef CLI_PHASE1_INTERPRETERERROR_H
#define CLI_PHASE1_INTERPRETERERROR_H

#include <stdexcept>
#include <string>

class InterpreterError : public std::runtime_error {
public:
    enum class Type {
        Lexical,
        UnknownCommand,
        Syntax,
        Semantic,
        Execution,
        OS
    };

    InterpreterError(Type type, const std::string& msg);

    Type type() const;

    std::string fullMessage() const;

private:
    Type type_;

    static std::string typeToString(Type type);
};

#endif // CLI_PHASE1_INTERPRETERERROR_H
