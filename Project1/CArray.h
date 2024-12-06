#pragma once
#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
using namespace std;
/*
1.双向迭代器
2.类型匹配模板
3.增删改查
*/

//正向迭代器
template<typename T>
class Iterator;

//反向迭代器
template<typename T>
class Reverse_Iterator;

//随机访问迭代器
template<typename T>
class Random_Access_Iterator;


template<typename T>
class CArray {
//构造
public:
	CArray(size_t nSize) : nSize(nSize) {
		//创建
		tArray = new T[nSize];
	};
	~CArray() {
		//释放空间
		delete[] tArray;
	};
	//拷贝构造  如果禁用:CArray(const CArray&) = delete
	CArray(const CArray& ca) {
		*this = ca;
	};
	//移动构造 禁用
	CArray(CArray&& ca) = delete;
//重载
public:
	//[]
	T& operator[](int nIndex) { 
		return tArray[nIndex];
	}
private:
	//禁用=
	CArray& operator=(const CArray&);

//迭代器
public:
	using Iterator = Iterator<T>;
	using Reverse_Iterator = Reverse_Iterator<T>;
	using Random_Access_Iterator = Random_Access_Iterator<T>;

	//正向迭代器
	Iterator begin() {
		return Iterator(tArray);
	}
	Iterator end() {
		return Iterator(tArray + nNowSize);
	}
	//反向迭代器
	Reverse_Iterator rbegin() {
		return Reverse_Iterator(tArray + nNowSize - 1);
	}
	Reverse_Iterator rend() {
		return Reverse_Iterator(tArray-1);
	}

//功能函数
public:
	//返回当前元素个数
	size_t nowSize() const{
		return nNowSize;
	}
	//返回数组大小
	size_t Size() const {
		return nSize;
	}
	//末尾增加元素
	void push_back(T nAdd) {
		if (nNowSize >=  nSize) {
			expand();
		}
		tArray[++nNowSize] = nAdd;
	}
	//末尾删除元素并返回
	T pop_back() {
		return tArray[nNowSize--];
	}
	//指定位置增加元素
	void insert(T tAdd,size_t nPoint) {		
		//越界
		if (nPoint > nSize) {
			return;
		}
		//无需移动
		if (nPoint > nNowSize-1) {
			tArray[nPoint] = tAdd;
			return;
		}
		//移动后面的元素
		for (size_t nTemp = nNowSize - 1; nTemp > nPoint;nTemp --) {
			tArray[nTemp] = tArray[nTemp - 1];
		}

		//新元素写入
		tArray[nPoint] = tAdd;
	}
	//根据元素查询下标
	int find(T tTemp) {
		for (int s = 0; s < nNowSize;s++) {
			if (tArray[s] == tTemp) {
				return s;
			}
		}
		return -1;
	}
private:
	//内部扩容
	void expand() {
		/*
		1.创建新的空间
		2.数据迁移
		3.删除旧空间
		4.更新总大小
		*/
		T* tTemp = new T[nSize * 2];
		memcpy(tTemp, tArray, sizeof(T) * nNowSize);
		delete[] tArray;
		tArray = tTemp;
		nSize *= 2;
	}

//参数
private:
	size_t nSize = 10;  //数组长度，默认10
	size_t nNowSize = 0;//当前存储数量，起始0
	T* tArray = nullptr;   //起始指针
};

//正向迭代器
template<typename T>
class Iterator {
public:
	Iterator(T* tArray): tArray(tArray){}
	T& operator*() {
		return *tArray;
	}
	Iterator& operator++() {
		tArray++;
		return *this;
	}
	bool operator!=(const Iterator& iTemp) {
		return iTemp.tArray != tArray;
	}
private:
	T* tArray = nullptr;
};


//反向迭代器
template<typename T>
class Reverse_Iterator {
public:
	Reverse_Iterator(T* tArrayEnd):tArrayEnd(tArrayEnd){}
	T& operator*() {
		return *tArrayEnd;
	}
	Reverse_Iterator& operator--() {
		tArrayEnd--;
		return *this;
	}
	bool operator!=(const Reverse_Iterator& iTemp) {
		return iTemp.tArrayEnd != tArrayEnd;
	}
ptivate:
	T* tArrayEnd = nullptr;
};


//随机迭代器
template<typename T>
class Random_Access_Iterator {
public:
	Random_Access_Iterator(T* tArray):tArray(tArray){}
	T& operator*() {
		return *tArray;
	}
	T& operator[](int nIndex) {
		return tArray[nIndex];
	}
	Random_Access_Iterator& operator++() {
		tArray++;
		return *this;
	}
	Random_Access_Iterator& operator--() {
		tArray--;
		return *this;
	}
	Random_Access_Iterator& operator+(int nStep) {
		tArray += nStep;
		return *this;
	}
	Random_Access_Iterator& operator-(int nStep) {
		tArray -= nStep;
		return *this;
	}
	bool operator!=(const Iterator& iTemp) {
		return iTemp.tArray != tArray;
	}
private:
	T* tArray = nullptr;
};