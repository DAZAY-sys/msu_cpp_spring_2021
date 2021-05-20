#pragma once
#include <iostream>

class Matrix
{
    friend class Proxy;
    class Proxy
    {
    private:
        size_t col_num;

    public:
        int32_t *data;
        Proxy(size_t b = 0);
        ~Proxy();
        int32_t& operator[](size_t j);
        void operator =(Proxy p);
    };

public:
    Matrix(size_t a = 0, size_t b = 0);
    ~Matrix();
    size_t getRows() const;
    size_t getColumns() const;

    Matrix& operator *=(uint32_t n);
    Proxy& operator[](size_t i);

    friend std::ostream& operator<<(std::ostream &out, Matrix &m);
    friend Matrix operator +(Matrix &m1, Matrix &m2);
    friend bool operator ==(Matrix &m1, Matrix &m2);
    friend bool operator !=(Matrix &m1, Matrix &m2);
private:
    size_t row_number, column_number;
    Proxy *rows;
};


