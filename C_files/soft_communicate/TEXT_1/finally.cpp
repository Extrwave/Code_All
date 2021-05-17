#include "time.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"

#define A 16000
#define B 51
#define C 3

float Calculation(float *ptr1, float *ptr2, int i);
int F_Calculation(float *ptr1, float *ptr2, float *mtr1, float *mtr2, int number, int number2, int *locate, float *max, int llist);
int Read(float *ptr1, float *ptr2, int list);
int Read_Max(float *ptr1, float *ptr2, int i);
int ReadPSS(float *ptr1, float *ptr2, int list);
void Files(char *str, int i);
void FilesPSS(char *str, int i);
int Maxim(float *p);

int main()
{
    double start = clock();
    int list, m_locate, list_p;
    int number;
    int number2;
    //ï¿½ï¿½Â¼ï¿½ï¿½ï¿½Ý¸ï¿½ï¿½ï¿½
    float F_max = 0;
    float a1[A], a2[A], consult[B], p_max[B];
    int match[C], p_locate[B];
    float max[A], maxi[A];

    //a1[]Îªï¿½Åºï¿½ï¿½ï¿½ï¿½Ýµï¿½Êµï¿½ï¿½ï¿½ï¿½a2[]Îªï¿½é²¿  consult[]Îªï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ýµï¿½ï¿½Åºï¿½Ç¿ï¿½ï¿½
    //maxÎªÊµï¿½ï¿½ï¿½ï¿½Ç¿ï¿½Åºï¿½ï¿½ï¿½ï¿½ï¿½Êµï¿½ï¿½ï¿½ï¿½maxiÎªï¿½é²¿

    for (list = 0; list <= 71; list++)
    {
        if (list == 12 || list == 32 || list == 52)
        {
            list = list + 8;
        }
        number = Read(a1, a2, list);
        consult[list] = Calculation(a1, a2, number);
        //printf("data%d.txtï¿½Åºï¿½Ç¿ï¿½ï¿½Îª %.6f\n", list, consult[list]);
    }

    //ï¿½Ò³ï¿½ï¿½ï¿½Ç¿ï¿½ï¿½Ò»ï¿½ï¿½
    m_locate = Maxim(consult);
    printf("×îÇ¿ÐÅºÅ×éÎª%d Ç¿¶ÈÎª%f\n", m_locate, consult[m_locate]);

    //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ò³ï¿½Æ¥ï¿½ï¿½ï¿??
    //ï¿½ï¿½È¡ï¿½ï¿½Ç¿ï¿½Åºï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½max
    for (list_p = 0; list_p < 3; list_p++)
    {
        number2 = ReadPSS(a1, a2, list_p);
        //¶ÁÈ¡µÄÊÇ»¬¶¯¼ÆËãÆ¥ÅäpssµÄÖµ½øÈëa1£¬a2
        for (list = 0; list <= 71; list++)
        {
            if (list == 12 || list == 32 || list == 52)
            {
                list = list + 8;
            }
            number = Read(max, maxi, list);
            //¶ÁÈ¡³öÃ¿Ò»¸öÐÅºÅµÄÖµ½øÈëmax£¬Ô­ÏÈ¶¨ÒåµÄÃû×Ö£¬´ÕºÏ×ÅÓÃÁË
            F_Calculation(a1, a2, max, maxi, number2, number, p_locate, p_max, list);
            //printf(" ÆäµÚ%d×éÆ¥ÅäÇ¿¶ÈÎª %d \n", list, match[list]);
            //½ØÖ¹Õâ¶ù£¬pssÒÑ¾­Íê³ÉÒ»´Î»¬¶¯¼ÆËã£¬²¢½«Ã¿Ò»ÌõÐÅºÅ×î´óÖµ¼ÇÂ¼ÔÚp_maxÖÐ
        }
        m_locate = Maxim(p_max);
        printf("¼ì²â×é %d ×î´óÏà¹ØÏµÊýÊÇ data%d µÚ %d ×é£¬ÖµÎª %f\n", list_p, m_locate, p_locate[m_locate], p_max[m_locate]);
    }
    double finish = clock();
    double duration = (double)(finish - start) / 1000;
    printf("\n\t×ÜÓÃÊ±£º%f seconds\n", duration);

    system("pause");
    return 0;
}

/************************************************************************/

//ï¿½ï¿½ï¿½ï¿½ï¿½Åºï¿½Ç¿ï¿½ï¿½
float Calculation(float *ptr1, float *ptr2, int i)
{
    int j;
    float consult = 0, n;
    for (j = 0; j < i; j++, ptr1++, ptr2++)
    {
        n = pow(*ptr1, 2.0) + pow(*ptr2, 2.0);
        //printf("ï¿½Åºï¿½Ç¿ï¿½ï¿½ %d = %f\n", j, n);
        consult += n;
    }
    return consult;
}

//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
int F_Calculation(float *ptr1, float *ptr2, float *mtr1, float *mtr2, int number2, int number, int *locate, float *max, int llist)
{

    float mean[A], Max;
    int i, j;
    int location = 0;
    for (i = 0; i <= number - number2; i++)
    {

        float ch = 0, chi = 0;
        for (j = 0; j < number2; j++)
        {
            ch += ptr1[j] * mtr1[j + i] + ptr2[j] * mtr2[j + i];  //Êµï¿½ï¿½ï¿½ï¿½ï¿??
            chi += ptr1[j] * mtr2[j + i] + ptr2[j] * mtr1[j + i]; //ï¿½é²¿ï¿½ï¿½ï¿??
        }
        mean[i] = pow(ch, 2) + pow(chi, 2); //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ã³ï¿½Öµï¿½ï¿½Ä£
    }
    Max = mean[0];
    for (i = 0; i < number - number2; i++)
    {
        if (mean[i] >= Max)
        {
            Max = mean[i];
            location = i;
        }
        else
            Max = Max;
    }
    max[llist] = Max;
    locate[llist] = location;
    return 0;
}

//ï¿½ï¿½È¡ï¿½ï¿½ï¿½ï¿½
int Read(float *ptr1, float *ptr2, int list)
{
    FILE *fp;

    int i = 0;
    int j;

    char str[60];
    Files(str, list);

    //Ö»ï¿½ï¿½ï¿½ï¿½Ê½ï¿½ï¿½ï¿½Ä¼ï¿½
    if ((fp = fopen(str, "r")) == NULL)
    {
        printf("open files fail!");
        exit(0);
    }
    //ï¿½ï¿½ï¿½Ä¼ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ý´ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½

    while (!feof(fp))
    {
        fscanf(fp, "%f", ptr1);
        fscanf(fp, "%f", ptr2);
        ptr1++;
        ptr2++;
        i++;
    }

    //ï¿½Ø±ï¿½ï¿½Ä¼ï¿½
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

    //Ö»ï¿½ï¿½ï¿½ï¿½Ê½ï¿½ï¿½ï¿½Ä¼ï¿½
    if ((fp = fopen(str, "r")) == NULL)
    {
        printf("open files fail!");
        exit(0);
    }
    //ï¿½ï¿½ï¿½Ä¼ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ý´ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½

    while (!feof(fp))
    {
        fscanf(fp, "%f", ptr1);
        fscanf(fp, "%f", ptr2);
        ptr1++;
        ptr2++;
        i++;
    }

    //ï¿½Ø±ï¿½ï¿½Ä¼ï¿½
    j = fclose(fp);
    if (j != 0)
        printf("close files fail!\n");

    return i;
}

/*
int Read_Max(float *ptr1, float *ptr2, int i)
{
    FILE *f;
    int number = 0, j;
    char str[B];
    //Ö»ï¿½ï¿½ï¿½ï¿½Ê½ï¿½ï¿½ï¿½Ä¼ï¿½
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

*/
//
void Files(char *str, int i)
{
    sprintf(str, "F:/AEx_Code/C_files/soft_communicate/TEXT_1/class_data_1/data%d.txt", i);
}

//
void FilesPSS(char *str, int i)
{
    sprintf(str, "F:/AEx_Code/C_files/soft_communicate/TEXT_1/class_data_1/PSS%d.txt", i);
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