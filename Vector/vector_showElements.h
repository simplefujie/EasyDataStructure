#pragma once
template<typename T>
inline int Vector<T>::showVectorElements()
{
	for (Rank i = 0; i < _size; i++)
	{
		std::cout << _elem[i] << " ";
	}
	std::cout << std::endl;
	return _size;
}