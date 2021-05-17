
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"
#include "windows.h"

#define MAX_NUM 30
#define N 5
#define M 0
#define UNLINK -1

typedef int VRtype;
typedef int Infotype;
typedef char Ptype;
typedef char Mtype;

typedef struct Node
{
    VRtype weight;  //�ڽӱ�Ȩֵ
    Infotype *next; //�����ָ��

    int function;
    int length;
    Mtype message;

} T_weight[MAX_NUM][MAX_NUM];

typedef struct
{
    Ptype vexs[MAX_NUM];   //��������//�ַ���
    T_weight arcs;         //�ڽӾ��󣬴������ߵĹ�ϵ
    int vexnum, arcnum;    //������������
    int receiver[MAX_NUM]; //�ڵ���Ϣ������
} MGraphs[MAX_NUM];

void Creat(MGraphs *G, int k);
void CreatM(MGraphs *G, int k);
int Iffull(MGraphs *G);
void Send(MGraphs *G, int vnum);
void Receive(MGraphs *G, int vnum);
void Print(MGraphs *G, int k);
void PrintM(MGraphs *G, int k);
void InitMGraph(MGraphs *G);
int Dijkstra(int s, int e);

int line = 0;
char empty[MAX_NUM];
//����������������DJSKL�㷨
const int Max = 10000;
int dist[MAX_NUM];
int node[MAX_NUM];

MGraphs MG[MAX_NUM];
MGraphs GG[MAX_NUM];

int main()
{
    FILE *ap;
    if ((ap = fopen("F:/AEx_Code/C_files/soft_communicate/TEXT_2/point.txt", "r")) == NULL)
    {
        printf("���ļ�ʧ�ܣ�");
        exit(0);
    }
    char lines[MAX_NUM];
    int i, j, k, a;

    //CreatM(&GG);
    printf("���ڶ�ȡ�ڵ���Ϣ...\n");
    Sleep(1500);
    while (fgets(lines, MAX_NUM, ap))
    {
        line++;
    }
    printf("���нڵ���%d��\n", line);

    //��ʼ���ڵ���ͼ
    for (i = 0; i < line; i++)
    {
        CreatM(GG, line - 1);
        Creat(MG, i);
    }
    //�������
    printf("��Ϣ��ȡ��ɣ�\n\n");

    //��ӡ���������ȷ��
    for (k = 0; k < line; k++)
    {
        Print(MG, k);
    }
    PrintM(GG, M);
    srand((unsigned)time(NULL));
    /*�ж�ת�����Ƿ�����*/ //GG�Ƿ���
    do
    {
        a = rand() % 6;
        printf("ѡȡ�ڵ�%d���к鷺~\n", a + 1);
        Receive(MG, a);
        Send(MG, a);
        PrintM(GG, M);
    } while (!Iffull(GG));
    //��ʼDJSKTRA�㷨
    //
    int begin, end;
    printf("������������·���Ľڵ�x,y:\n");
    scanf("%d,%d", &begin, &end);
    if (begin > line || begin < 1 || end > line || end < 1)
        printf("�������!\n");
    int shortest = Dijkstra(begin - 1, end - 1);

    if (shortest != 0)
        printf("%d\n", shortest);
    else
        printf("�ڵ�%d��%d����ͨ��\n", begin, end);

    system("pause");
    return 0;
}

void Creat(MGraphs *G, int k) //�����1 2 3 4 5 6
{
    int i, j, n; //�������ͱ���

    for (i = 0; i < line; i++)
    {
        G[k]->arcnum = line;
        G[k]->vexnum = line;
    }
    //��ʼ���ڵ�ͼ������ͼ

    for (i = 0; i < line; i++)
    {
        for (j = 0; j < line; j++)
        {
            G[k]->arcs[i][j].weight = UNLINK;
            G[k]->arcs[i][j].next = NULL;
        }
    }

    //�ļ���ȡ�����
    FILE *fp;
    if ((fp = fopen("F:/AEx_Code/C_files/soft_communicate/TEXT_2/point.txt", "r")) == NULL)
    {
        printf("���ļ�ʧ�ܣ�");
        exit(0);
    }
    for (i = 0; i < k; i++)
        fgets(empty, MAX_NUM, fp);

    for (j = 0; j < line; j++)
    {
        fscanf(fp, "%d ", &G[k]->arcs[k][j].weight);
        //��Ϊ������ͼ������G->arcs[][][].next=NULL����ı�
    }
    fclose(fp);
}

void CreatM(MGraphs *G, int k) //�����ܱ�, �ڵ���
{
    G[k]->arcnum = line;
    G[k]->vexnum = line;
    int i, j, n; //�������ͱ���
                 //��ʼ���ڵ�ͼ������ͼ

    for (i = 0; i < line; i++)
    {
        for (j = 0; j < line; j++)
        {
            G[M]->arcs[i][j].weight = UNLINK;
            G[M]->arcs[i][j].next = NULL;
            G[M]->receiver[i] = UNLINK;
        }
    }
}

void Send(MGraphs *G, int vnum)
{
    int i, j, m, n;
    int mark = 1;

    for (m = 0; m < line; m++)
    {
        for (n = 0; n < line; n++)
        {
            GG[M]->arcs[m][n].weight = G[vnum]->arcs[m][n].weight;
        }
        if (G[vnum]->arcs[vnum][m].weight != UNLINK)
        {
            GG[M]->receiver[m] = m;
            //��¼�⴮�����Ǵ����ĸ��ڵ��
        }
    }
}

void Receive(MGraphs *G, int vnum)
{
    int i, j, m, n;
    for (j = 0; j < line; j++)
        //�жϹ���������û�д����Լ�������
        if (GG[M]->receiver[j] == vnum)
        {
            for (m = 0; m < line; m++)
                if (m != vnum)
                    for (n = 0; n < line; n++)
                        G[vnum]->arcs[m][n].weight = GG[M]->arcs[m][n].weight;
        }
    InitMGraph(GG);
}

int Iffull(MGraphs *G)
{
    int i, j, n;
    int a;
    for (i = 0; i < line; i++)
    {
        a = 0;
        for (j = 0; j < line; j++)
        {
            if (G[M]->arcs[i][j].weight > UNLINK)
            {
                a = 1;
            }
        }
        if (a == 0)
            return 0; //δ��
    }
    return 1; //����
}

void Print(MGraphs *G, int k)
{
    int i, j;
    printf("�ڵ�%d�����ݣ�\n", k + 1);
    for (i = 0; i < line; i++)
    {
        for (j = 0; j < line; j++)
        {
            printf("%d ", G[k]->arcs[i][j].weight);
        }
        printf("\n");
    }
    printf("\n\n");
}

void PrintM(MGraphs *G, int k)
{
    int i, j;
    printf("��������ڵ�����ݣ�\n");
    for (i = 0; i < line; i++)
    {
        for (j = 0; j < line; j++)
        {
            printf("%d ", G[k]->arcs[i][j].weight);
        }
        printf("\n");
    }
    printf("\n\n");
}

void InitMGraph(MGraphs *G)
{
    int i, j;
    for (i = 0; i < line; i++)
    {
        for (j = 0; j < line; j++)
        {
            G[M]->arcs[i][j].weight = UNLINK;
            G[M]->arcs[i][j].next = NULL;
        }
    }
}

int Dijkstra(int s, int e)
{
    //��ȡ���·��
    for (int i = 0; i < line; i++)
    {
        for (int j = 0; j < line; j++)
        {
            //scanf("%d ", GG[M]->arcs[i][j].weight);
            if (!GG[M]->arcs[i][j].weight)
                GG[M]->arcs[i][j].weight = Max;
        }
    }

    for (int i = 0; i < line; i++)
    {
        dist[i] = GG[M]->arcs[s][i].weight;
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
            if (dist[i] > dist[v] + GG[M]->arcs[i][v].weight)
            {
                dist[i] = dist[v] + GG[M]->arcs[i][v].weight;
            }
        }
    }
    return dist[e];
}