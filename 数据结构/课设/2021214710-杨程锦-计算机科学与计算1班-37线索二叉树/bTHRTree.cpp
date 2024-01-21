#include "bTHRTree.h"


ifstream ifs("D:\\TREE.txt");
ofstream ofs("D:\\storeOrderTREE.txt");

bTHRNode::bTHRNode() {
    this->rightChild = NULL;
    this->leftChild = NULL;
    this->parent = NULL;
    this->leftTag = 0;
    this->rightTag = 0;
}


void bTHRTree::visit(Node2 T, int x) {
    switch (x) {
        case 1:
            ofs << T->data << " ";
            break;
        case 2:
            stack.push(T);
            break;
        case 3:
            queue.push(T);
            break;
    }

}

//有孩子为0  没孩子为1

void bTHRTree::createTree(Node2 &T, Node2 parent) {
    char ch;
    ifs >> ch;
    if (ch == '#') {
        T = NULL;
    } else {
        T = new bTHRNode();
        T->data = ch;
        T->parent = parent;
        createTree(T->leftChild, T);
        createTree(T->rightChild, T);
    }
}

//中序 左根右
void bTHRTree::inThreading1(Node2 &T, Node2 &pre){
    Node2 G = T;
    if(G != NULL){
        inThreading1(G->leftChild, pre);
        if(G->leftChild == NULL){
            G->leftTag = 1;
            G->leftChild = pre;
        } else {
            G->leftTag = 0;
        }
        if(pre != NULL && pre->rightChild == NULL){
            pre->rightTag = 1;
            pre->rightChild = G;
        }
        pre = G;
        inThreading1(G->rightChild, pre);
    }
}
void bTHRTree::TinOrder(Node2 T, int x) {
    Node2 G = T;
    while (G){
        while (G->leftTag == 0){
            G = G->leftChild;
        }
        visit(G, x);
        while (G->rightTag == 1){
            G = G->rightChild;
            visit(G, x);
        }
        G = G->rightChild;
    }
    cout << endl;
//    cout << "文件已输出！";
}

//先序 根左右
void bTHRTree::inThreading2(Node2 &T, Node2 &pre) {
    Node2 G = T;
    if (G != NULL){
        if (G->leftChild == NULL){
            G->leftChild = pre;
            G->leftTag = 1;
        }
        if (pre != NULL && pre->rightChild == NULL){
            pre->rightChild = G;
            pre->rightTag = 1;
        }
        pre = G;
        if (G->leftTag == 0 && G->leftChild != NULL){
            inThreading2(G->leftChild, pre);
        }
        if (G->rightTag == 0 && G->rightChild != NULL){
            inThreading2(G->rightChild, pre);
        }
    }
}
void bTHRTree::PreOrder(Node2 T, int x) {
    Node2 G = T;
    while (G){
        while (G->leftTag == 0){
            visit(G, x);
            G = G->leftChild;
        }
        visit(G, x);
        G = G->rightChild;
    }
    cout << endl;
//    cout << "文件已输出！";
}

//后序 左右根
void bTHRTree::inThreading3(Node2 &T, Node2 &pre) {
    Node2 G = T;
    if (G != NULL){
        if (G->leftTag == 0 && G->leftChild != NULL){
            inThreading3(G->leftChild, pre);
        }
        if (G->rightTag == 0 && G->rightChild != NULL){
            inThreading3(G->rightChild, pre);
        }
        if (G->leftChild == NULL){
            G->leftChild = pre;
            G->leftTag = 1;
        }
        if (pre != NULL && pre->rightChild == NULL){
            pre->rightChild = G;
            pre->rightTag = 1;
        }
        pre = G;
    }
}

void bTHRTree::PostOrder(Node2 T, int x) {
    if (T != NULL){
        Node2 G = T;
        pre = NULL;
        while (pre != T){
            while (G->leftChild != NULL && G->leftTag == 0) {
                G = G->leftChild;
            }
            while (G != NULL && G->rightTag == 1){
                visit(G, x);
                pre = G;
                G = G->rightChild;
            }
            while (pre != T && G->rightChild == pre){
                visit(G, x);
                pre = G;
                if (pre != T){
                    G = G->parent;
                }
            }
            if (G->rightTag == 0){
                G = G->rightChild;
            }
        }
    }
//    cout << "文件已输出！";
}

//逆转线索化
void bTHRTree::reverseThread(Node2 T) {
    if (T != NULL){
        if (T->leftTag == 1 && T->rightTag == 1){
            T->leftChild = NULL;
            T->rightChild = NULL;
            T->leftTag = 0;
            T->rightTag = 0;
        }
        if (T->leftTag == 0 && T->rightTag == 1){
            T->rightChild = NULL;
            T->rightTag = 0;
            reverseThread(T->leftChild);
        }
        if (T->leftTag == 1 && T->rightTag == 0){
            T->leftChild = NULL;
            T->leftTag = 0;
            reverseThread(T->rightChild);
        }
        if (T->leftTag == 0 && T->rightTag == 0){
            reverseThread(T->leftChild);
            reverseThread(T->rightChild);
        }
    }

}

//删除节点
void bTHRTree::deleteNode(Node2 T, char x) {
    Node2 G = T;
    if (G != NULL){
        if (G->data > x){
            pre = G;
            deleteNode(G->leftChild,x);
        } else if (G->data < x){
            pre = G;
            deleteNode(G->rightChild, x);
        } else if (G->data == x){
            if (pre->rightChild == G){
                pre->rightChild = NULL;
                pre->rightTag = 1;
            } else if (pre->leftChild == G){
                pre->leftChild = NULL;
                pre->leftTag = 1;
            }
            free(G);
        }
    }
}

//插入节点
void bTHRTree::insertNode(Node2 P, Node2 R) {
    if (P->leftChild != NULL && P->rightChild != NULL){
        cout << "无法插入节点" << endl;
    }
    if (P->leftChild != NULL && P->rightChild == NULL){
        P->rightChild = R;
        R->parent = P;
    }
    if (P->leftChild == NULL && P->rightChild != NULL){
        P->leftChild = R;
        R->parent = P;
    }
    if (P->leftChild == NULL && P->rightChild == NULL){
        P->leftChild = R;
        R->parent = P;
    }
}

//节点入栈
void bTHRTree::initStack(Node2 T, int type) {
    switch (type) {
        case  1:{
            //中序
            inThreading1(T, pre);
            TinOrder(T, 2);
            break;
        }
        case 2:{
            //先序
            inThreading2(T, pre);
            PreOrder(T, 2);
            break;
        }
        case 3:{
            //后序
            inThreading3(T, pre);
            PostOrder(T, 2);
            break;
        }
    }
}

//查找前驱
Node2 bTHRTree::searchPreNode(char x) {
    while (stack.top()->data != x){
        stack.pop();
    }
    stack.pop();
    if (!stack.empty()){
        return stack.top();
    } else {
        return NULL;
    }
}

//节点入队
void bTHRTree::initQueue(Node2 T, int type) {
    switch (type) {
        case  1:{
            //中序
            inThreading1(T, pre);
            TinOrder(T, 3);
            break;
        }
        case 2:{
            //先序
            inThreading2(T, pre);
            PreOrder(T, 3);
            break;
        }
        case 3:{
            //后序
            inThreading3(T, pre);
            PostOrder(T, 3);
            break;
        }
    }
}

//查找后继
Node2 bTHRTree::searchNextNode(char x) {
    while (queue.front()->data != x){
        queue.pop();
    }
    queue.pop();
    if (!queue.empty()){
        return queue.front();
    } else {
        return NULL;
    }
}

