#include "vector.h"
#include <math.h>
#include <random>
template<typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
	// ����ռ䣬��ģ����
	_elem = new T[_capacity = 2 * (hi - lo)];
	size = 0;

	// �������Ԫ�أ���A����ǰ����
	while (hi<lo)
	{
		_elem[size++] = A[lo++];
	}
}

template<typename T>
void Vector<T>::expand()
{
	if (_size < _capacity) return; //��δ��Աʱ����������
	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY; //��������С����
	T* oldElem = _elem;  _elem = new T[_capacity <<= 1]; //�����ӱ�
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i]; //����ԭ�������ݣ�TΪ�������ͣ��������ظ�ֵ������'='��
	delete[] oldElem; //�ͷ�ԭ�ռ�
}

template<typename T>
void Vector<T>::shrink()
{
	if (_capacity < DEFAULT_CAPACITY << 1) return; //����������DEFAULT_CAPACITY����
	if (_size << 2 > _capacity) return; //��25%Ϊ��
	T* oldElem = _elem;  _elem = new T[_capacity >>= 1]; //��������
	for (int i = 0; i < _size; i++) _elem[i] = oldElem[i]; //����ԭ��������
	delete[] oldElem; //�ͷ�ԭ�ռ�
}


template<typename T>
inline Vector<T>& Vector<T>::operator=(Vector<T> const& V)
{
	if (_elem) delete[] _elem;
	copyFrom(V._elem, 0, V._size);
	return *this; // ���ص�ǰ��������ã��Ա���ʽ��ֵ
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