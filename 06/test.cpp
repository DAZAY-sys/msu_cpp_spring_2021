#include <cassert>
#include "format.hpp"
#include <algorithm>

void NormalTest()
{
    std::string answer;
    answer = format("{1} * {0} = {0}", 14, 1);
    assert (answer == "1 * 14 = 14");

    answer = format("My name is {0} and I am {1} years old. Love, {0}!",
            "Alice", 7);
    assert (answer == "My name is Alice and I am 7 years old. Love, Alice!");
}

void BracketTest()
{
    std::string answer;
    try
    {
        answer = format("{1}} + {5} = {0}", 2, 14);
    }
    catch (const ArgError& error)
    {
        assert(error.message_ == "Incorrect argument index!\n");
    }

    try
    {
        answer = format("{argument} + {1} = {0}", 2, "argument");
    }
    catch (const IndexError& error)
    {
        assert(error.message_ == "Wrong symbols brackets!\n");
    }
}

void ArgTest()
{
    std::string answer;

    answer = format("Many {0} are given, only {5} {3} be taken{4}.", "arguments", 2.0, "would", "will", '.', 3.0, 7);
    assert (answer == "Many arguments are given, only 3 will be taken..");

    answer = format("{0} + {1} = {1}", false, true);
    assert (answer == "0 + 1 = 1");
}

int main()
{
    NormalTest();
    BracketTest();
    ArgTest();
    std::cout << "SUCCESS\n";
    return 0;
}
