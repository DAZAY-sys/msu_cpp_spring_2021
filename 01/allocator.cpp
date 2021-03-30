#include "allocator.hpp"

Allocator::Allocator()
{
    data = nullptr;
    maxSize = 0;
    occupiedSize = 0;
}

Allocator::~Allocator()
{
    delete[] data;
}

void Allocator::MakeAllocator(std::size_t maxSize)
{
    if (data)
        delete[] data;

    try {
        data = new char[maxSize];
        this->maxSize = maxSize;
        occupiedSize = 0;
    }
    catch (std::bad_alloc) {
        this->maxSize = 0;
    }
}

char* Allocator::alloc(std::size_t size)
{
    if (occupiedSize + size <= maxSize) {
        char* r = data + occupiedSize;
        occupiedSize += size;
        return r;
    }
    else {
        return nullptr;
    }
}

void Allocator::reset()
{
    occupiedSize = 0;
}
