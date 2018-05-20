//文件名MGraph.h 邻接表实现，对于无向图入度和出度相同，对于有向图方便查出度，不方便查入度																
#ifndef MGRAPH_H
#define MGRAPH_H
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<deque>
#include<stack>
using namespace std;

struct ArcNode {
	int headvex;         //弧起点
	int tailvex;         //弧终点
	ArcNode * headlink;  //入边表指针域，指向终点相同的下一条边
	ArcNode * taillink;  //出边表指针域，指向起点相同的下一条边
}; //边信息

template<typename T>
struct VerNode {
	T data;
	ArcNode * firstin;   //指向顶点的入边信息，即该顶点是弧终点
	ArcNode * firstout;  //指向顶点的出边信息，即该顶点是弧起点
}; //顶点数组

template<typename T>
class MGraph
{
private:
	vector<VerNode<T>> vertex;
	stack<T> result;
public:
	MGraph(vector<T> ver_in, multimap<int, int> arc_input);//十字链表表存储，建立具有n个顶点e条边的图
	~MGraph();
	bool DFSTraverse(int v);
	bool BFSTraverse(int v);
	bool TopologySort();
	void TopologySortbyDFS();
	int GetNodeNum();
};
template<typename T>
int MGraph<T>::GetNodeNum()
{
	return vertex.size();
}

//十字链表构建图，方便查询入度和出度
template<typename T>
MGraph<T>::MGraph(vector<T> ver_input, multimap<int, int> arc_input)
{
	VerNode<T> ver;
	ver.firstin = nullptr;
	ver.firstout = nullptr;
	for_each(ver_input.begin(), ver_input.end(), [&](T temp)
	{
		ver.data = temp;
		vertex.emplace_back(ver);
	});  //存储图的顶点信息

	for_each(arc_input.rbegin(), arc_input.rend(), [&](auto a)
	{
		auto s = new ArcNode;
		s->headvex = a.first;
		s->tailvex = a.second;
		s->headlink = nullptr;
		s->taillink = nullptr;
		s->taillink = vertex[a.first].firstout;
		vertex[a.first].firstout = s;
	});   //存储有向图的出边信息
	for_each(arc_input.rbegin(), arc_input.rend(), [&](auto a)
	{
		ArcNode * temp = vertex[a.first].firstout;
		while (temp->tailvex != a.second)
			temp = temp->taillink;
		temp->headlink = vertex[a.second].firstin;
		vertex[a.second].firstin = temp;
	});   //存储有向图的入边信息
}

/*
非递归实现
（1）栈S初始化；visited[n]=0；
（2）访问顶点v；visited[v]=1；顶点v入栈S
（3）while(栈S非空)
x=栈S的顶元素(不出栈)；
if(存在并找到未被访问的x的邻接点w)
访问w；visited[w]=1；
w进栈;
else
x出栈；
*/
template<typename T>
bool MGraph<T>::DFSTraverse(int v)
{
	if (v > vertex.size() - 1)
		return false;
	vector<int> visited(GetNodeNum(), 0);
	visited[v] = 1;
	cout << v << " ";
	deque<int> deq;
	deq.push_back(v);
	while (!deq.empty()) {
		int x = deq.back();
		ArcNode * node = vertex[x].firstout;
		while (node && visited[node->tailvex] == 1)
		{
			node = node->taillink;
		}
		if (node && visited[node->tailvex] == 0) {
			visited[node->tailvex] = 1;
			deq.push_back(node->tailvex);
			cout << node->tailvex << " ";
		}
		else
		{
			//拓扑排序
			//由于加入顶点到集合中的时机是在dfs方法即将退出之时，
			//而dfs方法本身是个递归方法，
			//仅仅要当前顶点还存在边指向其他不论什么顶点，
			//它就会递归调用dfs方法，而不会退出。
			//因此，退出dfs方法，意味着当前顶点没有指向其他顶点的边了
			//，即当前顶点是一条路径上的最后一个顶点。
			//换句话说其实就是此时该顶点出度为0了
			result.push(deq.back());
			deq.pop_back();
		}
	}
	cout << endl;
	return true;
}

/*
（1）初始化队列Q；visited[n]=0；
（2）访问顶点v；visited[v]=1；顶点v入队列Q；
（3） while（队列Q非空）
v=队列Q的对头元素出队；
w=顶点v的第一个邻接点；
while（w存在）
如果w未访问，则访问顶点w；
visited[w]=1；
顶点w入队列Q；
w=顶点v的下一个邻接点。
*/
template<typename T>
bool MGraph<T>::BFSTraverse(int v)
{
	if (v > vertex.size() - 1)
		return false;
	vector<int> visited(GetNodeNum(), 0);
	visited[v] = 1;
	cout << v << " ";
	deque<int> deq;
	deq.push_back(v);

	int w, x;
	ArcNode * node;
	while (!deq.empty())
	{
		x = deq.front();
		node = vertex[x].firstout;
		deq.pop_front();
		if (node != nullptr)
		{
			w = node->tailvex;
			while (1)
			{
				if (visited[w] == 0)
				{
					visited[w] = 1;
					cout << w << " ";
					deq.push_back(w);
				}
				if (node->taillink)
				{
					node = node->taillink;
					w = node->tailvex;
				}
				else
					break;
			}
		}
	}
	cout << endl;
	return true;
}

template<typename T>
bool MGraph<T>::TopologySort()
{
	vector<int> indegree(vertex.size());
	stack<int> s;
	for_each(vertex.begin(), vertex.end(), [&](auto temp)
	{
		ArcNode *p = temp.firstin;
		while (p)
		{
			indegree[temp.data]++;
			p = p->headlink;
		}
	});

	//把入度为0的顶点入栈
	for_each (indegree.begin(), indegree.end(), [&](auto temp)
	{
		if (!temp) {
			s.push(temp);
		}
	});

	//count用于计算输出的顶点个数
	int count = 0;
	ArcNode * temp;
	int i = 0;
	while (!s.empty()) {//如果栈为空，则结束循环
		i = s.top();
		s.pop();//保存栈顶元素，并且栈顶元素出栈
		cout << this->vertex[i].data << " ";//输出拓扑序列
		temp = this->vertex[i].firstout;
		while (temp) {
			if (!(--indegree[temp->tailvex])) {//如果入度减少到为0，则入栈
				s.push(temp->tailvex);
			}
			temp = temp->taillink;
		}
		++count;
	}
	if (count == vertex.size()) {
		cout << endl;
		return true;
	}
	cout << "此图有环，无拓扑序列" << endl;
	return false;//说明这个图有环
}

template<typename T>
void MGraph<T>::TopologySortbyDFS()
{
	//输出拓扑序列，因为我们每次都是找到了出度为0的顶点加入栈中，
	//所以输出时其实就要逆序输出，这样就是每次都是输出入度为0的顶点
	while (result.size())
	{
		cout << result.top() << " ";
		result.pop();
	}
	cout << endl;
}

template<typename T>
MGraph<T>::~MGraph()
{
	ArcNode * temp = nullptr;
	for_each(vertex.begin(), vertex.end(), [&](auto p)
	{
		temp = p.firstout;
		while (temp) {
			p.firstout = temp->taillink;
			delete(temp);
			temp = p.firstout;
		}
		p.firstout = nullptr;
	});
}

#endif