//
// Created by Dun Jik on 1/13/2026.
//

#include "Tokenizer.h"
#include "../errors/InterpreterError.h"
#include <cctype>


// Tokenizuje komandnu liniju: razdvaja po whitespace-u,
// ali tretira sadržaj u navodnicima kao jedan argument

std::vector<std::string> Tokenizer::tokenize(const std::string& linija) {
    std::vector<std::string> tokens;
    std::string curr;

    bool inQuotes = false;      // da li smo trenutno unutar navodnika
    bool quoteClosed = false;   // da li je zatvoren string argument

    for (char c : linija)
    {
        if (c == '"')
        {
            if (!inQuotes)
            {
                // novi string argument u navodnicima
                if (quoteClosed)
                    throw InterpreterError(InterpreterError::Type::Semantic, "Text after closing quote in argument");
                inQuotes = true;
                curr += c;
            }
            else
            {
                // zatvaranje string argumenta u navodnicima
                inQuotes = false;
                quoteClosed = true;
                curr += c;

                tokens.push_back(curr);
                curr.clear();
            }
        }
        else if (std::isspace(static_cast<unsigned char>(c)) && !inQuotes && !quoteClosed)
        {
            // whitespace razdvaja tokene samo van navodnika
            if (!curr.empty())
            {
                tokens.push_back(curr);
                curr.clear();
            }
        }
        else
        {
            // nije dozvoljen tekst nakon zatvarajućeg navodnika
            if (quoteClosed)
                throw InterpreterError(InterpreterError::Type::Semantic, "Text after closing quote in argument");

            curr += c;
        }
    }

    // neparan broj navodnika tj samo 1 navodnik
    if (inQuotes)
        throw InterpreterError(InterpreterError::Type::Semantic, "Missing closing quote in argument");

    if (!curr.empty())
        tokens.push_back(curr);

    return tokens;
}
