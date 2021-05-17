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
    VRtype weight;  //�ڽӱ�Ȩֵ
    Infotype *next; //�����ָ��

    int function;
    int length;
    Mtype message;
} MeNode, T_weight[MAX_NUM][MAX_NUM];

typedef struct
{
    Ptype vexs[MAX_NUM];    //��������//�ַ���
    T_weight arcs[MAX_NUM]; //�ڽӾ��󣬴������ߵĹ�ϵ
    int vexnum, arcnum;     //������������
    int receiver[MAX_NUM];  //������
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
    //��ʼ���ڵ���ͼ
    for (i = 0; i < line; i++)
    {
        Creat(&MG, i);
    }
    //�������
    printf("��Ϣ��ȡ��ɣ�");

    while (Iffull(&GG)) /*�ж�ת�����Ƿ�����*/ //GG�Ƿ���
    {
        srand((unsigned)time(NULL));
        a = rand() % 6;
        SwitchS(a);
    }
}

void Creat(MGraph *G, int k) //�����1 2 3 4 5 6
{
    int i, j, n; //�������ͱ���
    int *ptr;
    char empty[MAX_NUM];
    printf("�����붥�����ͱ������Զ��Ÿ��� \n");
    scanf("%d,%d", G->vexnum, G->arcnum);
    fflush(stdin); //���������
    for (i = 0; i < G->vexnum; i++)
    {
        G->vexs[i] = i;
    }

    //��ʼ���ڵ�ͼ������ͼ
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
    printf("���ڶ�ȡ�ڵ���Ϣ\n");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");

    //�ļ���ȡ�����
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
            //��Ϊ������ͼ������G->arcs[][][].next=NULL����ı�
            if (G->arcs[k][i][j].weight > UNLINK)
            {
                *ptr = j;
                ptr++;
            }
        }
    }
}

void CreatM(MGraph *G, int vnum) //�����1 2 3 4 5 6
{
    int i, j, n; //�������ͱ���
    //��ʼ���ڵ�ͼ������ͼ
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
                    SwitchT(G, j); //ֻҪ�����Ӿʹ���ȫ��Ԫ�أ����Ѵ��ڣ��򲻻����
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
                return 0; //δ��
            else
                return 1; //����
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