#include "iostream"
using namespace std;

class Node{
public:
    Node *next;
    char data;
};

class skewer {
private:
    Node *head;
    int length;
public:
    skewer();
    void travelSkewer();
    void createSkewer(string s);
    int compareSkewer(skewer s2);
};
