#pragma once
#include <iostream>
#include <cmath>

class BigInt
{
public:
    BigInt(std::string = "");
    BigInt(const BigInt& d);
    BigInt(BigInt&& d);
    BigInt& operator = (const BigInt & b);
    BigInt& operator = (BigInt && b);

    const BigInt operator - () const;
    ~BigInt();

    friend std::ostream& operator << (std::ostream &out, const BigInt &b);
    friend BigInt operator + (const BigInt &b1, const BigInt &b2);
    friend BigInt operator - (const BigInt &b1, const BigInt &b2);

    friend BigInt operator + (const BigInt &d1, const int32_t num);
    friend BigInt operator - (const BigInt &d1, const int32_t num);
    friend BigInt operator * (const BigInt &d1, const int32_t num);

    friend BigInt operator * (const BigInt &d1, const BigInt &b2);
    friend bool operator == (const BigInt &d1, const BigInt &d2);
    friend bool operator == (const BigInt &d1, const int64_t num);
    friend bool operator != (const BigInt &d1, const BigInt &d2);
    friend bool operator > (const BigInt &d1, const BigInt &d2);
    friend bool operator >= (const BigInt &d1, const BigInt &d2);
    friend bool operator < (const BigInt &d1, const BigInt &d2);
    friend bool operator <= (const BigInt &d1, const BigInt &d2);

private:
    BigInt& remove_zeros();
    bool is_negative;
    size_t arrSize;
    int32_t *arr;
    static const size_t SIZE = 9;
    static const int MAXSIZE = 1000000000;
};


