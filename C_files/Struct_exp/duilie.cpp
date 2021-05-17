
/*用队列模拟服务台前的排队现象问题

求出业务员空闲时间 客户平均等待时间*/

#include <stdio.h>
#include <stdlib.h>

typedef struct
{

    int arrive; //到达时间
    int treat;  //需要占用的时间
} QNODE;

typedef struct node
{
    QNODE data;
    struct node *next;
} LNODE;

LNODE *front, *rear;

void InQueue(QNODE e)
{

    LNODE *p = (LNODE *)malloc(sizeof(LNODE));

    p->data = e;

    p->next = NULL;

    if (!front)

        front = rear = p;

    else

        rear = rear->next = p;
}

int OutQueue(QNODE *e)

{

    LNODE *delp;

    if (!front)

        return 0; //队空

    *e = front->data;

    delp = front;

    front = front->next;

    if (!front)

        rear = NULL;

    free(delp);

    return 1;
}

int main()

{

    char Fname[120]; //读取文件的文件名

    FILE *fp;

    QNODE temp, curr;

    //dwait业务员总的空闲时间 clock当前时间 wait客户总的等待时间

    //cout客户总数

    int have = 0, dwait = 0, clock = 0, wait = 0, count = 0, finish;

    if ((fp = fopen("wenben.txt", "r")) == NULL)

    {

        printf("open file error!");

        return 0;
    }

    front = rear = NULL;               //初始化队列

    have = fscanf(fp, "%d %d", &temp.arrive, &temp.treat);

    do
    {

        if (!front && !(have - 2))

        {

            dwait += temp.arrive - clock;

            clock = temp.arrive;

            InQueue(temp);

            have = fscanf(fp, "%d %d", &temp.arrive, &temp.treat);
        }

        count++;

        OutQueue(&curr);

        wait += (clock - curr.arrive);

        finish = clock + curr.treat;

        while (!(have - 2) && temp.arrive <= finish)

        {

            InQueue(temp);

            have = fscanf(fp, "%d %d", &temp.arrive, &temp.treat);
        }

        clock = finish;

    } while (!(have - 2) || front);

    printf(" worker wait time: %d\n customer wait time average: %f\n", dwait, (double)wait / count);

    printf(" all time: %d\n number of customer: %d\n all wait time: %d\n", clock, count, wait);

    return 0;
}
