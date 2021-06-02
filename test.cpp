#include <cassert>
#include "bigint.hpp"

void ComparisonTest()
{
    BigInt b1 ("1234567");
    BigInt b2 ("1712345");
    BigInt b3 ("1234567");
    BigInt b4 ("-1623456");
    BigInt b5 ("-1234567");

    assert(b1 < b2);
    assert(b1 <= b3);
    assert(!(b1 > b2));
    assert(b1 >= b3);
    assert(b4 <= b1);
    assert(b2 > b4);
    assert(b4 < b5);
    assert(b1 == b3);
    assert(b4 != b5);
}

void ConstructorTest()
{
    BigInt b1;
    assert(b1 == 0);

    BigInt b2("1234567890");
    assert(b2 == 1234567890);

    BigInt b3("-987654321");
    assert(b3 == -987654321);

    BigInt b4("001");
    assert(b4 == 1);
}

void MultiplyTest()
{
    BigInt big1;
    BigInt big2("999");
    BigInt big3("-2");
    big1 = big2 * big3;
    assert (big2 * big3 == 999 * (-2));

    big2 = BigInt("123456789123456789123456789123456789");
    big3 = BigInt("12345678123456123");

    assert(big2 * big3 == BigInt("1524157780673596308642643308642643307118485527969047"));
}

void AddTest()
{
    BigInt big2("9999");
    BigInt big3("-100");
    assert(big2 + big3 == 9999 - 100);
    assert(big2 - big3 == 9999 + 100);
    assert(big3 - big2 == -100 - 9999);
}

void NumberTest()
{
    BigInt big1("9999");
    int64_t num = 1200000;
    assert( big1 + num == 9999 + num);
    assert (big1 - num == 9999 - num);
    assert (big1 * num == (9999 * num));
}

void MoveCheckTest()
{
    BigInt big1("9999");
    BigInt big2 = std::move(big1);
    assert(big2 == 9999);

    big1 = std::move(big2);
    assert(big1 == 9999);
}

void TestExample()
{
    BigInt a("1");
    BigInt b("123456789012345678901234567890");
    BigInt c = a * b + 2;
    BigInt d;
    d = std::move(c);
    a = d + b;
    assert(a == BigInt("246913578024691357802469135782"));
}

int main()
{
    ComparisonTest();
    ConstructorTest();
    MultiplyTest();
    AddTest();
    NumberTest();
    MoveCheckTest();
    TestExample();

    std::cout << "SUCCESS\n";
    return 0;
}
