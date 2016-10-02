#include <string>
#include <sstream>
#include <vector>
#include "BigInt.h"

BigInt::BigInt(string number)
{
	ToVector(number);
}

BigInt::BigInt()
{
	ToVector(0);
}

BigInt::BigInt(long long number)
{
	ToVector(number);
}

BigInt::BigInt(int number)
{
	ToVector(number);
}

BigInt::BigInt(vector<int> nums, bool is_neg)
{
	numbers = nums;
	_isNegative = is_neg;
}

BigInt::BigInt(const BigInt &obj) {
	_isNegative = obj.IsNegative();

	for (int t : obj.numbers)
	{
		numbers.push_back(t);
	}
}

int BigInt::getLength() const
{
	return numbers.size();
}

bool BigInt::IsNegative() const
{
	return _isNegative;
}

BigInt& BigInt::operator+=(const BigInt& b)
{
	if (!IsNegative() && b.IsNegative())
	{
		BigInt temp(b);
		temp = Abs(temp);
		return operator-=(temp);
	}

	if (IsNegative() && !b.IsNegative())
	{
		auto thisValue = BigInt(*this);
		thisValue._isNegative = false;
		auto temp = BigInt(b);
		temp -= thisValue;
		*this = temp;
		return *this;
	}

	vector<int> number1;
	vector<int> number2;

	EqualLength(b, number1, number2);

	vector<int> result;
	int rest = 0;

	for (int i = number1.size() - 1; i >= 0; --i)
	{
		int sum = number1[i] + number2[i] + rest;

		if (sum > 9)
		{
			rest = 1;
			sum -= 10;
		}
		else
		{
			rest = 0;
		}

		result.push_back(sum);
	}

	if (rest > 0)
	{
		result.push_back(rest);
	}

	vector<int> reverse_result = Reverse(result);

	(*this).numbers = reverse_result;

	return *this;
}

BigInt& BigInt::operator-=(const BigInt& b)
{
	if (!IsNegative() && b.IsNegative())
	{
		return (*this)+=(Abs(b));
	}

	if (IsNegative() && !b.IsNegative())
	{
		auto temp(b);
		temp._isNegative = true;
		return (*this)+=(temp);
	}

	vector<int> number1;
	vector<int> number2;

	EqualLength(b, number1, number2);

	int number1Bigger = 0;

	for (unsigned int i = 0; i < number1.size(); ++i)
	{
		if (number1[i] > number2[i])
		{
			number1Bigger = 1;
			break;
		}
		if (number1[i] < number2[i])
		{
			number1Bigger = -1;
			break;
		}
	}

	if (number1Bigger == 0)
	{
		vector<int> t;
		t.push_back(0);
		numbers = t;
		return *this;
	}

	vector<int> result;

	if (number1Bigger == 1)
	{
		for (int i = number1.size() - 1; i >= 0; --i)
		{
			if (number1[i] < number2[i])
			{
				number1[i] += 10;
				number1[i - 1] -= 1;
			}

			int res = number1[i] - number2[i];

			result.push_back(res);
		}
	}
	else if (number1Bigger == -1)
	{
		for (int i = number2.size() - 1; i >= 0; --i)
		{
			if (number2[i] < number1[i])
			{
				number2[i] += 10;
				number2[i - 1] -= 1;
			}

			int res = number2[i] - number1[i];

			result.push_back(res);
		}
	}

	auto can_copy = false;
	vector<int> result_without_zero;

	for (int i = result.size() - 1; i >= 0; --i)
	{
		if (result[i] != 0)
		{
			can_copy = true;
		}

		if (can_copy)
		{
			result_without_zero.push_back(result[i]);
		}
	}

	(*this).numbers = result_without_zero;

	if (!IsNegative() && !b.IsNegative())
	{
		if (number1Bigger == -1)
		{
			_isNegative = true;
		}
	}

	if (IsNegative() && b.IsNegative())
	{
		if (number1Bigger == -1)
		{
			_isNegative = false;
		}
	}

	return *this;
}

BigInt& BigInt::operator*=(const BigInt& number2)
{
	vector<int> a = Reverse(numbers);
	vector<int> b = Reverse(number2.numbers);

	vector<int> c(a.size() + b.size(), 0);

	for (size_t i = 0; i < a.size(); ++i)
	{
		int carry = 0;

		for (unsigned int j = 0; j < b.size() || carry; ++j)
		{
			long long cur = c[i + j] + a[i] * 1ll * (j < b.size() ? b[j] : 0) + carry;

			c[i + j] = int(cur % 10);
			carry = int(cur / 10);
		}
	}

	while (c.size() > 1 && c.back() == 0)
	{
		c.pop_back();
	}

	vector<int> result = Reverse(c);

	numbers = result;

	if (IsNegative() && !number2.IsNegative())
	{
		_isNegative = true;
	}
	else if (!IsNegative() && number2.IsNegative())
	{
		_isNegative = true;
	}
	else
	{
		_isNegative = false;
	}

	return *this;
}

BigInt& BigInt::operator/=(const BigInt& number2)
{
	if (number2.IsZero())
	{
		throw "Division by zero";
	}

	if (IsZero())
	{
		vector<int> temp;
		temp.push_back(0);
		numbers = temp;
		_isNegative = false;
		return *this;
	}

	bool number2Bigger = Abs(*this)._Compare(Abs(number2));

	if (number2Bigger)
	{
		vector<int> temp;
		temp.push_back(0);
		numbers = temp;
		_isNegative = false;
		return *this;
	}

	vector<int> res;
	for (int i = (*this).getLength() - 1; i >= 0; --i)
	{
		res.push_back(0);
	}

	BigInt currentValue(0);
	for (int i = 0; i < (*this).getLength(); ++i)
	{
		currentValue = currentValue * BigInt(10);
		currentValue.numbers[currentValue.getLength() - 1] = (*this).numbers[i];

		int x = 0;
		int left_index = 0;
		int right_index = 10;

		while (left_index <= right_index)
		{
			int middle = (left_index + right_index)/2;

			auto cur = Abs(number2) * BigInt(middle);

			if (Abs(cur) <= Abs(currentValue))
			{
				x = middle;
				left_index = middle + 1;
			}
			else
			{
				right_index = middle - 1;
			}
		}

		res[i] = x;
		currentValue = currentValue - Abs(number2) * BigInt(x);
	}

	res = Reverse(res);

	while (res.size() > 1 && res.back() == 0)
	{
		res.pop_back();
	}

	res = Reverse(res);

	numbers = res;

	if (IsNegative() && !number2.IsNegative())
	{
		_isNegative = true;
	}
	else if (!IsNegative() && number2.IsNegative())
	{
		_isNegative = true;
	}
	else
	{
		_isNegative = false;
	}

	return *this;
}

int BigInt::operator[](size_t index) const
{
	return numbers[index];
}

BigInt::operator bool() const
{
	return !IsZero();
}

BigInt BigInt::operator+() const
{
	BigInt temp(*this);
	return temp;
}

BigInt BigInt::operator-() const
{
	BigInt temp(*this);

	if (IsNegative())
	{
		temp._isNegative = false;
	}
	else
	{
		temp._isNegative = true;
	}

	return temp;
}

BigInt& BigInt::operator=(const BigInt& other)
{
	if (this != &other)
	{
		numbers = other.numbers;
		_isNegative = other.IsNegative();
	}
	return *this;
}

//порівнює
bool BigInt::_Compare(BigInt const& rhs) const
{
	if (IsNegative() && !rhs.IsNegative())
	{
		return true;
	}

	if (!IsNegative() && rhs.IsNegative())
	{
		return false;
	}

	if (getLength() < rhs.getLength())
	{
		return true;
	}

	if (getLength() > rhs.getLength())
	{
		return false;
	}

	for (int i = 0; i < getLength(); ++i)
	{
		if (numbers[i] < rhs[i])
		{
			if (IsNegative())
			{
				return false;
			}
			return true;
		}
		if (numbers[i] > rhs[i])
		{
			if (IsNegative())
			{
				return true;
			}
			return false;
		}
	}

	return false;
}

//обгортка для порівняння
int BigInt::Compare(BigInt const& rhs) const
{
	if ((*this)._Compare(rhs))
	{
		return -1;
	}
	if (rhs._Compare(*this))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool BigInt::IsZero() const
{
	if (numbers.size() == 1 && numbers[0] == 0)
	{
		return true;
	}

	return false;
}

string int_to_string(int i)
{
	stringstream ss;
	string s;
	ss << i;
	s = ss.str();

	return s;
}

string BigInt::ToString() const
{
	string result = "";

	if (IsNegative() && !IsZero())
	{
		result += "-";
	}

	for (int i = 0; i < getLength(); ++i)
	{
		int a = (*this)[i];
		result += int_to_string(a);
	}

	return result;
}

vector<int> BigInt::Reverse(vector<int> const& numbers)
{
	vector<int> reverse_result;

	for (int i = numbers.size() - 1; i >= 0; --i)
	{
		reverse_result.push_back(numbers[i]);
	}

	return reverse_result;
}

void BigInt::EqualLength(BigInt const& b, vector<int>& number1, vector<int>& number2) const
{
	int diff_length = getLength() - b.getLength();

	if (diff_length > 0)
	{
		number1 = (*this).numbers;

		for (int i = 0; i < diff_length; ++i)
		{
			number2.push_back(0);
		}

		for (int i = 0; i < b.getLength(); ++i)
		{
			number2.push_back(b[i]);
		}
	}
	else if (diff_length < 0)
	{
		for (int i = 0; i < b.getLength(); ++i)
		{
			number2.push_back(b[i]);
		}

		for (int i = 0; i < (diff_length * (-1)); ++i)
		{
			number1.push_back(0);
		}

		for (int i = 0; i < getLength(); ++i)
		{
			number1.push_back((*this)[i]);
		}
	}
	else
	{
		for (int i = 0; i < b.getLength(); ++i)
		{
			number1.push_back((*this)[i]);
			number2.push_back(b[i]);
		}
	}
}

void BigInt::ToVector(string const& number)
{
	unsigned int from = 0;

	if (number[0] == '-')
	{
		_isNegative = true;
		from = 1;
	}
	else
	{
		_isNegative = false;
	}

	for (unsigned int i = from; i < number.length(); ++i)
	{
		int ia = number[i] - '0';
		numbers.push_back(ia);
	}
}

void BigInt::ToVector(long long a)
{
	if (a < 0)
	{
		_isNegative = true;
		a = (-1) * a;
	}
	else
	{
		_isNegative = false;
	}

	if (a == 0)
	{
		numbers.push_back(0);
	}

	vector<int> temp;

	while (a)
	{
		int x = a % 10;
		a /= 10;
		temp.push_back(x);
	}

	for (int i = temp.size() - 1; i >= 0; --i)
	{
		numbers.push_back(temp[i]);
	}
}

BigInt Abs(BigInt number)
{
	BigInt n(number);
	BigInt zero(0);

	bool is_less = n._Compare(zero);

	if (is_less)
	{
		n *= BigInt(-1);
	}
	return n;
}

ostream& operator<<(ostream& os, const BigInt& obj)
{
	if (obj.IsNegative())
	{
		os << "-";
	}

	for (int i = 0; i < obj.getLength(); ++i)
	{
		os << obj[i];
	}

	return os;
}

istream& operator >> (istream& is, BigInt& obj)
{
	bool leadZeros = true;
	bool negative = false;
	vector<int> numbers;

	while (is.good())
	{
		char c = static_cast<char>(is.get());
		int ic = c - '0';

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
			else if (ic == 0 && leadZeros)
			{
			}
			else
			{
				numbers.push_back(ic);
				leadZeros = false;
			}
		}
	}

	BigInt temp(numbers, negative);
	obj = temp;

	return is;
}

BigInt operator+(const BigInt& lhs, const BigInt& rhs)
{
	auto temp(lhs);
	return temp += rhs;
}

BigInt operator-(const BigInt& lhs, const BigInt& rhs)
{
	auto temp(lhs);
	return temp -= rhs;
}

BigInt operator*(const BigInt& lhs, const BigInt& rhs)
{
	auto temp(lhs);
	return temp *= rhs;
}

BigInt operator/(const BigInt& lhs, const BigInt& rhs)
{
	auto temp(lhs);
	return temp /= rhs;
}

bool operator<=(const BigInt& left, const BigInt& right)
{
	return left.Compare(right) <= 0;
}

bool operator>=(const BigInt& left, const BigInt& right)
{
	return left.Compare(right) >= 0;
}

bool operator==(const BigInt& left, const BigInt& right)
{
	return left.Compare(right) == 0;
}

bool operator!=(const BigInt& left, const BigInt& right)
{
	return left.Compare(right) != 0;
}

bool operator<(const BigInt& left, const BigInt& right)
{
	return left.Compare(right) < 0;
}

bool operator>(const BigInt& left, const BigInt& right)
{
	return left.Compare(right) > 0;
}