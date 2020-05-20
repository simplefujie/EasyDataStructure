#include "vector.h"
#include<iostream>
using namespace std;

int main()
{
	Vector<int> myVector(3,3,3);
	myVector.showVectorElements();
	myVector.insert(0, 1);
	cout << myVector[0];
	return 0;
}
