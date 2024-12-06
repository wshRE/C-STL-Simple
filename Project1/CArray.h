#pragma once
#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
using namespace std;
/*
1.˫�������
2.����ƥ��ģ��
3.��ɾ�Ĳ�
*/

//���������
template<typename T>
class Iterator;

//���������
template<typename T>
class Reverse_Iterator;

//������ʵ�����
template<typename T>
class Random_Access_Iterator;


template<typename T>
class CArray {
//����
public:
	CArray(size_t nSize) : nSize(nSize) {
		//����
		tArray = new T[nSize];
	};
	~CArray() {
		//�ͷſռ�
		delete[] tArray;
	};
	//��������  �������:CArray(const CArray&) = delete
	CArray(const CArray& ca) {
		*this = ca;
	};
	//�ƶ����� ����
	CArray(CArray&& ca) = delete;
//����
public:
	//[]
	T& operator[](int nIndex) { 
		return tArray[nIndex];
	}
private:
	//����=
	CArray& operator=(const CArray&);

//������
public:
	using Iterator = Iterator<T>;
	using Reverse_Iterator = Reverse_Iterator<T>;
	using Random_Access_Iterator = Random_Access_Iterator<T>;

	//���������
	Iterator begin() {
		return Iterator(tArray);
	}
	Iterator end() {
		return Iterator(tArray + nNowSize);
	}
	//���������
	Reverse_Iterator rbegin() {
		return Reverse_Iterator(tArray + nNowSize - 1);
	}
	Reverse_Iterator rend() {
		return Reverse_Iterator(tArray-1);
	}

//���ܺ���
public:
	//���ص�ǰԪ�ظ���
	size_t nowSize() const{
		return nNowSize;
	}
	//���������С
	size_t Size() const {
		return nSize;
	}
	//ĩβ����Ԫ��
	void push_back(T nAdd) {
		if (nNowSize >=  nSize) {
			expand();
		}
		tArray[++nNowSize] = nAdd;
	}
	//ĩβɾ��Ԫ�ز�����
	T pop_back() {
		return tArray[nNowSize--];
	}
	//ָ��λ������Ԫ��
	void insert(T tAdd,size_t nPoint) {		
		//Խ��
		if (nPoint > nSize) {
			return;
		}
		//�����ƶ�
		if (nPoint > nNowSize-1) {
			tArray[nPoint] = tAdd;
			return;
		}
		//�ƶ������Ԫ��
		for (size_t nTemp = nNowSize - 1; nTemp > nPoint;nTemp --) {
			tArray[nTemp] = tArray[nTemp - 1];
		}

		//��Ԫ��д��
		tArray[nPoint] = tAdd;
	}
	//����Ԫ�ز�ѯ�±�
	int find(T tTemp) {
		for (int s = 0; s < nNowSize;s++) {
			if (tArray[s] == tTemp) {
				return s;
			}
		}
		return -1;
	}
private:
	//�ڲ�����
	void expand() {
		/*
		1.�����µĿռ�
		2.����Ǩ��
		3.ɾ���ɿռ�
		4.�����ܴ�С
		*/
		T* tTemp = new T[nSize * 2];
		memcpy(tTemp, tArray, sizeof(T) * nNowSize);
		delete[] tArray;
		tArray = tTemp;
		nSize *= 2;
	}

//����
private:
	size_t nSize = 10;  //���鳤�ȣ�Ĭ��10
	size_t nNowSize = 0;//��ǰ�洢��������ʼ0
	T* tArray = nullptr;   //��ʼָ��
};

//���������
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


//���������
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


//���������
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