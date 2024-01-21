#include<iostream>
#include <fstream>
using namespace std;
ifstream q1;
typedef struct Node
{
	char data;
	int depth;
	Node* left,* right;
	int LTag, RTag;
	Node(char data)
	{
		this->data = data;
		this->left = left;
		this->right = right;
		this->LTag = 1;
		this->RTag = 1;
	}
}Node;

class btree {
public:
	btree();
	void createBinaryTree(Node*& cur);
	void midorder() { midorder(root); };
	void getdepth() { getdepth(root, 1); }
	void Threading() { Threading(root); }
	void ThreadingPrint() { ThreadingPrint(root); }
	void midorder(Node* cur);
	void getdepth(Node* p, int depth);
	void ThreadingPrint(Node* T);
	void Threading(Node* T);
	void insert(char data1,char data2);
protected:
	Node *root;
};
btree::btree() {
	createBinaryTree(root);
}
void btree::createBinaryTree(Node*&cur)
{
	char data;
	cout << "input the root if you donot want continue the nod input enough '#'" << endl;
	/*cin >> data;*/
	q1>>data;
	if (cur == root) {
		root = new Node(data);
		createBinaryTree(root->left);
		createBinaryTree(root->right);
	}
	else{
		if (data == '#') {
			cur=NULL;
			return;
		}
		else
		{
			//按前序遍历输入构建二叉树
			cur = new Node(data);
			createBinaryTree(cur->left);
			createBinaryTree(cur->right);
		}
	}
}
void btree::midorder(Node* cur) {
	if (cur != NULL) {
		midorder(cur->left);
		cout << cur->data <<":"<<cur->depth<< " ";
		midorder(cur->right);
	}
	return;
}
void btree::getdepth(Node* p, int depth)
{
	if (!p) 
		return;
	p->depth = depth;
	//if (p->left == NULL && p->right == NULL) 
	//	ans = max(ans, p->depth);
	getdepth(p->left, depth + 1);
	getdepth(p->right, depth + 1);
}
Node* pre = NULL; //pre表示前驱节点，初始化为NULL
/////////////////////////////////////////////////////////////////////////////////////////////先序
void btree::Threading(Node* T) {
	if (T == NULL) 
		return; //当前节点是空
	if (T->left == NULL) { //当前节点左为空，那么左孩子应指向前驱pre
		T->left = pre;
		T->LTag = 0;
	}
	if (pre != NULL && pre->right == NULL) { //pre结点右孩子为空，那么右孩子应指向后继节点，也就是当前节点T
		pre->right = T;
		pre->RTag = 0;
	}
	pre = T; //更新pre为当前节点
	if (T->LTag == 1) Threading(T->left); //有左孩子递归线索化左子树
	if (T->RTag == 1) Threading(T->right); //有右孩子递归线索化右子树
	return;
}
////根据前序线索二叉树输出前序序列
void btree::ThreadingPrint(Node* T) {
	while (T != NULL) { //当前节点不为空
		cout << T->data << " "; //输出当前节点的内容
		if (T->LTag == 1) T = T->left; //如果有左孩子，那么左孩子必为后继节点
		else T = T->right; /*如果没有左孩子，那么左孩子指向了当前节点的前驱。
                              如果右孩子存在，那么右孩子就是后继，
                              如果右孩子不存在，那么右孩子肯定指向后继节点，
                              除非是最后一个节点右孩子会指向NULL，
                              那么此时恰好跳出while循环，输出结束*/
	}
	cout << endl;
	return;
}
//////////////////////////////////////////////////////////////////////////////////////////中序
//void btree::Threading(Node* T) {
//	if (T == NULL)
//	{
//		return;
//	}
//	Threading(T->left);    // 左
//	if (T->left == NULL) { //当前节点左为空，那么左孩子应指向前驱pre
//		T->left = pre;
//		T->LTag = 0;
//	}
//	if (pre != NULL && pre->right == NULL) { //pre结点右孩子为空，那么右孩子应指向后继节点，也就是当前节点T
//		pre->RTag = 0;
//		pre->right = T;
//	}
//	Threading(T->right);   //右
//}
/////////////////////////////////////////////////////////////////////////////////////////后序
//void btree::Threading(Node* T) {
//	if (T == NULL)
//	{
//		return;
//	}
//	Threading(T->left);    // 左
//	Threading(T->right);   //右
//	if (T->left == NULL) { //当前节点左为空，那么左孩子应指向前驱pre
//		T->left = pre;
//		T->LTag = 0;
//	}
//	if (pre != NULL && pre->right == NULL) { //pre结点右孩子为空，那么右孩子应指向后继节点，也就是当前节点T
//		pre->RTag = 0;
//		pre->right = T;
//	}
//}

void btree::insert(char data1,char data2){
	Node* T = root;
	while (T->data != data1) {
		if (T->LTag == 1) 
			T = T->left; //如果有左孩子，那么左孩子必为后继节点
		else T = T->right;
	}
	Node* p = T;
	Node* s;
	s = new Node(data2);
	s->left = p->left;
	s->LTag = 1;

	s->right = p;
	s->RTag = 1;

	p->left = s;
	p->LTag = 1;
	if (s->left->LTag == 1)
		s->left->right = p;

