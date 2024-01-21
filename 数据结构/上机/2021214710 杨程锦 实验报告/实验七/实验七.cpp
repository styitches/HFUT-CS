#include<iostream>
#include<iomanip>
using namespace std;
int fun()
{
	srand(time(0) + rand());
	return rand() % 1000;
}
void test1() {
	cout << "请输入数据长度" << endl;
	int* x, a, b, c = 0;
	cin >> a;
	x = new int[a];
	for (int o = 0; o < a; o++) {
		x[o] = fun();
		cout << x[o]<<"  ";
	}
	cout << "请输入待查找的数据" << endl;
	cin >> b;
	for (int o = 0; o < a; o++) {
		if (x[o] == b) {
			cout << "第" << o + 1 << "个数据=" << b << endl;
			c++;
		}
	}
	if (!c)cout << "未找到" << b << endl;
}
void test2() {
	class btree
	{
	public:
		btree* left;
		btree* right;
		int data;
		btree(int i) :left(NULL), right(NULL), data(i) {}

		void insert(int a) {
			if (a < data && left)
				left->insert(a);
			else if (a < data && !left)
				left = new btree(a);
			else if (a > data && right)
				right->insert(a);
			else if (a > data && !right)
				right = new btree(a);
		};
		static void find(const btree* b, int find) {
			int mm = 0;
			find_(b, mm, find);
		}
		static void find_(const btree* b, int mm, int find) {
			if (b != NULL)
			{
				if (find <= b->data) {
					find_(b->left, mm, find);
				}
				if (b->data == find)cout << "找到了" << endl;
				if (find >= b->data) {
					find_(b->right, mm, find);
				}
			}
		};//中序遍历
		static void inorder(const btree* b) {
			int mm = 0;
			inorder_(b, mm);
			cout << endl;
		}
		static void inorder_(const btree* b, int mm) {
			if (b != NULL)
			{
					inorder_(b->left, mm);
				cout << b->data << " ";
					inorder_(b->right, mm);
			}
		};//中序遍历
		~btree()
		{
			if (left)
				delete left;
			if (right)
				delete right;
		}
	};
	int* zu, mm, f;
	cout << "请输入数据长度" << endl;
	cin >> mm;
	zu = new int[mm];

	for (int i = 0; i < mm; ++i)
	{
		zu[i] = fun();
	}
	btree* root = new btree(zu[0]);
	for (int i = 1; i < mm; ++i)
	{
		root->insert(zu[i]);
	}
	btree::inorder(root);
	cout << "请输入要找的数据" << endl;
	cin >> f;
	btree::find(root, f);
	cout << endl;
	delete root;
}
void test3() {
	typedef int T;
	struct node {
		T data;
		node* next;
	};
	class ll {
	private:
		node x[10];
	public:
		ll() {
			for (int o = 0; o < 10; o++) {
				x[o].data = o;
			}
		}
		void insert_num(T data_) {
			int y = data_ % 10;
			node* p = new node;
			p->data = data_;
			p->next = NULL;
			node* q = x[y].next;
			x[y].next = p;
			p->next = q;
		}
		void find(int data_) {
			int y = data_ % 10;
			node* p = &x[y];
			p = p->next;
			while (p != NULL) {
				if (p->data == data_) {
					cout << "找到了" << endl;
					return;
				}
				p = p->next;
			}
			cout << "未找到" << endl;
		}
	};
	ll x;
	cout << "请输入数据长度" << endl;
	int length, num;
	cin >> length;
	for (int o = 0; o < length; o++) {
		x.insert_num(fun());
	}
	cout << "请输入需要查找的数据" << endl;
	cin >> num;
	x.find(num);

}
void test3_() {
	const int p_ = 100000;
	cout << "请输入数据长度" << endl;
	int length, * node, temp;
	cin >> length;
	node = new int[length * 12 / 10];
	temp = length / 2;
	for (int o = 0; o < length; o++) {
		node[o] = p_;
	}
	for (int p = 0; p < length; p++) {
		int insert = fun();
		int insert_ = insert % temp;
		if (p_ == node[insert_]) {
			node[p] = insert;
		}
		else {
			for (int mm = insert + 1; mm < length; mm++) {
				if (p_ == node[mm]) {
					node[p] = insert;
				}
			}
		}
	}
	cout << "请输入需要查找的数据" << endl;
	int find;
	cin >> find;
	for (int pp = find % temp; pp < length; pp++) {
		if (node[pp] == find) {
			cout << "找到了" << endl;
			return;
		}
	}
	cout << "没有找到" << endl;


}
//void partition(int A[], int s, int t, int &cutpoint)
////对数组A中下标为s～t的子表进行划分
//{
//	int x = A[s];     //保存中间元素，腾出空位
//	int i = s; int j = t;
//	while (i != j) {
//		while (i<j && A[j]>x)   j--;
//		if (i < j) { A[i] = A[j];  i = i + 1; }
//		while (i < j && A[i] < x)   i++;
//		if (i < j) { A[j] = A[i];   j = j - 1; }
//	}
//	A[i] = x;  cutpoint = i;
//}
//void Quick_sort(int A[], int s, int t)
//{
//	int i = 0;
//	if (s < t) {
//		partition(A, s, t, i);  //划分
//		Quick_sort(A, s, i - 1);  //对前面子表快速排序
//		Quick_sort(A, i + 1, t);  //对后面子表快速排序
//	}
//}


void test01() {//////基于顺序表查找
	int* x, length;
	cout << "请输入数据长度" << endl;
	cin >> length;
	x = new int[length];
	for (int o = 0; o < length; o++) {
		x[o] = fun();
	}
	cout << "排序前" << endl;
	for (int o = 0; o < length; o++) {
		cout << setw(6) << x[o];
		if ((o + 1) % 10 == 0)cout << endl;
	}
	for (int o = length - 1; o >= 0; o--) {
		for (int p = 1; p <= o; p++) {
			if (x[p] < x[p - 1]) {
				int temp = x[p];
				x[p] = x[p - 1];
				x[p - 1] = temp;
			}
		}
	}
	cout << "排序后" << endl;
	for (int o = 0; o < length; o++) {
		cout << setw(6) << x[o] << " ";
		if ((o + 1) % 10 == 0)cout << endl;
	}
}
void test02() {
	class btree
	{
	public:
		btree* left;
		btree* right;
		int data;
		btree(int i) :left(NULL), right(NULL), data(i) {}

		void insert(int a) {
			if (a < data && left)
				left->insert(a);
			else if (a < data && !left)
				left = new btree(a);
			else if (a > data && right)
				right->insert(a);
			else if (a > data && !right)
				right = new btree(a);
		};
		static void inorder(const btree* b) {
			int mm = 0;
			inorder_(b, mm);
		}
		static void inorder_(const btree* b, int mm) {
			if (b != NULL)
			{
				inorder_(b->left, mm);
				cout << b->data<<" ";
				inorder_(b->right, mm);
			}
		};//中序遍历
		~btree()
		{
			if (left)
				delete left;
			if (right)
				delete right;
		}
	};
	int* zu, mm;
	cout << "请输入数据长度" << endl;
	cin >> mm;
	zu = new int[mm];

	for (int i = 0; i < mm; ++i)
	{
		zu[i] = fun();
	}
	btree* root = new btree(zu[0]);
	for (int i = 1; i < mm; ++i)
	{
		root->insert(zu[i]);
	}

	btree::inorder(root);
	cout << endl;
	delete root;
}
void test03() {
	struct Node
	{
		int data;//数据域
		Node* next;//指针域
	};
	//定义程序所需的特殊队列
	class Queue
	{
	private:
		Node* front;//链式对列的头指针
		Node* rear;//链队的尾指针
	public:
		//构造函数，初始化队列（带头结点的链式队列）
		Queue()
		{
			//开始先构造一个空结点，没有数据元素存储
			Node* p = new Node;
			p->data = NULL;
			p->next = NULL;
			//开始是空链队，首尾指针分别去指向队头结点
			front = p;
			rear = p;
		}
		//析构函数，销毁链队的结点占据的内存
		~Queue()
		{
			//标记指针
			Node* p = front;
			//辅助的标记指针，作用是删除结点
			Node* q;
			//循环遍历整个队列，直到标记指针 p 为 null
			while (p != NULL)
			{
				//比较常见的删除结点内存的写法
				q = p;
				//指向队列的下一个结点
				p = p->next;
				//销毁之
				delete q;
			}
		}
		//入队方法，从尾进入，节点不存在，需要自行创建结点的方法
		void push(int e)
		{
			Node* p = new Node;
			p->data = e;
			//本结点作为了队列的尾结点
			p->next = NULL;
			//然后连接结点到队尾
			rear->next = p;
			//最后尾指针指向新的末位结点
			rear = p;
		}
		//入队方法，尾进入，节点原来就存在的方法，不需要再新建结点和存储结点的内容
		void push(Node* p)
		{
			//设置此结点为尾结点
			p->next = NULL;
			//链接结点
			rear->next = p;
			//尾指针指向新的尾结点
			rear = p;
		}
		//求数据元素的最大位数的方法，也就是求出需要分配和收集的次数
		int lengthData()
		{
			int length = 0;//保存数据元素的 最大位数
			int n = 0;   //单个数据元素具有的位数
			int d;      //用来存储待比较的数据元素
			//指示指针
			Node* p = front->next;
			//遍历
			while (p != NULL)
			{
				//取出结点的数据，也就是代比较的数据元素
				d = p->data;
				//如果 d 为正数，很重要的一个技巧，必须是 d 大于 0 的判断
				while (d > 0)
				{
					//数据位数分离算法
					d /= 10;
					//单个数据元素的位数存储在此
					n++;
				}
				//沿着链队后移一个元素
				p = p->next;
				//找出数据元素的最大位数
				if (length < n)
				{
					length = n;
				}
				//重新循环往复，n 设置为0
				n = 0;
			}
			//返回最终位数
			return length;
		}
		//判断队列是否为空
		bool empty()
		{
			//队头指针和队尾指针重合，说明空
			if (front == rear)
			{
				return true;
			}
			//否则为不空
			return false;
		}
		//清除队列中的元素
		void clear()
		{
			//直接把头结点之后的链接断开
			front->next = NULL;
			//设置尾指针指向头结点即可，回到了构造函数初始化的情景
			rear = front;
		}
		//输出队列中的元素,传入引用参数比较好
		void print(Queue& que)
		{
			//第一个结点是头结点，next 才是第一个存储元素的结点
			Node* p = que.front->next;
			//直到尾结点为止
			int m = 0;
			while (p != NULL)
			{
				m++;
				cout <<p->data << " ";
				//遍历所有结点
				if (m % 10 == 0)cout << endl;
				p = p->next;
			}
		}
		//基数排序过程
		void RadixSort(Queue& que)
		{
			//声明一个指针数组，该指针数组中存放十个指针，这十个指针需要分别指向十个队列，这是模拟10个桶，因为是0-9的数字，取值范围为10
			Queue* arr[10];
			//初始化这十个队列
			for (int i = 0; i < 10; i++)
			{
				//初始化建立头结点
				arr[i] = new Queue;
			}
			//取得待排序数据元素中的最大位数
			int maxLen = que.lengthData();
			//因为是 LSD 方式，从后到前，开始比较关键字，然后分配再收集，故开始设置数据分离算法中的除数为 1
			int d = 1;
			//将初始队列中的元素分配到十个队列中,maxlen 代表了需要分配和收集的次数
			for (int i = 0; i < maxLen; i++)
			{
				Node* p = que.front->next;
				//辅助指针 q
				Node* q;
				//余数为k，则存储在arr[k]指向的链式队列（桶）中
				int k;
				//遍历原始序列
				while (p != NULL)
				{
					//重要的技巧，数据分离算法过程,最后勿忘模10，取余数，分离出需要的关键字位
					k = (p->data / d) % 10;
					q = p->next;
					//把本结点 p 加入对应的队列中
					arr[k]->push(p);
					//指针后移，指向下一个结点
					p = q;
				}
				//清空原始队列
				que.clear();
				//分配完毕，马上将十个队列中的数据收集到原始队列中
				for (int i = 0; i < 10; i++)
				{
					if (!arr[i]->empty())
					{
						//从首节点开始遍历，不是头结点开始
						Node* p = arr[i]->front->next;
						//辅助指针 q
						Node* q;
						while (p != NULL)
						{
							q = p->next;
							//收集到原始队列中，这就是为什么每次分配完毕，需要清除原始队列
							que.push(p);
							p = q;
						}
					}
				}
				//一趟的分配收集完毕，最后要清空十个队列
				for (int i = 0; i < 10; i++)
				{
					arr[i]->clear();
				}
				//进行下一趟的分配和收集
				d *= 10;
			}
			//输出队列中排好序的元素
			print(que);
		}
	};
	Queue oldque;
	int i;

	cout << "请输入数据长度" << endl;
	cin >> i;
	//顺序输入元素
	while (i != 0)
	{
		int x = fun();
		oldque.push(x);
		cout << x << " ";
		i--;
	}
	cout << endl;
	//基数排序
	oldque.RadixSort(oldque);

	return;
}
int main() {
		//test1();//顺序表查找
		//test2();//树表查找
		//test3();//拉链法查找
		//test3_();//线性探测法查找
		//test01();//顺序表排序
		test02();//树表排序
		//test03();//基数排序
}
