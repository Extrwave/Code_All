#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define MAX_NUM 20
#define N 5
#define UNLINK 0

typedef int VRtype;
typedef int Infotype;
typedef char Ptype;

typedef struct Node
{
    VRtype weight;  //邻接表权值
    Infotype *next; //弧相关指针
} MeNode, T_weight[MAX_NUM][MAX_NUM];

typedef struct
{
    Ptype vexs[MAX_NUM]; //顶点向量
    T_weight arcs;       //邻接矩阵，储存边与边的关系
    int vexnum, arcnum;  //顶点数，弧数
    int mark1, mark2;    //判断是否被发送过
} MGraph;

void Creat(MGraph *G, int k);
void CreatM(MGraph *G);
int Iffull(MGraph *G);
void SwitchS(int j);
void SwitchT(MGraph *G, int j);
void IfSend(MGraph *G);

MGraph G0, G1, G2, G3, G4, G5, GG;

int main()
{
    int i, a;
    Creat(&G0, 0);
    Creat(&G1, 1);
    Creat(&G2, 2);
    Creat(&G3, 3);
    Creat(&G4, 4);
    Creat(&G5, 5);
    CreatM(&GG);

    while (Iffull(&GG)) /*判断转发表是否完整*/ //GG是否满
    {
        srand((unsigned)time(NULL));
        a = rand() % 6;
        SwitchS(a);
    }
}

void Creat(MGraph *G, int k) //创造表1 2 3 4 5 6
{
    int i, j; //顶点数和边数
    printf("请输入顶点数和边数：以逗号隔开 \n");
    scanf("%d,%d", G->vexnum, G->arcnum);
    fflush(stdin); //清除缓存区
    for (i = 0; i < G->vexnum; i++)
    {
        scanf("%c", G->vexs[i]);
    }

    //初始化节点图或者总图

    for (i = 0; i < G->vexnum; i++)
    {
        for (j = 0; j < G->vexnum; j++)
        {
            G->arcs[i][j].weight = UNLINK;
            G->arcs[i][j].next = NULL;
        }
    }
    printf("请输入节点权值：逗号隔开\n");
    for (j = 0; j < G->arcnum; j++)
    {
        scanf("%d", G->arcs[k - 1][j].weight);
        //因为是无向图，所以G->arcs[][].next=NULL无需改变
    }
    //当节点被写入新信息后，mark1  +1，当节点发送信息后，mark2  +1
    //当mark1==mark2时无需发送
    G->mark1 = 1;
    G->mark2 = 0;
}

void CreatM(MGraph *G) //创造表0 1 2 3 4 5
{
    int i, j; //顶点数和边数
    printf("请输入顶点数和边数：以逗号隔开 \n");
    scanf("%d,%d", G->vexnum, G->arcnum);
    fflush(stdin); //清除缓存区
    for (i = 0; i < G->vexnum; i++)
    {
        scanf("%c", G->vexs[i]);
    }

    //初始化节点图或者总图

    for (i = 0; i < G->vexnum; i++)
    {
        for (j = 0; j < G->vexnum; j++)
        {
            G->arcs[i][j].weight = UNLINK;
            G->arcs[i][j].next = NULL;
        }
    }
}

void InitMGraph(MGraph *G)
{
    int i, j;
    for (i = 0; i < G->vexnum; i++)
    {
        for (j = 0; j < G->vexnum; j++)
        {
            G->arcs[i][j].weight = UNLINK;
            G->arcs[i][j].next = NULL;
        }
    }
}

void Send(MGraph *G1, MGraph *G2)
{
    int i, j;
    int k = 0; //判断是否有效传递
    for (i = 0; i < G1->arcnum; i++)
    {
        for (j = 0; j < G1->arcnum; j++)
        {
            if (G1->arcs[i][j].weight >= G2->arcs[i][j].weight)
            {
                G1->arcs[i][j].weight = G2->arcs[i][j].weight;
                k++;
            }
        }
    }
    if (k != 0)
    {
        G1->mark1++;
        G2->mark1 = G2->mark2 = 0;
        //应老师要求，每进行一次洪泛，输出结果一次
        for (i = 0; i < G1->arcnum; i++)
        {
            for (j = 0; j < G1->arcnum; j++)
            {
                printf("%d ", G1->arcs[i][j]);
            }
            printf("\n");
        }
        //应老师要求，每进行一次洪泛，输出结果一次
    }
    printf("\n\n\n");
}

void IfSend(MGraph *G)
{
    char str[N];
    int i, j;
    if (G->mark1 != G->mark2)
    {
        for (i = 0; i < G->arcnum; i++)
        {
            for (j = 0; j < G->arcnum; j++)
            {
                if (G->arcs[i][j].weight > UNLINK)
                {
                    SwitchT(G, j); //只要相连接就传递全部元素，如已存在，则不会接受
                }
            }
        }
    }
}

void SwitchT(MGraph *G, int j)
{
    switch (j)
    {
    case 0:
        Send(&G0, G);
        break;
    case 1:
        Send(&G1, G);
        break;
    case 2:
        Send(&G2, G);
        break;
    case 3:
        Send(&G3, G);
        break;
    case 4:
        Send(&G4, G);
        break;
    case 5:
        Send(&G5, G);
        break;

    default:
        break;
    }
}

void SwitchS(int j)
{
    switch (j)
    {
    case 0:
        IfSend(&G0);
        break;
    case 1:
        IfSend(&G1);
        break;
    case 2:
        IfSend(&G2);
        break;
    case 3:
        IfSend(&G3);
        break;
    case 4:
        IfSend(&G4);
        break;
    case 5:
        IfSend(&G5);
        break;
    default:
        break;
    }
}

int Iffull(MGraph *G)
{
    int i, j;
    int a;
    for (i = 0; i < G->arcnum; i++)
    {
        a = 0;
        for (j = 0; j < G->arcnum; j++)
        {
            if (G->arcs[i][j].weight > UNLINK)
            {
                a = 1;
            }
            if (a == 0)
                return 0; //未满
        }
        return 1; //已满
    }
}

void Dijkstra(int v)
{
}