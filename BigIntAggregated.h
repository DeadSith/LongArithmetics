//
// Created by deadsith on 16.10.16.
//

#ifndef LONGARITHMETICS_BIGINTAGGREGATED_H
#define LONGARITHMETICS_BIGINTAGGREGATED_H

#include "BigInt.h"

class BigIntAggregated
{
private:
    BigInt _bigInt;
    void _setColor(int color);
    int _color;

    BigIntAggregated (const BigInt& number);
public:
    BigIntAggregated operator +(const BigIntAggregated& other) const;
    BigIntAggregated operator -(const BigIntAggregated& other) const;
    BigIntAggregated operator *(const BigIntAggregated& other) const;
    BigIntAggregated operator /(const BigIntAggregated& other) const;
    BigIntAggregated operator %(const BigIntAggregated& other) const;

    BigIntAggregated& operator +=(const BigIntAggregated& other);
    BigIntAggregated& operator -=(const BigIntAggregated& other);
    BigIntAggregated& operator *=(const BigIntAggregated& other);
    BigIntAggregated& operator /=(const BigIntAggregated& other);
    BigIntAggregated& operator %=(const BigIntAggregated& other);
    
    friend bool operator<=(const BigIntAggregated& left, const BigIntAggregated& right);
    friend bool operator>=(const BigIntAggregated& left, const BigIntAggregated& right);
    friend bool operator==(const BigIntAggregated& left, const BigIntAggregated& right);
    friend bool operator!=(const BigIntAggregated& left, const BigIntAggregated& right);
    friend bool operator<(const BigIntAggregated& left, const BigIntAggregated& right);
    friend bool operator>(const BigIntAggregated& left, const BigIntAggregated& right);

    ostream& operator<<(ostream& os);
    istream& operator >> (istream& is);

    explicit BigIntAggregated(string number,int color = 30);
    BigIntAggregated();
    BigIntAggregated(long long number,int color = 30);
    BigIntAggregated(vector<int> nums, bool isNegative,int color = 30);
    BigIntAggregated(const BigIntAggregated &obj);


    BigIntAggregated& operator=(const BigIntAggregated& other);
    BigIntAggregated operator ++();
    BigIntAggregated operator ++(int);
    BigIntAggregated operator --();
    BigIntAggregated operator --(int);
    
    int getLength() const;
    bool IsNegative() const;
    
    static BigIntAggregated Pow(const BigIntAggregated& number, unsigned int power);
    BigIntAggregated Abs() const;
    BigIntAggregated GCD(const BigIntAggregated& other) const;
    BigIntAggregated LCM(const BigIntAggregated& other) const;
    BigIntAggregated Root(int n) const;
};


#endif //LONGARITHMETICS_BIGINTAGGREGATED_H
