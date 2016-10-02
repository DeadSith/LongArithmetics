#pragma once
#include <iostream>
#include <vector>

using namespace std;

class BigInt
{
public:
	explicit BigInt(string number);

	BigInt();

	BigInt(long long number);

	BigInt(vector<int> nums, bool isNegative);

	BigInt(const BigInt &obj);

	int getLength() const;

	bool IsNegative() const;

	BigInt& operator+=(const BigInt& number);

	BigInt& operator-=(const BigInt& number);

	BigInt& operator*=(const BigInt& number);

	BigInt& operator/=(const BigInt& number);

	int operator[](size_t index) const;

	explicit operator bool() const;

	BigInt operator+() const;

	BigInt operator-() const;

	BigInt& operator=(const BigInt& other);

	int Compare(BigInt const& other) const;

	bool IsZero() const;	

private:
	bool LessThan(BigInt const& number) const;
	bool _isNegative;
	vector<int> digits;

	static vector<int> Reverse(vector<int> const& numbers);
	void EqualLength(const BigInt& b, vector<int> & number1, vector<int> & number2) const;
	void ToVector(string const& number);
	void ToVector(long long a);
	friend BigInt Abs(BigInt number);

	friend ostream& operator<<(ostream& os, const BigInt& obj);
	friend istream& operator >> (istream& is, BigInt& obj);

	friend BigInt operator+(const BigInt& left, const BigInt& right);
	friend BigInt operator-(const BigInt& left, const BigInt& right);
	friend BigInt operator*(const BigInt& left, const BigInt& right);
	friend BigInt operator/(const BigInt& left, const BigInt& right);

	friend bool operator<=(const BigInt& left, const BigInt& right);
	friend bool operator>=(const BigInt& left, const BigInt& right);
	friend bool operator==(const BigInt& left, const BigInt& right);
	friend bool operator!=(const BigInt& left, const BigInt& right);
	friend bool operator<(const BigInt& left, const BigInt& right);
	friend bool operator>(const BigInt& left, const BigInt& right);
};