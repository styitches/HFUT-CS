#include<iostream>
using namespace std;
typedef struct node
{
	char data;
	/*int weight;*/
	node* fristchild = NULL;
	node* nextbrother = NULL;
	node(char data)
	{
		this->data = data;
	}
};
class tree {
public:
	tree();
	void createtree(node*& cur);
	void order(node* cur);
	void order();
protected:
	node* fristroot;
};
tree::tree() {
	createtree(fristroot);
}
void tree::createtree(node*& cur)
{
	char data;
	cout << "input the root if you donot want continue the nod input enough '#'" << endl;
	cin >> data;
	if (cur == fristroot) {
		fristroot = new node(data);
		createtree(fristroot->fristchild);
		createtree(fristroot->nextbrother);
	}
	else {
		if (data == '#') {
			cur = NULL;
			return;
		}
		else
		{
			//按前序遍历输入构建树
			cur = new node(data);
			createtree(cur->fristchild);
			createtree(cur->nextbrother);
		}
	}
}
void tree::order(node* cur) {
	if (cur != NULL) {
		order(cur->fristchild);
		cout << cur->data << " ";
		order(cur->nextbrother);
	}
	return;
}
void tree::order() {
	order(fristroot);
}