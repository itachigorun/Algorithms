/*
0-1 背包问题：给定 N 件物品和一个容量为 W 的背包，物品 i 的重量是 wi，其价值为 vi 。

问：一件物品可以选择多次，应该如何选择装入背包的物品，使得装入背包中的物品的总价值最大？
 
分析：与01背包相比，就是for (int j = 1; j <= W; j++) 改为 1~W ，01背包是W~1
*/

#include <iostream>  
#include <algorithm>

using namespace std;

//物品数据结构  
typedef struct commodity
{
	int value;  //价值  
	int weight; //重量  
}commodity;

const int N = 6;  //物品个数  
const int W = 12; //背包的容量  

				  //初始物品信息  
commodity goods[N + 1] = { { 0,0 },{ 8,4 },{ 10,6 },{ 6,2 } ,{ 3,2 },{ 7,5 },{ 2,1 } };
int select[N + 1][W + 1] = { 0 };

// 如果要求恰好装满背包，则初始化时F[0]为0其余负无穷(即让结果算出负数即可)，若不要求装满背包，只要求价值最大化，则全部赋0	
int F[W+1] = { 0 }; 
//int F[W+1] = { 0,-10000,-10000,-10000,-10000,-10000,-10000,-10000,-10000,-10000,-10000,-10000 };

int timeLessValue()
{

	for (int i = 1; i <= N; i++) //物品编号从 1~N  
	{
		for (int j = 1; j <= W; j++) //背包容量从 1~W  
		{
			if (goods[i].weight <= j)
				F[j] = max(F[j], F[j - goods[i].weight] + goods[i].value);
			cout << F[j] << ' ';
		}
		cout << endl;
	}

	return F[W];
}


int main()
{
	//优化后时间复杂度：O(NW)
	cout << "The time optimization value is: " << timeLessValue() << endl;
	return 0;
}


/*
timeLessValue()
时间复杂度：O(N*W)
空间复杂度：O(W)

价值数组v = { 8, 10, 6, 3, 7, 2 }
重量数组w = { 4, 6, 2, 2, 5, 1 }

背包容量W = 12时对应的F[i]数组
0 |	1  2  3  4  5  6  7  8  9  10  11  12
--|-----------------------------------------------
0 | 0  0  0  0  8  8  8  8  8  16  16  16
1 | 0  0  0  0  10 10 10 10 10 20  20  20
2 | 0  0  0  0  10 10 10 10 10 20  20  20
3 | 0  0  0  0  10 10 10 10 10 20  20  20
4 | 0  7  7  14 14 21 21 28 28 35  35  42
5 | 0  7  7  14 14 21 21 28 28 35  35  42
*/