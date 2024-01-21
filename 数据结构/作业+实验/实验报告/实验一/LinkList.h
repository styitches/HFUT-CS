//
// Created by Styit on 2022/4/23.
//
#include "iostream"
using namespace std;
class Node{
public:
    int data;
    Node* next;
};
class LinkList{
private:
    int length;
    Node* head;
public:
    LinkList();
    ~LinkList();
    int GetLength();
    void TravelList();
    void CreatLinkList();
    void SearchNode(int i);
    void InsertNode(int i, int x);
    void DeleteNode(int i);
    void InsertNodeRule(int x);
    void DisconnectList();
    void ConnectList();
};