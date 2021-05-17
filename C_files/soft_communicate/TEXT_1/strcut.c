#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"

void Files(char *str, int i)
{
    sprintf(str, "F:\\CDGL\\con_soft_B\\class_data_1\\data%d.txt", i);
}

int main()
{
    int i;
    char str[60];
    for (i = 0; i < 3; i++)
    {
        Files(str, i);
        puts(str);
         Files(str, i);
         puts(str);
        
    }
    system("pause");
    return 0;
}
