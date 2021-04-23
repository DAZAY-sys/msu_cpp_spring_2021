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
    Data x { 1, true, 2 }, y {0, false, 0};
    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}

void ErrorTest()
{
    Data x { 1, true, 2 };
    Data2 y {"str", false, 2};
    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::CorruptedArchive);
    assert(x.b != y.b);
    assert(x.c == y.c);
}

void WrongDimension()
{
    Data x {1, true, 2};
    Data3 y {0, false};
    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::CorruptedArchive);
    assert(x.a == y.a);
    assert(x.b == y.b);
}

void ReadFromEmptyStream()
{
    Data y {0, false, 1};
    std::stringstream stream;

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::CorruptedArchive);
    assert(y.a == 0);
    assert(y.b == false);
    assert(y.c == 1);
}

int main()
{
    DefaultTest();
    ErrorTest();
    WrongDimension();
    ReadFromEmptyStream();

    std::cout << "SUCCESS\n";

    return 0;
}
