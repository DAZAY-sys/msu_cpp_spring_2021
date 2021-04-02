#pragma once
#include <iostream>
#include <vector>

const uint64_t MAXSIZE = std::numeric_limits<uint64_t>::max();

class TokenParser
{
public:
    TokenParser();
    ~TokenParser() = default;

    void SetStartCallback(void (*func)());
    void SetEndCallback(void (*func)());
    void SetDigitTokenCallback(void (*DigitCallBack)(uint64_t x));
    void SetWordTokenCallback(void (*CallBack)(std::string x));
    void CallStartCallback();
    void CallEndCallback();
    const std::vector<std::string> Parser(const std::string &line);

private:
    void (*digitCallback)(uint64_t x);
    void (*wordCallback)(std::string x);
    void (*startF)();
    void (*endF)();
    void CheckTokensAndCall(const std::vector<std::string> &tokens);
};
