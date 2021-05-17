#include "ethernet.h"

Ethernet zhen;      //读取input帧
Ethernet zhen_file; //存放合并生成的新文件帧
Ether info;         //存放写入信息帧

unsigned char DD[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
unsigned char SD[6] = {0xD0, 0xC5, 0xD3, 0xDA, 0x56, 0x7B};
unsigned char AA[7] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
unsigned char BUQI = {0xFF};
unsigned char Define = 0xAB;
unsigned char Mode[2] = {0x08, 0x88};
unsigned char Check = 0xFF;

char origin_file[10] = {"input"};
char new_file[10] = {"new_file"};
char data_file[10] = {"info.txt"};
char combine_file[20] = {"group_7_output"};
int main(void)
{
    init(zhen); //初始化帧
    init(zhen_file);
    read(origin_file, zhen);

    //这儿进行检验函数
    for (int l = 0; l < zhen[0].Count; l++)
    {
        crc8(&zhen[l], zhen[l].length);
        if (zhen[l].Current == 0)     //代表帧错误
            write(zhen[l], new_file); //将其写入new_file中
    }
    Print(zhen);
    Control_Data(&info);        //完善帧的控制信息
    ReadData(data_file, &info); //获取数据段到info里面
    //测试得出，写入数据过多原因是write函数本身造成的，不是数据源的错
    write(info, new_file);
    //以上代码测试正确，下面新增合并input与new_file文件
    //合并new_file与input
    Combine(new_file, combine_file, zhen, zhen_file);
    //在以上的代码中，input已经被读取到了zhen这个结构体数组里面，只需读取newfile到zhen_file里面，同时写入zhen与zhen_file即可
    puts("\n运行完毕，查看：");
    getchar();

    return 0;
}

void read(char *ptr, Ethernet origin)
{
    unsigned char IFAA[7];
    int value = 1; //默认设置不是前导码
    int j = -1;    //j用于记录帧个数
    FILE *fp;
    if ((fp = fopen(ptr, "rb")) == NULL)
    {
        printf("\n读取文件失败，请检查文件是否存在！\n默认位置为源码目录.");
        exit(0); //遇错退出程序
    }
    while (!feof(fp))
    {
        if (value) //不是前导码,如果不是前导码会一直执行，直到找到前导码
        {
            for (int i = 0; i < 7; i++)
                fread(&IFAA[i], 1, 1, fp); //读取7位数字，继续判断是否是前导码
            //fread函数，第一个参数是读取到哪儿，第二个参数是读取区域大小，第三参数：读取次数，最后文件指针
            value = IFaa(IFAA, AA); //判断是不是前导码
        }
        else //读取到了前导码
        {
            fseek(fp, -7, SEEK_CUR); //将文件指针回归到前导码开始之前
            //设定j为负一，读取到前导码意味着新帧的开始 +1
            readDetail(fp, origin, ++j); //fp为当前文件指针位置，origin，j为帧序列标记
        }

        //frea函数读取块之后，文件指针已经在下一个数据的地方了，不需要手动移动
        //fseek(fp, 1, SEEK_CUR); //定位偏移，每次后移一位进行签前导码判断
    }
    fclose(fp);
} //读取这块还有个问题，就是如果fread读取到文件尾之后，会返回怎样的值，如果读取7个读取到了下一个帧的前导码咋办？

void readDetail(FILE *fp, Ethernet origin, int locate)
{
    if (!feof(fp)) //用于递归函数进入时判断是否已经到达文件尾
    {
        int k = 0;
        unsigned char IFAA[7];
        origin[0].Count = locate + 1; //记录帧数
        number = locate + 1;          //记录帧数，没啥用,代码迭代保留以防 BUG
        for (k = 0; k < sizeof(origin[locate].QDM); k++)
            fread(&origin[locate].QDM[k], 1, 1, fp); //读取前导码
        fread(&origin[locate].Define, 1, 1, fp);     //读取帧前定界符
        for (k = 0; k < sizeof(origin[locate].Daddre); k++)
            fread(&origin[locate].Daddre[k], 1, 1, fp); //读取目的MAC
        for (k = 0; k < sizeof(origin[locate].Saddre); k++)
            fread(&origin[locate].Saddre[k], 1, 1, fp); //读取源址MAC
        for (k = 0; k < sizeof(origin[locate].Mode); k++)
            fread(&origin[locate].Mode[k], 1, 1, fp);

        //获取数据段
        int Dnum = 0; //记录数据段位数，包括赋值用得上

        while (!feof(fp))
        {
            for (k = 0; k < sizeof(origin[locate].QDM); k++)
                fread(&IFAA[k], 1, 1, fp);
            if (!(IFaa(IFAA, AA))) //如果读取到了下一帧的前导码，新帧的开始
            {
                // 用下一帧前的第一位作为本帧的校验码
                Dnum -= 1;
                origin[locate].Check = origin[locate].Detail[Dnum];
                //将赋值的校验码清除

                origin[locate].Detail[Dnum] = '\0';
                //fseek(fp, -8, SEEK_CUR); //指针退回到校验值前
                //fread(&origin[locate].Check, 1, 1, fp);
                //将帧的个数增加一个，方便写入
                fseek(fp, -7, SEEK_CUR);
                origin[locate].length = Dnum;
                readDetail(fp, origin, ++locate);
            }
            else //读取到的字符不是前导码
            {
                if (feof(fp)) //如果已经读取到了文件末尾,此时IFAA里面6位数据，最后一位是文件尾指针
                {
                    //printf("最后几位是:");
                    for (k = 0; k < 5; k++)
                    {
                        //1-5位赋值给数据流
                        origin[locate].Detail[Dnum] = IFAA[k];
                        //printf("%c ", origin[locate].Detail[Dnum]);
                        Dnum++;
                    }
                    origin[locate].length = Dnum;
                    //这儿中途忘记赋值了，最后printf看不到结果，还以为是文件指针末尾的问题处理错了
                    //第一次BUG就是只显示三帧，结果检查出来也是printf时候循环数量少了一次，浪费了许多时间。。。。。。无语
                    //printf("\n校验码是:");
                    for (k = 5; k < 6; k++)
                    {
                        // 将IFAA第6位赋值给校验码
                        origin[locate].Check = IFAA[k];
                        //printf("%X", origin[locate].Check);
                        return;
                    }
                }
                origin[locate].Detail[Dnum] = IFAA[0];
                fseek(fp, -6, SEEK_CUR); //将文件指针偏移回去6位，因为只写入了一位,一次只写入一个字节（7个中的第一个）
                Dnum++;
            } //则把读取到的7个字节第一个赋给数据段，这样一来如果读取到了下一帧的前导码，前导码也不会被写入数据段中
        }
    }
    return;
}

int IFaa(unsigned char *a1, unsigned char *a2)
{
    int iff = 0;
    for (int i = 0; i < 7; i++)
    {
        if (a1[i] != a2[i])
        {
            iff = 1;
            return iff;
        }
    }
    return iff;
}

void Print(Ethernet origin)
{
    int i = 0, j = 0;
    for (i = 0; i < origin[0].Count; i++)
    {
        printf("\n序号：%d\n", i + 1);
        printf("前导码：");
        for (j = 0; j < sizeof(origin[i].QDM); j++)
        {
            printf("%X ", origin[i].QDM[j]);
        }
        printf("\n帧前定界符：%X", origin[i].Define);
        printf("\n目的地址DA：");
        for (j = 0; j < sizeof(origin[i].Daddre); j++)
        {
            printf("%X ", origin[i].Daddre[j]);
        }
        printf("\n源地址SA：");
        for (j = 0; j < sizeof(origin[i].Saddre); j++)
        {
            printf("%X ", origin[i].Saddre[j]);
        }
        printf("\n类型字段：");
        for (j = 0; j < sizeof(origin[i].Mode); j++)
        {
            printf("%X ", origin[i].Mode[j]);
        }
        printf("\n数据字段：");
        for (j = 0; j < origin[i].length; j++)
        {
            printf("%c", origin[i].Detail[j]);
        }
        printf("\nCRC校验：%X", origin[i].Check);
        //
        if (origin[i].Current == 0)
            printf("\nCRC检验帧错误：应为%X", origin[i].RCheck);
        else
            printf("\nCRC校验帧正确！");
        printf("\n\n");
    }
}

void write(Ether origin, char *str)
{
    int k = 0;
    FILE *fpp;
    if ((fpp = fopen(str, "ab+")) == NULL)
        printf("创建文件失败！");
    fflush(stdout);
    fflush(stdin);
    fwrite(&origin.QDM[k], sizeof(origin.QDM), 1, fpp);       //写入前导码
    fwrite(&origin.Define, 1, 1, fpp);                        //写入帧前定界符
    fwrite(&origin.Daddre[k], sizeof(origin.Daddre), 1, fpp); //写入目的MAC
    fwrite(&origin.Saddre[k], sizeof(origin.Saddre), 1, fpp); //写入源址MAC
    fwrite(&origin.Mode, sizeof(origin.Mode), 1, fpp);        //写入协议模式
    fwrite(&origin.Detail[k], origin.length, 1, fpp);         //写入数据
    fclose(fpp);
}

void Control_Data(Ether *origin)
{
    int i;
    origin->Count = 1; //用于打印输出控制循环
    for (i = 0; i < sizeof(AA); i++)
        origin->QDM[i] = AA[i]; //完善前导码
    origin->Define = Define;    //完善帧前定界符
    for (i = 0; i < sizeof(DD); i++)
        origin->Daddre[i] = DD[i]; //完善目的地址
    for (i = 0; i < sizeof(DD); i++)
        origin->Saddre[i] = SD[i]; //完善源地址
    for (i = 0; i < sizeof(Mode); i++)
        origin->Mode[i] = Mode[i]; //完善协议
    origin->Check = Check;         //完善校验码
}

void ReadData(char *ptr, Ether *origin) //ptr文件名，origin是存放结构体
{
    int i = 0;
    FILE *tp;
    if ((tp = fopen(ptr, "r")) == NULL)
        printf("打开文件失败！");
    for (i = 0; !feof(tp); i++)
        fread(&origin->Detail[i], 1, 1, tp);
    fclose(tp);
    while (i <= 46) //补齐不足46字节的信息
    {
        origin->Detail[i] = BUQI;
        i++;
    }
    origin->length = i + 1;
}

void init(Ethernet origin)
{
    int j;
    for (int i = 0; i < MAX; i++)
    {
        for (j = 0; j < sizeof(origin[i].QDM); j++)
            origin[i].QDM[j] = '\0';
        origin[i].Define = '\0';
        for (j = 0; j < sizeof(origin[i].Daddre); j++)
            origin[i].Daddre[j] = '\0';
        for (j = 0; j < sizeof(origin[i].Saddre); j++)
            origin[i].Saddre[j] = '\0';
        for (j = 0; j < sizeof(origin[i].Mode); j++)
            origin[i].Mode[j] = '\0';
        for (j = 0; j < sizeof(origin[i].Detail); j++)
            origin[i].Detail[j] = '\0';
    }
}

void Combine(char *file, char *new, Ethernet origin_zhen, Ethernet new_zhen)
{
    int i = 0;
    read(file, new_zhen);
    //Print(zhen_file);
    for (i = 0; i < origin_zhen[0].Count; i++)
        write(origin_zhen[i], new);
    for (i = 0; i < origin_zhen[0].Count + 1; i++)
        write(new_zhen[i], new);
    printf("结合文件写入到Group文件完成！");
}

unsigned char crc8(Ether *origin, int len)
{
    unsigned char *ptr;
    ptr = (unsigned char *)(&origin->Daddre[0]);

    unsigned char crc = 0X00; /* 计算的初始crc值 */

    // for (int k = 0; k < len + 14; k++, *ptr++)
    //     printf("%c ", *ptr);
    // printf("\n\n");

    for (int j = 0; j < len + 14; j++)
    {
        //printf("%X ", crc);
        crc ^= *ptr;
        ptr++;                      /* 每次先与需要计算的数据异或,计算完指向下一数据 */
        for (int i = 8; i > 0; --i) /* 下面这段计算过程与计算一个字节crc一样 */
        {
            if (crc & 0x80)
                crc = (crc << 1) ^ 0x07;
            else
                crc = (crc << 1);
        }
    }
    // len += 14 - 1;
    // while (len--)
    // {
    //     crc ^= (*ptr++);            /* 每次先与需要计算的数据异或,计算完指向下一数据 */
    //     for (int i = 8; i > 0; i--) /* 下面这段计算过程与计算一个字节crc一样 */
    //     {
    //         if (crc & 0x80) /* 判断最高位是否为1 */
    //         {
    //             crc = crc << 1;
    //             crc ^= 0x07;
    //         }
    //         /* 最高位为1，不需要异或，往左移一位，然后与0x31异或 */
    //         /* 0x31(多项式：x8+x5+x4+1，100110001)，最高位不需要异或，直接去掉 */
    //         else
    //         {
    //             crc = crc << 1; /* 最高位为0时，不需要异或，整体数据往左移一位 */
    //         }
    //     }
    // }
    if (crc != origin->Check)
    {
        origin->RCheck = crc;
        origin->Current = 0;
        return crc;
    }
    else
    {
        origin->Current = 1;
        return crc;
    }
}