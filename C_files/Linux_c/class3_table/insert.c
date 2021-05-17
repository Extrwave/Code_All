#include "electable.h"

void insert(Electron *p)
{
    int lenth;
    int sequence, con;
    Electron *p1, *p2;
    p2 = p;
    lenth = length(p);
    printf("The table's length :%d \n", lenth);
    printf("Please input the insert (\"0\" is default) sequence :");
    fflush(stdin);
    scanf("%d", &sequence);
    if (sequence >= 0 && sequence <= lenth)
    {
        p1 = (Electron *)malloc(sizeof(Electron)); //生成的节点
        //0 默认头插
        if (sequence == 0)
        {
            p1->next = p2->next;
            p2->next = p1; //完成链表的插入

            printf("Please enter the number:");
            fflush(stdin);
            scanf("%ld", &p1->number);
            printf("Please enter the vaule:");
            fflush(stdin);
            scanf("%d", &p1->vaule);
            printf("Please enter the address:");
            fflush(stdin);
            scanf("%s", p1->address);
            printf("\t%ld\t%d\t%s has been inserted !\n", p1->number, p1->vaule, p1->address);
        }
        else if (sequence < 0)
        {
            printf("Input Error !");
        }
        else
        {
            for (int i = 0; i < sequence; i++)
            {
                p2 = p2->next;
            }

            p1->next = p2->next;
            p2->next = p1; //完成链表的插入

            printf("Please enter the number:");
            fflush(stdin);
            scanf("%ld", &p1->number);
            printf("Please enter the vaule:");
            fflush(stdin);
            scanf("%d", &p1->vaule);
            printf("Please enter the address:");
            fflush(stdin);
            scanf("%s", p1->address);
            printf("\t%ld\t%d\t%s has been inserted !\n", p1->number, p1->vaule, p1->address);
        }
        con = back();
        if (con)
            insert(p);
        return;
    }
    else
    {
        printf("Input error !\n");
        con = back();
        if (con)
            insert(p);
        return;
    }
}