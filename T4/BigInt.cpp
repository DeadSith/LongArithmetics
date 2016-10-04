#include <string>
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

BigInt::BigInt(vector<int> nums, bool is_neg)
{
	digits = nums;
	_isNegative = is_neg;
}

BigInt::BigInt(const BigInt &obj) {
	_isNegative = obj.IsNegative();

	for (int d : obj.digits)
	{
		digits.push_back(d);
	}
}

BigInt::~BigInt()
{
	digits.clear();
}

int BigInt::getLength() const
{
	return digits.size();
}

bool BigInt::IsNegative() const
{
	return _isNegative;
}

BigInt& BigInt::operator+=(const BigInt& number)
{
	if (!IsNegative() && number.IsNegative())
	{
		BigInt temp(number);
		temp = Abs(temp);
		return operator-=(temp);
	}

	if (IsNegative() && !number.IsNegative())
	{
		auto thisValue = BigInt(*this);
		thisValue._isNegative = false;
		auto temp = BigInt(number);
		temp -= thisValue;
		*this = temp;
		return *this;
	}

	vector<int> number1;
	vector<int> number2;

	EqualLength(number, number1, number2);

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

	auto reverse_result = Reverse(result);

	(*this).digits = reverse_result;

	return *this;
}

BigInt& BigInt::operator-=(const BigInt& number)
{
	if (!IsNegative() && number.IsNegative())
	{
		return (*this)+=(Abs(number));
	}

	if (IsNegative() && !number.IsNegative())
	{
		auto temp(number);
		temp._isNegative = true;
		return *this+=(temp);
	}

	vector<int> number1;
	vector<int> number2;

	EqualLength(number, number1, number2);

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
		digits = t;
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
	vector<int> clearResult;//результат без нулів
	auto copy = false;
	for (int i = result.size() - 1; i >= 0; --i)
		{		
		if (result[i] != 0)
		{
			copy = true;
		}

		if (copy)
		{
			clearResult.push_back(result[i]);
		}
	}

	(*this).digits = clearResult;

	if (!IsNegative() && !number.IsNegative())
	{
		if (number1Bigger == -1)
		{
			_isNegative = true;
		}
	}

	if (IsNegative() && number.IsNegative())
	{
		if (number1Bigger == -1)
		{
			_isNegative = false;
		}
	}

	return *this;
}

BigInt& BigInt::operator*=(const BigInt& number)
{
	auto a = Reverse(digits);
	auto b = Reverse(number.digits);
	vector<int> c(a.size() + b.size(), 0);
	for (auto i = 0; i < a.size(); i++)
	{
		int carry = 0;
		for (auto j = 0; j < b.size() || carry; j++)
		{
			auto cur = c[i + j] + a[i]  * (j<b.size()?b[j]:0) + carry;
			c[i + j] = int(cur % 10);
			carry = int(cur / 10);
		}
	}
	while (c.size() > 1 && c.back() == 0)
	{
		c.pop_back();
	}
	auto result = Reverse(c);
	digits = result;
	if (IsNegative() && !number.IsNegative())
	{
		_isNegative = true;
	}
	else if (!IsNegative() && number.IsNegative())
	{
		_isNegative = true;
	}
	else
	{
		_isNegative = false;
	}

	return *this;	
}

BigInt& BigInt::operator/=(const BigInt& number)
{
	if (number.IsZero())
	{
		cerr<< "Division by zero";
		cin.get();
		exit(-1);
	}
	if (IsZero())
	{
		vector<int> temp;
		temp.push_back(0);
		digits = temp;
		_isNegative = false;
		return *this;
	}

	bool number2Bigger = Abs(*this).LessThan(Abs(number));

	if (number2Bigger)
	{
		vector<int> temp;
		temp.push_back(0);
		digits = temp;
		_isNegative = false;
		return *this;
	}

	vector<int> res;
	for (int i = 0; i < (*this).getLength(); i++)
	{
		res.push_back(0);
	}
	BigInt currentValue(0);
	auto abs = Abs(number);
	for (int i = 0; i < (*this).getLength(); ++i)
	{
		currentValue = currentValue * 10;
		currentValue.digits[currentValue.getLength() - 1] = (*this).digits[i];

		int x = 0;
		int left = 0;
		int right = 10;

		while (left <= right)
		{
			int middle = (left + right) /2;

			auto cur = abs * middle;

			if (Abs(cur) <= Abs(currentValue))
			{
				x = middle;
				left = middle + 1;
			}
			else
			{
				right = middle - 1;
			}
		}

		res[i] = x;
		currentValue = currentValue - abs * x;
	}

	res = Reverse(res);

	while (res.size() > 1 && res.back() == 0)
	{
		res.pop_back();
	}

	res = Reverse(res);

	digits = res;
	if (IsNegative() && !number.IsNegative())
	{
		_isNegative = true;
	}
	else if (!IsNegative() && number.IsNegative())
	{
		_isNegative = true;
	}
	else
	{
		_isNegative = false;
	}

	return *this;
}

//Знак залежить від знаку першого числа
BigInt& BigInt::operator%=(const BigInt& number)
{
	(*this) = (*this) - ((*this) / number)*number;
	return *this;
}

int BigInt::operator[](size_t index) const
{
	return digits[index];
}

BigInt::operator bool() const
{
	return !IsZero();
}

BigInt BigInt::operator+() const
{
	BigInt res(*this);
	return res;
}

BigInt BigInt::operator-() const
{
	BigInt res(*this);

	if (IsNegative())
	{
		res._isNegative = false;
	}
	else
	{
		res._isNegative = true;
	}

	return res;
}

BigInt& BigInt::operator=(const BigInt& other)
{
	if (this != &other)
	{
		digits = other.digits;
		_isNegative = other.IsNegative();
	}
	return *this;
}

//порівнює
bool BigInt::LessThan(BigInt const& other) const
{
	if (IsNegative() && !other.IsNegative())
	{
		return true;
	}

	if (!IsNegative() && other.IsNegative())
	{
		return false;
	}

	if (getLength() < other.getLength())
	{
		return true;
	}

	if (getLength() > other.getLength())
	{
		return false;
	}

	for (int i = 0; i < getLength(); ++i)
	{
		if (digits[i] < other[i])
		{
			if (IsNegative())
			{
				return false;
			}
			return true;
		}
		if (digits[i] > other[i])
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
int BigInt::Compare(BigInt const& other) const
{
	if ((*this).LessThan(other))
	{
		return -1;
	}
	if (other.LessThan(*this))
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
	if (digits.size() == 1 && digits[0] == 0)
	{
		return true;
	}

	return false;
}

bool BigInt::IsPrime(BigInt number)
{
	if (number <= 1) return false;
	if (number <= 3) return true;
	if (number%2==0||number%3==0)
		return false;
	unsigned long long k = 1;
	BigInt b(6*k-1);
	 while (b*b<=number)
	{
		if (number%b == 0)
			return false;
		b += 2;
		if (number%b == 0)
			return false;
		k++;
		b = 6 * k - 1;
	}
	return true;
}

BigInt BigInt::Pow(const BigInt& number, unsigned int power)
{
	if (power == 0)
		return 1;
	if (power == 1)
		return number;
	BigInt res(number);
	for (unsigned i = 1; i < power; i++)
		res *= number;
	return res;
}

BigInt BigInt::Factorial(unsigned n)
{
	if (n < 2)
		return 1;
	BigInt res(2);
	for (unsigned i = 3; i <= n; i++)
		res *= i;
	return res;
}

vector<int> BigInt::Reverse(vector<int> const& digits)
{
	vector<int> reverse_result;

	for (int i = digits.size() - 1; i >= 0; --i)
	{
		reverse_result.push_back(digits[i]);
	}

	return reverse_result;
}

void BigInt::EqualLength(BigInt const& b, vector<int>& number1, vector<int>& number2) const
{
	int diff = getLength() - b.getLength();

	if (diff > 0)
	{
		number1 = (*this).digits;

		for (int i = 0; i < diff; ++i)
		{
			number2.push_back(0);
		}

		for (int i = 0; i < b.getLength(); ++i)
		{
			number2.push_back(b[i]);
		}
	}
	else if (diff < 0)
	{
		for (int i = 0; i < b.getLength(); ++i)
		{
			number2.push_back(b[i]);
		}

		for (int i = 0; i < (diff * (-1)); ++i)
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
	auto from = 0;
	if (number[0] == '-')
	{
		_isNegative = true;
		from = 1;
	}
	else
	{
		_isNegative = false;
	}
	for (auto i = from; i < number.length(); i++)
	{
		digits.push_back(number[i] - '0');
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
		digits.push_back(0);
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
		digits.push_back(temp[i]);
	}
}

BigInt Abs(BigInt number)
{
	number._isNegative = false;
	return number;
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

	BigInt temp(numbers, negative);
	obj = temp;

	return is;
}

BigInt operator+(const BigInt& left, const BigInt& right)
{
	auto temp(left);
	return temp += right;
}

BigInt operator-(const BigInt& left, const BigInt& right)
{
	auto temp(left);
	return temp -= right;
}

BigInt operator*(const BigInt& left, const BigInt& right)
{
	auto temp(left);
	return temp *= right;
}

BigInt operator/(const BigInt& left, const BigInt& right)
{
	auto temp(left);
	return temp /= right;
}

BigInt operator%(const BigInt& left, const BigInt& right)
{
	auto temp(left);
	return temp %= right;
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