
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#define A 16000
#define B 51

float n, consult;

void Calculation(float ptr1[], float ptr2[],int i);
int Read(float ptr1[], float ptr2[]);

int main()
{
    int number;
    //记录数据个数
    float a1[A], a2[A],a3[B];
    //a1[]为信号数据的实部，a2[]为虚部
    number = Read(a1, a2);
    Calculation(a1, a2,number);

    printf("信号强度为 %.6f\n", consult);
    system("pause");

    return 0;
}


//计算信号强度
void Calculation(float *ptr1, float *ptr2,int i)
{
    int j;
    for (j = 0; j < i; j++,ptr1++,ptr2++)
    {
        n = pow(*ptr1, 2.0) + pow(*ptr2, 2.0);
        //printf("信号强度 %d = %f\n", j, n);
        consult += n;
    }
}


//读取数据
int Read(float *ptr1, float *ptr2)
{
    FILE *fp;
    //读取数据暂存于g进行赋值
    int i = 0;
    int j;
    //只读格式打开文件
    if ((fp = fopen("F:\\CDGL\\con_soft_B\\class_data_1\\data0.txt", "a+")) == NULL)
    {
        printf("open files fail!");
        exit(0);
    }
    //打开文件读出数据存入数组

    while (!feof(fp))
    {
        fscanf(fp, "%f", ptr1);   
        fscanf(fp, "%f", ptr2);
        ptr1++;ptr2++;i++;
    }

    //关闭文件
    j = fclose(fp);
    if (j == 0)
        printf("close files OK!\n");
    else
        printf("close files fail!\n");

    return i;
}