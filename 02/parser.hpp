#pragma once
#include <iostream>
#include <vector>

const uint64_t MAXSIZE = std::numeric_limits<uint64_t>::max();

class TokenParser
{
public:
    using TypeBegin = void(*)();
    using TypeInt = void(*)(uint64_t);
    using TypeWord = void(*)(std::string);

    std::vector<std::string> words;
    std::vector<uint64_t> numbers;

    TokenParser();
    ~TokenParser() = default;

    void SetStartCallback(TypeBegin ptr);
    void SetEndCallback(TypeBegin ptr);
    void SetDigitTokenCallback(TypeInt ptr);
    void SetWordTokenCallback(TypeWord ptr);
    void CallStartCallback();
    void CallEndCallback();
    void Parser(const std::string &line);

private:
    TypeInt digitCallback;
    TypeWord wordCallback;
    TypeBegin startF,endF;
    void CheckTokensAndCall(const std::vector<std::string> &tokens);
};
