#include "customVector.h"

template <class T>
customVector<T>::customVector()
{
	_size = -1;
}

template <class T>
customVector<T>::customVector(size_t size, T element)
{
	_size = size;
	for (auto i = 0; i < size; i++)
		elements[i] = element;
}

template <class T>
customVector<T>::~customVector()
{
}

template <class T>
size_t customVector<T>::size() const
{
	return _size+1;
}

template <class T>
void customVector<T>::pop_back()
{
	if (_size > 0)
		_size--;
}

template <class T>
void customVector<T>::clear()
{
	_size = -1;
}

template <class T>
void customVector<T>::push_back(T element)
{
	_size++;
	elements[_size] = element;
}

template <class T>
T customVector<T>::operator[](size_t index) const
{
	if(index<_size)
		return elements[index];
	throw "Out of range";
}
