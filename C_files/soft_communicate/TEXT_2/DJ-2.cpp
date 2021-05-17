#include <stdio.h>
#include <math.h>

const int MAX_NUM = 200;
const int Max = 10000;
int cost[MAX_NUM][MAX_NUM];
int dist[MAX_NUM];
int node[MAX_NUM];

int line = 6;

int jslj(int s, int e)
{
    for (int i = 0; i < line; i++)
    {
        dist[i] = cost[s][i];
        node[i] = 0;
    }
    dist[s] = 0;
    while (true)
    {
        int v = -1;
        for (int u = 0; u < line; u++)
        {
            if (!node[u] && (v == -1 || dist[u] < dist[v]))
                v = u;
        }
        if (v == -1)
            break;

        node[v] = 1;
        for (int i = 0; i < line; i++)
        {
            if (dist[i] > dist[v] + cost[i][v])
            {
                dist[i] = dist[v] + cost[i][v];
            }
        }
    }
    return dist[e];
}
int main()
{
    int s, e;
    for (int i = 0; i < line; i++)
    {
        for (int j = 0; j < line; j++)
        {
            scanf("%d ", &cost[i][j]);
            if (!cost[i][j] || cost[i][j] == 0)
                cost[i][j] = Max;
        }
    }
    scanf("%d%d", &s, &e);
    if (s > line || s < 1 || e > line || e < 1)
        printf("输入错误!\n");
    int zdlj = jslj(s - 1, e - 1);

    if (zdlj != 0)
        printf("%d\n", zdlj);
    else
        printf("%d不连通！\n", Max);
}