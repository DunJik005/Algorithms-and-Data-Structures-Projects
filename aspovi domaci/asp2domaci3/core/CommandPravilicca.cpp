#include "CommandPravilicca.h"
#include "../commands/EchoCommand.h"
#include "../commands/TimeCommand.h"
#include "../commands/DateCommand.h"
#include "../commands/TouchCommand.h"
#include "../commands/WcCommand.h"
#include "../errors/InterpreterError.h"



// na osnovu tokena komandne linije kreira odgovarajuci command objekat
// i proverava ispravnost argumenata u skladu sa specifikacijom komandi
std::unique_ptr<Command> CommandPravilicca::create(const std::vector<std::string>& tokens) {

    const std::string& name = tokens[0];

    if (name == "wc")
    {
        if (tokens.size() < 2)
            throw InterpreterError( InterpreterError::Type::Semantic, "wc: missing option");

        if (tokens[1] == "-c")
            return std::make_unique<WcCommand>(WcCommand::Mode::Chars);
        if (tokens[1] == "-w")
            return std::make_unique<WcCommand>(WcCommand::Mode::Words);

        throw InterpreterError( InterpreterError::Type::Semantic, "wc: invalid option");
    }

    if (name == "echo")
        return std::make_unique<EchoCommand>();

    if (name == "time")
    {
        if (tokens.size() != 1)
            throw InterpreterError(InterpreterError::Type::Semantic, "time: too many arguments");
        return std::make_unique<TimeCommand>();
    }

    if (name == "date")
    {
        if (tokens.size() != 1)
            throw InterpreterError(InterpreterError::Type::Semantic, "date: too many arguments");
        return std::make_unique<DateCommand>();
    }

    if (name == "touch")
    {
        if (tokens.size() != 2)
            throw InterpreterError(InterpreterError::Type::Semantic, "touch: invalid number of arguments");
        return std::make_unique<TouchCommand>(tokens[1]);
    }

    throw InterpreterError(InterpreterError::Type::UnknownCommand, name);

}
