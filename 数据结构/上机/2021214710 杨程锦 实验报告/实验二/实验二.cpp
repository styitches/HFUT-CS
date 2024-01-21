//#include <iostream>
//using namespace std;
//typedef int elementype;
//typedef int Error_code;
//typedef struct node {
//    node *next;
//    elementype data;
//};
//class noheadlist {
//public:
//    noheadlist();
//    ~noheadlist();
//    Error_code insert(int i,elementype x);
//    Error_code element_delete(int i);
//    Error_code get_element(int i, elementype &x);
//    Error_code length();
//private:
//    int count;
//     node  *head;
//};
//noheadlist::noheadlist() {
//    count = 0;
//}
//Error_code noheadlist::length() {
//    return count;
//}
//Error_code noheadlist::insert(int i, elementype x) {
//    node* p;
//    p = new node;
//    p->data = x;
//    if (count == 0) {
//        p->next = p;
//        head = p;
//    }
//    else
//    {
//        node* q=head;
//        for (int j = 1; j < i; j++)
//            q = q->next;
//        p->next = q->next;
//        q->next = p;
//    }
//    count++;
//    return 1;
//}
//Error_code noheadlist::element_delete(int i) {
//    node* q = head;
//    node* p;
//    for (int j = 0; j < i; j++)
//        q = q->next;
//    p = q->next;
//    q->next = p->next;
//    delete p;
//    count--;
//    return 1;
//}
//Error_code noheadlist::get_element(int i, elementype& x) {
//    node* q = head;
//    for (int j = 0;j < i;j++)
//        q = q->next;
//    x = q->data;
//    return 1;
//}
//noheadlist::~noheadlist() {
//    while (count > 0)
//        element_delete(length());
//}
//int main()
//{
//    noheadlist(List);
//    for (int i = 0; i < 15; i++) {
//        List.insert(i, i);
//    }
//    int judge = 0;
//    for (int i = 0; i < List.length(); i++) {
//        elementype x;
//        List.get_element(i, x);
//        cout << x << " ";
//        if (!(x - i<3 && x - i>-3))
//            judge = 1;
//    }
//    cout << endl;
//    if (judge == 0)
//        cout << "TRUE";
//    else if (judge == 1)
//        cout << "FLASE";
//}




//////////////////////


//#include <iostream>
//typedef int elemenType;
//typedef int Error_code;
//const int maxlen = 10;
//using namespace std;
//class List {
//public:
//    List();
//    int  Length() const;
//    Error_code  Get_element(const int i, elemenType& x) const;
//    int  Locate(const elemenType x) const;
//    Error_code  Insert(const int i, const elemenType x);
//    Error_code Delete_element(const int i);
//private:
//    int data[maxlen];
//    int count;
//};
//List::List() { count = 0; }
//int  List::Length()const { return count; }
//Error_code List::Get_element(const int i, elemenType& x) const {
//    if (i<0 || i>count)
//        return 0;
//    x = data[i];
//    return 1;
//}
//int  List::Locate(const elemenType x) const {
//    for (int i = 0; i < Length(); i++)
//        if (data[i] == x)
//            return (i + 1);
//    return 0;
//}
//Error_code  List::Insert(const int i, const elemenType x)
//{
//    if (count == maxlen)
//        return 0;
//    if (i < 0 || i > Length() + 1)
//        return 0;
//    for (int j = count; j >= i; j--)
//        data[j] = data[j - 1];
//    data[i] = x;
//    count++;
//    return 1;
//}
//Error_code List::Delete_element(const int i)
//{
//    if (Length() == 0) return 0;
//    if (i < 0 || i > Length()) return 0;
//    for (int j = i + 1; j <= Length(); j++)
//        data[j - 2] = data[j - 1];
//    count--;
//    return 1;
//}
//void U(List A, List B, List& C) {
//    for (int i = 0; i < A.Length(); i++) {
//        int x = 0;
//        A.Get_element(i, x);
//        C.Insert(i, x);
//    }
//    int x = 0, y = 0; bool judge = 0;
//    for (int i = 0; i < B.Length(); i++) {
//        judge = 0;
//        for (int j = 0; j < A.Length(); j++) {
//            A.Get_element(j, x);
//            B.Get_element(i, y);
//            if (x == y)
//                judge = 1;
//        }
//        if (judge == 0)
//            C.Insert(C.Length(), y);
//    }
//};
//void n(List A, List B, List& C) {
//    int x = 0, y = 0;
//    for (int i = 0; i < A.Length(); i++)
//        for (int j = 0; j < B.Length(); j++) {
//            A.Get_element(i, x);
//            B.Get_element(j, y);
//            if (x == y)
//                C.Insert(C.Length(), y);
//        }
//}
//void different(List A, List B, List& C) {
//    int x = 0, y = 0; bool judge = 0;
//    for (int i = 0; i < B.Length(); i++) {
//        judge = 0;
//        for (int j = 0; j < A.Length(); j++) {
//            A.Get_element(i, x);
//            B.Get_element(j, y);
//            if (x == y)
//                judge = 1;
//        }
//        if (judge == 0)
//            C.Insert(C.Length(), x);
//    }
//    for (int i = 0; i < A.Length(); i++) {
//        judge = 0;
//        for (int j = 0; j < B.Length(); j++) {
//            A.Get_element(j, x);
//            B.Get_element(i, y);
//            if (x == y)
//                judge = 1;
//        }
//        if (judge == 0)
//            C.Insert(C.Length(), y);
//    }
//};
//int main()
//{
//    List(A);
//    A.Insert(0, 1);
//    A.Insert(1, 2);
//    A.Insert(2, 3);
//    A.Insert(3, 4);
//    for (int i = 0; i < A.Length(); i++) {
//        int x;
//        A.Get_element(i, x);
//        cout << x << " ";
//    }
//    cout << endl;
//    List(B);
//    B.Insert(0, 3);
//    B.Insert(1, 4);
//    B.Insert(2, 5);
//    B.Insert(3, 6);
//    for (int i = 0; i < B.Length(); i++) {
//        int x;
//        B.Get_element(i, x);
//        cout << x << " ";
//    }
//    cout << endl;
//    List(C1);
//    List(C2);
//    List(C3);
//    //U，C， different
//    U(A, B, C1);
//    n(A, B, C2);
//    different(A, B, C3);
//        for (int i = 0; i < C1.Length(); i++) {
//            int x;
//            C1.Get_element(i, x);
//            cout << x << " ";
//        }
//        cout << endl;
//        for (int i = 0; i < C2.Length(); i++) {
//            int x;
//            C2.Get_element(i, x);
//            cout << x << " ";
//        }
//        cout << endl;
//        for (int i = 0; i < C3.Length(); i++) {
//            int x;
//            C3.Get_element(i, x);
//            cout << x << " ";
//        }
//        cout << endl;
//    A.~List();
//    B.~List();
////    C.~List();
//}

/////////////////////////////

#include <iostream>
#include"../duList.h"
using namespace std;
int main() {
	duList(list);
	int x;
	for (int i = 0; i < 9; i++) {
		cin >> x;
		list.Insert(i, x);
	}
	int* a = new int[list.Length()];
	for (int i = 0; i < 9; i++) {
		list.Get_element(i, x);
		a[i] = x;
	}
	int judge = 0;
	for (int i = 0; i < list.Length() / 2; i++) {
		if (a[i] != a[list.Length() - i-1])
			judge = 1;
	}
	if (judge == 0)
		cout << "TRUE";
	else if (judge == 1)
		cout << "FLASE";
	
	/*list.~duList();*/
}