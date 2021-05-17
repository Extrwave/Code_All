#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"
#include "windows.h"

#define MAX_NUM 30
#define N 5
#define UNLINK 0

typedef int VRtype;
typedef int Infotype;
typedef char Ptype;
typedef char Mtype;

typedef struct Node
{
    VRtype weight;  //邻接表权值
    Infotype *next; //弧相关指针

    int function;
    int length;
    Mtype message;
} MeNode, T_weight[MAX_NUM][MAX_NUM];

typedef struct
{
    Ptype vexs[MAX_NUM];    //顶点向量//字符串
    T_weight arcs[MAX_NUM]; //邻接矩阵，储存边与边的关系
    int vexnum, arcnum;     //顶点数，弧数
    int receiver[MAX_NUM];  //接收者
} MGraph;

void Creat(MGraph *G);
void CreatM(MGraph *G);
int Iffull(MGraph *G);
void SwitchS(int j);
void SwitchT(MGraph *G, int j);
void Send(MGraph *G, int vnum);
void IfSend(MGraph *G);

MGraph MG;
MGraph GG;

int main()
{
    FILE *ap;
    ap = fopen("F:/VS_code/C_filse/soft_communicate/TEXT_2/point.txt", "r");
    char lines[MAX_NUM];
    int i, a;
    int line = 0;
    while (fgets(lines, MAX_NUM, ap))
    {
        line++;
    }
    CreatM(&GG);
    //初始化节点总图
    for (i = 0; i < line; i++)
    {
        Creat(&MG, i);
    }
    //创建完成
    printf("信息读取完成！");

    while (Iffull(&GG)) /*判断转发表是否完整*/ //GG是否满
    {
        srand((unsigned)time(NULL));
        a = rand() % 6;
        SwitchS(a);
    }
}

void Creat(MGraph *G, int k) //创造表1 2 3 4 5 6
{
    int i, j, n; //顶点数和边数
    int *ptr;
    char empty[MAX_NUM];
    printf("请输入顶点数和边数：以逗号隔开 \n");
    scanf("%d,%d", G->vexnum, G->arcnum);
    fflush(stdin); //清除缓存区
    for (i = 0; i < G->vexnum; i++)
    {
        G->vexs[i] = i;
    }

    //初始化节点图或者总图
    for (n = 0; n < G->vexnum; n++)
    {
        for (i = 0; i < G->vexnum; i++)
        {
            for (j = 0; j < G->vexnum; j++)
            {
                G->arcs[n][i][j].weight = UNLINK;
                G->arcs[n][i][j].next = NULL;
            }
        }
    }
    printf("正在读取节点信息\n");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");

    //文件读取输入吧
    FILE *fp;
    fp = fopen("F:/VS_code/C_filse/soft_communicate/TEXT_2/point.txt", "r");
    for (i = 0; i < k; i++)
        fgets(&empty[i], MAX_NUM, fp);
    ptr = G->receiver;
    for (i = 0; i < G->arcnum; i++)
    {
        for (j = 0; j < G->arcnum; j++)
        {
            fscanf(fp, "%d ", G->arcs[k][i][j].weight);
            /*wenjian*/
            //因为是无向图，所以G->arcs[][][].next=NULL无需改变
            if (G->arcs[k][i][j].weight > UNLINK)
            {
                *ptr = j;
                ptr++;
            }
        }
    }
}

void CreatM(MGraph *G, int vnum) //创造表1 2 3 4 5 6
{
    int i, j, n; //顶点数和边数
    //初始化节点图或者总图
    for (n = 0; n < vnum; n++)
    {
        for (i = 0; i < vnum; i++)
        {
            for (j = 0; j < vnum; j++)
            {
                G->arcs[n][i][j].weight = UNLINK;
                G->arcs[n][i][j].next = NULL;
            }
        }
    }
}

void InitMGraph(MGraph *G)
{
    int i, j, n;
    for (n = 0; n < MAX_NUM; n++)
    {
        for (i = 0; i < G->vexnum; i++)
        {
            for (j = 0; j < G->vexnum; j++)
            {
                G->arcs[n][i][j].weight = UNLINK;
                G->arcs[n][i][j].next = NULL;
            }
        }
    }
}

void Send(MGraph *G, int vnum)
{
    int i, j, n;
    int *Gtr;
    int *GGtr;
    Gtr = G->receiver;
    GGtr = GG.receiver;
    for (i = 0; i < G->arcnum; i++)
    {
        for (j = 0; j < G->arcnum; j++)
        {
            if (GG.arcs[vnum][i][j].weight != G->arcs[vnum][i][j].weight)
            {
                GGtr[j] = Gtr[j];
                GG.arcs[vnum][i][j].weight = G->arcs[vnum][i][j].weight;
                GG.arcs[vnum][i][j].message = G->arcs[vnum][i][j].message;
            }
        }
    }
}

void Receive(MGraph *G, int vnum)
{
    int i, j;
    int *Gtr;
    int *GGtr;
    Gtr = G->receiver;
    GGtr = GG.receiver;
    for (i = 0; i < G->arcnum; i++)
    {
        for (j = 0; j < G->arcnum; j++)
        {
            if (GG.receiver[j] == vnum)
            {
                Gtr[j] = GGtr[j];
                G->arcs[vnum][i][j].weight = GG.arcs[vnum][i][j].weight;
                G->arcs[vnum][i][j].message = GG.arcs[vnum][i][j].message;
            }
        }
    }
}
/*
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
*/

int Iffull(MGraph *G)
{
    int i, j, n;
    int a;
    for (n = 0; i < G->arcnum; n++)
    {
        for (i = 0; i < G->arcnum; i++)
        {
            a = 0;
            for (j = 0; j < G->arcnum; j++)
            {
                if (G->arcs[n][i][j].weight > UNLINK)
                {
                    a = 1;
                }
            }
            if (a == 0)
                return 0; //未满
            else
                return 1; //已满
        }
    }
}

void SwitchS(int j)
{
    switch (j)
    {
    case 0:
        Send(&MG, 0);
        break;
    case 1:
        Send(&MG, 1);
        break;
    case 2:
        Send(&MG, 2);
        break;
    case 3:
        Send(&MG, 3);
        break;
    case 4:
        Send(&MG, 4);
        break;
    case 5:
        Send(&MG, 5);
        break;
    default:
        break;
    }
}

void Dijkstra(int v)
{
}