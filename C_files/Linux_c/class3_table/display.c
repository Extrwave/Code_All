#include "electable.h"

void display(Electron *p)
{
    while (p->next != NULL) //��Ϊ���ǵ�ͷ���û������
    {
        printf("\t%ld\t%d\t%s\n", p->next->number, p->next->vaule, p->next->address);
        p = p->next;
    }
    printf("Electronic Table is all !");
    printf("Any key to quit !");
    fflush(stdin);
    getchar();
    return;
}
