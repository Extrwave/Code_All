#include "electable.h"

int length(Electron *p)
{
    int number = -1; //��Ϊͷ��㲻����һ������
    while (p != NULL)
    {
        p = p->next;
        number++;
    }
    return number;
}
