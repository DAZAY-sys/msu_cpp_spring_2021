#pragma once

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

    void makeAllocator (size_t maxSize) {
        if (data) {
            delete[] data;
            std::cout << "NOT NULL\n";
        }
        data = new char[maxSize];
        this->maxSize = maxSize;
        occupiedSize = 0;
    }

    char* alloc(size_t size) {
        if (occupiedSize+size <= maxSize) {
            occupiedSize += size;
            char * r = data + occupiedSize;
            std::cout << "MOVED SUCCESS\n";
            return r;
        } else {
            std::cout << "NO MORE PLACE\n";
            return nullptr;
        }
    }

    void reset() {
        std::cout << "RESETING ALL\n";
        occupiedSize = 0;
    }

private:
    char* data;
    size_t maxSize;
    size_t occupiedSize;
};
