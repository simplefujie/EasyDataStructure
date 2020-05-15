#include "vector.h"
#include <math.h>
#include <random>
template<typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
	// 分配空间，规模清零
	_elem = new T[_capacity = 2 * (hi - lo)];
	size = 0;

	// 逐个复制元素，从A到当前向量
	while (hi<lo)
	{
		_elem[size++] = A[lo++];
	}
}

template<typename T>
void Vector<T>::expand()
{
	if (_size < _capacity) return; //尚未满员时，不必扩容
	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY; //不低于最小容量
	T* oldElem = _elem;  _elem = new T[_capacity <<= 1]; //容量加倍
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i]; //复制原向量内容（T为基本类型，或已重载赋值操作符'='）
	delete[] oldElem; //释放原空间
}

template<typename T>
void Vector<T>::shrink()
{
	if (_capacity < DEFAULT_CAPACITY << 1) return; //不致收缩到DEFAULT_CAPACITY以下
	if (_size << 2 > _capacity) return; //以25%为界
	T* oldElem = _elem;  _elem = new T[_capacity >>= 1]; //容量减半
	for (int i = 0; i < _size; i++) _elem[i] = oldElem[i]; //复制原向量内容
	delete[] oldElem; //释放原空间
}


template<typename T>
inline Vector<T>& Vector<T>::operator=(Vector<T> const& V)
{
	if (_elem) delete[] _elem;
	copyFrom(V._elem, 0, V._size);
	return *this; // 返回当前对象的引用，以便链式赋值
}

template<typename T>
T& Vector<T>::operator[](Rank r)
{
	return _elem[r];
}

template<typename T>
const T& Vector<T>::operator[](Rank r) const
{
	return _elem[r];
}

template<typename T>
inline void Vector<T>::unsort(Rank lo, Rank hi)
{
	T* V = _elem + lo;
	for (Rank i = hi - lo; i > 0; i--)
	{
		swap(V[i - 1], V[rand() % i]);
	}
}