#pragma once
#include <cassert>

template<typename T>
class Iterator;

template<typename T>
class Reverse_Iterator;

template<typename T>
class CList
{
private:
    //节点
    struct tagNode
    {
        tagNode() :m_nVal() {};
        tagNode(const T& nVal) :m_nVal(nVal) {}
        T m_nVal;
        tagNode* m_pLast = nullptr;//前驱结点
        tagNode* m_pNext = nullptr;//后继结点
    };

public:
    //节点别名
    using Node = tagNode*;
    //迭代器
    using Iterator = Iterator<T>;
    using Reverse_Iterator = Reverse_Iterator<T>;

private:
    //初始化----创建头尾节点并连接
    void Init()
    {
        m_HeadNode = new tagNode;
        m_TailNode = new tagNode;
        m_HeadNode->m_pNext = m_TailNode;
        m_TailNode->m_pLast = m_HeadNode;
    }
public:
    //正向迭代器
        //返回第一个元素
    Iterator begin() {
        return Iterator(m_HeadNode->m_pNext, m_TailNode);
    }
    //返回最后一个元素
    Iterator end() {
        return Iterator(m_TailNode, m_TailNode);
    }

    //反向迭代器
          //返回最后一个元素
    Reverse_Iterator rbegin() {
        return Reverse_Iterator(m_HeadNode, m_TailNode->m_pLast);
    }
    //返回第一个元素
    Reverse_Iterator rend() {
        return Reverse_Iterator(m_HeadNode, m_HeadNode);
    }

    
    CList(std::initializer_list<T> ilist) {
        Init();
        for (auto i = ilist.begin(); i != ilist.end(); i++) {
            InsertTail(*i);
        }
    }

    //无参构造
    CList()
    {
        Init();
    };
    //析构
    ~CList()
    {
        clear();
        if (m_HeadNode != nullptr)
        {
            delete m_HeadNode;
            delete m_TailNode;
        }

        m_nCount = 0;
    };
    //拷贝构造
    CList(const CList& cl)
    {
        Init();
        *this = cl;
    };
    //移动构造
    CList(CList&& cl)
    {
        m_HeadNode = cl.m_HeadNode;
        m_TailNode = cl.m_TailNode;
        m_nCount = cl.GetCount();
        cl.m_HeadNode = nullptr;
        cl.m_TailNode = nullptr;
        cl.m_nCount = 0;
    };
    //重载=
    CList& operator=(const CList& cl)
    {
        if (this == &cl)
        {
            return *this;
        }
        clear();
        Node nodeStart = cl.m_HeadNode->m_pNext;
        while (nodeStart != nullptr && nodeStart != cl.m_TailNode)
        {
            InsertTail(nodeStart->m_nVal);
            nodeStart = nodeStart->m_pNext;
        }
        return *this;
    };
    //插入节点
    CList& Insert(Node node, const T& data)
    {
        //创建一个新结点
        if (node == nullptr)
        {
            return *this;
        }
        Node pNewNode = new tagNode(data);
        Node pNowNode = node->m_pLast;//得到上一个结点
        pNowNode->m_pNext = pNewNode;
        node->m_pLast = pNewNode;
        pNewNode->m_pLast = pNowNode;
        pNewNode->m_pNext = node;
        ++m_nCount;
        return *this;
    };

    //头插
    CList& InsertHead(const T& data)
    {
        return Insert(m_HeadNode->m_pNext, data);
    };

    //尾插
    CList& InsertTail(const T& data)
    {
        return Insert(m_TailNode, data);
    };

    //删除节点
    CList& Delete(Node node)
    {
        if (node == nullptr)
        {
            return *this;
        }
        Node pLastNood = node->m_pLast;
        pLastNood->m_pNext = node->m_pNext;
        Node pNextNood = node->m_pNext;
        pNextNood->m_pLast = pLastNood;
        delete node;
        --m_nCount;
        return *this;
    };

    //去头
    CList& DeleteHead()
    {
        if (m_nCount == 0)
        {
            return *this;
        }
        return Delete(m_HeadNode->m_pNext);
    };

    //去尾
    CList& DeleteTail()
    {
        if (m_nCount == 0)
        {
            return *this;
        }
        return Delete(m_TailNode->m_pLast);
    };

    //重载[]
    T& operator[](Node node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        return node->m_nVal;
    };

    //根据内容查找节点
    Node Find(const T& data)
    {
        Node nodeStart = m_HeadNode->m_pNext;
        while (nodeStart != nullptr)
        {
            if (nodeStart->m_nVal == data)
            {
                return nodeStart;
            }
            nodeStart = nodeStart->m_pNext;
        }
        return nullptr;
    };

    //清空
    void clear()
    {
        while (!IsEmpty())
        {
            DeleteHead();
        }
    };

    //获取当前数字
    size_t GetCount()const
    {
        return m_nCount;

    };

    //判空
    bool IsEmpty()const
    {
        return GetCount() == 0;
    };

public:
    Node m_HeadNode = nullptr;//头结点
    Node m_TailNode = nullptr;//尾结点
    size_t m_nCount = 0;//元素个数
};


//迭代器实现
template<typename T>
class Iterator
{
public:
    //无参构造
    Iterator() = default;

    //节点和尾指针
    Iterator(typename CList<T>::Node pNode, typename CList<T>::Node pTailGuard)
    {
        m_pNode = pNode;
        m_pTailGuard = pTailGuard;
    }

    //重写前++ ---> 到下一个
    Iterator& operator++()
    {
        assert(m_pNode != nullptr); //不能为空
        assert(m_pNode != m_pTailGuard);//不能往后移动

        //移动
        m_pNode = m_pNode->m_pNext;

        return *this;
    }
    //重写后++
    Iterator operator++(int) {
        return ++ * this;
        //Iterator tTemp = *this;
        //++* this;
        //return tTemp;
    }



    //重写* -----> 取值
    T& operator*() const
    {
        return m_pNode->m_nVal;
    }
    T* operator->() const {
        return &(operator*());
    }

    bool operator!=(const Iterator& itr)
    {
        return m_pNode != itr.m_pNode;
    }
    bool operator==(const Iterator& itr) const {
        return m_pNode == itr.m_pNode;
    }
private:
    typename CList<T>::Node m_pNode = nullptr;
    typename CList<T>::Node m_pTailGuard = nullptr;
};



//反向迭代器
template<typename T>
class Reverse_Iterator
{
public:
    //无参构造
    Reverse_Iterator() = default;

    //节点和尾指针
    Reverse_Iterator(typename CList<T>::Node pHeadNode, typename CList<T>::Node pNode)
    {
        m_HeadNode = pHeadNode;
        m_pNode = pNode;
    }

    //重写前++ ---> 到上一个
    Reverse_Iterator& operator++()
    {
        assert(m_pNode != nullptr); //不能为空
        assert(m_pNode != m_HeadNode);//不能往后移动

        //移动
        m_pNode = m_pNode->m_pLast;

        return *this;
    }
    //重写后++
    Reverse_Iterator operator++(int) {
        return ++ * this;
    }


    //重写* -----> 取值
    T& operator*() const
    {
        return m_pNode->m_nVal;
    }
    T* operator->() const {
        return &(operator*());
    }

    bool operator!=(const Reverse_Iterator& itr)
    {
        return m_pNode != itr.m_pNode;
    }
    bool operator==(const Reverse_Iterator& itr) const {
        return m_pNode == itr.m_pNode;
    }
private:
    typename CList<T>::Node m_HeadNode = nullptr;
    typename CList<T>::Node m_pNode = nullptr;
};
