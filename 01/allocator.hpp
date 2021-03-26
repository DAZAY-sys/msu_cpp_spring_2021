#pragma once
#include <iostream>

class Allocator
{
public:
    Allocator() {
        data = nullptr;
        maxSize = 0;
        occupiedSize = 0;
    }

    ~Allocator() {
        delete[] data;
    }

    void makeAllocator (std::size_t maxSize) {
        if (data)
            delete[] data;
    
        try {
            data = new char[maxSize];
            this->maxSize = maxSize;
            occupiedSize = 0;
        }
        catch(std::bad_alloc) {
            this->maxSize = 0;
        }
    }

    char* alloc(std::size_t size) {
        if (occupiedSize + size <= maxSize) {
            occupiedSize += size;
            char * r = data + occupiedSize;
            return r;
        } else {
            return nullptr;
          }
    }

    void reset() {
        occupiedSize = 0;
    }

private:
    char* data;
    std::size_t maxSize;
    std::size_t occupiedSize;
};
