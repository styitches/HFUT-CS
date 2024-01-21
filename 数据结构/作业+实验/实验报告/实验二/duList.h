#pragma once
#include<iostream>
typedef int elementype;
typedef int Error_code;
using namespace std;
typedef struct dunode {
    elementype data;
    dunode* prior, * next;
};
class duList {
public:
    duList();            
    Error_code Length();
    Error_code Insert(int i,elementype x);
    Error_code element_delete(int i);
    Error_code Get_element(int i,elementype &x);
    Error_code change();
    ~duList();
private:
    int count;
    dunode *head;
};
duList::duList() {
    head = new dunode;
    head->prior = head;
    head->next = head;
    count = 0;
}
Error_code duList::Length() { return count; }
Error_code duList::Insert(int i, elementype x) {
    dunode* p = head, * q;
    q = new dunode;
    for (int k = 0; i > k; k++) {
        p = p->next;
    }
    p->next = q;
    q->data = x;
    q->prior = p;
    p = q;
    count++;
    return 1;
}
Error_code duList::element_delete(int i) {
    dunode* p;
    p = head->next;
    for (int k = 0; k < i; k++)
        p = p->next;
    p->prior->next = p->next;
    p->next->prior = p->prior;
    count--;
    delete p;
    return 1;
}
Error_code duList::Get_element(int i, elementype& x) {
    dunode* s= head->next;
    for (int k = 0; k < i; k++)
        s = s->next;
    x = s->data;
    return 1;
}
Error_code duList::change() {
    dunode* p=head->next, * q;
    for (int i = 0; i < Length();i++) {
        q = head->next->next;
        p->next = q->next;
        q->next->prior = p;
        p->prior = q;
        q->next=p;
        head->next = q;
        q->prior = head;
   }
        
    return 1;
}
duList::~duList(){
    while (Length() > 0)
        element_delete(Length());
    delete head;
    }