#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#define MAX 20 //源文件好像只有四帧，这里定义20吧

extern unsigned char DD[6];
extern unsigned char SD[6];
extern unsigned char AA[7];
extern unsigned char BUQI;
extern unsigned char Define;
extern unsigned char Mode[2];
extern unsigned char Check;
int number; //记录帧的个数，因为递归函数返回值不好整
typedef struct zhen
{
    int Count;                  //帧的总个数，只在第一帧记录
    unsigned char QDM[7];       //帧的前导码
    unsigned char Define;       //帧前定界符
    unsigned char Daddre[6];    //目的地址
    unsigned char Saddre[6];    //源地址
    unsigned char Mode[2];      //协议类型
    unsigned char Detail[1500]; //数据段
    unsigned int length;        //数据端真实长度
    unsigned char Check;        //正常来说是四位，但这次实验减轻难度，为1位
    unsigned char RCheck;       //更正后的check
    int Current;                //正确与否
} Ethernet[MAX], Ether;         //正式可以用链表，这里简单的可以直接用数组

#ifndef ETHERNET_H
#define ETHERNET_H
void init(Ethernet origin);                                                   //初始化
void read(char *ptr, Ethernet origin);                                        //读取帧
void write(Ether origin, char *str);                                          //写入帧
int IFaa(unsigned char *a1, unsigned char *a2);                               //判断是不是帧前定界符
void Control_Data(Ether *origin);                                             //赋值写入帧信息的帧控制信息
void Combine(char *file, char *new, Ethernet origin_zhen, Ethernet new_zhen); //合并两个文件
void ReadData(char *ptr, Ether *origin);                                      //获取组员信息
void readDetail(FILE *fp, Ethernet origin, int locate);                       //读取帧数据段
void Print(Ethernet origin);                                                  //显示出读取的帧
unsigned char crc8(Ether *origin, int len);
#endif //ETHERNET_H