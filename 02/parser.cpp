#include "parser.hpp"
#include <algorithm>

TokenParser::TokenParser()
{
    this->digitCallback = nullptr;
    this->wordCallback = nullptr;
    this->startF = nullptr;
    this->endF = nullptr;
}

void TokenParser::CallStartCallback()
{
    if (this->startF != nullptr)
        this->startF();
}

void TokenParser::CallEndCallback()
{
    if (this->endF != nullptr)
        this->endF();
}

void TokenParser::SetDigitTokenCallback(TypeInt callback)
{
    this->digitCallback = callback;
}

void TokenParser::SetWordTokenCallback(TypeWord callback)
{
    this->wordCallback = callback;
}

void TokenParser::SetStartCallback(TypeBegin startF)
{
    this->startF = startF;
}

void TokenParser::SetEndCallback(TypeBegin endF)
{
    this->endF = endF;
}

void TokenParser::Parser(const std::string &line)
{
    CallStartCallback();
    std::vector<std::string> tokens;

    this->words.clear();
    this->numbers.clear();

    size_t pos = 0, lastPos = 0;
    std::string word;

    while ((pos = line.find_first_of("\n \t \v ", lastPos)) != std::string::npos) {
        word = line.substr(lastPos, pos - lastPos);
        if (word.length() != 0) {
            tokens.push_back(word);
        }
        lastPos = pos + 1;
    }

    word = line.substr(lastPos);
    if (word.length() != 0)
        tokens.push_back(word);

    TokenParser::CheckTokensAndCall(tokens);
    CallEndCallback();
}

void TokenParser::CheckTokensAndCall(const std::vector<std::string> &tokens)
{
    auto dig_check = [](unsigned char c) { return !std::isdigit(c); };
    auto word_check = [](unsigned char c) { return !(std::isdigit(c) || std::isalpha(c)); };
    bool move_done;
    uint64_t number;

    for (unsigned int i = 0; i < tokens.size(); i++) {
        move_done = false;

        if (std::find_if(std::begin(tokens[i]), std::end(tokens[i]),
                dig_check) == std::end(tokens[i])) {
            try {
                number = std::stoull(tokens[i]);
                this->numbers.push_back(number);

                if (this->digitCallback != nullptr)
                    this->digitCallback(number);
                move_done = true;
            }
            catch (std::out_of_range) {}
        }

        if (!move_done and std::find_if(std::begin(tokens[i]), std::end(tokens[i]),
                word_check) == std::end(tokens[i])) {
            this->words.push_back(tokens[i]);
            if (this->wordCallback != nullptr)
                this->wordCallback(tokens[i]);
        }
    }
}
