//
// Created by deadsith on 08.10.16.
//

#include "BigIntInherited.h"

BigIntInherited::BigIntInherited(string number, int color) : BigInt(number)
{
    _setColor(color);
}

BigIntInherited::BigIntInherited() : BigInt()
{
    _setColor(30);
}

BigIntInherited::BigIntInherited(long long number, int color) : BigInt(number)
{
    _setColor(color);
}

BigIntInherited::BigIntInherited(vector<int> nums, bool isNegative, int color) : BigInt(nums, isNegative)
{
    _setColor(color);
}

BigIntInherited::BigIntInherited(const BigIntInherited &obj)
{
    _isNegative = obj.IsNegative();
    digits.clear();
    for (int d : obj.digits)
    {
        digits.push_back(d);
    }
    _color = obj._color;
}

void BigIntInherited::_setColor(int color)
{
    if (color > 29 && color < 38)
    {
        _color = color;
    }
    else
    { _color = 30; }
}

ostream &operator<<(ostream &os, const BigIntInherited &obj)
{
    os << "\033[0;" << obj._color << "m";
    os << (BigInt) obj;
    os << "\033[0;" << 30 << "m";
    return os;
}

BigIntInherited &BigIntInherited::operator=(const BigIntInherited &other)
{
    if (this != &other)
    {
        digits = other.digits;
        _isNegative = other.IsNegative();
        _color = other._color;
    }
    return *this;
}

istream &operator>>(istream &is, BigIntInherited &obj)
{
    bool leadZeros = true;
    bool negative = false;
    vector<int> numbers;

    while (is.good())
    {
        char c = static_cast<char>(is.get());
        int intC = c - '0';

        if (c == '\n')
        {
            break;
        }

        if (c == EOF)
        {
            break;
        }

        if (c == '\0')
        {
            break;
        }

        if (is.good())
        {
            if (c == '-')
            {
                negative = true;
            }
            else if (c == '+')
            {
                negative = false;
            }
            else if (intC == 0 && leadZeros)
            {
            }
            else
            {
                numbers.push_back(intC);
                leadZeros = false;
            }
        }
    }
    cout << "Enter color (30-38): ";
    int color;
    is >> color;
    BigIntInherited temp(numbers, negative, color);
    obj = temp;
    return is;
}

BigIntInherited BigIntInherited::operator++()
{
    *this += 1;
    return *this;
}

BigIntInherited BigIntInherited::operator++(int)
{
    *this += 1;
    return *this;
}

BigIntInherited BigIntInherited::operator--()
{
    *this -= 1;
    return *this;
}

BigIntInherited BigIntInherited::operator--(int)
{
    *this -= 1;
    return *this;
}

BigIntInherited BigIntInherited::GCD(const BigIntInherited &other) const
{
    if (*this < other)
    {
        return other.GCD(*this);
    }
    BigIntInherited x(*this);
    BigIntInherited y(other);
    while (y > 0)
    {
        BigIntInherited f(x % y);
        x = y;
        y = f;
    }
    return x;
}

BigIntInherited::BigIntInherited(BigInt parent)
{
    this->digits = parent.getDigits();
    this->_isNegative = parent.IsNegative();
    this->_color = 30;
}

BigIntInherited BigIntInherited::LCM(const BigIntInherited &other) const
{
    return *this / other.GCD(*this) * other;
}

//Returns n-th root of number or the closest n-th root of numbers smaller to it
BigIntInherited BigIntInherited::Root(int n) const
{
    if (n % 2 == 0 && *this < 1)
    {
        return 0;
    }
    if (*this == 0)
    {
        return 0;
    }
    BigIntInherited start(1);
    BigIntInherited end(*this);
    BigIntInherited middle = (start + end) / 2;
    BigIntInherited pow = BigIntInherited::Pow(middle, n);
    while (pow != *this)
    {
        if (pow > *this)
        {
            end = middle;
        }
        else
        { start = middle; }
        middle = (start + end) / 2;
        if (middle == start || middle == end)
        {
            break;
        }
        pow = BigIntInherited::Pow(middle, n);
    }
    return middle;
}



