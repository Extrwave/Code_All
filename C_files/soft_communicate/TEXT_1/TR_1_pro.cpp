
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
    //��¼���ݸ���
    float a1[A], a2[A],a3[B];
    //a1[]Ϊ�ź����ݵ�ʵ����a2[]Ϊ�鲿
    number = Read(a1, a2);
    Calculation(a1, a2,number);

    printf("�ź�ǿ��Ϊ %.6f\n", consult);
    system("pause");

    return 0;
}


//�����ź�ǿ��
void Calculation(float *ptr1, float *ptr2,int i)
{
    int j;
    for (j = 0; j < i; j++,ptr1++,ptr2++)
    {
        n = pow(*ptr1, 2.0) + pow(*ptr2, 2.0);
        //printf("�ź�ǿ�� %d = %f\n", j, n);
        consult += n;
    }
}


//��ȡ����
int Read(float *ptr1, float *ptr2)
{
    FILE *fp;
    //��ȡ�����ݴ���g���и�ֵ
    int i = 0;
    int j;
    //ֻ����ʽ���ļ�
    if ((fp = fopen("F:\\CDGL\\con_soft_B\\class_data_1\\data0.txt", "a+")) == NULL)
    {
        printf("open files fail!");
        exit(0);
    }
    //���ļ��������ݴ�������

    while (!feof(fp))
    {
        fscanf(fp, "%f", ptr1);   
        fscanf(fp, "%f", ptr2);
        ptr1++;ptr2++;i++;
    }

    //�ر��ļ�
    j = fclose(fp);
    if (j == 0)
        printf("close files OK!\n");
    else
        printf("close files fail!\n");

    return i;
}