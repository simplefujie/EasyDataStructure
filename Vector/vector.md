## 第二章 向量

### (a) 接口与实现

向量属于线性结构。

本章主要介绍如何定制数据结构的接口以及如何利用算法来高效的实现我们所定制的接口。如向量查找和排序的算法。

首先区分以下什么使抽象数据类型ADT，什么使数据结构DS

- 抽象数据类型=数据模型+一组定义在该数据模型上的**操作**
- 数据结构=基于某种特定语言来实现ADT的一套**算法**。同一种抽象数据类型可能由多种数据结构来实现。

然后我们来区分以下什么使接口，什么是实现

- **接口**时抽象数据类型提供给外部使用者的功能
- **实现**是抽象数据类型实现它所承诺的功能的具体方法

向量和数组的关系：向量可以看成是数组的抽象与泛化，它由一组元素按照线性次序**封装**而成。各个元素可以**寻秩访问**，元素的类型不限于基本的数据类型。维护更加统一和安全，支持更为复杂的数据结构的定制与实现。

#### 析构与构造函数

构造函数一共有5种类型：

- 以指定的元素填满所有的向量空间
- 数组整体复制
- 数组部分复制
- 向量整体复制
- 向量部分复制

```c++
//5种构造函数
Vector ( int c = DEFAULT_CAPACITY, int s = 0, T v = 0 ) //容量为c、规模为s、所有元素初始为v
   { _elem = new T[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v ); } //s<=c
Vector ( T const* A, Rank n ) { copyFrom ( A, 0, n ); } //数组整体复制
Vector ( T const* A, Rank lo, Rank hi ) { copyFrom ( A, lo, hi ); } //区间
Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); } //向量整体复制
Vector ( Vector<T> const& V, Rank lo, Rank hi ) { copyFrom ( V._elem, lo, hi ); } //区间
// 析构函数
~Vector() { delete [] _elem; } //释放内部空间
```

#### 内部函数：copyFrom

将数组的部分区间复制给向量。原理如下图所示：

![](https://i.loli.net/2020/05/19/Mq9ZwFXjKJmAvz5.png)

```c++
/**
@Description: 数组部分复制。复制数组部分区间给向量，向量容量设置为数组区间的2倍
*/
template<typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
	_elem = new T[_capacity = 2 * (hi - lo)];//给向量分配空间
	//逐一复制数组元素给向量
	_size = 0;
	while (lo<hi)
	{
		_elem[_size++] = A[lo++];//复制到_elem[0,hi)
	}
}
```

参数解释：

- Q：为什么_capacity=2*(hi-low)

  A：因为使_capacity为size的2倍，可以让我们后面进行操作时，不必频繁的执行扩容操作

### （b)可扩充向量

当向量容量即将用完的时候，扩充向量的容量为之前的两倍；当装填因子太小的时候，缩小向量容量

- 上溢：\_size>\_capacity
- 下溢：装填因子λ=\_size/\_capacity<50%

##### 内部函数：expand

向量空间不足的时候，扩充向量容量为原来的两倍，原理图如下：

![](https://i.loli.net/2020/05/19/vfLWOp7xrU8tdRH.png)

```c++
/**
@Description: 向量空间不足的时候，将向量空间扩容为原来的两倍
*/
template<typename T>
void Vector<T>::expand()
{
	if (_size < _capacity)return; //没有发送上溢的时候，直接返回
	_capacity = max(_capacity, DEFAULT_CAPACITY);//不低于最小容量
	T* old = _elem; _elem = new T[_capacity <<= 1];//容量倍增
	for (int i = 0; i < _size; i++)
	{
		_elem[i] = old[i];
	}
	delete[] old;//释放原来的空间
}
```

得益于向量的封装，尽管扩容后数据区的物理地址有所改变，但是不至于出现野指针

Q：为什么容量扩容时采用加倍策略而不是增加固定大小的内存空间

A：采用加倍策略扩容时，扩容的**分摊时间复杂度**为O(1)；采用追加固定内存空间时，扩容分摊时间复杂度是O(n)

### (c)无序向量

#### 向量的寻秩访问

重载运算符[ ]

```c++
/**
@Description：重载运算符[]，实现向量的寻秩访问
@Return：返回一个T类型元素的引用，使用它是为了作为左值使用
*/
template<typename T>
T& Vector<T>::operator[](Rank r) const
{
	return _elem[r];
}
```

#### 向量的插入

在秩r的位置上，插入元素e。自后向前移动元素，以此在秩r的位置上腾出位置。

![QQ截图20200519164816](https://i.loli.net/2020/05/19/R5PsHlAWSOf9GJK.png)

```c++
/**
@Description：在秩为r的位置，插入元素e；
@Return：秩r
*/
template<typename T>
Rank Vector<T>::insert(Rank r, T const& e)
{
	expand();//若有必要，就扩容
	//自后向前，后移元素
	for (int i = _size; i>r ; i--)
	{
		_elem[i] = _elem[i - 1];
	}
	//插入新元素
	_elem[r] = e;
	_size++;
	return r;// 返回秩
}
```

#### 区间删除

删除向量中区间[lo,hi)的所有元素，返回删除元素的个数。自前向后依次复制元素，避免元素被覆盖。

![image-20200519171719247](https://i.loli.net/2020/05/19/JZp74QkP5B92oWf.png)

```c++
/**
@Description：删除向量中区间[lo,hi)的所有元素
@Return：返回删除元素的个数
*/
template<typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
	if (lo == hi)return 0;
	//删除区间[lo,hi)的元素
	while (hi<_size)
	{
		//从前往后依次复制，否则可能会导致部分元素被覆盖
		_elem[lo++] = _elem[hi++];
	}
	//更新规模，有必要则进行缩容
	_size = lo;
	shrink();
	return hi - lo;
}
```

#### 单元素删除

单元素删除等价于多元素删除的区间为[r,r+1)

```c++
/**
@Description：删除秩为r的元素
@Return：返回被删除元素的值
*/
template<typename T>
T Vector<T>::remove(Rank r)
{
	T e = _elem[r];
	remove(r, r + 1);
	return e;
}
```

Q：为什么不先定义单元素删除，再通过单元素删除来定义区间删除？

A：这样子会导致区间删除的效率很低，每次都要一格一格的删除

#### 查找

无需向量只需要重载==或者！=即可，有序向量还需要重载<或者>

![image-20200519173232433](https://i.loli.net/2020/05/19/VXpcy4kAG1j6hWS.png)

从后向前查找目标元素，找到对应元素后就停止。返回最终的停止位置的秩

```c++
/**
@Description：在向量区间[lo,hi)中查找元素e
@Return：最终停止时的秩
*/
template<typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const
{
	while (lo < hi-- && _elem[hi] != e);//逆向查找，注意这里lo<hi--很是巧妙
	return hi;//当hi<lo，代表查找失败
}
```

