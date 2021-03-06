// T4.cpp : Defines the entry point for the console application.
//
#include "BigInt.h"
#include "assert.h"
#include "BigIntInherited.h"
#include "BigIntAggregated.h"

void test()
{
    BigIntAggregated a("120");
    BigIntAggregated b("0");
    assert(a - b == a);
    assert(a + b == a);
    assert(a * b == b);
    a = BigIntAggregated("120134");
    b = BigIntAggregated("213");
    assert(a / b == 564);
    assert(a * b == 25588542);
    a = BigIntAggregated(
            "100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
    b = BigIntAggregated("9999999999999999931398190359470212947659194368");
    BigIntAggregated res("10000000000000000068601809640529787522961634227");
    assert(a / b == res);
    a = -5;
    b = 2;
    assert(a / b == -2);
    assert(a == -5);
    a = 100000000175;
    b = -278;
    res = BigIntAggregated("-359712230");
    assert(a / b == res);
    a = 500000;
    b = 2500;
    assert(a % b == 0);
    a = 15;
    b = 606;
    assert(b.GCD(a) == a.GCD(b));
    assert(a.GCD(b) == 3);
    b = 605;
    assert(a.GCD(b) == 5);
    b = 600;
    assert(b.GCD(a) == 15);
    a = 3;
    b = 5;
    assert(a.LCM(b) == 15);
    a = 8;
    assert(a.Root(3) == 2);
}

int main()
{
    test();
    /*cin >> b;
    cout << b;
    auto p = BigIntInherited::Pow(2, 50) + 1;
    cout << BigIntInherited::IsPrime(p) << endl;
    cout << BigIntInherited::Pow(2, 10) <<endl;
    cout << BigIntInherited::Pow(2, 100) << endl;
    cout << BigIntInherited::Factorial(100) << endl;*/
    BigIntAggregated a;
    cin>>a;
    (a++)++;
    cout << a << endl;
    cin.get();
    return 0;
}