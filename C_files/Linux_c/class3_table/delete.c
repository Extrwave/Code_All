#include "electable.h"

void delete (Electron *p)
{
    int lenth;
    int sequence, con;
    if (p->next == NULL) //头结点没有数据，所以看next
    {
        printf("no items to delete !");
        return;
    }
    lenth = length(p);
    Electron *p1 = p->next; //p1为需要删除得点
    Electron *p2 = p;       //用于删除点的上一位
    printf("The table's length :%d \n", lenth);
    printf("Please input the sequence(\"0\" is default) of need delete:");
    fflush(stdin);
    scanf("%d", &sequence);
    if (sequence >= 0 && sequence <= lenth)
    {
        if (sequence == 0)
        {
            p1 = p->next;       //记录到第一个节点
            p->next = p1->next; //将删除位置上一节点的next指向下一节点的head
            printf("\t%ld\t%d\t%s has been delete !\n", p1->number, p1->vaule, p1->address);
            free(p1);
        }
        else if (sequence < 1)
        {
            printf("Input Error !");
        }
        else
        {
            for (int i = 1; i < sequence; i++)
            {
                p1 = p1->next;
                p2 = p2->next; //p2记录为删除点的上一个节点
            }
            p2->next = p1->next; //将删除位置上一节点的next指向下一节点的head
            printf("\t%ld\t%d\t%s has been delete !\n", p1->number, p1->vaule, p1->address);
            free(p1);
        }
        con = back();
        if (con)
            insert(p);
        return;
    }
    else
    {
        printf("Input error !");
        con = back();
        if (con)
            delete (p);
        return;
    }
}