#pragma once
template <class T>
class customVector
{
public:
	customVector();
	customVector(size_t size, T element);
	~customVector();
	size_t size() const;
	void pop_back();
	void clear();
	void push_back(T element);
	T operator[](size_t index) const;
private:
	int _size;
	T elements[2000];
};
