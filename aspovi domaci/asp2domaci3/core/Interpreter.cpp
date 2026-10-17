#include "Interpreter.h"
#include "CommandPravilicca.h"
#include "Command.h"
#include "Tokenizer.h"

#include "../io/InputBase.h"
#include "../io/StdinInput.h"
#include "../io/StringInput.h"
#include "../io/FileInput.h"

#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "../errors/InterpreterError.h"




// glavna petlja interpretera
// ispisuje prompt, cita liniju i izvrsava komandu
void Interpreter::run() {
    std::string linija;

    while (true)
    {
        std::cout << "$ " << std::flush;

        if (!std::getline(std::cin, linija))
            break;

        try
        {
            executeLine(linija);
        }
        catch (const InterpreterError& e) {
            // centralizovano ispisivanje poruka o greskama
            std::cout << e.fullMessage() << std::endl;
        }
    }
}





// parsira i izvrsava jednu komandnu liniju
void Interpreter::executeLine(const std::string& linija) {
    // tokenizacija ulaza (komanda + argumenti)
    auto tokens = Tokenizer::tokenize(linija);
    if (tokens.empty())
        return;

    auto command = CommandPravilicca::create(tokens);

    std::unique_ptr<InputBase> input;

    // odredjivanje ulaznog toka za komandu
    if (command->needsArgument())
    {
        // ako nema argumenta, koristi se stdin
        if (tokens.size() == command->inputTokenIndex())
            input = std::make_unique<StdinInput>();
        else
        {
            const std::string& argument = tokens[command->inputTokenIndex()];

            // string argument ili ulaz iz fajla
            if (argument.size() >= 2 && argument.front() == '"' && argument.back() == '"')
                input = std::make_unique<StringInput>(argument.substr(1, argument.size() - 2));
            else
                input = std::make_unique<FileInput>(argument);
        }
    }
    // izvrsavanje komande sa pripremljenim ulazom
    command->execute(std::move(input));
}
