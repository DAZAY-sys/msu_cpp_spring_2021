#pragma once
#include <iostream>

class Allocator {
private:
    char* data;
    std::size_t maxSize;
    std::size_t occupiedSize;

public:
    Allocator();
    void MakeAllocator(std::size_t maxSize);
    char* alloc(std::size_t size);
    void reset();
    ~Allocator();
};
