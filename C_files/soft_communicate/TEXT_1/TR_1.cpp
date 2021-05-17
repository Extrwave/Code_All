
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#define A 40000



int Calculation(float *ptr);

int main()
{
    int i = -1;
    int j;
    float n, consult;
    //a1[]为信号数据的实部，a2[]为虚部
    float a1[A], a2[A], g;

    FILE *fp;

    //只读格式打开文件
    if ((fp = fopen("F:\\CDGL\\con_soft_B\\class_data_1\\data0.txt", "a+")) == NULL)
    {
        printf("open files fail!");
        exit(0);
    }

    //打开文件读出数据存入数组
    while (!feof(fp))
    {
        i++;
        fscanf(fp, "%f", &g);
        a1[i] = g;
        fscanf(fp, "%f", &g);
        a2[i] = g;
    }
    //关闭文件
    j = fclose(fp);
    if (j == 0)
        printf("close files OK!\n");
    else
        printf("close files fail!\n");

    //进行信号强度计算
    for (j = 0; j <= i; j++)
    {
        n = pow(a1[j], 2.0) + pow(a2[j], 2.0);
        //printf("信号强度 %d = %f\n", j, n);
        consult += n;
    }

    printf("信号强度为 %.6f\n", consult);
    system("pause");

    return 0;
}
