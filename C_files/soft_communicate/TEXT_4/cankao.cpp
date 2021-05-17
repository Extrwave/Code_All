#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp = fopen("23.bmp", "rb");
    if (fp == 0)
    {
        printf("文件打开失败\n");
        return 0;
    }

    BITMAPFILEHEADER FileHead;
    BITMAPINFOHEADER InfoHead;
    fread(&FileHead, sizeof(BITMAPFILEHEADER), 1, fp);
    fread(&InfoHead, sizeof(BITMAPINFOHEADER), 1, fp);

    int width = InfoHead.biWidth;
    int height = InfoHead.biHeight;
    int biCount = InfoHead.biBitCount;
    int lineByte = (width * biCount / 8 + 3) / 4 * 4;

    RGBQUAD *pColorTable;

    pColorTable = new RGBQUAD[256];
    fread(pColorTable, sizeof(RGBQUAD), 256, fp);

    unsigned char *BmpBuf;
    BmpBuf = new unsigned char[lineByte * height];
    fread(BmpBuf, lineByte * height, 1, fp);
    fclose(fp);

    // 右旋转90
    unsigned char *BmpBuf2;
    int lineByte2 = (height * biCount / 8 + 3) / 4 * 4;

    BmpBuf2 = new unsigned char[lineByte2 * width];
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            unsigned char *p;
            p = (unsigned char *)(BmpBuf2 + lineByte2 * i + j);
            (*p) = 255;
        }
    }
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            unsigned char *p, *p3;
            p = (unsigned char *)(BmpBuf + lineByte * j + i);                 // 原图像
            p3 = (unsigned char *)(BmpBuf2 + lineByte2 * i + height - j - 1); // 新图像
            (*p3) = (*p);
        }
    }

    FILE *fpo = fopen("23_90.bmp", "wb");
    if (fpo == 0)
        return 0;

    fwrite(&FileHead, sizeof(BITMAPFILEHEADER), 1, fpo);

    BITMAPINFOHEADER InfoHead2;
    InfoHead2.biBitCount = biCount;
    InfoHead2.biClrImportant = 0;
    InfoHead2.biClrUsed = 0;
    InfoHead2.biCompression = 0;
    InfoHead2.biHeight = width;
    InfoHead2.biPlanes = 1;
    InfoHead2.biSize = 40;
    InfoHead2.biSizeImage = lineByte2 * width;
    InfoHead2.biWidth = height;
    InfoHead2.biXPelsPerMeter = 0;
    InfoHead2.biYPelsPerMeter = 0;

    fwrite(&InfoHead2, sizeof(BITMAPINFOHEADER), 1, fpo);
    fwrite(pColorTable, sizeof(RGBQUAD), 256, fpo);
    fwrite(BmpBuf2, lineByte2 * width, 1, fpo);


    fclose(fpo);

    system("pause");
    return 1;
}