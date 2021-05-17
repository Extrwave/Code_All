#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"

#define LEN 20
#define MAX_NUM 100
#define year 3
#define MAX_COU 20
#define DINFINT 30000
#define center 3

typedef struct Node
{
    char name[LEN];
    float six;       //06年
    float ten;       //10年
    float seven;     //07年
    float dis[year]; //三个归一化数据值
    int str;         //所属类别，刚开始统一为 -1
} Mind[MAX_COU];

int N_line();
void FMaxMin(Mind *G);
void CountGY(Mind *G, Mind *G1);
void CountGL(Mind *G1);
void FCountGL(Mind *G1);
void Read_Data();
void Print();

int Number;
Mind Coun[MAX_COU];
Mind CounG[MAX_COU];
Mind FGL[year]; //迭代聚类中心数据暂存处

float max1 = 0, min1 = DINFINT, max2 = 0, min2 = DINFINT, max3 = 0, min3 = DINFINT;

int main()
{
    int i, j, k;
    Number = N_line();
    printf("国家数量为%d个\n", Number);
    Read_Data();
    CountGY(Coun, CounG);
    //printf("选取几个聚类中心？：");
    //scanf("%d", &center);
    CountGL(CounG);  //第一次聚类
    FCountGL(CounG); //迭代聚类
    Print();
    system("pause");
    return 0;
}

int N_line()
{
    int num = 0;
    char mid[MAX_NUM];
    FILE *fp;
    if ((fp = fopen("F:/VS_code/C_files/soft_communicate/TEXT_3/data.txt", "r")) == NULL)
    {
        printf("打开文件失败！");
        exit(0);
    }
    while (fgets(mid, MAX_NUM, fp))
    {
        num++;
    }
    fclose(fp);
    return num;
}

void Read_Data()
{
    int i;
    FILE *fp;
    if ((fp = fopen("F:/VS_code/C_files/soft_communicate/TEXT_3/data.txt", "r")) == NULL)
    {
        printf("打开文件失败！\n");
        exit(0);
    }

    //初始化结构体存入数组
    for (i = 0; i < Number; i++)
    {
        fscanf(fp, "%s", &Coun[i]->name);
        strcpy(CounG[i]->name, Coun[i]->name);
        fscanf(fp, " %f", &Coun[i]->six);
        fscanf(fp, " %f", &Coun[i]->ten);
        fscanf(fp, " %f", &Coun[i]->seven);
        printf("%s %.1f %.1f %.1f %s %.1f %.1f %.1f\n", Coun[i]->name, Coun[i]->six, Coun[i]->ten, Coun[i]->seven, CounG[i]->name, CounG[i]->six, CounG[i]->ten, CounG[i]->seven);
    }
}

void FMaxMin(Mind *G)
{
    int i;
    for (i = 0; i < Number; i++)
    {
        if (G[i]->six >= max1)
            max1 = G[i]->six;
        if (G[i]->six <= min1)
            min1 = G[i]->six;
        if (G[i]->ten >= max2)
            max2 = G[i]->ten;
        if (G[i]->ten <= min2)
            min2 = G[i]->ten;
        if (G[i]->seven >= max3)
            max3 = G[i]->seven;
        if (G[i]->seven <= min3)
            min3 = G[i]->seven;
    }
}

void CountGL(Mind *G1)
{
    int i, j;
    int a, b, c; //作为初始聚类中心
    printf("输入x,y,z作为第一次聚类中心\n");
    scanf("%d,%d,%d", &a, &b, &c);
    /*
    a=rand()%Number
    b=rand()%Number
    c-rand()%Number
    */
    int rear = DINFINT; //找出的距离聚类中心最小的一个
    for (i = 0; i < Number; i++)
    {
        G1[i]->dis[0] = pow(G1[i]->six - G1[a - 1]->six, 2) + pow(G1[i]->ten - G1[a - 1]->ten, 2) + pow(G1[i]->seven - G1[a - 1]->seven, 2);
        G1[i]->dis[1] = pow(G1[i]->six - G1[b - 1]->six, 2) + pow(G1[i]->ten - G1[b - 1]->ten, 2) + pow(G1[i]->seven - G1[b - 1]->seven, 2);
        G1[i]->dis[2] = pow(G1[i]->six - G1[c - 1]->six, 2) + pow(G1[i]->ten - G1[c - 1]->ten, 2) + pow(G1[i]->seven - G1[c - 1]->seven, 2);
        for (j = 0; j < center; j++)
        {
            if (G1[i]->dis[j] <= rear)
            {
                rear = G1[i]->dis[j];
                G1[i]->str = j;
            }
        }
    }
}

void FCountGL(Mind *G1)
{
    int j = 0, k = 0, l = 0;
    int marks[center];
    int mark = 0;
    //sum[][]记录06年的三个聚类中心，记录10年的三个聚类中心，记录07年的三个聚类中心
    //年   6 10  7
    //sum  0  1  2
    // A  0
    // B  1
    // C  2
    float sum[center][center] = {0};
    int rear = DINFINT; //找出的距离聚类中心最小的一个
    //求出再次聚类时的聚类中心
    for (int i = 0; i < Number; i++)
    {

        if (G1[i]->str == 0)
        {
            sum[0][0] += G1[i]->six;
            sum[0][1] += G1[i]->ten;
            sum[0][2] += G1[i]->seven;
            j++;
        }
        if (G1[i]->str == 1)
        {
            sum[1][0] += G1[i]->six;
            sum[1][1] += G1[i]->ten;
            sum[1][2] += G1[i]->seven;
            k++;
        }
        if (G1[i]->str == 2)
        {
            sum[2][0] += G1[i]->six;
            sum[2][1] += G1[i]->ten;
            sum[2][2] += G1[i]->seven;
            l++;
        }
    }
    //平均值为聚类中心值
    FGL[0]->six = sum[0][0] / j;
    FGL[0]->ten = sum[0][1] / j;
    FGL[0]->seven = sum[0][2] / j;

    FGL[1]->six = sum[1][0] / k;
    FGL[1]->ten = sum[1][1] / k;
    FGL[1]->seven = sum[1][2] / k;

    FGL[2]->six = sum[2][0] / l;
    FGL[2]->ten = sum[2][1] / l;
    FGL[2]->seven = sum[2][2] / l;
    //进行聚类计算
    for (int i = 0; i < Number; i++)
    {
        G1[i]->dis[0] = pow(G1[i]->six - FGL[0]->six, 2) + pow(G1[i]->ten - FGL[0]->ten, 2) + pow(G1[i]->seven - FGL[0]->seven, 2);
        G1[i]->dis[1] = pow(G1[i]->six - FGL[1]->six, 2) + pow(G1[i]->ten - FGL[1]->ten, 2) + pow(G1[i]->seven - FGL[1]->seven, 2);
        G1[i]->dis[2] = pow(G1[i]->six - FGL[2]->six, 2) + pow(G1[i]->ten - FGL[2]->ten, 2) + pow(G1[i]->seven - FGL[2]->seven, 2);
        //用mark标记上一次聚类结果，方便这一次比较
        marks[i] = G1[i]->str;
        for (j = 0; j < 3; j++)
        {
            if (G1[i]->dis[j] <= rear)
            {
                rear = G1[i]->dis[j];
                G1[i]->str = j;
            }
        }
        if (marks[i] != G1[i]->str)
            mark = 1;
    }
    if (mark == 0)
        printf("迭代计算相同结果，完成分级\n");
    else
    {
        printf("迭代计算结果不一致，继续迭代\n");
        FCountGL(CounG);
    }
}

void CountGY(Mind *G, Mind *G1)
{
    int i;
    for (i = 0; i < Number; i++)
    {
        FMaxMin(G);
        G1[i]->six = (G[i]->six - min1) / (max1 - min1);
        G1[i]->ten = (G[i]->ten - min2) / (max2 - min2);
        G1[i]->seven = (G[i]->seven - min3) / (max3 - min3);
    }
    //归一化完成
}

void Print()
{
    for (int j = 0; j < center; j++)
    {
        printf("第%d级球队是：", j + 1);
        for (int i = 0; i < Number; i++)
        {
            if (CounG[i]->str == j)
                printf("%s  ", CounG[i]->name);
        }
        printf("\n");
    }
}
