#include <cassert>
#include "allocator.hpp"

void DefaultWorkTest()
{
    Allocator al;
    al.MakeAllocator(15);
    char* ptr1 = al.alloc(10);
    assert(ptr1 != nullptr);

    char* ptr2 = al.alloc(5);
    assert(ptr2 != nullptr);

    assert(ptr2 - ptr1 == 10);
}

void ResetTest()
{
    Allocator al;
    al.MakeAllocator(15);
    char* ptr1 = al.alloc(10);
    assert(ptr1 != nullptr);
    al.reset();
    assert(ptr1 != nullptr);

    char* ptr2 = al.alloc(15);
    assert(ptr2 != nullptr);

    assert(ptr2 == ptr1);
}

void OutOfSpaceTest()
{
    Allocator al;
    al.MakeAllocator(15);
    char* ptr1 = al.alloc(16);
    assert(ptr1 == nullptr);
}

void MakeAllocatorTwiceTest()
{
    Allocator al;
    al.MakeAllocator(2);
    al.MakeAllocator(10);
    char* ptr1 = al.alloc(6);
    assert(ptr1 != nullptr);

    char* ptr2 = al.alloc(2);
    assert(ptr2 != nullptr);

    assert(ptr2 - ptr1 == 6);
}

void OutOfMemoryTest()
{
    Allocator al;
    al.MakeAllocator(150000000000);
    char* ptr1 = al.alloc(16);
    assert(ptr1 == nullptr);
}

void BeforeMakeAllocTest()
{
    Allocator al;
    char* ptr1 = al.alloc(6);
    assert(ptr1 == nullptr);
}

void BoundaryTest()
{
    Allocator al;
    al.MakeAllocator(10);
    char* ptr1 = al.alloc(10);
    assert(ptr1 != nullptr);

    char* ptr2 = al.alloc(6);
    assert(ptr2 == nullptr);

    al.reset();

    char* ptr3 = al.alloc(10);
    assert(ptr3 != nullptr);
    assert(ptr3 == ptr1);
}

int main()
{
    DefaultWorkTest();
    ResetTest();
    OutOfSpaceTest();
    MakeAllocatorTwiceTest();
    OutOfMemoryTest();
    BeforeMakeAllocTest();
    BoundaryTest();

    std::cout << "SUCCESS\n";

    return 0;
}
