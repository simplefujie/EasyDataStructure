#pragma once
/**
@Description: Overload subscript operator, which can refer to each element in the form of an array
@Return: Reference of element with rank r
*/
template<typename T>
inline T& Vector<T>::operator[](Rank r) const
{
	if (r >= _size)
	{
		std::cout << "Warning: your input  rank is bigger than vector size" << std::endl;
		T result = -1;
		return result;
	}
	return _elem[r];
}

