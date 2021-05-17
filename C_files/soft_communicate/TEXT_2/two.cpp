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
    Ptype vexs[MAX_NUM];   //��������//�ַ���
    T_weight arcs;         //�ڽӾ��󣬴������ߵĹ�ϵ
    int vexnum, arcnum;    //������������
    int receiver[MAX_NUM]; //������
} MGraphs[MAX_NUM];

void Creat(MGraphs *G, int k);
void CreatM(MGraphs *G, int k);
int Iffull(MGraphs *G);
void Send(MGraphs *G, int vnum);
void Receive(MGraphs *G, int vnum);
void Print(MGraphs *G, int k);

int vum, aum;
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
        Creat(&MG[i], i);
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
        Receive(&MG[a], a);
        Send(&MG[a], a);
        for (k = 0; k < line; k++)
        {
            Print(&GG[k], k);
        }
    } while (!Iffull(GG));
    /*
    for (k = 0; k < line; k++)
    {
        Print(&GG[k], k);
    }
    */
    system("pause");
    return 0;
}

void Creat(MGraphs *G, int k) //�����1 2 3 4 5 6
{
    int i, j, n; //�������ͱ���
    int *ptr;
    ptr = G[k]->receiver;
    char empty[MAX_NUM];
    G[k]->arcnum = line;
    G[k]->vexnum = line;
    //��ʼ���ڵ�ͼ������ͼ

    for (i = 0; i < G[0]->vexnum; i++)
    {
        for (j = 0; j < G[0]->vexnum; j++)
        {
            G[n]->receiver[i] = line + 1; //ȷ��δ���ӵ�ֵ���䲻ͬ
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

    for (j = 0; j < G[0]->arcnum; j++)
    {
        fscanf(fp, "%d ", &G[k]->arcs[k][j].weight);
        //��Ϊ������ͼ������G->arcs[][][].next=NULL����ı�
        if (G[k]->arcs[i][j].weight > UNLINK)
        {
            *ptr = j;
            ptr++;
        }
    }
    fclose(fp);
}

void CreatM(MGraphs *G, int k) //�����ܱ�, �ڵ���
{
    G[0]->arcnum = line;
    G[0]->vexnum = line;
    int i, j, n; //�������ͱ���
    //��ʼ���ڵ�ͼ������ͼ
    for (n = 0; n < k; n++)
    {
        for (i = 0; i < vum; i++)
        {
            for (j = 0; j < vum; j++)
            {
                G[n]->receiver[i] = line + 1; //ȷ��δ���ӵ�ֵ���䲻ͬ
                G[n]->arcs[i][j].weight = UNLINK;
                G[n]->arcs[i][j].next = NULL;
            }
        }
    }
}

void Send(MGraphs *G, int vnum)
{
    int i, j, n;
    int mark = 1;
    int *Gtr;
    int *GGtr;
    Gtr = G[vnum]->receiver;
    GGtr = GG[vnum]->receiver;
    while (GGtr)
        GGtr++;

    for (i = 0; i < G[0]->arcnum; i++)
    {
        for (j = 0; j < G[0]->arcnum; j++)
        {
            if (GG[vnum]->arcs[i][j].weight != G[vnum]->arcs[i][j].weight)
            {
                for (n = 0; n < GG[0]->arcnum; n++)
                {
                    //�ж���Ϣ�Ƿ��Ѿ����չ���
                    if (GG[vnum]->receiver[i] == j)
                        mark = 0;
                }
                if (mark == 1)
                    *GGtr = Gtr[j];
                //δ���ܹ����򴫸���������
                GG[vnum]->arcs[i][j].weight = G[vnum]->arcs[i][j].weight;
                GGtr++;
            }
        }
    }
}

void Receive(MGraphs *G, int vnum)
{
    int i, j;
    //   int *Gtr;
    //    int *GGtr;
    //    Gtr = G[vnum]->receiver;   //������ָ��
    //    GGtr = GG[vnum]->receiver; //������������
    for (i = 0; i < G[0]->arcnum; i++)
    {
        for (j = 0; j < G[0]->arcnum; j++)
        {
            //�жϹ���������û�д����Լ�������
            if (GG[vnum]->receiver[j] == vnum)
            {
                G[vnum]->receiver[j] = GG[vnum]->receiver[j];
                //��¼����˭������
                G[vnum]->arcs[i][j].weight = GG[vnum]->arcs[i][j].weight;
            }
        }
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
    printf("�ڵ�%d�����ݣ�\n", k + 1);
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