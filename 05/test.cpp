#include <cassert>
#include <sstream>
#include "serializer.hpp"

struct Data2
{
    std::string a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};

struct Data3
{
    uint64_t a;
    bool b;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b);
    }
};

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
    Data3 x {18446744073709551615ULL, true}, y {0, false};

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
    Data3 x {0, 1}, y {0, false};

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
    Data2 y {"str", false, 5};
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
    Data3 y {0, false};
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
    Data3 x {0, false};
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

int main()
{
    DefaultTest();
    DefaultTestTwoDim();
    ErrorTest();
    BoolType();
    WrongDimensionMore();
    WrongDimensionLess();
    ReadFromEmptyStream();

    std::cout << "SUCCESS\n";

    return 0;
}
