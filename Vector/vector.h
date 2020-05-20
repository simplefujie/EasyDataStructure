#pragma once
#include <iostream>
typedef int Rank; //rank
#define DEFAULT_CAPACITY  3 //Default initial capacity (can be set larger in practical applications)

template <typename T> class Vector { //Vector template class
protected:
    Rank _size; int _capacity;  T* _elem; //Scale, capacity, data area
    void expand();// expand _capacity when vector doesn't have enough space
public:
    // constructors
    Vector(int c = DEFAULT_CAPACITY, Rank s = 0, T v = 0)
    {
        _capacity = c; _size = s;
        _elem = new T[_capacity];
        for (Rank i = 0; i < _size; i++)
        {
            _elem[i] = v;
        }
    }
    Vector(T const* A, Rank n) { copyFrom(A, 0, n); } //Array copy
    Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //Array partial copy
    Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); } //vector copy
    Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //vector partial copy
    // destructor
    ~Vector() { delete[] _elem; } //free up internal space
    int showVectorElements();
    T& operator[](Rank r)const;
    Rank insert(Rank r, T const& e);
}; //Vector

#include "vector_implementation.h"