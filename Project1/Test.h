#pragma once
#include <iostream>

template <typename T> 
class Array {
public:
  Array(int size) : m_size(size) { // ���캯��,��������ռ�
    m_data = new T[size]; 
  }

  ~Array() { // ��������,�ͷ�����ռ�
    delete[] m_data;
  }

  T& operator[](int index) { // ����[]�����,���ڷ���Ԫ��
    return m_data[index];
  }

  int size() const { // ���������С
    return m_size;
  }

  // ���������
  class ForwardIterator {
  public:
    ForwardIterator(T* p) : m_p(p) {}
    
    T& operator*() { return *m_p; }
    
    ForwardIterator& operator++() {
      m_p++;
      return *this;
    }
    
    bool operator!=(const ForwardIterator& rhs) {
      return m_p != rhs.m_p; 
    }

  private:
    T* m_p;
  };

  // ���������
  class ReverseIterator {
  public:
    ReverseIterator(T* p) : m_p(p) {}
    
    T& operator*() { return *m_p; }
    
    ReverseIterator& operator--() {
      m_p--;
      return *this;
    }
    
    bool operator!=(const ReverseIterator& rhs) {
      return m_p != rhs.m_p;
    }

  private:
    T* m_p;
  };

  // ������ʵ�����
  class RandomAccessIterator {
  public:
    RandomAccessIterator(T* p) : m_p(p) {}

    T& operator*() { return *m_p; }

    T& operator[](int index) {
      return m_p[index];
    }

    RandomAccessIterator& operator++() {
      m_p++;
      return *this;
    }

    RandomAccessIterator& operator--() {
      m_p--;
      return *this;
    }

    RandomAccessIterator& operator+(int offset) {
      m_p += offset;
      return *this;
    }

    RandomAccessIterator& operator-(int offset) {
      m_p -= offset;
      return *this; 
    }

    bool operator!=(const RandomAccessIterator& rhs) {
      return m_p != rhs.m_p;
    }

  private:
    T* m_p;
  };

  ForwardIterator begin() { // �������������ָ����ʼλ��
    return ForwardIterator(m_data);
  }

  ForwardIterator end() { // �������������ָ��ĩβλ��
    return ForwardIterator(m_data + m_size); 
  }

  ReverseIterator rbegin() { // ���ط��������ָ��ĩβλ��
    return ReverseIterator(m_data + m_size - 1);
  }

  ReverseIterator rend() { // ���ط��������ָ����ʼλ��
    return ReverseIterator(m_data - 1);
  }

  RandomAccessIterator rabegin() { // ����������ʵ�����ָ����ʼλ��
    return RandomAccessIterator(m_data);
  }

  RandomAccessIterator raend() { // ����������ʵ�����ָ��ĩβλ��
    return RandomAccessIterator(m_data + m_size);
  }

private:
  T* m_data;
  int m_size;
};

//int main() {
//  Array<int> arr(5);
//
//  for(int i = 0; i < 5; i++) {
//    arr[i] = i;
//  }
//
//  // �������
//  for(auto it = arr.begin(); it != arr.end(); ++it) {
//    std::cout << *it << " "; 
//  }
//
//  // �������
//  for(auto it = arr.rbegin(); it != arr.rend(); ++it) {
//    std::cout << *it << " ";
//  }
//
//  // �������
//  for(int i = 0; i < arr.size(); ++i) {
//    std::cout << arr.rabegin()[i] << " ";
//  }
//
//  return 0;
//}