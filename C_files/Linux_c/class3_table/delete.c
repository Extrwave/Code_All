#include "electable.h"

void delete (Electron *p)
{
    int lenth;
    int sequence, con;
    if (p->next == NULL) //ͷ���û�����ݣ����Կ�next
    {
        printf("no items to delete !");
        return;
    }
    lenth = length(p);
    Electron *p1 = p->next; //p1Ϊ��Ҫɾ���õ�
    Electron *p2 = p;       //����ɾ�������һλ
    printf("The table's length :%d \n", lenth);
    printf("Please input the sequence(\"0\" is default) of need delete:");
    fflush(stdin);
    scanf("%d", &sequence);
    if (sequence >= 0 && sequence <= lenth)
    {
        if (sequence == 0)
        {
            p1 = p->next;       //��¼����һ���ڵ�
            p->next = p1->next; //��ɾ��λ����һ�ڵ��nextָ����һ�ڵ��head
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
                p2 = p2->next; //p2��¼Ϊɾ�������һ���ڵ�
            }
            p2->next = p1->next; //��ɾ��λ����һ�ڵ��nextָ����һ�ڵ��head
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