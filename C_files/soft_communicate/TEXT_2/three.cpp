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

} MeNode[MAX_NUM], T_weight[MAX_NUM][MAX_NUM];

typedef struct
{
    Ptype vexs[MAX_NUM]; //��������//�ַ���
    T_weight arcs;       //�ڽӾ��󣬴������ߵĹ�ϵ
    int vexnum, arcnum;  //������������
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
        printf("���ļ�ʧ�ܣ�");
        exit(0);
    }
    char lines[MAX_NUM];
    int i, j, k, a;

    while (fgets(lines, MAX_NUM, ap))
    {
        line++;
    }
    printf("���нڵ���%d��\n", line);

    //CreatM(&GG);
    printf("���ڶ�ȡ�ڵ���Ϣ...");
    Sleep(1500);
    //��ʼ���ڵ���ͼ
    for (i = 0; i < line; i++)
    {
        CreatM(GG, line - 1);
        Creat(MG, i);
    }
    //�������
    printf("��Ϣ��ȡ��ɣ�\n");

    //��ӡ���������ȷ��
    for (k = 0; k < line; k++)
    {
        Print(&MG[k], k);
    }

    /*�ж�ת�����Ƿ�����*/ //GG�Ƿ���
    do
    {
        srand((unsigned)time(NULL));
        a = rand() % 6;
        printf("ѡȡ�ڵ�%d���к鷺~", a);
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

void Creat(MGraphs *G, int k) //�����1 2 3 4 5 6
{
    int i, j, n; //�������ͱ���
    char empty[MAX_NUM];
    for (i = 0; i < k; i++)
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
            G[k]->arcs[i][j].weight = NULL;
        }
    }

    //�ļ���ȡ�����
    FILE *fp;
    if ((fp = fopen("F:/VS_code/C_files/soft_communicate/TEXT_2/point.txt", "r")) == NULL)
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
    //    Gtr = G[vnum]->receiver;   //������ָ��
    //    GGtr = GG[vnum]->receiver; //������������
    for (i = 0; i < line; i++)
        for (j = 0; j < line; j++)
            //�жϹ���������û�д����Լ�������
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
                return 0; //δ��
        }
    }
    return 1; //����
}

void Print(MGraphs *G, int k)
{
    int i, j;
    printf("�ڵ�%d�����ݣ�\n", k);
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