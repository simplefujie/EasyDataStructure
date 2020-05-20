#pragma once
/**
@Description: double _capacity when vector doesn't have enough space
*/
template<typename T>
inline void Vector<T>::expand()
{
	if (_size < _capacity)return;
	if (_capacity < DEFAULT_CAPACITY)_capacity = DEFAULT_CAPACITY;
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];// double _capacity
	for (int i = 0; i < _size; i++)
	{
		_elem[i] = oldElem[i];//copy elem to new space
	}
	delete[] oldElem;
}