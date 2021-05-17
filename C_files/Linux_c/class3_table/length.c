#include "electable.h"

int length(Electron *p)
{
    int number = -1; //因为头结点不算是一个数据
    while (p != NULL)
    {
        p = p->next;
        number++;
    }
    return number;
}
