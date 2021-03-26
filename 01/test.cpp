# include "allocator.hpp"
# include <iostream>

    Allocator first;
    first.makeAllocator(15);
    first.alloc(6);
    first.alloc(10);
    first.alloc(10);
    first.reset();
    first.alloc(20);
    first.alloc(10);
    first.alloc(6);
    
    first.alloc(20);
    first.alloc(10);

void DefaultWorkTest()
{
    Allocator al;
    al.makeAllocator(15);
    al.alloc(10);
    al.alloc(2);
    al.alloc(3);
}

void ResetTest()
{
    Allocator al;
    al.makeAllocator(15);
    // al.alloc(10);
    al.reset();
    al.alloc(15);
}

void OutOfSpaceTest()
{
    Allocator al;
    al.makeAllocator(15);
    al.alloc(16);
}

void MakeAllocatorTwice()
{
    Allocator al;
    al.makeAllocator(2);
    al.makeAllocator(10);
    al.alloc(6);
}


int main()
{
    DefaultWorkTest();
    ResetTest();
    OutOfSpaceTest();
    MakeAllocatorTwice();

    std::cout << "SUCCESS\n";

    return 0;
}