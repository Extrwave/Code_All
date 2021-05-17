#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#define MAX 20 //Դ�ļ�����ֻ����֡�����ﶨ��20��

extern unsigned char DD[6];
extern unsigned char SD[6];
extern unsigned char AA[7];
extern unsigned char BUQI;
extern unsigned char Define;
extern unsigned char Mode[2];
extern unsigned char Check;
int number; //��¼֡�ĸ�������Ϊ�ݹ麯������ֵ������
typedef struct zhen
{
    int Count;                  //֡���ܸ�����ֻ�ڵ�һ֡��¼
    unsigned char QDM[7];       //֡��ǰ����
    unsigned char Define;       //֡ǰ�����
    unsigned char Daddre[6];    //Ŀ�ĵ�ַ
    unsigned char Saddre[6];    //Դ��ַ
    unsigned char Mode[2];      //Э������
    unsigned char Detail[1500]; //���ݶ�
    unsigned int length;        //���ݶ���ʵ����
    unsigned char Check;        //������˵����λ�������ʵ������Ѷȣ�Ϊ1λ
    unsigned char RCheck;       //�������check
    int Current;                //��ȷ���
} Ethernet[MAX], Ether;         //��ʽ��������������򵥵Ŀ���ֱ��������

#ifndef ETHERNET_H
#define ETHERNET_H
void init(Ethernet origin);                                                   //��ʼ��
void read(char *ptr, Ethernet origin);                                        //��ȡ֡
void write(Ether origin, char *str);                                          //д��֡
int IFaa(unsigned char *a1, unsigned char *a2);                               //�ж��ǲ���֡ǰ�����
void Control_Data(Ether *origin);                                             //��ֵд��֡��Ϣ��֡������Ϣ
void Combine(char *file, char *new, Ethernet origin_zhen, Ethernet new_zhen); //�ϲ������ļ�
void ReadData(char *ptr, Ether *origin);                                      //��ȡ��Ա��Ϣ
void readDetail(FILE *fp, Ethernet origin, int locate);                       //��ȡ֡���ݶ�
void Print(Ethernet origin);                                                  //��ʾ����ȡ��֡
unsigned char crc8(Ether *origin, int len);
#endif //ETHERNET_H