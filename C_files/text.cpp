#include "string.h"
#include "stdio.h"

typedef struct C
{
    char brand[4];
    long length;
    long wideth;
    long weight;
} CAR;

int main()
{
    CAR message = {"BWM", 4, 2, 1600};
    // char str[4] = "BWM";
    // CAR message;
    // strcpy(message.brand, str);
    // message.length = 4;
    // message.wideth = 2;
    // message.weight = 1600;
    // ²âÊÔÐÞ¸ÄGIT
    printf("brand=%s,length=%d,wideth=%d,weight=%d", message.brand, message.length, message.wideth, message.weight);
    return 0;
}