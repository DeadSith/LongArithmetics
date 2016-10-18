//
// Created by deadsith on 08.10.16.
//

#ifndef LONGARITHMETICS_BIGINTINHERITED_H
#define LONGARITHMETICS_BIGINTINHERITED_H


#include "BigInt.h"


class BigIntInherited : public BigInt
{
public:
    explicit BigIntInherited(string number, int color = 30);
    BigIntInherited();
    BigIntInherited(BigInt parent);
    BigIntInherited(long long number, int color = 30);
    BigIntInherited(vector<int> nums, bool isNegative, int color = 30);
    BigIntInherited(const BigIntInherited &obj);
    
    BigIntInherited &operator=(const BigIntInherited &other);
    
    BigIntInherited& operator++();
    BigIntInherited& operator++(int);
    BigIntInherited& operator--();
    BigIntInherited& operator--(int);
    
    BigIntInherited GCD(const BigIntInherited &other) const;
    BigIntInherited LCM(const BigIntInherited &other) const;
    BigIntInherited Root(int n) const;

private:
    void _setColor(int color);
    int _color;
        
    friend ostream &operator<<(ostream &os, const BigIntInherited &obj);
    friend istream &operator>>(istream &is, BigIntInherited &obj);
    
};


#endif //LONGARITHMETICS_BIGINTINHERITED_H
