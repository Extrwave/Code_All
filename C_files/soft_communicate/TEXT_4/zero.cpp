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

// //�ļ�ͷ������14���ֽ�
// typedef struct Header
// {
//     unsigned short bfType; //λͼ���
//     unsigned int bfSize;   //λͼ�ļ���С
//     unsigned short bfReserved1;
//     unsigned short bfReserved2;
//     unsigned int bfOffBits; //ͼ������λ��
// } FileHeader;

// //λͼ��Ϣͷ,����40�ֽ�
// typedef struct Info
// {
//     unsigned int biSize; //���ṹ�Ĵ�С�����ݲ�ͬ�Ĳ���ϵͳ����ͬ
//     int biWidth;         //BMPͼ��Ŀ�ȣ���λ����
//     int biHeight;        //BMPͼ��ĸ߶ȣ���λ����
//     unsigned short biPlanes;
//     unsigned short biBitCount;  //BMPͼ���ɫ��
//     unsigned int biCompression; //ѹ����ʽ��0��ʾ��ѹ��
//     unsigned int biSizeImage;   //BMPͼ�����ݴ�С��������4�ı�����ͼ�����ݴ�С����4�ı���ʱ��0��䲹��
//     int biXPelsPerMeter;        //ˮƽ�ֱ���
//     int biYPelsPerMeter;        //��ֱ�ֱ���
//     unsigned int biClrUsed;     //BMPͼ��ʹ�õ���ɫ
//     unsigned int biClrImportant;
// } InfoHeader;

//ͼ��ĵ�ɫ���ַ��00000036h��ʼ�洢
//��¼ͼ��Ŀ��
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
        printf("��ת�ɹ�!%d\n", k);
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

    fread(&FileHead, sizeof(BITMAPFILEHEADER), 1, fp); //ʹָ�������ļ�ͷ
    fread(&InfoHead, sizeof(BITMAPINFOHEADER), 1, fp); //��ǰλ�ÿ�ʼ��ȡ��������Ϣͷ

    Width = InfoHead.biWidth;
    Height = InfoHead.biHeight;
    BitCount = InfoHead.biBitCount;
    lineByte = (Width * BitCount / 8 + 3) / 4 * 4; //����4������4����һ�������ֽ���

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
    lineByte2 = (Height * BitCount / 8 + 3) / 4 * 4; //����4������4����һ�������ֽ���
    BmpBufOne = (unsigned char *)malloc(sizeof(unsigned char) * lineByte2 * Height);
    //�����ת

    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            unsigned char *p, *p3;
            p = (unsigned char *)(BmpBuf + lineByte * j + i);                   // ԭͼ��
            p3 = (unsigned char *)(BmpBufOne + lineByte2 * j + Height - i - 1); // ��ͼ��
            (*p3) = (*p);
        }
    }

    return 1;
}