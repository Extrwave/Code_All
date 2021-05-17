#include <string.h>
#include "stdio.h"
#include <malloc.h>
#include <conio.h>
#include <stdlib.h>
#define MAX 10
typedef struct student
{
    char name[8];
    int score;
} STU[MAX];


int Initstu(STU a, int n)
{
    printf("请输入 10 位同学的姓名于成绩：\n");
    for (int i = 1; i < n + 1; i++)
    {
        scanf("%s", a[i].name);
        scanf("%d",&a[i].score);
    }
    return 0;
}

int Sort1(STU a, int n)
{
    int i, j;
    for (i = 2; i <= n; i++)
    {
        if (a[i].score < a[i - 1].score) /* 需将L->r[i]插入有序子表 */
        {
            a[0] = a[i]; /* 设置哨兵 */
            for (j = i - 1; a[j].score > a[0].score; j--)
                a[j + 1] = a[j]; /* 记录后移 */
            a[j + 1] = a[0];     /* 插入到正确位置 */
        }
    }
    return 0;
}

int Sort2(STU a, int n)
{
    int i, j;
    student k;
    for (i = 1; i < n; i++)
    {
        for (j = n - 1; j >= i; j--) /* 注意j是从后往前循环 */
        {
            if (a[j].score > a[j + 1].score) /* 若前者大于后者（注意这里与上一算法的差异）*/
            {
                k=a[j];
                a[j]=a[j+1];
                a[j+1]=k;
            /*    k = a[j].score; /* 交换L->r[j]与L->r[j+1]的值 */
            /*    a[j].score = a[j + 1].score;
                a[j + 1].score = k;
            */
            }
        }
    }
    return 0;
}

int main()
{
    STU stu;
    Initstu(stu,MAX);
    Sort1(stu,MAX);
    for(int i=1; i <= MAX; i++)
    {
        printf("%s %d ",stu[i].name,stu[i].score);
    }
    printf("\n");
    Initstu(stu,MAX);
    Sort2(stu,MAX);
    for(int i=1; i <= MAX; i++)
    {
        printf("%s %d ",stu[i].name,stu[i].score);
        
    }
    printf("\n");
    system("pause");
    return 0;
}
