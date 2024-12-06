#pragma once
#include <iostream>

template <typename T> 
class Array {
public:
  Array(int size) : m_size(size) { // 构造函数,分配数组空间
    m_data = new T[size]; 
  }

  ~Array() { // 析构函数,释放数组空间
    delete[] m_data;
  }

  T& operator[](int index) { // 重载[]运算符,用于访问元素
    return m_data[index];
  }

  int size() const { // 返回数组大小
    return m_size;
  }

  // 正向迭代器
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

  // 反向迭代器
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

  // 随机访问迭代器
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

  ForwardIterator begin() { // 返回正向迭代器指向起始位置
    return ForwardIterator(m_data);
  }

  ForwardIterator end() { // 返回正向迭代器指向末尾位置
    return ForwardIterator(m_data + m_size); 
  }

  ReverseIterator rbegin() { // 返回反向迭代器指向末尾位置
    return ReverseIterator(m_data + m_size - 1);
  }

  ReverseIterator rend() { // 返回反向迭代器指向起始位置
    return ReverseIterator(m_data - 1);
  }

  RandomAccessIterator rabegin() { // 返回随机访问迭代器指向起始位置
    return RandomAccessIterator(m_data);
  }

  RandomAccessIterator raend() { // 返回随机访问迭代器指向末尾位置
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
//  // 正向遍历
//  for(auto it = arr.begin(); it != arr.end(); ++it) {
//    std::cout << *it << " "; 
//  }
//
//  // 反向遍历
//  for(auto it = arr.rbegin(); it != arr.rend(); ++it) {
//    std::cout << *it << " ";
//  }
//
//  // 随机访问
//  for(int i = 0; i < arr.size(); ++i) {
//    std::cout << arr.rabegin()[i] << " ";
//  }
//
//  return 0;
//}