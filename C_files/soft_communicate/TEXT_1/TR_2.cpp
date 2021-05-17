
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"

#define A 15000
#define B 51
#define C 3

float Calculation(float *ptr1, float *ptr2, int i);
int F_Calculation(float *ptr1, float *ptr2, float *mtr1, float *mtr2, int number, int number2);
int Read(float *ptr1, float *ptr2, int list);
int Read_Max(float *ptr1, float *ptr2, int i);
int ReadPSS(float *ptr1, float *ptr2, int list);
void Files(char *str, int i);
void FilesPSS(char *str, int i);
int Maxim(float *p);

int main()
{
    int list, m_locate;
    int number;
    int number2;
    //��¼���ݸ���

    float a1[A], a2[A], consult[B];
    int match[C];
    float max[A], maxi[A];

    //a1[]Ϊ�ź����ݵ�ʵ����a2[]Ϊ�鲿  consult[]Ϊ�������ݵ��ź�ǿ��
    //maxΪʵ����ǿ�ź�����ʵ����maxiΪ�鲿

    for (list = 0; list <= 71; list++)
    {
        if (list == 12 || list == 32 || list == 52)
        {
            list = list + 8;
        }
        number = Read(a1, a2, list);
        consult[list] = Calculation(a1, a2, number);
        //printf("data%d.txt�ź�ǿ��Ϊ %.6f\n", list, consult[list]);
    }

    //�ҳ���ǿ��һ��
    m_locate = Maxim(consult);
    printf("��ǿ�ź���Ϊ%d ǿ��Ϊ%f\n", m_locate, consult[m_locate]);

    //���������ҳ�ƥ���??
    //��ȡ��ǿ�ź�������max
    number = Read_Max(max, maxi, m_locate);

    //��ȡƥ���ź�pss�����л�������
    for (list = 0; list < 3; list++)
    {
        number2 = ReadPSS(a1, a2, list);
        match[list] = F_Calculation(a1, a2, max, maxi, number2, number);
        printf(" ���%d��ƥ��ǿ��Ϊ %d \n", list, match[list]);
    }
    /*
    for (int k = 0; k < 3; k++)
    {
        printf("%d  ", match[k]);
    }
    */

    system("pause");
    return 0;
}

/************************************************************************/

//�����ź�ǿ��
float Calculation(float *ptr1, float *ptr2, int i)
{
    int j;
    float consult = 0, n;
    for (j = 0; j < i; j++, ptr1++, ptr2++)
    {
        n = pow(*ptr1, 2.0) + pow(*ptr2, 2.0);
        //printf("�ź�ǿ�� %d = %f\n", j, n);
        consult += n;
    }
    return consult;
}

//��������
int F_Calculation(float *ptr1, float *ptr2, float *mtr1, float *mtr2, int number2, int number)
{

    float mean[A], Max;
    int locate = 0;
    int i, j;
    for (i = 0; i <= number - number2; i++)
    {
        float ch = 0, chi = 0;
        for (j = 0; j < number2; j++)
        {
            ch += ptr1[j] * mtr1[j + i] + ptr2[j] * mtr2[j + i];  //ʵ�����??
            chi += ptr1[j] * mtr2[j + i] + ptr2[j] * mtr1[j + i]; //�鲿���??
        }
        mean[i] = pow(ch, 2) + pow(chi, 2); //�������������ó�ֵ��ģ
    }
    Max = mean[0];
    for (i = 0; i < number - number2; i++)
    {
        if (mean[i] >= Max)
        {
            Max = mean[i];
            locate = i;
        }
        else
            Max = Max;
    }

    return locate;
}

//��ȡ����
int Read(float *ptr1, float *ptr2, int list)
{
    FILE *fp;

    int i = 0;
    int j;

    char str[60];
    Files(str, list);

    //ֻ����ʽ���ļ�
    if ((fp = fopen(str, "r")) == NULL)
    {
        printf("open files fail!");
        exit(0);
    }
    //���ļ��������ݴ�������

    while (!feof(fp))
    {
        fscanf(fp, "%f", ptr1);
        fscanf(fp, "%f", ptr2);
        ptr1++;
        ptr2++;
        i++;
    }

    //�ر��ļ�
    j = fclose(fp);
    if (j != 0)
        printf("close files fail!\n");

    return i;
}

//
int ReadPSS(float *ptr1, float *ptr2, int list)
{
    FILE *fp;

    int i = 0;
    int j;

    char str[B];
    FilesPSS(str, list);

    //ֻ����ʽ���ļ�
    if ((fp = fopen(str, "r")) == NULL)
    {
        printf("open files fail!");
        exit(0);
    }
    //���ļ��������ݴ�������

    while (!feof(fp))
    {
        fscanf(fp, "%f", ptr1);
        fscanf(fp, "%f", ptr2);
        ptr1++;
        ptr2++;
        i++;
    }

    //�ر��ļ�
    j = fclose(fp);
    if (j != 0)
        printf("close files fail!\n");

    return i;
}

//
int Read_Max(float *ptr1, float *ptr2, int i)
{
    FILE *f;
    int number = 0, j;
    char str[B];
    //ֻ����ʽ���ļ�
    Files(str, i);

    if ((f = fopen(str, "r")) == NULL)
    {
        printf("open files fail!");
        exit(0);
    }

    rewind(f);
    while (!feof(f))
    {
        fscanf(f, "%f", ptr1);
        fscanf(f, "%f", ptr2);
        ptr1++;
        ptr2++;
        number++;
    }

    j = fclose(f);
    if (j != 0)
        printf("close files fail!\n");

    return number;
}

//
void Files(char *str, int i)
{
    sprintf(str, "F:\\CDGL\\con_soft_B\\class_data_1\\data%d.txt", i);
}

//
void FilesPSS(char *str, int i)
{
    sprintf(str, "F:\\CDGL\\con_soft_B\\class_data_1\\PSS%d.txt", i);
}

//
int Maxim(float *p)
{
    float max;
    int locate = 0;
    max = p[0];
    for (int list = 0; list <= 71; list++)
    {
        if (list == 12 || list == 32 || list == 52)
        {
            list = list + 8;
        }
        if (p[list] >= max)
        {
            max = p[list];
            locate = list;
        }
        else
            max = max;
    }
    return locate;
}