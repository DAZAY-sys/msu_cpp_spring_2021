#include "allocator.hpp"
#include <cassert> 

void DefaultWorkTest()
{
    Allocator al;
    al.makeAllocator(15);
    char* ptr1 = al.alloc(10);
    char* ptr2 = al.alloc(5);

    assert(ptr2 - ptr1 == 10);
}

void ResetTest()
{
    Allocator al;
    al.makeAllocator(15);
    char* ptr1 = al.alloc(10);
    al.reset();
    char* ptr2 = al.alloc(15);

    assert(ptr2 == ptr1);
}

void OutOfSpaceTest()
{
    Allocator al;
    al.makeAllocator(15);
    char* ptr1 = al.alloc(16);

    assert(ptr1 == nullptr);
}

void MakeAllocatorTwiceTest()
{
    Allocator al;
    al.makeAllocator(2);
    al.makeAllocator(10);
    char* ptr1 = al.alloc(6);
    char* ptr2 = al.alloc(2);

    assert(ptr2 - ptr1 == 6);
    
}

void OutOfMemoryTest()
{
    Allocator al;
    al.makeAllocator(150000000000);
    char* ptr1 = al.alloc(16);

    assert(ptr1 == nullptr);
}

int main()
{
    DefaultWorkTest();
    ResetTest();
    OutOfSpaceTest();
    MakeAllocatorTwiceTest();
    OutOfMemoryTest();
    
    std::cout << "SUCCESS\n";

    return 0;
}
