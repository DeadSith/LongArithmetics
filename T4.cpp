// T4.cpp : Defines the entry point for the console application.
//
#include "BigInt.h"
#include "assert.h"

void test()
{
	BigInt a("120");
	BigInt b("0");
	assert(a - b == a);
	assert(a + b == a);
	assert(a*b == b);
	a = BigInt("120134");
	b = BigInt("213");
	assert(a / b == 564);
	assert(a*b == 25588542);
	a = BigInt("100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
	b = BigInt("9999999999999999931398190359470212947659194368");
	BigInt res("10000000000000000068601809640529787522961634227");
	assert(a / b == res);
	a = -5;
	b = 2;
	assert(a / b == -2);
	a = 100000000175;
	b = -278;
	res = BigInt("-359712230");
	auto c = a / b;
	assert(a / b == res);
	a = 500000;
	b = 2500;
	assert(a%b == 0);
}

int main()
{
	test();	
	auto p = BigInt::Pow(2, 50) + 1;
	cout << BigInt::IsPrime(p) << endl;
	cout << BigInt::Pow(2, 10) <<endl;
	cout << BigInt::Pow(2, 100) << endl;
	cout << BigInt::Factorial(100) << endl;
	cin.get();
	return 0;
}