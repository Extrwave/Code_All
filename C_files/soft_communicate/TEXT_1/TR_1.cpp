
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
    //a1[]Ϊ�ź����ݵ�ʵ����a2[]Ϊ�鲿
    float a1[A], a2[A], g;

    FILE *fp;

    //ֻ����ʽ���ļ�
    if ((fp = fopen("F:\\CDGL\\con_soft_B\\class_data_1\\data0.txt", "a+")) == NULL)
    {
        printf("open files fail!");
        exit(0);
    }

    //���ļ��������ݴ�������
    while (!feof(fp))
    {
        i++;
        fscanf(fp, "%f", &g);
        a1[i] = g;
        fscanf(fp, "%f", &g);
        a2[i] = g;
    }
    //�ر��ļ�
    j = fclose(fp);
    if (j == 0)
        printf("close files OK!\n");
    else
        printf("close files fail!\n");

    //�����ź�ǿ�ȼ���
    for (j = 0; j <= i; j++)
    {
        n = pow(a1[j], 2.0) + pow(a2[j], 2.0);
        //printf("�ź�ǿ�� %d = %f\n", j, n);
        consult += n;
    }

    printf("�ź�ǿ��Ϊ %.6f\n", consult);
    system("pause");

    return 0;
}
