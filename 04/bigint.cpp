#include "bigint.hpp"
#include <iomanip>
#include <utility>

BigInt::BigInt(std::string str)
{
    if (str == "" or str == "0")
    {
        arrSize = 1;
        arr = new int32_t[arrSize];
        arr[0] = 0;
        is_negative = false;
    }
    else
    {
        arrSize = std::max(1, int32_t(std::ceil(str.length() * 1.0 / SIZE)));
        size_t i;
        if (str[0] == '-')
        {
            str = str.substr(1);
            i = str.length();
            arrSize = std::max(1, int(std::round(str.length() * 1.0 / SIZE)));
            arr = new int32_t[arrSize];
            is_negative = true;
        }
        else
        {
            i = str.length();
            is_negative = false;
            arr = new int32_t[arrSize];
        }
        for (size_t j = 0; j < arrSize && i > 0; j++)
        {
            if (i < SIZE)
                arr[j] = std::stoi(str.substr(0, i));
            else
                arr[j] = std::stoi(str.substr(i - SIZE, SIZE));
            i -= SIZE;
        }
        remove_zeros();
    }
}

BigInt::~BigInt()
{
    delete[] arr;
    arr = nullptr;
}

std::ostream& operator << (std::ostream &out, const BigInt &big)
{
    if (big.arr)
    {
        char old_fill = out.fill('0');
        if (big.is_negative)
            out << '-';
        for (int i = big.arrSize - 1; i >= 0; i--)
        {
            if (i != int(big.arrSize) - 1)
                out << std::setw(BigInt::SIZE) << big.arr[i];
            else
                out << big.arr[i];
        }
        out.fill(old_fill);
    }
    else
        std::cout << 0;
    out << std::endl;
    return out;
}

BigInt::BigInt (const BigInt& d)
{
    arrSize = d.arrSize;
    arr = new int[arrSize];
    is_negative = d.is_negative;

    for (size_t i = 0; i < d.arrSize; i++)
        arr[i] = d.arr[i];
}

BigInt::BigInt(BigInt&& d):is_negative(d.is_negative), arrSize(d.arrSize), arr(d.arr)
{
    d.arr = nullptr;
    d.arrSize = 0;
    d.is_negative = 0;
}

BigInt& BigInt::operator = (BigInt && b)
{
    is_negative = b.is_negative;
    arrSize = b.arrSize;
    if (arr)
        delete[] arr;
    arr = b.arr;
    b.arr = nullptr;
    b.arrSize = 0;
    b.is_negative = 0;
    return *this;
}

BigInt& BigInt::operator = (const BigInt& d)
{
    if (d == *this)
        return *this;

    if (arr)
        delete[] arr;

    arrSize = d.arrSize;
    is_negative = d.is_negative;

    arr = new int32_t[arrSize];
    for (size_t i = 0; i < arrSize; i++)
        arr[i] = d.arr[i];
    return *this;
}

BigInt operator + (const BigInt &d1, const BigInt &d2)
{
    BigInt result;
    if(result.arr)
        delete[] result.arr;
    int32_t add = 0;
    result.arrSize = std::max(d1.arrSize, d2.arrSize);
    result.arr = new int32_t[result.arrSize];

    int32_t d1_part;

    if (d1.is_negative)
    {
        if (d2.is_negative)
            return -(-d1 + (-d2));
        else
            return d2 - (-d1);
    }
    else if (d2.is_negative)
         return d1 - (-d2);

    for (size_t i = 0; i < std::max(d1.arrSize, d2.arrSize) || add != 0; i++)
    {
        if (i >= result.arrSize and add != 0)
        {
            BigInt new_result;
            delete[] new_result.arr;

            new_result.arrSize = result.arrSize + 1;
            new_result.arr = new int32_t[new_result.arrSize];
            for (size_t i = 0; i < new_result.arrSize - 1; i++)
            {
                new_result.arr[i] = result.arr[i];
            }
            result = new_result;
        }

        if (i == d1.arrSize)
            d1_part = 0;
        else
            d1_part = d1.arr[i];
        result.arr[i] = d1_part + add +(i < d2.arrSize ? d2.arr[i] : 0);
        add = result.arr[i] >= BigInt::MAXSIZE;
        if (add != 0)
            result.arr[i] -= BigInt::MAXSIZE;
    }
    return result;
}

BigInt operator + (const BigInt &d1, const int32_t num)
{
    BigInt d2(std::to_string(num));
    return d1 + d2;
}

BigInt operator - (const BigInt &d1, const int32_t num)
{
    BigInt d2(std::to_string(num));
    return d1 - d2;
}

BigInt operator * (const BigInt& d1, const int32_t num)
{
    BigInt d2(std::to_string(num));
    return d1 * d2;
}

BigInt operator - (const BigInt &d1, const BigInt &d2)
{
    if (d2.is_negative)
        return d1 + (-d2);
    else if (d1.is_negative)
        return -(-d1 + d2);
    else if (d1 < d2)
        return -(d2 - d1);

    BigInt result;
    delete[] result.arr;
    int32_t add = 0;
    result.arrSize = std::max(d1.arrSize, d2.arrSize);
    result.arr = new int32_t[result.arrSize];

    int32_t d1_part;
    for (size_t i = 0; i < std::max(d1.arrSize, d2.arrSize) || add != 0; i++)
    {
        if (i >= result.arrSize and add != 0)
        {
            BigInt new_result;
            delete[] new_result.arr;
            new_result.arrSize = result.arrSize + 1;
            new_result.arr = new int32_t[new_result.arrSize];
            for (size_t i = 0; i < new_result.arrSize - 1; i++)
            {
                new_result.arr[i] = result.arr[i];
            }
            result = new_result;
        }

        result.arr[i] = d1.arr[i] - add - (i < d2.arrSize ? d2.arr[i] : 0);
        add = result.arr[i] < 0;
        if (add != 0)
            result.arr[i] += BigInt::MAXSIZE;
    }
    return result;
}

const BigInt BigInt::operator - () const
{
    BigInt d2 = *this;
    d2.is_negative = !(is_negative);
    return d2;
}

BigInt operator *(const BigInt& left, const BigInt& right)
{
    BigInt result;
    delete[] result.arr;
    result.arrSize = left.arrSize + right.arrSize;
    result.arr = new int32_t [result.arrSize];
    for (size_t j = 0; j < result.arrSize; j++)
        result.arr[j] = 0;
    result.is_negative = left.is_negative || right.is_negative;

    int32_t carry = 0;
    for (size_t i = 0; i < left.arrSize; i++)
    {
        carry = 0;
        for (size_t j = 0; j < right.arrSize || carry != 0; j++)
        {
            long long cur = result.arr[i+j] + left.arr[i] * 1LL * (j < right.arrSize ? right.arr[j] : 0) + carry;
            result.arr[i + j] = static_cast<int32_t>(cur % BigInt::MAXSIZE);
            carry = static_cast<int32_t>(cur / BigInt::MAXSIZE);
        }
    }
    result.remove_zeros();
    return result;
}

BigInt& BigInt::remove_zeros()
{
    size_t k = 0;
    for (int i = arrSize - 1; i >= 0; i--)
    {
        if (arr[i] == 0)
            k += 1;
        else
            break;
    }
//    std::cout <<"))" <<*this;
//    std::cout <<"K "<<k << ' '<< arrSize <<std::endl;

    if (k != 0)
    {
        BigInt result;
        delete[] result.arr;
        result.arrSize = arrSize - k;

        result.arr = new int32_t [result.arrSize];
        result.is_negative = is_negative;

        for (size_t i = 0; i < result.arrSize; i++)
        {
            result.arr[i] = arr[i];
        }
        *this = result;
    }
    return *this;
}

bool operator == (const BigInt &d1, const BigInt &d2)
{
    if (d1.arrSize == d2.arrSize and d1.is_negative == d2.is_negative)
    {
        for (int i = d1.arrSize - 1; i >= 0; i--)
        {
            if (d1.arr[i] != d2.arr[i])
                return false;
        }
        return true;
    }
    else
        return false;
}

bool operator == (const BigInt &d1, const int64_t num)
{
    std::string s = std::to_string(num);
    BigInt d2(s);
    return d1 == d2;
}

bool operator != (const BigInt &d1, const BigInt &d2)
{
    return !(d1 == d2);
}

bool operator > (const BigInt &d1, const BigInt &d2)
{
    return d2 < d1;
}

bool operator >= (const BigInt &d1, const BigInt &d2)
{
    return d2 <= d1;
}

bool operator < (const BigInt &d1, const BigInt &d2)
{
    if (d1.is_negative > d2.is_negative)
        return true;
    if (d1.is_negative < d2.is_negative)
        return false;
    if (d1.arrSize < d2.arrSize)
        return not d1.is_negative;
    if (d1.arrSize > d2.arrSize)
        return d1.is_negative;

    size_t k = 0;
    for (int i = d1.arrSize - 1; i >= 0; i--)
    {
        if (d1.arr[i] == d2.arr[i])
            k += 1;
        else if (d1.is_negative)
        {
            if (d1.arr[i] < d2.arr[i])
                return false;
            else if (d1.arr[i] > d2.arr[i])
                return true;
        }
        else
        {
            if (d1.arr[i] < d2.arr[i])
                return true;
            else if (d1.arr[i] > d2.arr[i])
                return false;
        }
    }
    if (k == d1.arrSize)
        return false;
    return true;
}

bool operator <= (const BigInt &d1, const BigInt &d2)
{
    return (d1 < d2 || d1 == d2);
}