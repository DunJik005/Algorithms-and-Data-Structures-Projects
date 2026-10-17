//
// Created by Dun Jik on 1/13/2026.
//

#ifndef CLI_PHASE1_TOKENIZER_H
#define CLI_PHASE1_TOKENIZER_H

#include <vector>
#include <string>

class Tokenizer {
public:
    static std::vector<std::string> tokenize(const std::string& line);
};


#endif //CLI_PHASE1_TOKENIZER_H