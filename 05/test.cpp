#include <cassert>
#include <sstream>
#include "serializer.hpp"

void DefaultTest()
{
    Data x { 1, true, 2 }, y { 0, false, 0 };
    std::stringstream stream;

    Serializer serializer(stream);
    const Error err_s = serializer.save(x);

    assert(err_s == Error::NoError);
    assert(serializer.string_out == "1 true 2");

    Deserializer deserializer(stream);
    const Error err_d = deserializer.load(y);

    assert(err_d == Error::NoError);
    assert(deserializer.string_in == "1 true 2");

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}

void DefaultTestTwoDim()
{
    Data2 x {18446744073709551615ULL, true}, y {0, false};

    std::stringstream stream;
    Serializer serializer(stream);
    const Error err_s = serializer.save(x);

    assert(err_s == Error::NoError);
    assert(serializer.string_out == "18446744073709551615 true");

    Deserializer deserializer(stream);
    const Error err_d = deserializer.load(y);

    assert(err_d == Error::NoError);
    assert(deserializer.string_in == "18446744073709551615 true");

    assert(x.a == y.a);
    assert(x.b == y.b);
}

void BoolType()
{
    Data2 x {0, 1}, y {0, false};

    std::stringstream stream;
    Serializer serializer(stream);
    const Error err_s = serializer.save(x);

    assert(err_s == Error::NoError);
    assert(serializer.string_out == "0 true");

    Deserializer deserializer(stream);
    const Error err_d = deserializer.load(y);

    assert(err_d == Error::NoError);
    assert(deserializer.string_in == "0 true");

    assert(x.a == y.a);
    assert(x.b == y.b);
}

void ErrorTest()
{
    Data x {1, true, 2};
    Data3 y {"str", false, 5};
    std::stringstream stream;

    Serializer serializer(stream);
    const Error err_s = serializer.save(x);

    assert(err_s == Error::NoError);
    assert(serializer.string_out == "1 true 2");

    Deserializer deserializer(stream);
    const Error err_d = deserializer.load(y);

    assert(err_d == Error::CorruptedArchive);
    assert(deserializer.string_in == "");
}

void WrongDimensionMore()
{
    Data x {1, true, 2};
    Data2 y {0, false};
    std::stringstream stream;

    Serializer serializer(stream);
    const Error err_s = serializer.save(x);

    assert(err_s == Error::NoError);
    assert(serializer.string_out == "1 true 2");

    Deserializer deserializer(stream);
    const Error err_d = deserializer.load(y);

    assert(err_d == Error::CorruptedArchive);
    assert(deserializer.string_in == "1 true");

    assert(x.a == y.a);
    assert(x.b == y.b);
}

void WrongDimensionLess()
{
    Data2 x {0, false};
    Data y {1, true, 2};

    std::stringstream stream;

    Serializer serializer(stream);
    const Error err_s = serializer.save(x);

    assert(err_s == Error::NoError);
    assert(serializer.string_out == "0 false");

    Deserializer deserializer(stream);
    const Error err_d = deserializer.load(y);

    assert(err_d == Error::CorruptedArchive);
    assert(deserializer.string_in == "0 false");

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(y.c == 2);
}

void ReadFromEmptyStream()
{
    Data y {0, false, 1};
    std::stringstream stream;

    Deserializer deserializer(stream);
    const Error err_d = deserializer.load(y);

    assert(err_d == Error::CorruptedArchive);
    assert(deserializer.string_in == "");

    assert(y.a == 0);
    assert(y.b == false);
    assert(y.c == 1);
}

void TestOneTypeBool()
{
    DataOneType<bool> x {true};
    DataOneType<bool> y {false};
    std::stringstream stream;

    Serializer serializer(stream);
    const Error err_s = serializer.save(x);

    assert(err_s == Error::NoError);
    assert(serializer.string_out == "true");

    Deserializer deserializer(stream);
    const Error err_d = deserializer.load(y);

    assert(err_d == Error::NoError);
    assert(deserializer.string_in == "true");

    assert(y.a == true);
}

void TestOneTypeInt()
{
    DataOneType<uint64_t> x {145};
    DataOneType<uint64_t> y {12};
    std::stringstream stream;

    Serializer serializer(stream);
    const Error err_s = serializer.save(x);

    assert(err_s == Error::NoError);
    assert(serializer.string_out == "145");

    Deserializer deserializer(stream);
    const Error err_d = deserializer.load(y);

    assert(err_d == Error::NoError);
    assert(deserializer.string_in == "145");

    assert(y.a == 145);
}

void DeserializerTestInt()
{
    DataOneType<uint64_t> y {12};
    std::stringstream stream;

    stream << "true";
    Deserializer deserializer1(stream);
    const Error err1 = deserializer1.load(y);
    assert(err1 == Error::CorruptedArchive);

    stream.str("");

    stream << "123qwerty";
    Deserializer deserializer2(stream);
    const Error err2 = deserializer2.load(y);
    assert(err2 == Error::CorruptedArchive);

    stream.str("");

    stream << "18446744073709551616";
    Deserializer deserializer3(stream);
    const Error err3 = deserializer3.load(y);
    assert(err3 == Error::CorruptedArchive);

    stream.str("");

    stream << "18446744073709551615";
    Deserializer deserializer4(stream);
    const Error err4 = deserializer4.load(y);
    assert(err4 == Error::NoError);
    assert(deserializer4.string_in == "18446744073709551615");
    assert(y.a == 18446744073709551615ULL);
}

void DeserializerTestBool()
{
    DataOneType<bool> y {true};
    std::stringstream stream;

    stream << "0";
    Deserializer deserializer1(stream);
    const Error err1 = deserializer1.load(y);
    assert(err1 == Error::CorruptedArchive);

    stream.str("");

    stream << "1";
    Deserializer deserializer2(stream);
    const Error err2 = deserializer2.load(y);
    assert(err2 == Error::CorruptedArchive);
}


int main()
{
    DefaultTest();
    DefaultTestTwoDim();
    ErrorTest();
    BoolType();
    WrongDimensionMore();
    WrongDimensionLess();
    ReadFromEmptyStream();
    TestOneTypeBool();
    TestOneTypeInt();
    DeserializerTestInt();
    DeserializerTestBool();

    std::cout << "SUCCESS\n";
    return 0;
}
