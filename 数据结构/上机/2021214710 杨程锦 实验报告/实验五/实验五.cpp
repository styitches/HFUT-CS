#include<iostream>
#include"..\btree.h"
#include"..\tree.h"
using namespace std;

//void tree::hforder(node* cur) {
//	while (fristroot->nextbrother!= NULL) {
//		if (cur->weight < (cur->nextbrother)->weight) {
//			node* s = cur;
//			node* p = cur->nextbrother;
//			p->fristchild = s->fristchild;
//			p->nextbrother = s->nextbrother;
//			p = s->fristchild;
//		}
//		cur=cur->nextbrother;
//		if (cur->nextbrother == NULL)
//			cur = fristroot;
//	}
//}
//void tree::weight() {
//	node* cur = fristroot;
//	while (cur->nextbrother != NULL) {
//		cin >> cur->weight;
//		cur = cur->nextbrother;
//	}
//}

int main()
{
	q1.open("F:\\各类代码\\数据结构\\实验五\\q1.txt");
	//btree tree;
	//tree.getdepth();
	//tree.midorder();//中序遍历
	//tree.Threading();
	//tree.insert('E', 'H');
	//tree.ThreadingPrint();
	tree mytree=tree();
	mytree.order();
}
//A B C # # D # # E F # # G # #
//A B E K # # F # # C G # # D H # I # J # # # L # M N # # #
//A # B # C # D # # 11 13 14 30
