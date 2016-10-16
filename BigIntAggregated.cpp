//
// Created by deadsith on 16.10.16.
//

#include "BigIntAggregated.h"

void BigIntAggregated::_setColor(int color)
{
    if (color > 29 && color < 38)
    {
        _color = color;
    }
    else
    { _color = 30; }
}

BigIntAggregated::BigIntAggregated(const BigInt &number)
{
    this->_bigInt = BigInt(number);
    _setColor(30);
}

BigIntAggregated::BigIntAggregated()
{
    _setColor(30);
    this->_bigInt = BigInt();
}

BigIntAggregated::BigIntAggregated(string number, int color)
{
    this->_bigInt = BigInt(number);
    _setColor(color);
}

BigIntAggregated::BigIntAggregated(long long number, int color)
{
    this->_bigInt = BigInt(number);
    _setColor(color);
}

BigIntAggregated::BigIntAggregated(vector<int> nums, bool isNegative, int color)
{
    this->_bigInt = BigInt(nums, isNegative);
    _setColor(color);
}

BigIntAggregated::BigIntAggregated(const BigIntAggregated &obj)
{
    _color = obj._color;
    this->_bigInt = BigInt(obj._bigInt);
}

BigIntAggregated &BigIntAggregated::operator=(const BigIntAggregated &other)
{
    if (this != &other)
    {
        this->_bigInt = BigInt(other._bigInt);
        _color = other._color;
    }
    return *this;
}

BigIntAggregated BigIntAggregated::operator++()
{
    *this += 1;
    return *this;
}

BigIntAggregated BigIntAggregated::operator++(int)
{
    *this += 1;
    return *this;
}

BigIntAggregated BigIntAggregated::operator--()
{
    *this -= 1;
    return *this;
}

BigIntAggregated BigIntAggregated::operator--(int)
{
    *this -= 1;
    return *this;
}

int BigIntAggregated::getLength() const
{
    return this->_bigInt.getLength();
}

bool BigIntAggregated::IsNegative() const
{
    return this->_bigInt.IsNegative();
}

BigIntAggregated BigIntAggregated::Abs() const
{
    return BigIntAggregated(this->_bigInt.getDigits(), false, _color);
}

BigIntAggregated BigIntAggregated::operator+(const BigIntAggregated &other) const
{
    return BigIntAggregated(this->_bigInt + other._bigInt);
}

BigIntAggregated BigIntAggregated::operator-(const BigIntAggregated &other) const
{
    return BigIntAggregated(this->_bigInt - other._bigInt);
}

BigIntAggregated BigIntAggregated::operator*(const BigIntAggregated &other) const
{
    return BigIntAggregated(this->_bigInt * other._bigInt);
    
}

BigIntAggregated BigIntAggregated::operator/(const BigIntAggregated &other) const
{
    return BigIntAggregated(this->_bigInt / other._bigInt);
    
}

BigIntAggregated BigIntAggregated::operator%(const BigIntAggregated &other) const
{
    return BigIntAggregated(this->_bigInt % other._bigInt);
}

BigIntAggregated &BigIntAggregated::operator+=(const BigIntAggregated &other)
{
    this->_bigInt += other._bigInt;
    return *this;
}

BigIntAggregated &BigIntAggregated::operator-=(const BigIntAggregated &other)
{
    this->_bigInt -= other._bigInt;
    return *this;
}

BigIntAggregated &BigIntAggregated::operator*=(const BigIntAggregated &other)
{
    this->_bigInt *= other._bigInt;
    return *this;
}

BigIntAggregated &BigIntAggregated::operator/=(const BigIntAggregated &other)
{
    this->_bigInt /= other._bigInt;
    return *this;
}

BigIntAggregated &BigIntAggregated::operator%=(const BigIntAggregated &other)
{
    this->_bigInt %= other._bigInt;
    return *this;
}

ostream &BigIntAggregated::operator<<(ostream &os)
{
    os << "\033[0;" << this->_color << "m";
    os << this->_bigInt;
    os << "\033[0;" << 30 << "m";
    return os;
}

istream &BigIntAggregated::operator>>(istream &is)
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
    BigIntAggregated temp(numbers, negative, color);
    *this = temp;
    return is;
}

BigIntAggregated BigIntAggregated::GCD(const BigIntAggregated &other) const
{
    if (*this < other)
    {
        return other.GCD(*this);
    }
    BigIntAggregated x(*this);
    BigIntAggregated y(other);
    while (y > 0)
    {
        BigIntAggregated f(x % y);
        x = y;
        y = f;
    }
    return x;
}

BigIntAggregated BigIntAggregated::LCM(const BigIntAggregated &other) const
{
    return (*this / other.GCD(*this)) * other;
}

bool operator<=(const BigIntAggregated &left, const BigIntAggregated &right)
{
    return left._bigInt <= right._bigInt;
}

bool operator>=(const BigIntAggregated &left, const BigIntAggregated &right)
{
    return left._bigInt >= right._bigInt;
}

bool operator==(const BigIntAggregated &left, const BigIntAggregated &right)
{
    return left._bigInt == right._bigInt;
}

bool operator!=(const BigIntAggregated &left, const BigIntAggregated &right)
{
    return left._bigInt != right._bigInt;
}

bool operator>(const BigIntAggregated &left, const BigIntAggregated &right)
{
    return left._bigInt > right._bigInt;
}

bool operator<(const BigIntAggregated &left, const BigIntAggregated &right)
{
    return left._bigInt < right._bigInt;
}

BigIntAggregated BigIntAggregated::Root(int n) const
{
    if (n % 2 == 0 && *this < 1)
    {
        return 0;
    }
    if (*this == 0)
    {
        return 0;
    }
    BigIntAggregated start(1);
    BigIntAggregated end(*this);
    BigIntAggregated middle = (start + end) / 2;
    BigIntAggregated pow = BigIntAggregated::Pow(middle, n);
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
        pow = BigIntAggregated::Pow(middle, n);
    }
    return middle;
}

BigIntAggregated BigIntAggregated::Pow(const BigIntAggregated &number, unsigned int power)
{
    return BigIntAggregated(BigInt::Pow(number._bigInt,power));
}
