#include "stdio.h"
#include "Windows.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"
#define MAX_LINE 16
#define MAX 25000

unsigned char *ReadImage();
int SaveImage(unsigned char *BmpBuf);
int Span();

// //文件头，共计14个字节
// typedef struct Header
// {
//     unsigned short bfType; //位图类别
//     unsigned int bfSize;   //位图文件大小
//     unsigned short bfReserved1;
//     unsigned short bfReserved2;
//     unsigned int bfOffBits; //图像数据位置
// } FileHeader;

// //位图信息头,共计40字节
// typedef struct Info
// {
//     unsigned int biSize; //本结构的大小，根据不同的操作系统而不同
//     int biWidth;         //BMP图像的宽度，单位像素
//     int biHeight;        //BMP图像的高度，单位像素
//     unsigned short biPlanes;
//     unsigned short biBitCount;  //BMP图像的色深
//     unsigned int biCompression; //压缩方式，0表示不压缩
//     unsigned int biSizeImage;   //BMP图像数据大小，必须是4的倍数，图像数据大小不是4的倍数时用0填充补足
//     int biXPelsPerMeter;        //水平分辨率
//     int biYPelsPerMeter;        //垂直分辨率
//     unsigned int biClrUsed;     //BMP图像使用的颜色
//     unsigned int biClrImportant;
// } InfoHeader;

//图像的调色板地址从00000036h开始存储
//记录图像的宽高
int Width = 0, Widthback, Widthsky;
int Height = 0, Heightback, Heightsky;
int BitCount, BitCountback, BitCountsky;
unsigned char *BmpBuf, *BmpBufOne;
int lineByte2, lineByte;

int main()
{
    int i, j, k;
    long int size;
    unsigned int ch, sh[MAX_LINE];
    ReadImage();
    printf("width = %d, height = %d \n", Width, Height);
    k = Span();
    if (k == 1)
        printf("旋转成功!%d\n", k);
    SaveImage(BmpBufOne);
    free(BmpBuf);
    free(BmpBufOne);

    system("pause");
    return 0;
}

unsigned char *ReadImage()
{
    FILE *fp;
    if ((fp = fopen("F:/AEx_Code/C_files/soft_communicate/TEXT_4/24.bmp", "rb")) == NULL)
    {
        printf("ERROR !\n");
        exit(0);
    }
    BITMAPFILEHEADER FileHead;
    BITMAPINFOHEADER InfoHead;

    fread(&FileHead, sizeof(BITMAPFILEHEADER), 1, fp); //使指针跳过文件头
    fread(&InfoHead, sizeof(BITMAPINFOHEADER), 1, fp); //当前位置开始读取，读入信息头

    Width = InfoHead.biWidth;
    Height = InfoHead.biHeight;
    BitCount = InfoHead.biBitCount;
    lineByte = (Width * BitCount / 8 + 3) / 4 * 4; //不足4个补足4个，一行所暂字节数

    BmpBuf = (unsigned char *)malloc(sizeof(unsigned char) * lineByte * Height);
    fread(BmpBuf, lineByte * Height, 1, fp);
    fclose(fp);

    return BmpBuf;
}

int SaveImage(unsigned char *BmpBuf)
{
    FILE *wp;
    if ((wp = fopen("F:/AEx_Code/C_files/soft_communicate/TEXT_4/24_span.bmp", "wb")) == NULL)
    {
        printf("ERROR !\n");
        exit(0);
    }

    BITMAPFILEHEADER FileHead;
    BITMAPINFOHEADER infoHead;
    FileHead.bfType = 0x4d42;
    fwrite(&FileHead, sizeof(BITMAPFILEHEADER), 1, wp);

    infoHead.biBitCount = BitCount;
    infoHead.biClrImportant = 0;
    infoHead.biClrUsed = 0;
    infoHead.biCompression = 0;
    infoHead.biHeight = Width;
    infoHead.biPlanes = 1;
    infoHead.biSize = 40;
    infoHead.biSizeImage = lineByte2 * Height;
    infoHead.biWidth = Height;
    infoHead.biXPelsPerMeter = 0;
    infoHead.biYPelsPerMeter = 0;

    fwrite(&infoHead, sizeof(BITMAPINFOHEADER), 1, wp);
    fwrite(BmpBufOne, Width * lineByte2, 1, wp);

    fclose(wp);

    return 0;
}

int Span()
{
    int i, j;
    lineByte2 = (Height * BitCount / 8 + 3) / 4 * 4; //不足4个补足4个，一行所暂字节数
    BmpBufOne = (unsigned char *)malloc(sizeof(unsigned char) * lineByte2 * Height);
    //完成旋转

    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            unsigned char *p, *p3;
            p = (unsigned char *)(BmpBuf + lineByte * j + i);                   // 原图像
            p3 = (unsigned char *)(BmpBufOne + lineByte2 * j + Height - i - 1); // 新图像
            (*p3) = (*p);
        }
    }

    return 1;
}