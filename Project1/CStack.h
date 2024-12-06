#pragma once
#include<iostream>
#include<cassert>
#include"CList.h"
//重封装List实现链栈
template<typename T>
struct CStack {
    //拷贝 构造 移动
    CStack();
    CStack(T t);  //入栈
    CStack(std::initializer_list<T> ilist); //批量入栈
    CStack(const CStack& cs);    //拷贝构造
    CStack(CStack&& cs);    //移动构造
    ~CStack();              //析构
//重载操作符
    // =  == 
    CStack& operator = (const CStack& cs);
    bool operator==(const CStack& cs);
    //栈操作 
       //Push进栈
    CStack& Push(T t);

    //Pop出栈
    T& Pop();

    //GetTop  读取栈顶
    T& GetTop();

    //StackEmtpy  栈空判断
    bool StackEmtpy();

private:
    void Init();           //初始化
    void Clear();         //删除
    CList<T>* m_pList = nullptr;//链表
};



template<typename T>
inline CStack<T>::CStack()
{
    Init();
}

//--------------------------------操作实现---------------------------------
template<typename T>
inline CStack<T>::CStack(T t)
{
    Init();
    m_pList->InsertHead(t);
}


template<typename T>
inline CStack<T>::CStack(std::initializer_list<T> ilist)
{
    Init();
    for (auto i : ilist) {
        m_pList->InsertHead(i);
    }
}


template<typename T>
inline CStack<T>::CStack(const CStack& cs)
{
    Init();
    *m_pList = *(cs.m_pList);
}
template<typename T>
inline CStack<T>::CStack(CStack&& cs) :
    m_pList(cs.m_pList)
{
    //    m_pList(std::move(cs.m_pList))
    cs.m_pList = nullptr;
}

template<typename T>
inline CStack<T>::~CStack()
{
    Clear();
}


template<typename T>
CStack<T>& CStack<T>::operator=(const CStack& cs)
{
    Clear();
    Init();
    *m_pList = *(cs.m_pList); //观察内存
    return *this;
    // TODO: 在此处插入 return 语句
}

template<typename T>
inline bool CStack<T>::operator==(const CStack& cs)
{
    return m_pList == cs.m_pList;
}

template<typename T>
inline CStack<T>& CStack<T>::Push(T t)
{
    // TODO: 在此处插入 return 语句
    m_pList->InsertHead(t);
    return *this;
}

template<typename T>
inline T& CStack<T>::Pop()
{
    // TODO: 在此处插入 return 语句
    T tTemp = *(m_pList->begin());
    m_pList->DeleteHead();
    return tTemp;
}

template<typename T>
inline T& CStack<T>::GetTop()
{
    // TODO: 在此处插入 return 语句
    return *(m_pList->begin());
}

template<typename T>
inline bool CStack<T>::StackEmtpy()
{
    return m_pList->GetCount() == 0;
}

template<typename T>
inline void CStack<T>::Init()
{
    m_pList = new  CList<T>();
}

template<typename T>
inline void CStack<T>::Clear()
{
    delete m_pList;
}

