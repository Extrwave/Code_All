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

} MeNode[MAX_NUM], T_weight[MAX_NUM][MAX_NUM];

typedef struct
{
    Ptype vexs[MAX_NUM]; //顶点向量//字符串
    T_weight arcs;       //邻接矩阵，储存边与边的关系
    int vexnum, arcnum;  //顶点数，弧数
} MGraphs[MAX_NUM];

void Creat(MGraphs *G, int k);
void CreatM(MGraphs *G, int k);
int Iffull(MGraphs *G);
void Send(MGraphs *G, int vnum);
void Receive(MGraphs *G, int vnum);
void Print(MGraphs *G, int k);

int line = 0;

MGraphs MG[MAX_NUM];
MGraphs GG[MAX_NUM];

int main()
{
    FILE *ap;
    if ((ap = fopen("F:/VS_code/C_files/soft_communicate/TEXT_2/point.txt", "r")) == NULL)
    {
        printf("打开文件失败！");
        exit(0);
    }
    char lines[MAX_NUM];
    int i, j, k, a;

    while (fgets(lines, MAX_NUM, ap))
    {
        line++;
    }
    printf("共有节点数%d个\n", line);

    //CreatM(&GG);
    printf("正在读取节点信息...");
    Sleep(1500);
    //初始化节点总图
    for (i = 0; i < line; i++)
    {
        CreatM(GG, line - 1);
        Creat(MG, i);
    }
    //创建完成
    printf("信息读取完成！\n");

    //打印检查数据正确性
    for (k = 0; k < line; k++)
    {
        Print(&MG[k], k);
    }

    /*判断转发表是否完整*/ //GG是否满
    do
    {
        srand((unsigned)time(NULL));
        a = rand() % 6;
        printf("选取节点%d进行洪泛~", a);
        Receive(MG, a);
        Send(MG, a);
        for (k = 0; k < line; k++)
        {
            Print(&GG[k], k);
        }
    } while (Iffull(GG));
    system("pause");
    return 0;
}

void Creat(MGraphs *G, int k) //创造表1 2 3 4 5 6
{
    int i, j, n; //顶点数和边数
    char empty[MAX_NUM];
    for (i = 0; i < k; i++)
    {
        G[k]->arcnum = line;
        G[k]->vexnum = line;
    }
    //初始化节点图或者总图

    for (i = 0; i < line; i++)
    {
        for (j = 0; j < line; j++)
        {
            G[k]->arcs[i][j].weight = UNLINK;
            G[k]->arcs[i][j].weight = NULL;
        }
    }

    //文件读取输入吧
    FILE *fp;
    if ((fp = fopen("F:/VS_code/C_files/soft_communicate/TEXT_2/point.txt", "r")) == NULL)
    {
        printf("打开文件失败！");
        exit(0);
    }
    for (i = 0; i < k; i++)
        fgets(empty, MAX_NUM, fp);

    for (j = 0; j < line; j++)
    {
        fscanf(fp, "%d ", &G[k]->arcs[k][j].weight);
        //因为是无向图，所以G->arcs[][][].next=NULL无需改变
    }
    fclose(fp);
}

void CreatM(MGraphs *G, int k) //创造总表, 节点数
{
    G[k]->arcnum = line;
    G[k]->vexnum = line;
    int i, j, n; //顶点数和边数
    //初始化节点图或者总图
    for (n = 0; n < k; n++)
    {
        for (i = 0; i < line; i++)
        {
            for (j = 0; j < line; j++)
            {
                G[n]->arcs[i][j].weight = UNLINK;
                G[n]->arcs[i][j].next = NULL;
            }
        }
    }
}

void Send(MGraphs *G, int vnum)
{
    int i, j, m, n;
    int mark = 1;
    for (i = 0; i < line; i++)
    {
        for (j = 0; j < line; j++)
        {
            if (GG[vnum]->arcs[i][j].weight != G[vnum]->arcs[i][j].weight)
            {
                for (m = 0; m < line; m++)
                    for (n = 0; n < line; n++)
                        GG[vnum]->arcs[m][n].weight = G[vnum]->arcs[m][n].weight;
            }
        }
    }
}

void Receive(MGraphs *G, int vnum)
{
    int i, j, m, n;
    //   int *Gtr;
    //    int *GGtr;
    //    Gtr = G[vnum]->receiver;   //接受者指针
    //    GGtr = GG[vnum]->receiver; //公共区接受者
    for (i = 0; i < line; i++)
        for (j = 0; j < line; j++)
            //判断公共区域有没有传给自己的数据
            if (GG[vnum]->arcs[i][j].weight == vnum)
            {
                for (n = 0; n < line; n++)
                    G[vnum]->arcs[i][n].weight = GG[vnum]->arcs[i][n].weight;
            }
}

int Iffull(MGraphs *G)
{
    int i, j, n;
    int a;
    for (n = 0; i < line; n++)
    {
        for (i = 0; i < line; i++)
        {
            a = 0;
            for (j = 0; j < line; j++)
            {
                if (G[n]->arcs[i][j].weight > UNLINK)
                {
                    a = 1;
                }
            }
            if (a == 0)
                return 0; //未满
        }
    }
    return 1; //已满
}

void Print(MGraphs *G, int k)
{
    int i, j;
    printf("节点%d的数据：\n", k);
    for (i = 0; i < line; i++)
    {
        for (j = 0; j < line; j++)
        {
            printf("%d ", MG[k]->arcs[i][j].weight);
        }
        printf("\n");
    }
    printf("\n\n");
}

void Dijkstra(int v)
{
}