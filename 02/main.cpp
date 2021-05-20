#include "parser.hpp"
#include <cassert>
#include <cstdint>
#include <cmath>
#include <limits>

std::vector<std::string> words;
std::vector<uint64_t> numbers;

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
    numbers.push_back(a);
    std::cout << "Digit found - " << a << std::endl;
}

void Word(std::string a)
{
    words.push_back(a);
    std::cout << "Word found - " << a << std::endl;
}

void DefaultWorkTest()
{
    numbers.clear();
    words.clear();

    std::string line = "on_e\ntwo\vthree32chh\t1234 ";
    TokenParser token_par;

    token_par.SetStartCallback(StartF);
    token_par.SetEndCallback(EndF);
    token_par.SetDigitTokenCallback(Digit);
    token_par.SetWordTokenCallback(Word);

    token_par.Parser(line);

    assert(words[0] == "on_e");
    assert(words[1] == "two");
    assert(words[2] == "three32chh");
    assert(numbers[0] == 1234);
}

void NoSetFunctionsTest()
{
    numbers.clear();
    words.clear();

    std::string line = "on_e\n   two  \vthree3ch\t1234 ";
    TokenParser token_par;

    token_par.Parser(line);

    assert(words.size() == 0);
    assert(numbers.size() == 0);
}

void PartSetFunctionsTest()
{
    numbers.clear();
    words.clear();

    TokenParser token_par;
    std::string line = "one\n128\v\v\t  /\t1234 ";

    token_par.SetEndCallback(EndF);
    token_par.SetDigitTokenCallback(Digit);

    token_par.Parser(line);

    assert(words.size() == 0);
    assert(numbers[0] == 128);
    assert(numbers[1] == 1234);
}

void EmptyWordTest()
{
    numbers.clear();
    words.clear();

    std::string line = "\n\t  \v \n";
    TokenParser token_par;

    token_par.SetStartCallback(StartF);
    token_par.SetEndCallback(EndF);
    token_par.SetDigitTokenCallback(Digit);
    token_par.SetWordTokenCallback(Word);

    token_par.Parser(line);

    assert(words.size() == 0);
    assert(numbers.size() == 0);
}

void BigNumberTest()
{
    numbers.clear();
    words.clear();

    std::string line = "18446744073709551616\n18446744073709551615";
    TokenParser token_par;

    token_par.SetStartCallback(StartF);
    token_par.SetEndCallback(EndF);
    token_par.SetDigitTokenCallback(Digit);
    token_par.SetWordTokenCallback(Word);

    token_par.Parser(line);

    assert(words[0] == "18446744073709551616");
    assert(numbers[0] == 18446744073709551615ULL);
}

void NullTest()
{
    numbers.clear();
    words.clear();

    std::string line1 = "";
    std::string line2 = "1";
    std::string line3 = "!";

    TokenParser token_par;

    token_par.SetStartCallback(StartF);
    token_par.SetEndCallback(EndF);
    token_par.SetDigitTokenCallback(Digit);
    token_par.SetWordTokenCallback(Word);

    token_par.Parser(line1);
    assert(numbers.size() == 0);
    assert(words.size() == 0);

    numbers.clear();
    words.clear();

    token_par.Parser(line2);
    assert(numbers[0] == 1);
    assert(words.size() == 0);

    numbers.clear();
    words.clear();

    token_par.Parser(line3);
    assert(numbers.size() == 0);
    assert(words[0] == "!");
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
