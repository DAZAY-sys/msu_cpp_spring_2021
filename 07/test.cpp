#include <cassert>
#include "vector.hpp"

void UsualWorkTest()
{
    MyVector<std::string> v;
    v.push_back("first");
    v.push_back("second");
    v.push_back("third");

    assert(v[0] == "first");
    assert(v[1] == "second");
    assert(v[2] == "third");
}

void SizeTest()
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);

    assert(v.size() == 2 and !v.empty());
    assert(v.pop_back() == 2);
    assert(v.size() == 1 and !v.empty());
    assert(v.pop_back() == 1);
    assert(v.size() == 0 and v.empty());
}

void PointerTest()
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    auto ptr1 = v.begin();
    auto ptr2 = v.end();
    assert (*ptr1 == 1);
    ++ptr1;
    assert(*ptr1 == 2);
    ++ptr1;
    assert(*ptr1 == 3 and ptr1 == v.end());
    assert (*ptr2 == 3);
    --ptr2;
    assert(*ptr2 == 2);
    --ptr2;
    assert(*ptr2 == 1 and ptr2 == v.begin());
}

void ReverseTest()
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    auto ptr1 = v.rbegin();
    auto ptr2 = v.rend();

    assert (*ptr1 == 3 and *ptr2 == 1);
    ++ptr1;
    --ptr2;
    assert(*ptr1 == 2 and *ptr2 == 2);
    ++ptr1;
    --ptr2;
    assert(*ptr1 == 1 and *ptr2 == 3);
}

void ReserveTest()
{
    MyVector<double> v;
    v.push_back(12.3);
    v.push_back(4.56);
    v.push_back(7.890);

    assert(v.capacity() >= 3 and v.size() == 3);
    v.reserve(10);
    assert(v.capacity() >= 10 and v.size() == 3);
}

void ResizeTest()
{
    MyVector<int> v;
    v.push_back(1);
    v.push_back(3);

    v.resize(10);
    assert(v.size() == 10 and v.capacity() >= 10);

    v.clear();
    assert(v.size() == 0 and v.capacity() >= 10);
}

void EmplaceTest()
{
    MyVector<MyStruct> v;
    MyStruct a = {1, "one"};
    v.push_back(a);
    v.emplace_back(2, "two");

    assert(v[0]._number == 1 and v[0]._word == "one");
    assert(v[1]._number == 2 and v[1]._word == "two");
    assert(v.size() == 2);
}

int main()
{
    UsualWorkTest();
    SizeTest();
    PointerTest();
    ReverseTest();
    ReserveTest();
    ResizeTest();
    EmplaceTest();
    std::cout << "SUCCESS\n";
    return 0;
}
