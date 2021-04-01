#include "parser.hpp"
#include <cassert>

void StartF()
{
    std::cout << "START\n";
}

void EndF()
{
    std::cout << "END\n";
}

void Digit(int a)
{
    std::cout << "Digit found - " << a << std::endl;
}

void Word(std::string a)
{
    std::cout << "Word found - " << a << std::endl;
}

void DefaultWorkTest()
{
    std::string line = "on_e\ntwo\vthree3\t1234 ";
    TokenParser token_par;

    token_par.SetStartCallback(StartF);
    token_par.SetEndCallback(EndF);
    token_par.SetDigitTokenCallback(Digit);
    token_par.SetWordTokenCallback(Word);

    token_par.CallStartCallback();
    const std::vector<std::string> token = token_par.Parser(line);
    token_par.CallEndCallback();

    assert(token[0] == "on_e");
    assert(token[1] == "two");
    assert(token[2] == "three3");
    assert(token[3] == "1234");
}

void NoSetFunctionsTest()
{
    std::string line = "on_e\n   two  \vthree3\t1234 ";
    TokenParser token_par;

    const std::vector<std::string> token = token_par.Parser(line);

    assert(token[0] == "on_e");
    assert(token[1] == "two");
    assert(token[2] == "three3");
    assert(token[3] == "1234");
}

void PartSetFunctionsTest()
{
    TokenParser token_par;
    std::string line = "one\n128\v\v\t  /\t1234 ";

    token_par.SetEndCallback(EndF);
    token_par.SetDigitTokenCallback(Digit);

    const std::vector<std::string> token = token_par.Parser(line);
    token_par.CallEndCallback();

    assert(token[0] == "one");
    assert(token[1] == "128");
    assert(token[2] == "/");
    assert(token[3] == "1234");
}

void CallWithoutSetTest()
{
    std::string line = "12 \r";
    TokenParser token_par;

    token_par.CallStartCallback();
    const std::vector<std::string> token = token_par.Parser(line);
    token_par.CallEndCallback();

    assert(token[0] == "12");
    assert(token[1] == "\r");
}

void EmptyWordTest()
{
    std::string line = "\n\t  \v \n";
    TokenParser token_par;

    token_par.SetStartCallback(StartF);
    token_par.SetEndCallback(EndF);
    token_par.SetDigitTokenCallback(Digit);
    token_par.SetWordTokenCallback(Word);

    token_par.CallStartCallback();
    const std::vector<std::string> token = token_par.Parser(line);
    token_par.CallEndCallback();

    assert(token.size() == 0);
}

int main()
{
//   Цикл для чтения напрямую, на тестах буду просто подавать строки
//   while(getline(std::cin, line))

    std::cout << "Test DefaultWorkTest:"<<std::endl;
    DefaultWorkTest();
    std::cout <<std::endl;

    std::cout << "Test NoSetFunctionsTest:"<<std::endl;
    NoSetFunctionsTest();
    std::cout <<std::endl;

    std::cout << "Test PartSetFunctionsTest:"<<std::endl;
    PartSetFunctionsTest();
    std::cout <<std::endl;

    std::cout << "Test CallWithoutSetTest:"<<std::endl;
    CallWithoutSetTest();
    std::cout <<std::endl;

    std::cout << "Test EmptyWordTest:"<<std::endl;
    EmptyWordTest();
    std::cout <<std::endl;

    std::cout<<"SUCCESS";
}