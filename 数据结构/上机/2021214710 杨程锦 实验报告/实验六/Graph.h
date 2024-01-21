#include<iostream>
using namespace std;
typedef int elementtype;
int E;
#define max 100
int inf = 99999;
bool visited[max];
typedef struct {
	int d;//到达某点的最短路径距离 
	int pre;//该最短路径是经过哪个点传过来的，源点或其他某个点 
}path;
class graph
{
public:
	elementtype node[max];     //顶点表 
	int distance[max][max];  //邻接矩阵
	int n;       //当前顶点数
	int e = 0;//边数
	int vis[max];//表示最短路径是否被找到
	path to[max];//记录当前某个点的最短路径及从那个点传过来
	graph()
	{
		int i, j;
		for (i = 1; i <= max; i++)
			node[i] = -1;
	};
	void visite(elementtype v) { cout << node[v] << "  "; }
	//无向图
	void create()
	{
		int i, j, k;
		cout << "请输入顶点数" << endl;
		cin >> n;
		for (i = 1; i <= n; i++) {
			vis[i] = 0;
		}
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++) {
				distance[i][j] = inf;
			}
			to[i].d = inf;
		}
		cout << "请输入各顶点的值" << endl;
		for (k = 1; k <= n; k++)
			cin >> node[k];
		cout << "请输入边：i j，i为-1时结束" << endl;
		cin >> i >> j;
		while (i != -1)
		{
			distance[i][j] = distance[j][i] = 1;
			cin >> i >> j;
		}
	};
	////有向图(网络)
	//void create()
	//{
	//	int i, j, k;
	//	cout << "请输入顶点数" << endl;
	//	cin >> n;
	//	for (i = 1; i <= n; i++) {
	//		vis[i] = 0;
	//	}
	//	for (i = 1; i <= n; i++) {
	//		for (j = 1; j <= n; j++) {
	//			distance[i][j] = inf;
	//		}
	//		to[i].d = inf;
	//	}
	//	cout << "请输入各顶点的值" << endl;
	//	for (k = 1; k <= n; k++)
	//		cin >> node[k];
	//	cout << "请输入边和边的值：i j k，i为-1时结束" << endl;
	//	cin >> i >> j;
	//	while (i != -1)
	//	{
	//		cin >> distance[i][j];
	//		cin >> i >> j;
	//	}
	//};
	int firstadj(elementtype v)
	{
		if (v != -1)
		{
			for (int col = 1; col <= n; col++)
				if (distance[v][col] != inf && distance[v][col] != 0) return col;
		}
		return -1;
	};
	int nextadj(elementtype v, elementtype m)
	{
		if (v != -1 && m != -1)
		{
			for (int col = m + 1; col <= n; col++)
				if (distance[v][col] != inf && distance[v][col] != 0) return col;
		}
		return  -1;
	};
	void  dfs(int v)
	{
		int w;
		visited[v] = true;
		w = firstadj(v);
		while (w != -1)
		{
			e++;
			if (!visited[w])
				dfs(w);
			w = nextadj(v, w);
		}
	}
	void travel() {
		for (int i = 1; i <= n; i++) {
			visited[i] = false;
		}
		for (int i = 1; i <= n; i++) {
			if (visited[i] == false) {
				dfs(i);
			}
		}
	}
	void Enum() {
		travel();
		e = e / 2;
	}
	//判断是否是树
	void istree() {
		int notrue = 0;
		for (int i = 1; i <= n; i++) {
			visited[i] = false;
		}
		e = 0;
		Enum();
		for (int i = 1; i <= n; i++) {
			if (!visited[i]) {
				notrue++;
			}
		}
		if (notrue != 0) {
			cout << "该无向图不连通，不是一颗树" << endl;
		}
		else if (notrue == 0 && e != n - 1) {
			cout << "该无向图图有回路，不是一颗树" << endl;
		}
		else {
			cout << "该无向图是一棵树" << endl;
		}
	}
	/*两点间的最短路径*/
	void path(int x, int y) {
		int i, min, j, k;
		for (i = 1; i <= n; i++) {
			to[i].d = distance[x][i]; //初始化源点到i点边权值，之后过程中会发生变化 
			if (distance[x][i] != inf && distance[x][i] != 0) {
				to[i].pre = x;
			}
		}
		vis[x] = 1;
		for (i = 1; i <= n; i++) {//共循环n-1次，每循环一次，确定一条最短路，再次循环时这条路就不用考虑了，去寻找下一条最短路 
			min = inf;
			for (j = 1; j <= n; j++) {//寻找下一条当前最短路 
				if (to[j].d < min && vis[j] == 0) {
					min = to[j].d;
					k = j;
				}
			}
			vis[k] = 1;//找到了，到k点的路是当前最短路，标记它，根据它寻找下一条最短路 
			for (j = 1; j <= n; j++) {
				if (to[j].d > to[k].d + distance[k][j] && vis[j] == 0) {//经过此k点到达j点的路径是否小于其他到达j点的路径 
					to[j].d = to[k].d + distance[k][j];
					to[j].pre = k;//改变j点是谁传来的，现在到j点的最短路径是经过k点的，由j点传来 
				}
			}
		}
		cout << "具体路径为：";
		cout << y;
		j = y;
		while (j != x) {
			j = to[j].pre;
			cout << "<-" << j;
		}
		cout << endl;
	}
	/*从原点到其他点的最短路径*/
	//void path() {
	//	int i, min, j, k;
	//	for (i = 2; i <= n; i++) {
	//		to[i].d = distance[1][i]; //初始化源点到i点边权值，之后过程中会发生变化 
	//		if (distance[1][i] != inf) {
	//			to[i].pre = 1;
	//		}
	//	}
	//	vis[1] = 1;
	//	for (i = 2; i <= n; i++) {//共循环n-1次，每循环一次，确定一条最短路，再次循环时这条路就不用考虑了，去寻找下一条最短路 
	//		min = inf;
	//		for (j = 2; j <= n; j++) {//寻找下一条当前最短路 
	//			if (to[j].d < min && vis[j] == 0) {
	//				min = to[j].d;
	//				k = j;
	//			}
	//		}
	//		vis[k] = 1;//找到了，到k点的路是当前最短路，标记它，根据它寻找下一条最短路 
	//		for (j = 2; j <= n; j++) {
	//			if (to[j].d > to[k].d + distance[k][j] && vis[j] == 0) {//经过此k点到达j点的路径是否小于其他到达j点的路径 
	//				to[j].d = to[k].d + distance[k][j];
	//				to[j].pre = k;//改变j点是谁传来的，现在到j点的最短路径是经过k点的，由j点传来 
	//			}
	//		}
	//	}
	//	for (i = 2; i <= n; i++) {//输出到达个点的最短路径 
	//		cout << "原点到该点的最短路径距离为：";
	//		cout << to[i].d << endl;
	//		cout << "具体路径为：";
	//		cout << i;
	//		j = i;
	//		while (j != 1) {
	//			j = to[j].pre;
	//			cout << "<-" << j;
	//		}
	//		cout << endl;
	//	}
	//}
};