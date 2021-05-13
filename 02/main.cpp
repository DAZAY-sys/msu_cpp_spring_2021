#include "parser.hpp"
#include <cassert>
#include <cstdint>
#include <cmath>
#include <limits>


void StartF()
{
    std::cout << "START\n";
}

void EndF()
{
    std::cout << "END\n";
}

void Digit(uint64_t a)
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

    token_par.Parser(line);

    assert(token_par.words[0] == "two");
    assert(token_par.words[1] == "three3");
    assert(token_par.numbers[0] == 1234);
}

void NoSetFunctionsTest()
{
    std::string line = "on_e\n   two  \vthree3\t1234 ";
    TokenParser token_par;

    token_par.Parser(line);

    assert(token_par.words[0] == "two");
    assert(token_par.words[1] == "three3");
    assert(token_par.numbers[0] == 1234);
}

void PartSetFunctionsTest()
{
    TokenParser token_par;
    std::string line = "one\n128\v\v\t  /\t1234 ";

    token_par.SetEndCallback(EndF);
    token_par.SetDigitTokenCallback(Digit);

    token_par.Parser(line);

    assert(token_par.words[0] == "one");
    assert(token_par.numbers[0] == 128);
    assert(token_par.numbers[1] == 1234);
}

void CallWithoutSetTest()
{
    std::string line = "12 \r";
    TokenParser token_par;

    token_par.Parser(line);

    assert(token_par.numbers[0] == 12);
    assert(token_par.words.size() == 0);
}

void EmptyWordTest()
{
    std::string line = "\n\t  \v \n";
    TokenParser token_par;

    token_par.SetStartCallback(StartF);
    token_par.SetEndCallback(EndF);
    token_par.SetDigitTokenCallback(Digit);
    token_par.SetWordTokenCallback(Word);

    token_par.Parser(line);

    assert(token_par.words.size() == 0);
    assert(token_par.numbers.size() == 0);
}

void BigNumberTest()
{
    std::string line = "18446744073709551616\n18446744073709551615";
    TokenParser token_par;

    token_par.SetStartCallback(StartF);
    token_par.SetEndCallback(EndF);
    token_par.SetDigitTokenCallback(Digit);
    token_par.SetWordTokenCallback(Word);

    token_par.Parser(line);

    assert(token_par.words[0] == "18446744073709551616");
    assert(token_par.numbers[0] == 18446744073709551615ULL);
}

void NullTest()
{
    std::string line1 = "";
    std::string line2 = "0 1";
    std::string line3 = "q";

    TokenParser token_par;

    token_par.SetStartCallback(StartF);
    token_par.SetEndCallback(EndF);
    token_par.SetDigitTokenCallback(Digit);
    token_par.SetWordTokenCallback(Word);

    token_par.Parser(line1);
    assert(token_par.numbers.size() == 0);
    assert(token_par.words.size() == 0);

    token_par.Parser(line2);
    assert(token_par.numbers[0] == 0);
    assert(token_par.numbers[1] == 1);
    assert(token_par.words.size() == 0);

    token_par.Parser(line3);
    assert(token_par.words[0] == "q");
    assert(token_par.numbers.size() == 0);
}

int main()
{
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

    std::cout << "Test BigNumberTest:"<<std::endl;
    BigNumberTest();
    std::cout <<std::endl;

    std::cout << "Test NullTest:"<<std::endl;
    NullTest();
    std::cout <<std::endl;

    std::cout<<"SUCCESS"<<std::endl;
}
