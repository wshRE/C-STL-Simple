#pragma once
#include"CList.h"
#include<iostream>
template<typename T>
struct CQueue {
    CQueue();
    CQueue(T t);
    CQueue(std::initializer_list<T> ilist);
    CQueue(const CQueue& cq);   //拷贝构造
    CQueue(CQueue&& cq);  //移动构造
    ~CQueue();

    //重载操作符
            // =  == 
    CQueue& operator = (const CQueue& cq);
    bool operator==(const CQueue& cq);

    //栈操作 
        //入队列
    CQueue& EnQueue(T t);
    //出队列并返回
    T& DeQueue();
    //返回队尾元素
    T& GetHead();
    //空判断---空返回true 
    bool QueueEmtpy();

private:
    void Init();           //初始化
    void Clear();         //删除
    CList<T>* m_pList = nullptr;//链表
};

template<typename T>
inline CQueue<T>::CQueue()
{
    Init();
}

//-------------------五件套--------------------------------
template<typename T>
inline CQueue<T>::CQueue(T t)
{
    Init();
    m_pList->InsertHead(t);
}

template<typename T>
inline CQueue<T>::CQueue(std::initializer_list<T> ilist)
{
    m_pList = new CList<T>(ilist);
}

template<typename T>
inline CQueue<T>::CQueue(const CQueue& cq)
{
    Init();
    *m_pList = *(cq.m_pList);
}

template<typename T>
inline CQueue<T>::CQueue(CQueue&& cq) :
    m_pList(cq.m_pList)
{//  //    m_pList(std::move(cs.m_pList))
    cq.m_pList = nullptr;
}

template<typename T>
inline CQueue<T>::~CQueue()
{
    Clear();
}

template<typename T>
inline CQueue<T>& CQueue<T>::operator=(const CQueue<T>& cq)
{
    // TODO: 在此处插入 return 语句
    Clear();
    Init();
    *m_pList = *(cq.m_pList); //观察内存
    return *this;
}

template<typename T>
inline bool CQueue<T>::operator==(const CQueue<T>& cq)
{
    return m_pList == cq.m_pList;
}

template<typename T>
inline CQueue<T>& CQueue<T>::EnQueue(T t)
{
    // TODO: 在此处插入 return 语句
    m_pList->InsertHead(t);  //头插
    return *this;
}

template<typename T>
inline T& CQueue<T>::DeQueue()
{
    // TODO: 在此处插入 return 语句
    T tTemp = *(m_pList->end());  //尾取
    m_pList->DeleteTail();
    return tTemp;
}

template<typename T>
inline T& CQueue<T>::GetHead()
{
    // TODO: 在此处插入 return 语句
    return *(m_pList->end());  //尾取
}

template<typename T>
inline bool CQueue<T>::QueueEmtpy()
{
    return m_pList->GetCount() == 0;
}

//--------------初始化与结束
template<typename T>
inline void CQueue<T>::Init()
{
    m_pList = new CList<T>();
}

template<typename T>
inline void CQueue<T>::Clear()
{
    delete m_pList;
}
