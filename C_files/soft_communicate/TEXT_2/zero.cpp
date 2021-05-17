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
    VRtype weight;  //�ڽӱ�Ȩֵ
    Infotype *next; //�����ָ��
} MeNode, T_weight[MAX_NUM][MAX_NUM];

typedef struct
{
    Ptype vexs[MAX_NUM]; //��������
    T_weight arcs;       //�ڽӾ��󣬴������ߵĹ�ϵ
    int vexnum, arcnum;  //������������
    int mark1, mark2;    //�ж��Ƿ񱻷��͹�
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

    while (Iffull(&GG)) /*�ж�ת�����Ƿ�����*/ //GG�Ƿ���
    {
        srand((unsigned)time(NULL));
        a = rand() % 6;
        SwitchS(a);
    }
}

void Creat(MGraph *G, int k) //�����1 2 3 4 5 6
{
    int i, j; //�������ͱ���
    printf("�����붥�����ͱ������Զ��Ÿ��� \n");
    scanf("%d,%d", G->vexnum, G->arcnum);
    fflush(stdin); //���������
    for (i = 0; i < G->vexnum; i++)
    {
        scanf("%c", G->vexs[i]);
    }

    //��ʼ���ڵ�ͼ������ͼ

    for (i = 0; i < G->vexnum; i++)
    {
        for (j = 0; j < G->vexnum; j++)
        {
            G->arcs[i][j].weight = UNLINK;
            G->arcs[i][j].next = NULL;
        }
    }
    printf("������ڵ�Ȩֵ�����Ÿ���\n");
    for (j = 0; j < G->arcnum; j++)
    {
        scanf("%d", G->arcs[k - 1][j].weight);
        //��Ϊ������ͼ������G->arcs[][].next=NULL����ı�
    }
    //���ڵ㱻д������Ϣ��mark1  +1�����ڵ㷢����Ϣ��mark2  +1
    //��mark1==mark2ʱ���跢��
    G->mark1 = 1;
    G->mark2 = 0;
}

void CreatM(MGraph *G) //�����0 1 2 3 4 5
{
    int i, j; //�������ͱ���
    printf("�����붥�����ͱ������Զ��Ÿ��� \n");
    scanf("%d,%d", G->vexnum, G->arcnum);
    fflush(stdin); //���������
    for (i = 0; i < G->vexnum; i++)
    {
        scanf("%c", G->vexs[i]);
    }

    //��ʼ���ڵ�ͼ������ͼ

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
    int k = 0; //�ж��Ƿ���Ч����
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
        //Ӧ��ʦҪ��ÿ����һ�κ鷺��������һ��
        for (i = 0; i < G1->arcnum; i++)
        {
            for (j = 0; j < G1->arcnum; j++)
            {
                printf("%d ", G1->arcs[i][j]);
            }
            printf("\n");
        }
        //Ӧ��ʦҪ��ÿ����һ�κ鷺��������һ��
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
                    SwitchT(G, j); //ֻҪ�����Ӿʹ���ȫ��Ԫ�أ����Ѵ��ڣ��򲻻����
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
                return 0; //δ��
        }
        return 1; //����
    }
}

void Dijkstra(int v)
{
}