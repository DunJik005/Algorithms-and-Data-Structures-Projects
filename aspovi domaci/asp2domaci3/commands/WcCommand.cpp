#include "WcCommand.h"
#include <iostream>
#include <sstream>

WcCommand::WcCommand(Mode mode) : mode(mode) {}

void WcCommand::execute(std::unique_ptr<InputBase> input) {
    // ucitava ceo ulaz (stdin, fajl ili string) u jedan string
    std::string text = input->readAll();

    if (mode == Mode::Chars)
        // ispisuje broj karaktera u tekstu
        std::cout << text.size() << std::endl;
    else
    {
        // razdvaja tekst po whitespacu i broji reci
        std::istringstream ss(text);
        std::string w;
        int count = 0;
        while (ss >> w)
            count++;
        std::cout << count << std::endl;
    }
}