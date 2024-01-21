#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
using namespace std;



class bTHRNode{
public:
    char data;
    bTHRNode* leftChild;
    bTHRNode* rightChild;
    bTHRNode* parent;
    int leftTag;
    int rightTag;

    bTHRNode();
};

typedef bTHRNode* Node2;


class bTHRTree{
public:

    void createTree(Node2 &T, Node2 parent);

    void visit(Node2 T, int x);

    //中序线索化
    void inThreading1(Node2 &T, Node2 &pre);
    void TinOrder(Node2 T, int x); //线索化过程

    //先序线索化
    void inThreading2(Node2 &T, Node2 &pre);
    void PreOrder(Node2 T, int x);

    //后序线索化
    void inThreading3(Node2 &T, Node2 &pre);
    void PostOrder(Node2 T, int x);

    //逆转线索化
    void reverseThread(Node2 T);

    //删除节点
    void deleteNode(Node2 T, char x);

    //插入节点
    void insertNode(Node2 P, Node2 R);

    //节点入栈
    void initStack(Node2 T, int type);

    //查找前驱
    Node2 searchPreNode(char x);

    //节点入队
    void initQueue(Node2 T, int type);

    //查找后继
    Node2 searchNextNode(char x);








    Node2 pre = NULL;
    Node2 T = new bTHRNode();
    Node2 parent;
    stack<Node2> stack;
    queue<Node2> queue;

};

