#include "skewer.h"

skewer::skewer() {
    head = new Node();
    head->next = NULL;
    this->length = 0;
}



void skewer::createSkewer(string s) {
    int lengths1 = s.length();
    Node *sym = new Node();
    sym = head;
    for (int i = 0; i < lengths1; i++){
        Node *p = new Node();
        p->data = s[i];
        sym->next = p;
        sym = p;
        length++;
    }
}

void skewer::travelSkewer() {
    Node *p = new Node();
    p = head->next;
    for (int i = 0; i < length; i++){
        cout << p->data;
        p = p->next;
    }
}

int skewer::compareSkewer(skewer s2) {
    Node *sym1 = new Node();
    Node *sym2 = new Node();
    sym1 = this->head->next;
    sym2 = s2.head->next;
    int minLength;
    if (this->length >= s2.length){
        minLength = s2.length;
    } else {
        minLength = this->length;
    }
    for (int i = 0; i < minLength; i++){
        if (sym1->data == sym2->data){
            if (i == minLength - 1){
                return 0;
            } else {
                sym1 = sym1->next;
                sym2 = sym2->next;
                continue;
            }
        } else if (sym1->data > sym2->data){
            return 1;
        } else {
            return -1;
        }
    }
}