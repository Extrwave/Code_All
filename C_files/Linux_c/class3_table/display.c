#include "electable.h"

void display(Electron *p)
{
    while (p->next != NULL) //因为考虑到头结点没有数据
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
