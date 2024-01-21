#include "iostream"
using namespace std;
class Node {
public:
    int data;
    Node* next;
};

class List {
public:
    List();
    ~List() {};
    void Init();//创建链表
    void Show();//遍历
    void Round();
private:
    int count;
    Node* head;
};
