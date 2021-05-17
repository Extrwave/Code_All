#include "electable.h"

Electron *creat()
{
    Electron *head;
    head = (Electron *)malloc(sizeof(Electron));
    head->next = NULL;
    return head;
}