#pragma once
#include <iostream>
#include <vector>

using namespace std;

class BigInt
{
public:
	explicit BigInt(string number);

	BigInt();

	explicit BigInt(long long number);

	explicit BigInt(int number);

	BigInt(vector<int> nums, bool is_neg);

	BigInt(const BigInt &obj);

	int getLength() const;

	bool IsNegative() const;

	BigInt& operator+=(const BigInt& b);

	BigInt& operator-=(const BigInt& b);

	BigInt& operator*=(const BigInt& number2);

	BigInt& operator/=(const BigInt& b);

	int operator[](size_t index) const;

	explicit operator bool() const;

	BigInt operator+() const;

	BigInt operator-() const;

	BigInt& operator=(const BigInt& other);

	int Compare(BigInt const& rhs) const;

	bool IsZero() const;

	string ToString() const;

private:
	bool _Compare(BigInt const& rhs) const;
	bool _isNegative;
	vector<int> numbers;

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
	friend BigInt operator/(const BigInt& lhs, const BigInt& rhs);

	friend bool operator<=(const BigInt& left, const BigInt& right);
	friend bool operator>=(const BigInt& left, const BigInt& right);
	friend bool operator==(const BigInt& left, const BigInt& right);
	friend bool operator!=(const BigInt& left, const BigInt& right);
	friend bool operator<(const BigInt& left, const BigInt& right);
	friend bool operator>(const BigInt& left, const BigInt& right);
};

/*BigInt Abs(BigInt number);

ostream& operator<<(ostream& os, const BigInt& obj);
istream& operator >> (istream& is, BigInt& obj);

BigInt operator+(const BigInt& left, const BigInt& right);
BigInt operator-(const BigInt& left, const BigInt& right);
BigInt operator*(const BigInt& left, const BigInt& right);
BigInt operator/(const BigInt& lhs, const BigInt& rhs);

bool operator<=(const BigInt& left, const BigInt& right);
bool operator>=(const BigInt& left, const BigInt& right);
bool operator==(const BigInt& left, const BigInt& right);
bool operator!=(const BigInt& left, const BigInt& right);
bool operator<(const BigInt& left, const BigInt& right);
bool operator>(const BigInt& left, const BigInt& right);*/
