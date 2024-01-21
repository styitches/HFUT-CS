//
// Created by Styit on 2022/4/23.
//
#include "LinkList.h"
LinkList::LinkList() {
    head = new Node();//创建一个头结点
    head->next = NULL;//头结点无后继结点
    length = 0;
}
LinkList::~LinkList() {
    Node *pre, *p;
    pre = head;
    p = pre->next;
    while(p != NULL){
        delete pre;
        pre = p;
        p = p->next;
    }
    delete pre;
}
int LinkList::GetLength() {
    return length;
}
void LinkList::CreatLinkList(){
    Node *p, *s;
    p = head;
    int c;
    cout << "请输入链表结点数目: " ;
    cin >> length;
    int i = 1;
    while(i <= length){
        cout << "请输入结点的值：" ;
        cin >> c;
        s = new Node();
        s->data = c;
        p->next = s;
        p = s;
        i++;
    }
    p->next = NULL;
}
void LinkList::TravelList() {
    Node *p;
    p = head->next;
    for(int i = 1; i <= length; i++){
        cout << p->data << "  " ;
        p = p->next;
    }
    cout << endl;
}
void LinkList::SearchNode(int i) {
    if(i <= 0 || i > length){
        cout << "i已越界，无法查找" << endl;
        return;
    }
    int k = 1;
    Node *p;
    p = head->next;
    while(k != i){
        p = p->next;
        k++;
    }
    cout << p->data << endl;
    return;
}
void LinkList::InsertNode(int i, int x) {
    if(i > length + 1 || i <= 0){
        cout << "i已越界，无法插入" << endl;
        return;
    }
    Node *p;
    p = head->next;
    if(i == 1){
        Node *s = new Node();
        s->data = x;
        s->next = head->next;
        head->next = s;
        length++;
    }else{
        for(int j = 1; j < i - 1;){
            p = p->next;
            j++;
        }
        Node *s;
        s = new Node();
        s->data = x;
        s->next = p->next;
        p->next = s;
        length++;
    }

}
void LinkList::DeleteNode(int i) {
    if(i > length || i <= 0){
        cout << "i已越界，无法查找" << endl;
        return;
    }
    Node *p = head->next;
    for(int j = 1; j < i - 1; j++){
        p = p->next;
    }
    Node *s = p->next;
    p->next = p->next->next;
    delete s;
    length--;
}
void LinkList::InsertNodeRule(int x) {
    Node *p;
    p = head->next;
    if(p->data > x){
        Node *s = new Node();
        s->data = x;
        head->next = s;
        s->next = p;
    }
    for(int i = 1; i <= length; i++) {
        if (p->next != NULL) {
            if (p->next->data >= x && p->data < x) {
                Node *s;
                s = new Node();
                s->data = x;
                s->next = p->next;
                p->next = s;
                length++;
                return;
            }else{
                p = p->next;
            }
        }else{
            Node *s;
            s = new Node();
            s->data = x;
            p->next = s;
            s->next = NULL;
            length++;
            return;
        }
    }
}
void LinkList::DisconnectList() {
    Node *p = this->head->next;
    int length = this->GetLength();
    LinkList first,second;
    first.length = 0;
    second.length = 0;
    Node *p1 = first.head;
    Node *p2 = second.head;
    for(int i = 1; i <= length ; i++){
        Node *s = new Node();
        s->data = p->data;
        if(i % 2 != 0){
            p1->next = s;
            s->next = NULL;
            p1 = p1->next;
            p = p->next;
            first.length++;
            continue;
        }else{
            p2->next = s;
            s->next = NULL;
            p2 = p2->next;
            p = p->next;
            second.length++;
            continue;
        }
    }
    cout << "奇数项数列：";
    first.TravelList();
    cout << endl << "偶数项数列：";
    second.TravelList();
}
void LinkList::ConnectList() {
    LinkList l1, l2;
    l1.CreatLinkList();
    l2.CreatLinkList();
    Node *p1 = l1.head->next;
    Node *p2 = l2.head->next;
    Node *p = this->head;
    if (l1.length != 0 && l2.length != 0){
        for (int i = 1; i <= l1.length + l2.length; i++) {
            if (p1 == NULL && p2 != NULL){
                Node *s = new Node();
                s->data = p2->data;
                s->next = NULL;
                p->next = s;
                p2 = p2->next;
                p = p->next;
                this->length++;
            }
            if (p2 == NULL && p1 != NULL){
                Node *s = new Node();
                s->data = p1->data;
                s->next = NULL;
                p->next = s;
                p1 = p1->next;
                p = p->next;
                this->length++;
            }
            if(p2 == NULL && p1 == NULL){
                break;
            }
            if (p1->data >= p2->data) {
                Node *s = new Node();
                s->data = p2->data;
                s->next = NULL;
                p->next = s;
                p2 = p2->next;
                p = p->next;
                this->length++;
            } else {
                Node *s = new Node();
                s->data = p1->data;
                s->next = NULL;
                p->next = s;
                p1 = p1->next;
                p = p->next;
                this->length++;
            }
        }
    }else if (l2.length == 0){
        for(int i = 0; i < l1.length; i++){
            Node *s = new Node();
            s->data = p1->data;
            s->next = NULL;
            p->next = s;
            p1 = p1->next;
            p = p->next;
            this->length++;
        }
    }else if (l1.length == 0){
        for(int i = 0; i < l2.length; i++){
            Node *s = new Node();
            s->data = p2->data;
            s->next = NULL;
            p->next = s;
            p2 = p2->next;
            p = p->next;
            this->length++;
        }
    }
    this->TravelList();
}
