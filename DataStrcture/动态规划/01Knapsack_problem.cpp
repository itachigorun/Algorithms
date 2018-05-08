/*
0-1 背包问题：给定 N 件物品和一个容量为 W 的背包，物品 i 的重量是 wi，其价值为 vi 。

问：一件物品只能选择一次，应该如何选择装入背包的物品，使得装入背包中的物品的总价值最大？
 
分析： i: 1->N  w: 1->W  
       F[i][w] = max{ F[i-1,w] , F[i-1,w-wi] + vi }
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
		for (int j = W; j >= 1; j--) //背包容量从 1~W  
		{
			if (goods[i].weight <= j)
				F[j] = max(F[j], F[j - goods[i].weight] + goods[i].value);
			cout << F[j] << ' ';
		}
		cout << endl;
	}

	return F[W];
}

int maxValue()
{
	for (int i = 1; i <= N; i++) //物品编号从 1~N  
	{
		for (int j = 1; j <= W; j++) //背包容量从 1~W  
		{
			if (goods[i].weight <= j)
				select[i][j] = max(select[i - 1][j], select[i - 1][j - goods[i].weight] + goods[i].value);
			else
				select[i][j] = select[i - 1][j];
		}
	}

	// 输出最大值列表
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= W; j++)
		{
			cout << select[i][j] << ' ';
		}
		cout << endl;
	}

	return select[N][W];
}

void printSelect()
{
	int remainSpace = W;
	//输出所选择的物品列表：  
	for (int i = N; i >= 1; i--)
	{
		if (remainSpace >= goods[i].weight)
		{
			if ((select[i][remainSpace] - select[i - 1][remainSpace - goods[i].weight] == goods[i].value))
			{
				cout << "item [" << goods[i].value << "," << goods[i].weight << "] is selected!" << endl;
				remainSpace = remainSpace - goods[i].weight;//如果第i个物品被选择，那么背包剩余容量将减去第i个物品的重量 ;  
			}
		}
	}
}

int main()
{
	//时间复杂度：O(N*W)
	cout << "The max value is: " << maxValue() << endl;
	//优化后时间复杂度：O(W)
	cout << "The time optimization value is: " << timeLessValue() << endl;
	// 打印所选择物品
	printSelect();
	return 0;
}

/*
maxValue()
时间复杂度：O(N*W)
空间复杂度：O(N*W)

价值数组v = { 8, 10, 6, 3, 7, 2 }
重量数组w = { 4, 6, 2, 2, 5, 1 }

背包容量W = 12时对应的select[i][j]数组。
0 |	1 	2 	3 	4 	5 	6 	7 	8 	9 	10 	11 	12
--|------------------------------------------------
1 |	0 	0 	0 	8 	8 	8 	8 	8 	8 	8 	8 	8
2 |	0 	0 	0 	8 	8 	10 	10 	10 	10 	18 	18 	18
3 |	0 	6 	6 	8 	8 	14 	14 	16 	16 	18 	18 	24
4 |	0 	6 	6 	9 	9 	14 	14 	17 	17 	19 	19 	24
5 |	0 	6 	6 	9 	9 	14 	14 	17 	17 	19 	21 	24
6 |	2 	6 	8 	9 	11 	14 	16 	17 	19 	19 	21 	24
*/

/*
timeLessValue()
时间复杂度：O(N*W)
空间复杂度：O(W)

价值数组v = { 8, 10, 6, 3, 7, 2 }
重量数组w = { 4, 6, 2, 2, 5, 1 }

背包容量W = 12时对应的F[i]数组
0 |	12  11 	10 	9 	8 	7 	6 	5 	4	3	2 	1
--|-----------------------------------------------
1 |	8   8   8   8   8   8   8   8   8   0   0   0
2 |	18  18  18  10  10  10  10  8   8   0   0   0
3 |	24  18  18  16  16  14  14  8   8   6   6   0
4 |	24  19  19  17  17  14  14  9   9   6   6   0
5 |	24  21  19  17  17  14  14  9   9   6   6   0
6 |	24  21  19  19  17  16  14  11  9   8   6   2
*/