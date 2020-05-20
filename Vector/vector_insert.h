#pragma once

/**
@Description: insert element e where the rank of vector is r
@Return: the rank where e is inserted
*/
template<typename T>
inline Rank Vector<T>::insert(Rank r, T const& e)
{
	expand();//judge if we need to expand vector
	for (int i = _size; i > r; i--)
	{
		_elem[i] = _elem[i-1];
	}
	_elem[r] = e;
	_size++;
	return r;
}