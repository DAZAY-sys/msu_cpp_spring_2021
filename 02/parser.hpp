#pragma once
#include <iostream>
#include <vector>

class TokenParser
{
public:
    TokenParser();
    ~TokenParser() = default;

    void SetStartCallback(void (*func)());
    void SetEndCallback(void (*func)());
    void SetDigitTokenCallback(void (*DigitCallBack)(int x));
    void SetWordTokenCallback(void (*CallBack)(std::string x));
    void CallStartCallback();
    void CallEndCallback();
    const std::vector<std::string> Parser(const std::string &line);

private:
    void (*digitCallback)(int x);
    void (*wordCallback)(std::string x);
    void (*startF)();
    void (*endF)();
    void CheckTokensAndCall(const std::vector<std::string> &tokens);
};