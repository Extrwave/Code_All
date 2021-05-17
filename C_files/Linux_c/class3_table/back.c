#include "electable.h"

int back()
{
    char b = 'w';
    while (b != 'q')
    {
        printf("Please press \"q\" to quit , and any key to continue:");
        fflush(stdin);
        b = getchar();
        if (b == 'q')
            return 0;
        else
        {
            printf("Input invalid !\n");
            return 1;
        }
    }
}