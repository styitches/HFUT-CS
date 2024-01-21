#include "JosephRing.h"
List::List() {
    head = NULL;
    count = 0;
}

void List::Init() {
    cout << "请输入元素： " << endl;
    int cur = 1;
    Node* ptr = new Node();
    head = ptr;
    ptr->data = cur;
    ptr->next = ptr;
    cur++;
    count++;
    while (cur != 42) {
        Node* s = new Node();
        s->data = cur;
        s->next = ptr->next;
        ptr->next = s;
        ptr = s;
        cur++;
        count++;
    }
    cout << "创建成功" << endl;
}

void List::Show() {
    Node* s = head;
    for (int i = 0; i < count; i++)
    {
        cout << s->data << " ";
        s = s->next;
    }
    cout << endl;
}

void List::Round() {
    Node* p = head;
    while (count > 2) {
        p = p->next;
        Node* a = p->next;
        if (a == head) {
            head = head->next;
        }
        p->next = p->next->next;
        free(a); count--;
        p = p->next;
    }
}
