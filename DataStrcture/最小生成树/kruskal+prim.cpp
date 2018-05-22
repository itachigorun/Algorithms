#include <iostream>
#include <queue>
using namespace std;

// 重定义边节点，便于操作
typedef struct ArcNode *Position;

/* 边节点
* 储存元素:
* AdjName:该有向边的尾结点
* Weight:该有向边的权重
* Next:该有向边的头结点的其他有向边
*/
struct ArcNode {
	int AdjName;
	int Weight;
	Position Next;
};

/* 边节点:（用于KrusKal算法）
* 储存元素:
* Vex1:该无向边的节点
* Vex2:该无向边的另一个节点
* Weight:该无向边的权重
*/
struct Edge {
	int Vex1;
	int Vex2;
	int Weight;

	// 重载“<”符号，用于KrusKal算法
	friend bool operator < (const Edge &a, const Edge &b) {
		return a.Weight > b.Weight;
	}
};

/* 顶点节点
* 储存元素:
* Name:该顶点的名称
* FirstArc:以该顶点为头结点的第一个有向边
*/
struct VexNode {
	int Name;
	Position FirstArc;
};

/* 表节点
* 储存元素:
* Known:该节点的状态
* Dist:该节点距指定节点的距离
* Path:指向该节点的节点
*/
struct TableNode {
	bool Known;
	int Dist;
	int Path;
};

/* ALGraph类
* 接口:
* Display:展示功能，展示距离表中的信息
* MakeEmpty:重置功能，重置该图中的所有边
* Creat:构建功能，在图中构建边
* KrusKal:KrusKal算法，在图中寻找最小生成树
* Prim:Prim算法，在图中寻找最小生成树
*/
class ALGraph
{
public:
	// 构造函数
	ALGraph(int = 10);
	// 析构函数
	~ALGraph();

	// 基础函数
	void Display();
	void MakeEmpty();
	void Creat();

	// 最小生成树函数
	void KrusKal();
	void Prim();

private:
	// 辅助函数
	void InitTable();

	// 数据成员
	int VexNum; // 储存顶点数
	int ArcNum; // 储存边数
	VexNode *AdjList; // 储存邻接表
	TableNode *Table; // 储存距离表
	priority_queue <Edge> H; // 储存优先队列（用于KrusKal算法）
};


/* Disjoint_Set类（不相交集）
* 接口:
* Find:查找功能:查找对应元素所对应的集合
* SetUnion:联合功能:将对应两个元素所在的集合链接
*/
class Disjoint_Set
{
public:
	// 构造函数
	Disjoint_Set(int = 10);
	// 析构函数
	~Disjoint_Set();

	// 接口函数
	int Find(int);
	void SetUnion(int, int);

private:
	int NumSets; // 储存总集合中元素的个数
	int *DisjSet; // 储存等价类森林
};


/* 构造函数:初始化对象
* 返回值:无
* 参数:vnum:图中的顶点数
*/
ALGraph::ALGraph(int vnum): VexNum(vnum), ArcNum(0) 
{
	// 申请邻接表储存空间
	AdjList = new VexNode[VexNum];
	// 申请距离表储存空间
	Table = new TableNode[VexNum];

	// 判断是否申请成功
	if (AdjList == NULL || Table == NULL) {
		cout << "邻接表申请失败!" << endl;
		return;
	}

	// 初始化邻接表以及距离表
	for (int i = 0; i < VexNum ; i++) {
		AdjList[i].FirstArc = NULL;
		AdjList[i].Name = i;
		Table[i].Dist = INT_MAX;
		Table[i].Known = false;
		Table[i].Path = 0;
	}
}

/* 析构函数:对象消亡时回收储存空间
* 返回值:无
* 参数:无
*/
ALGraph::~ALGraph()
{
	// 重置所有的边
	MakeEmpty();

	// 删除邻接表
	delete AdjList;
	AdjList = NULL;

	// 删除距离表
	delete Table;
	Table = NULL;
}

/* 重置函数:重置所有的边
* 返回值:无
* 参数:无
*/
void ALGraph::MakeEmpty() {
	// 暂时储存中间节点
	Position P;

	// 遍历邻接表
	for (int i = 0; i < VexNum ; i++) {
		P = AdjList[i].FirstArc;

		// 遍历所有链接的边
		while (P != NULL) {
			AdjList[i].FirstArc = P->Next;
			delete P;
			P = AdjList[i].FirstArc;
		}
	}

	// 边数初始化
	ArcNum = 0;
}

/* 构建函数:在图中构建有向边
* 返回值:无
* 参数:无
*/
void ALGraph::Creat()
{
	int tmp; // 储存边数
	tmp = 10;
	ArcNum = tmp;

	struct node {
		int v;
		int w;
		int weight;
	};
	node node[10] = {
	{ 0,1,1 },
	{ 0,2,2 },
	{ 1,3,4 },
	{ 1,4,4 },
	{ 2,3,5 },
	{ 2,4,9 },
	{ 2,6,6 },
	{ 3,5,7 },
	{ 4,5,3 },
	{ 4,6,1 },
	};
	// 创建所有的无向边
	for (int i = 0; i < tmp; i++) {
		// v:边的顶点
		// w:边的另一个顶点
		// weight:边的权重
		int v, w, weight;
		v = node[i].v;
		w = node[i].w;
		weight = node[i].weight;
		// 构建一个单向边
		Position P1 = new ArcNode();
		P1->AdjName = w;
		P1->Weight = weight;
		P1->Next = AdjList[v].FirstArc;
		AdjList[v].FirstArc = P1;

		// 构建另一个单向边
		Position P2 = new ArcNode();
		P2->AdjName = v;
		P2->Weight = weight;
		P2->Next = AdjList[w].FirstArc;
		AdjList[w].FirstArc = P2;

		// 构建一个无向边（用于KrusKal算法）
		Edge E;
		E.Vex1 = v;
		E.Vex2 = w;
		E.Weight = weight;

		// 将该无向边压入优先队列
		H.push(E);
	}
}

/* 初始化函数:初始化距离表
* 返回值:无
* 参数:无
*/
void ALGraph::InitTable() {
	// 遍历所有的距离表
	for (int i = 0; i < VexNum ; i++) {
		// 初始化参数
		Table[i].Dist = INT_MAX;
		Table[i].Known = false;
		Table[i].Path = 0;
	}
}

/* 展示函数:展示距离表中的信息
* 返回值:无
* 参数:无
*/
void ALGraph::Display() {
	// 遍历所有的距离表
	cout << "Prim:" << endl;
	for (int i = 0; i < VexNum ; i++) {
		cout << Table[i].Path << "--" << i<<": " << Table[i].Dist << endl;
	}
}

/* KrusKal算法:寻找最小生成树
* 返回值:无
* 参数:无
*/
void ALGraph::KrusKal() {
	// S:不相交集，用于判断两个顶点是否链接
	// v:一条无向边的顶点
	// w:一条无向边的另一个顶点
	// EdgeAccepted:已经生成的边数
	// V:顶点v所在的集合
	// W:顶点w所在的集合
	// E:无向边节点
	Disjoint_Set S(VexNum);
	int v, w, EdgeAccepted = 0;
	int V, W;
	Edge E;

	// 初始化距离表
	InitTable();

	// 一直寻找直到生成的边数为:VexNum - 1
	while (EdgeAccepted < VexNum - 1) {
		// 获取最小的无向边
		E = H.top();
		H.pop();

		// 获取无向边的顶点
		v = E.Vex1;
		w = E.Vex2;

		// 获取顶点所在的集合
		V = S.Find(v);
		W = S.Find(w);

		// 判断两个顶点是否在同一个集合
		if (V != W) {
			// 生成边数增加
			EdgeAccepted++;
			// 链接量顶点
			S.SetUnion(V, W);
			// 输出信息
			cout << E.Vex1 << "--" << E.Vex2 << ": " << E.Weight << endl;;
		}
	}
}

/* Prim算法:寻找最小生成树
* 返回值:无
* 参数:无
*/
void ALGraph::Prim() {
	// v:一条无向边的顶点
	// w:一条无向边的另一个顶点
	// counter:计数器，统计边数
	// P:储存边节点
	int v, w;
	Position P;

	// 初始化距离表，并选取起始节点
	InitTable();
	v = 0;
	Table[v].Dist = 0;
	Table[v].Known = true;

	// 一直寻找，直到边数为:VexNum - 1
	for(int counter=0;counter<VexNum;)
	{
		// 获取边节点
		P = AdjList[v].FirstArc;

		// 遍历完该节点所有无向边
		while (P != NULL) {
			w = P->AdjName;
			// 判断是否需要更新距离表信息
			if (Table[w].Known == false && Table[w].Dist > P->Weight) {
				Table[w].Dist = P->Weight;
				Table[w].Path = v;
			}
			// 指向下一个无向边
			P = P->Next;
		}

		// 寻找不构成圈的权重最小的无向边
		int Min = INT_MAX;
		for (int i = 0; i < VexNum ; i++) {
			if (Table[i].Known == false && Min > Table[i].Dist) {
				v = i;
				Min = Table[i].Dist;
			}
		}

		// 链接该无向边，计数器增加
		Table[v].Known = true;
		counter++;
	}
}

/* 构造函数:初始化对象
* 返回值:无
* 参数:nums:整个集合中元素的个数
*/
Disjoint_Set::Disjoint_Set(int nums)
	: NumSets(nums) {
	DisjSet = new int[NumSets + 1]; // 申请不相交集森林的存储空间

	if (DisjSet == NULL)
		cout << "不相交集申请失败!" << endl;

	// 初始化森林中的每棵树
	else
		for (int i = NumSets; i > 0; i--)
			DisjSet[i] = -1;
}

/* 析构函数:对象消亡时回收存储空间
* 返回值:无
* 参数:无
*/
Disjoint_Set::~Disjoint_Set()
{
	delete DisjSet;
	DisjSet = NULL;
}

/* 联合函数:将两个集合链接
* 返回值 : 无
* 参数 : Root1 : 想要合并的一个集合；Root2 : 想要合并的另一个集合
*/
void  Disjoint_Set::SetUnion(int Root1, int Root2) {
	// 找到对应元素所在集合的根部
	Root1 = Find(Root1);
	Root2 = Find(Root2);

	int tmp = DisjSet[Root1] + DisjSet[Root2];
	// case1:当Root2集合高度大于Root1时
	if (DisjSet[Root2] < DisjSet[Root2])
	{
		DisjSet[Root1] = Root2; // 将Root1合并到Root2中
		DisjSet[Root2] = tmp;
	}
	else {
		DisjSet[Root2] = Root1;
		DisjSet[Root1] = tmp;
	}
}

/* 查找函数:查找对应元素所在的集合
* 返回值:SetTpye:对应元素所在集合的根
* 参数:X:想要查找的元素
*/
int Disjoint_Set::Find(int X) {
	// 判断是否是根部
	if (DisjSet[X] < 0)
		return X;

	// 继续寻找根部
	// 同时进行路径压缩:
	// 将中途检索到的每一个节点的父节点都变为根；
	// 注意:此处不用重新计算高度！虽然高度会改变，但是我们
	// 使用估计高度（或称为秩--rank）；
	else
		return DisjSet[X] = Find(DisjSet[X]);
}

int main()
{
	ALGraph A(7);
	A.Creat();
	A.KrusKal();

	A.Prim();
	A.Display();

	return 0;
}
