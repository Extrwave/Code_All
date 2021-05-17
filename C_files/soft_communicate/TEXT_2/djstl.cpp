#include <cstdio>
using namespace std;
#define max 10000
#define MAX_NUM 6
#define N 5
#define UNLINK -1
#define inf 20000
int n = 6;
int e = 6;
int cost[20][20];
int dist[20]; //这个数组用来记录当前从v到各个顶点的最短路径长度，算法的核心思想就是通过不断修改这个表实现
int pre[20];  //这个数组用来存放最短路径
int S[20];	  //这个数组用来标记结点的访问与否，如果该结点被访问，则为1，如果该结点还没有访问，则为0；

void Dijkstra(int v)
{
	for (int i = 0; i < n; i++)
	{
		dist[i] = cost[v][i]; //初始化
		S[i] = 0;			  //标志位初始为0
		if (dist[i] < max)
			pre[i] = v; //若存在边，则前趋为原点
		else
			pre[i] = -1; //否则，前趋为-1,不可达
	}
	S[0] = 1; //原点标志为1
	for (int i = 0; i < n - 1; i++)
	{				   //循环n-1次
		int u;		   //u为待选顶点
		int min = inf; //令初始最小值>max，使距离值为max的顶点也能加到S中
		for (int j = 0; j < n; j++)
		{
			if ((!S[j]) && dist[j] < min)
			{ //寻找距离S最小的顶点u
				min = dist[j];
				u = j;
			}
		}
		S[u] = 1; //将其标志设置为1
		for (int k = 0; k < n; k++)
		{ //调整未加入S的点的的距离值
			if ((!S[k]) && dist[k] > dist[u] + cost[u][k])
			{
				dist[k] = dist[u] + cost[u][k];
				pre[k] = u; //若通过u减小了k的距离，则修改k的前趋为u
			}
		}
	}
	printf("\nThe result:\n"); //输出结果
	for (int i = 0; i < n; i++)
	{
		printf("<%d,%d>:  ", v + 1, i + 1);
		int p = pre[i];
		if (p != -1)
		{							 //若可达输出最短路径
			printf("%d  ", dist[i]); //输出最短距离
			printf("%d", i + 1);	 //根据前趋逆向输出最短路径
			while (p != v)
			{
				printf("<--%d", p + 1);
				p = pre[p];
			}
			printf("<--%d", v + 1);
		}
		else
		{ //若不可达则输出“inf”
			printf("inf");
		}
		printf("\n");
	}
}