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

void TokenParser::SetDigitTokenCallback(void (*callback)(uint64_t x))
{
    this->digitCallback = callback;
}

void TokenParser::SetWordTokenCallback(void (*callback)(std::string x))
{
    this->wordCallback = callback;
}

void TokenParser::SetStartCallback(void (*startF)())
{
    this->startF = startF;
}

void TokenParser::SetEndCallback(void (*endF)())
{
    this->endF = endF;
}

const std::vector<std::string> TokenParser::Parser(const std::string &line)
{
    std::vector<std::string> tokens;
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
    return tokens;
}


     
//     std::cout<<max_unsigned_int_size<<std::endl;

//    uint64_t a = std::stoull("18446744073709551615");



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

                if (this->digitCallback != nullptr)
                    this->digitCallback(number);
                move_done = true;
            }
            catch (std::out_of_range) {}
        }

        if (!move_done and std::find_if(std::begin(tokens[i]), std::end(tokens[i]),
                word_check) == std::end(tokens[i])) {
            if (this->wordCallback != nullptr)
                this->wordCallback(tokens[i]);
        }
    }
}
