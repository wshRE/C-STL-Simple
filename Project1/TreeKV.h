#pragma once
#include<iostream>
#include"CString.h"
#include"CList.h"
#include"CQueue.h"
#include"CStack.h"
const size_t WHITE = 0;//新节点
const size_t GRAY = 1; //已访问
template<typename T, typename T1, typename T2>  //T:KEY  T1:VALUE  T2:LINK
class TreeKVAndLink {
public:
    //节点
    template<typename T, typename T1, typename T2>
    struct TreeNode {
        TreeNode() :m_tValue(), m_tValue1() {
            m_tLeft = nullptr;
            m_tRight = nullptr;
            m_tFather = nullptr;
            m_nHeight = 0;  //左右高度差
            m_list = new CList<T2>();
            m_nStore = -1;    //文件偏移量----学生id树/课程id树
        }
        TreeNode(T t, T1 t1) :m_tValue(t), m_tValue1(t1) {
            m_tLeft = nullptr;
            m_tRight = nullptr;
            m_tFather = nullptr;
            m_nHeight = 0;
            m_list = new CList<T2>();
            m_nStore = -1;
        }
        TreeNode(T t, T1 t1,int m_nStore) :m_tValue(t), m_tValue1(t1), m_nStore(m_nStore) {
            m_tLeft = nullptr;
            m_tRight = nullptr;
            m_tFather = nullptr;
            m_nHeight = 0;
            m_list = new CList<T2>();
        }
        T m_tValue;   //key  
        T1 m_tValue1;  //value
        int m_nHeight;   //树高度
        int m_nStore;   //文件偏移 --------------------学生id树专用（暂未初始化）
        TreeNode<T, T1, T2>* m_tLeft;
        TreeNode<T, T1, T2>* m_tRight;
        TreeNode<T, T1, T2>* m_tFather; //父节点
        CList<T2>* m_list;//挂载链表
    };
    //非递归遍历栈
    template<typename T, typename T1, typename T2>
    struct TreeStack {
        TreeStack() :nColor() {
            tNode = nullptr;
        }
        TreeStack(size_t ncolor, TreeNode<T, T1, T2>* tnode) {
            nColor = ncolor;
            tNode = tnode;
        }
        size_t nColor;    //颜色  0为白色  1为灰色
        TreeNode<T, T1, T2>* tNode;  //节点
    };


    //基础套件
/*完成*/  TreeKVAndLink();
/*完成*/  TreeKVAndLink(const TreeKVAndLink<T, T1, T2>& t);
/*完成*/  TreeKVAndLink(TreeKVAndLink<T, T1, T2>&& t);
/*完成*/  ~TreeKVAndLink();

    //初始化与结束
/*完成*/  void Init();
/*完成*/  void ClearTree(TreeNode<T, T1, T2>* tree);
/*完成*/  void ClearLink(TreeNode<T, T1, T2>* tree);

    //树操作
//增 
        //插入节点---不带偏移
    TreeKVAndLink<T, T1, T2>& InsertNode(T tValue, T1 tvalue1);
    TreeKVAndLink<T, T1, T2>& InsertNode(T tValue, T1 tvalue1,int nOffset);  //带偏移
        //插入链表----传入id 和 节点
    TreeKVAndLink<T, T1, T2>& InsertLink(T tValue, T2 tvalue1);
//查
        //查找----通过主键查找----仅返回树节点
    TreeNode<T, T1, T2>* Find(T tValue);
        //中序后继查找
    TreeNode<T, T1,T2>* FindInNode(TreeNode<T, T1,T2>* tnode);
//删
        //删除----按照KEY删除树节点---11删链表ClearLink 2.删节点
    TreeKVAndLink<T, T1, T2>& DeleteValue(T tValue);
        //删除----删除链表节点------T2:将学生id打包成链表节点
    TreeKVAndLink<T, T1, T2>& DeleteLink(T tValue,T2 tValue1);

//改通过查完成

//平衡

        //获取根节点的指针
    TreeNode<T, T1, T2>* GetRoot() {
        return m_tRoot;
    }
    //获取节点高度
    int GetHeight(TreeNode<T, T1, T2>* pNode);
    //计算高度
    void CalcHeight(TreeNode<T, T1, T2>* pNode);
    //调整高度
    void AdjustHeight(TreeNode<T, T1, T2>* pNode);
    //左旋
    void LeftRotate(TreeNode<T, T1, T2>* pnode);
    //右旋
    void RightRotate(TreeNode<T, T1, T2>* pnode);


    size_t GetCount() {
        return m_nCount;
    }


private:
    TreeNode<T, T1, T2>* m_tRoot;  //根节点
    size_t m_nCount = 0;    //节点数量
};



//----------------------基础套件--------------------
    //构造
template<typename T, typename T1, typename T2>
inline TreeKVAndLink<T, T1, T2>::TreeKVAndLink()
{
    Init();
}

//拷贝构造
template<typename T, typename T1, typename T2>
inline TreeKVAndLink<T, T1, T2>::TreeKVAndLink(const TreeKVAndLink<T, T1, T2>& t)
{
    Init();
    *m_tRoot = *(t);
}
//移动拷贝
template<typename T, typename T1, typename T2>
inline TreeKVAndLink<T, T1, T2>::TreeKVAndLink(TreeKVAndLink<T, T1, T2>&& t)
{
    m_tRoot = t.m_tRoot;
    t.m_tRoot = nullptr;
}
//析构
template<typename T, typename T1, typename T2>
inline TreeKVAndLink<T, T1, T2>::~TreeKVAndLink()
{
    //链表清除
    ClearLink(m_tRoot);
    //树清除
    ClearTree(m_tRoot);
    //重置
    m_tRoot->m_tLeft = nullptr;
    m_tRoot->m_tRight = nullptr;
    m_tRoot->m_tFather = nullptr;
    m_tRoot->m_nHeight = 0;  //左右高度差
    m_tRoot->m_list = nullptr;
}


//-------------------------初始化与结束-------------------------------------
//初始化
template<typename T, typename T1, typename T2>
inline void TreeKVAndLink<T, T1, T2>::Init()
{
    m_tRoot = new TreeNode<T, T1, T2>();
}
//清空树
template<typename T, typename T1, typename T2>
inline void TreeKVAndLink<T, T1, T2>::ClearTree(TreeNode<T, T1, T2>* tree)
{
    if (!tree) {
        return;
    }
    ClearTree(tree->m_tLeft);
    ClearTree(tree->m_tRight);
    //清理自身
    if (tree->m_tFather && tree->m_tFather->m_tLeft == tree) {
        tree->m_tFather->m_tLeft = nullptr;
    }
    else if (tree->m_tFather && tree->m_tFather->m_tRight == tree) {
        tree->m_tFather->m_tRight = nullptr;
    }
    ClearLink(tree);
    delete tree;
    return;
}

//清空某节点的链表
template<typename T, typename T1, typename T2>
inline void TreeKVAndLink<T, T1, T2>::ClearLink(TreeNode<T, T1, T2>* tnode)
{
    //循环删除节点的链表
    tnode->m_list->clear();
}

//插入节点---不带偏移
template<typename T, typename T1, typename T2>
inline TreeKVAndLink<T, T1, T2>& TreeKVAndLink<T, T1, T2>::InsertNode(T tValue, T1 tvalue1)
{
    //// TODO: 在此处插入 return 语句
    //    // TODO: 在此处插入 return 语句
    //if (m_tRoot->m_tValue == NULL) {
    //    m_tRoot->m_tValue = tValue;
    //    m_tRoot->m_tValue1 = tvalue1;
    //    return *this;
    //}
    //TreeNode<T, T1, T2>* pTemp = m_tRoot;
    //TreeNode<T, T1, T2>* pTempPre = pTemp;
    //while (pTemp) {
    //    pTempPre = pTemp;
    //    if (pTemp->m_tValue < tValue) {
    //        pTemp = pTemp->m_tRight;
    //    }
    //    else if (pTemp->m_tValue == tValue) {
    //        return *this;
    //    }
    //    else {
    //        pTemp = pTemp->m_tLeft;
    //    }
    //}
    //if (pTempPre == nullptr) {
    //    return *this;
    //}
    //if (tValue < pTempPre->m_tValue) {
    //    pTempPre->m_tLeft = new TreeNode<T, T1, T2>(tValue, tvalue1);
    //    pTempPre->m_tLeft->m_tFather = pTempPre;
    //}
    //else if (tValue > pTempPre->m_tValue) {
    //    pTempPre->m_tRight = new TreeNode<T, T1, T2>(tValue, tvalue1);
    //    pTempPre->m_tRight->m_tFather = pTempPre;
    //}

               //如果根节点为空,则默认无数据,新建一个根节点
    if (m_tRoot == nullptr)
    {
        m_tRoot = new TreeNode<T, T1, T2>(tValue, tvalue1);
        m_nCount++;
        return *this;
    }

    //如果根节点有数据
    TreeNode<T, T1, T2>* pCurNode = m_tRoot;
    TreeNode<T, T1, T2>* pNewNode = new TreeNode<T, T1, T2>(tValue, tvalue1);
    while (pCurNode != nullptr)
    {
        //如果数据比当前根节点小,从左孩子开始查询
        if (tValue < pCurNode->m_tValue)
        {
            //如果这个位置的数据是空的,那么将指针指向开始储存的值,并且总结点数+1
            if (pCurNode->m_tLeft == nullptr)
            {
                pCurNode->m_tLeft = pNewNode;
                pNewNode->m_tFather = pCurNode;
                m_nCount++;
                AdjustHeight(pCurNode);
                return *this;
            }
            pCurNode = pCurNode->m_tLeft;
        }
        //如果数据比当前根节点大,从右孩子开始查询
        else if (tValue > pCurNode->m_tValue)
        {
            //如果这个位置的数据是空的,那么将指针指向开始储存的值,并且总结点数+1
            if (pCurNode->m_tRight == nullptr)
            {
                pCurNode->m_tRight = pNewNode;
                pNewNode->m_tFather = pCurNode;
                m_nCount++;
                AdjustHeight(pCurNode);
                return *this;
            }
            pCurNode = pCurNode->m_tRight;
        }
        else
        {
            //树中已经有此数据,释放内存
            delete pNewNode;
            return *this;
        }
    }
    return *this;
}
//插入---带偏移
template<typename T, typename T1, typename T2>
inline TreeKVAndLink<T, T1, T2>& TreeKVAndLink<T, T1, T2>::InsertNode(T tValue, T1 tvalue1, int nOffset)
{

    //如果根节点为空,则默认无数据,新建一个根节点
    if (m_tRoot == nullptr)
    {
        m_tRoot = new TreeNode<T, T1, T2>(tValue, tvalue1, nOffset);
        m_nCount++;
        return *this;
    }

    //如果根节点有数据
    TreeNode<T, T1, T2>* pCurNode = m_tRoot;
    TreeNode<T, T1, T2>* pNewNode = new TreeNode<T, T1, T2>(tValue, tvalue1, nOffset);
    while (pCurNode != nullptr)
    {
        //如果数据比当前根节点小,从左孩子开始查询
        if (tValue < pCurNode->m_tValue)
        {
            //如果该节点没有左孩子，则新节点插入到这里
            if (pCurNode->m_tLeft == nullptr)
            {
                pCurNode->m_tLeft = pNewNode;
                pNewNode->m_tFather = pCurNode;
                m_nCount++;
                AdjustHeight(pCurNode);
                return *this;
            }
            pCurNode = pCurNode->m_tLeft;
        }
        //如果数据比当前根节点大,从右孩子开始查询
        else if (tValue > pCurNode->m_tValue)
        {
            //如果这个位置的数据是空的,那么将指针指向开始储存的值,并且总结点数+1
            if (pCurNode->m_tRight == nullptr)
            {
                pCurNode->m_tRight = pNewNode;
                pNewNode->m_tFather = pCurNode;
                m_nCount++;
                AdjustHeight(pCurNode);
                return *this;
            }
            pCurNode = pCurNode->m_tRight;
        }
        else
        {
            //树中已经有此数据,释放内存
            delete pNewNode;
            return *this;
        }
    }
    return *this;
}


//插入链表---T2为链表节点
template<typename T, typename T1, typename T2>
inline TreeKVAndLink<T, T1, T2>& TreeKVAndLink<T, T1, T2>::InsertLink(T tValue, T2 tvalue1)
{
    // TODO: 在此处插入 return 语句
    TreeNode<T, T1, T2>* treenode = Find(tValue);  //查找节点
    //如果节点不存在 则 返回，因为缺少课程名
    if (treenode == nullptr) {
        return *this;
    }
    //if (treenode->m_list->Find(tvalue1) == NULL) { 
    //    treenode->m_list->InsertHead(tvalue1);
    //}
    treenode->m_list->InsertHead(tvalue1);
    return *this;
}

//查找节点
template<typename T, typename T1, typename T2>
inline TreeKVAndLink<T, T1, T2>::TreeNode<T, T1, T2>* TreeKVAndLink<T, T1, T2>::Find(T tValue)
{
    TreeNode<T, T1,T2>* pTemp = m_tRoot;
    while (pTemp) {
        if (pTemp->m_tValue < tValue) {
            pTemp = pTemp->m_tRight;
        }
        else if (pTemp->m_tValue > tValue) {
            pTemp = pTemp->m_tLeft;
        }
        else {
            return pTemp;
        }
    }
    return nullptr;
}

//查找中序后继
template<typename T, typename T1, typename T2>
inline TreeKVAndLink<T, T1, T2>::TreeNode<T, T1, T2>* TreeKVAndLink<T, T1, T2>::FindInNode(TreeNode<T, T1, T2>* tnode)
{
    TreeNode<T, T1,T2>* tTempRoot = m_tRoot;
    TreeNode<T, T1,T2>* tTemp = m_tRoot;
    while (tTempRoot) {
        if (tTempRoot->m_tValue > tnode->m_tValue) {
            tTemp = tTempRoot;
            tTempRoot = tTempRoot->m_tLeft;
        }
        else {
            tTempRoot = tTempRoot->m_tRight;
        }
    }
    return tTemp;
}


//删除节点
template<typename T, typename T1, typename T2>
inline TreeKVAndLink<T, T1, T2>& TreeKVAndLink<T, T1, T2>::DeleteValue(T tValue)
{
    // TODO: 在此处插入 return 语句
    TreeNode<T, T1, T2>* tnode = Find(tValue);
    if (tnode == nullptr) {
        return *this;
    }
    //删除链表
    ClearLink(tnode);

    //删除节点
               //叶子节点
    if (tnode->m_tLeft == nullptr && tnode->m_tRight == nullptr)
    {
        //如果是根节点,直接删除
        if (tnode->m_tFather == nullptr)
        {
            m_tRoot = nullptr;
        }
        //如果节点值大于他爹的值,表示要删除的结点在他爹的右侧,将他爹的右侧指针置空
        else if (tnode->m_tFather->m_tValue < tnode->m_tValue)
        {
            tnode->m_tFather->m_tRight = nullptr;
        }
        //如果节点值小于他爹的值,表示要删除的结点在他爹的左侧,将他爹的左侧指针置空
        else if (tnode->m_tFather->m_tValue > tValue)
        {
            tnode->m_tFather->m_tLeft = nullptr;

        }
        //如果他爹不是空,表示不是根节点,需要一层一层向上遍历,将结点高度更新
        if (tnode->m_tFather != nullptr)
        {
            AdjustHeight(tnode->m_tFather);
        }
        //释放空间
        delete tnode;
        m_nCount--;
        return *this;
    }
    //单孩子节点
    else if (tnode->m_tLeft != nullptr && tnode->m_tRight == nullptr)
    {
        //如果要删除的节点有左孩子,而右孩子是空的
        TreeNode<T, T1, T2>* pDel = nullptr;
        //如果他爹是空的,那么要删除的结点为根节点,根结点的左孩子上位了,接着将根结点置空
        if (tnode->m_tFather == nullptr)
        {
            m_tRoot = tnode->m_tLeft;
            pDel = m_tRoot;
            m_tRoot->m_tFather = nullptr;
        }
        //如果不是根节点
        else
        {
            //如果要删除的结点他爹的值大于他的值,说明被删除的结点在左边
            if (tnode->m_tFather->m_tValue > tnode->m_tValue)
            {
                //如果要删除的值左侧的孩子的父亲指针指向要删除的值的父亲,父亲的左指针等于要删除的值的左节点
                tnode->m_tLeft->m_tFather = tnode->m_tFather;
                tnode->m_tFather->m_tLeft = tnode->m_tLeft;
                pDel = tnode->m_tLeft;
            }
            //如果要删除的结点他爹的值小于他的值,说明被删除的结点在右边
            else if (tnode->m_tFather->m_tValue < tnode->m_tValue)
            {
                //被删除的结点左孩子的父亲指针指向被删除结点的父亲指针,父亲指针的左指针指向删除值的右孩子
                tnode->m_tLeft->m_tFather = tnode->m_tFather;
                tnode->m_tFather->m_tRight = tnode->m_tLeft;
                pDel = tnode->m_tLeft;
            }
        }
        delete tnode;
        AdjustHeight(pDel);
    }
    else if (tnode->m_tLeft == nullptr && tnode->m_tRight != nullptr)//有右孩子，左孩子为空
    {
        TreeNode<T, T1, T2>* pDel = nullptr;
        if (tnode->m_tFather == nullptr)//根节点
        {
            m_tRoot = tnode->m_tRight;
            m_tRoot->m_tFather = nullptr;
            pDel = m_tRoot;
        }
        else//不是根节点
        {
            if (tnode->m_tFather->m_tValue > tValue)//要删的 父节点的值，大于val，所以放父节点左边
            {
                tnode->m_tRight->m_tFather = tnode->m_tFather;//要删的 右孩子的父节点指向 要删掉节点 的父节点
                tnode->m_tFather->m_tLeft = tnode->m_tRight;//要删的 父节点的 左孩子节点 指向要删掉节点的 右孩子
                pDel = tnode->m_tRight;
            }
            else if (tnode->m_tFather->m_tValue < tValue)//要删的 父节点的值，小于val，所以放父节点右边
            {
                tnode->m_tRight->m_tFather = tnode->m_tFather;
                tnode->m_tFather->m_tRight = tnode->m_tRight;
                pDel = tnode->m_tRight;
            }
        }
        delete tnode;
        AdjustHeight(pDel);
    }

    //双孩子节点
    else if (tnode->m_tLeft != nullptr && tnode->m_tRight != nullptr)
    {

        TreeNode<T, T1, T2>* pMax = tnode->m_tLeft;
        TreeNode<T, T1, T2>* pDel = tnode->m_tLeft;
        while (pMax->m_tRight)
        {
            pMax = pMax->m_tRight;
        }
        pDel = pMax;

        //左子树最大值 接替被删节点的位置,
        if (tnode->m_tFather != nullptr)
        {
            if (tnode->m_tFather->m_tValue > tValue)
            {
                tnode->m_tFather->m_tLeft = pMax;
            }
            else if (tnode->m_tFather->m_tValue < tValue)
            {
                tnode->m_tFather->m_tRight = pMax;
            }

        }

        tnode->m_tRight->m_tFather = pMax;
        //如果左子树没有右节点。左子树第一个就是最大
        if (pMax->m_tFather == tnode)
        {
            tnode->m_tLeft = tnode->m_tLeft->m_tLeft;
        }
        else
        {
            pMax->m_tFather->m_tRight = nullptr;
            tnode->m_tLeft->m_tFather = pMax;
        }

        if (tnode->m_tFather != nullptr)
        {
            pMax->m_tFather = tnode->m_tFather;//不为根节点，就把替换的最大值 指向父节点
        }
        else
        {
            pDel = pMax->m_tFather;
            pMax->m_tFather = nullptr;//如果是根节点，父节点为空

            m_tRoot = pMax;
        }
        pMax->m_tLeft = tnode->m_tLeft;
        pMax->m_tRight = tnode->m_tRight;
        if (pDel->m_tFather == tnode)
        {
            delete tnode;
            AdjustHeight(pMax->m_tLeft);
        }
        else
        {
            delete tnode;
            AdjustHeight(pDel);
        }

    }
    return *this;



    //   //思路一： 
    ////  1.查找右子树最小值，记录值
    ////  2.删除最小值的节点
    ////  3.更改值为最小值
    ////思路二
    ////传入为空
    //TreeNode<T, T1, T2>* tNodePre = tnode->m_tFather;
    //TreeNode<T, T1, T2>* tInNodeNext = tNodePre;
    ////删除根节点
    //if (tNodePre == nullptr) {
    //    //左右子树都有---找中序后继
    //    if (tnode->m_tLeft && tnode->m_tRight) {
    //        tInNodeNext = FindInNode(tnode); //中序后继
    //        if (tInNodeNext->m_tFather->m_tLeft == tInNodeNext) {
    //            tInNodeNext->m_tFather->m_tLeft = tInNodeNext->m_tRight;
    //        }
    //        else {
    //            tInNodeNext->m_tFather->m_tRight = tInNodeNext->m_tRight;
    //        }
    //        if (tInNodeNext->m_tRight) {
    //            tInNodeNext->m_tRight->m_tFather = tInNodeNext->m_tFather;
    //        }
    //        m_tRoot->m_tValue = tInNodeNext->m_tValue;
    //        m_tRoot->m_tValue1 = tInNodeNext->m_tValue1;
    //        delete tInNodeNext;
    //    }
    //    //仅有左子树
    //    else if (tnode->m_tLeft && !tnode->m_tRight) {
    //        m_tRoot = tnode->m_tLeft;
    //        m_tRoot->m_tFather = nullptr;
    //        delete tnode;
    //    }
    //    //仅有右子树
    //    else if (!tnode->m_tLeft && tnode->m_tRight) {
    //        m_tRoot = tnode->m_tRight;
    //        m_tRoot->m_tFather = nullptr;
    //        delete tnode;
    //    }//根节点且无左右子树
    //    //无左右子树
    //    else {
    //        tnode->m_tValue = NULL;
    //    }
    //}//删除非根节点
    ////删除的不是根节点
    //else {
    //    //左右子树都有---找中序后继
    //    if (tnode->m_tLeft && tnode->m_tRight) {
    //        tInNodeNext = FindInNode(tnode); //中序后继
    //        //如果中序后继是其父节点的左子树
    //        if (tInNodeNext->m_tFather->m_tLeft == tInNodeNext) {
    //            tInNodeNext->m_tFather->m_tLeft = tInNodeNext->m_tRight;
    //        }
    //        else {
    //            tInNodeNext->m_tFather->m_tRight = tInNodeNext->m_tRight;
    //        }

    //        if (tInNodeNext->m_tRight != nullptr) {
    //            tInNodeNext->m_tRight->m_tFather = tInNodeNext->m_tFather;
    //        }
    //        tnode->m_tValue = tInNodeNext->m_tValue;
    //        tnode->m_tValue1 = tInNodeNext->m_tValue1;
    //        delete tInNodeNext;
    //    }
    //    //仅有左子树
    //    else if (tnode->m_tLeft && !tnode->m_tRight) {
    //        if (tNodePre->m_tLeft == tnode) {
    //            tNodePre->m_tLeft = tnode->m_tLeft;
    //        }
    //        else {
    //            tNodePre->m_tRight = tnode->m_tLeft;
    //        }
    //        tnode->m_tLeft->m_tFather = tNodePre;
    //        AdjustHeight(tNodePre);
    //        delete tnode;
    //    }
    //    //仅有右子树
    //    else if (!tnode->m_tLeft && tnode->m_tRight) {
    //        if (tNodePre->m_tLeft == tnode) {
    //            tNodePre->m_tLeft = tnode->m_tRight;
    //        }
    //        else {
    //            tNodePre->m_tRight = tnode->m_tRight;
    //        }
    //        tnode->m_tRight->m_tFather = tNodePre;
    //        AdjustHeight(tNodePre);
    //        delete tnode;
    //    }
    //    //不是根节点并且没有左右子树
    //    else {
    //        if (tNodePre->m_tLeft == tnode) {
    //            tNodePre->m_tLeft = nullptr;
    //        }
    //        else {
    //            tNodePre->m_tRight = nullptr;
    //        }
    //        AdjustHeight(tNodePre);
    //        delete tnode;
    //    }
    //}
    //return *this;
}


//删除链表内的某个值
template<typename T, typename T1, typename T2>
inline TreeKVAndLink<T, T1, T2>& TreeKVAndLink<T, T1, T2>::DeleteLink(T tValue, T2 tValue1)
{
    // TODO: 在此处插入 return 语句
    TreeNode<T, T1, T2>* tnode = Find(tValue);//找到节点
    //链表中没有找到匹配  ----标记
    if (tnode->m_list->Find(tValue1) == NULL) {
        return *this;
    }
    tnode->m_list->Delete(tnode->m_list->Find(tValue1));

    return *this;

}


template<typename T, typename T1, typename T2>
inline int TreeKVAndLink<T, T1, T2>::GetHeight(TreeNode<T, T1, T2>* pNode)
{
    return pNode == nullptr ? 0 : pNode->m_nHeight;
}

template<typename T, typename T1, typename T2>
inline void TreeKVAndLink<T, T1, T2>::CalcHeight(TreeNode<T, T1, T2>* pNode)
{
    pNode->m_nHeight = max(GetHeight(pNode->m_tRight), GetHeight(pNode->m_tLeft)) + 1;
    return;
}

//调整高度
template<typename T, typename T1, typename T2>
inline void TreeKVAndLink<T, T1, T2>::AdjustHeight(TreeNode<T, T1, T2>* pNode)
{
    while (pNode != nullptr)
    {
        //计算高度
        CalcHeight(pNode);

        //判断是否平衡
        if (std::abs(GetHeight(pNode->m_tLeft) - GetHeight(pNode->m_tRight)) > 1)
        {
            if (GetHeight(pNode->m_tRight) > GetHeight(pNode->m_tLeft))
            {
                auto pK = pNode->m_tRight;
                /*
                        p                          p
                        |                          |
                        n                          k
                          \                      /   \
                            k          ==>      n      kr
                           /  \                  \      \
                          kl   kr                 kl    krr
                                \
                                 krr
                */
                if (GetHeight(pK->m_tLeft) < GetHeight(pK->m_tRight))
                {
                    LeftRotate(pNode);
                }
                /*
                        p                   p                       p
                        |                   |                       |
                        n                   n                       kl
                          \        K 右旋     \           n 左旋   /   \
                            k        ==>       kl          ==>  n      k
                           /  \               /  \               \      \
                          kl   kr           klr   k               klr   kr
                         /                         \
                        klr                        kr
                */
                else
                {
                    RightRotate(pK);
                    LeftRotate(pNode);
                }
            }
            else
            {
                auto pK = pNode->m_tLeft;
                /*
                        p                          p
                        |                          |
                        n                          k
                      /                          /   \
                     k                 ==>     kl      n
                   /  \                       /      /
                  kl   kr                   kll     kr
                  /
                kll
                */
                if (GetHeight(pK->m_tLeft) > GetHeight(pK->m_tRight))
                {
                    RightRotate(pNode);
                }
                /*
                        p                  p                  p
                        |                  |                  |
                        n    k 左旋         n    n 右旋        kr
                      /                  /                  /   \
                     k         ==>     kr         ==>     k      n
                   /  \               /  \               /      /
                  kl   kr           k    krr           kl      krr
                        \          /
                        krr       kl
                */
                else
                {
                    LeftRotate(pK);
                    RightRotate(pNode);
                }
            }
        }
        //沿着父节点一路向上
        pNode = pNode->m_tFather;
    }
}

template<typename T, typename T1, typename T2>
inline void TreeKVAndLink<T, T1, T2>::LeftRotate(TreeNode<T, T1, T2>* pnode)
{
    TreeNode<T, T1, T2>* pMon = pnode;
    TreeNode<T, T1, T2>* pFather = pnode->m_tFather;
    TreeNode<T, T1, T2>* pRightSon = pnode->m_tRight;
    TreeNode<T, T1, T2>* pLeftSon = pRightSon->m_tLeft;

    if (pFather != nullptr)
    {
        if (pFather->m_tRight == pMon)
        {
            pFather->m_tRight = pRightSon;
        }
        else
        {
            pFather->m_tLeft = pRightSon;
        }
    }
    else
    {
        m_tRoot = pRightSon;
    }
    if (pLeftSon != nullptr)
    {
        pLeftSon->m_tFather = pMon;
    }
    pRightSon->m_tLeft = pMon;
    pRightSon->m_tFather = pFather;
    pMon->m_tRight = pLeftSon;
    pMon->m_tFather = pRightSon;
    CalcHeight(pMon);
    CalcHeight(pRightSon);
}

template<typename T, typename T1, typename T2>
inline void TreeKVAndLink<T, T1, T2>::RightRotate(TreeNode<T, T1, T2>* pnode)
{
    TreeNode<T, T1, T2>* pMon = pnode;
    TreeNode<T, T1, T2>* pFather = pnode->m_tFather;
    TreeNode<T, T1, T2>* pLeftSon = pnode->m_tLeft;
    TreeNode<T, T1, T2>* pRightSon = pLeftSon->m_tRight;

    if (pFather != nullptr)
    {
        if (pFather->m_tLeft == pMon)
        {
            pFather->m_tLeft = pLeftSon;
        }
        else
        {
            pFather->m_tRight = pLeftSon;
        }
    }
    else
    {
        m_tRoot = pLeftSon;
    }
    if (pRightSon != nullptr)
    {
        pRightSon->m_tFather = pMon;
    }
    pLeftSon->m_tRight = pMon;
    pLeftSon->m_tFather = pFather;
    pMon->m_tLeft = pRightSon;
    pMon->m_tFather = pLeftSon;
    CalcHeight(pMon);
    CalcHeight(pLeftSon);
}




