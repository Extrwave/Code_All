#include "stdio.h"
#include "math.h"
#include"stdlib.h"

typedef int KeyType;
#define MAXSIZE 10000 /* 用于要排序数组个数最大值，可根据需要修改 */

typedef struct
{
    int key;
    int length = 0; /* 用于记录顺序表的长度 */
} Node;

typedef Node SeqList[MAXSIZE];

int Input(SeqList R, KeyType k)
{
    R->length++;
    R[R->length-1].key = k;
    return 0;
}

int Length(SeqList R)
{
    return R->length;
}

int SeqSearch(SeqList R, int n, KeyType k)
{
    int i = 0;
    while (i < n && R[i].key != k)
    {
        //printf("%d", R[i].key);
        i++;
    }
    if (i >= n)
    {
        printf("NO FIND !");
        return -1;
    }
    else
    {
        printf("FINGING : %d in the %dth location", R[i].key, i+1);
        return i;
    }
}

int BinSearch(SeqList R, int n, KeyType k)
{
    int low = 0, high = n - 1, mid, count = 0;
    while (low <= high)
    {
        mid = (low + high) / 2;
        printf("第%d次查找：在[ %d ,%d ]中找到元素R[%d]:%d\n ", ++count, low, high, mid, R[mid].key);
        if (R[mid].key == k)
        {
            printf("\nFINDING ! ");
            return mid;
        }
        if (R[mid].key > k)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

int main()
{
    int i;
    int number; //用于顺序的折半查找
    int arr[MAXSIZE]={11,21,31,41,51,61,71,81};
    SeqList R, S;
    for (i = 0; i < 8; i++)
    {
        Input(R, arr[i]);   
    }
    printf("\nPlease input the number need to find:  ");
    scanf("%d", &number);
    SeqSearch(R, Length(R), number);

    //二分法

    for (i = 0; i < 8; i++)
    {
        Input(S, arr[i]);   
    }
    printf("\nPlease input the number need to find:  ");
    scanf("%d", &number);
    BinSearch(S, Length(S), number);
    system("pause");
    return 0;
}
