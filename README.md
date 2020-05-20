# EasyDataStructure

> 本项目具体内容是在学堂在线上跟着清华大学老师：邓俊辉老师，学习数据结构时的代码。

## 接口与实现的编码风格

在编写程序的时候，所有代码的什么都编写来类里，所有代码的实现都编写在其他文件中。

比如说，在定义vector这个类的时候。我首先创造了一个文件：vector.h，在这个头文件里，我定义了所有关于vector的接口。当我要实现vector中的insert接口的时候，我创建了一个文件vector_insert.h，在这个文件里我定义了insert的具体实现方法。为了让编译器知道vector.h中的insert方法已经被实现了，我又新建了要给vector_implementation.h文件，这个文件的作用是include所有的实现头文件，如vector_insert.h。最后我在vector.h的末尾include了vector_implementation.h这个文文件。这样编译器就可以通过vector_implementation.h这个文件找到具体的insert实现位置是vector_insert.h，具体的图解如下：

<img src="https://i.loli.net/2020/05/20/QiTEfRJG18SxVrO.png" style="zoom:67%;" />