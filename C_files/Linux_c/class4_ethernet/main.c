#include "ethernet.h"

Ethernet zhen;      //��ȡinput֡
Ethernet zhen_file; //��źϲ����ɵ����ļ�֡
Ether info;         //���д����Ϣ֡

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
    init(zhen); //��ʼ��֡
    init(zhen_file);
    read(origin_file, zhen);

    //������м��麯��
    for (int l = 0; l < zhen[0].Count; l++)
    {
        crc8(&zhen[l], zhen[l].length);
        if (zhen[l].Current == 0)     //����֡����
            write(zhen[l], new_file); //����д��new_file��
    }
    Print(zhen);
    Control_Data(&info);        //����֡�Ŀ�����Ϣ
    ReadData(data_file, &info); //��ȡ���ݶε�info����
    //���Եó���д�����ݹ���ԭ����write����������ɵģ���������Դ�Ĵ�
    write(info, new_file);
    //���ϴ��������ȷ�����������ϲ�input��new_file�ļ�
    //�ϲ�new_file��input
    Combine(new_file, combine_file, zhen, zhen_file);
    //�����ϵĴ����У�input�Ѿ�����ȡ����zhen����ṹ���������棬ֻ���ȡnewfile��zhen_file���棬ͬʱд��zhen��zhen_file����
    puts("\n������ϣ��鿴��");
    getchar();

    return 0;
}

void read(char *ptr, Ethernet origin)
{
    unsigned char IFAA[7];
    int value = 1; //Ĭ�����ò���ǰ����
    int j = -1;    //j���ڼ�¼֡����
    FILE *fp;
    if ((fp = fopen(ptr, "rb")) == NULL)
    {
        printf("\n��ȡ�ļ�ʧ�ܣ������ļ��Ƿ���ڣ�\nĬ��λ��ΪԴ��Ŀ¼.");
        exit(0); //�����˳�����
    }
    while (!feof(fp))
    {
        if (value) //����ǰ����,�������ǰ�����һֱִ�У�ֱ���ҵ�ǰ����
        {
            for (int i = 0; i < 7; i++)
                fread(&IFAA[i], 1, 1, fp); //��ȡ7λ���֣������ж��Ƿ���ǰ����
            //fread��������һ�������Ƕ�ȡ���Ķ����ڶ��������Ƕ�ȡ�����С��������������ȡ����������ļ�ָ��
            value = IFaa(IFAA, AA); //�ж��ǲ���ǰ����
        }
        else //��ȡ����ǰ����
        {
            fseek(fp, -7, SEEK_CUR); //���ļ�ָ��ع鵽ǰ���뿪ʼ֮ǰ
            //�趨jΪ��һ����ȡ��ǰ������ζ����֡�Ŀ�ʼ +1
            readDetail(fp, origin, ++j); //fpΪ��ǰ�ļ�ָ��λ�ã�origin��jΪ֡���б��
        }

        //frea������ȡ��֮���ļ�ָ���Ѿ�����һ�����ݵĵط��ˣ�����Ҫ�ֶ��ƶ�
        //fseek(fp, 1, SEEK_CUR); //��λƫ�ƣ�ÿ�κ���һλ����ǩǰ�����ж�
    }
    fclose(fp);
} //��ȡ��黹�и����⣬�������fread��ȡ���ļ�β֮�󣬻᷵��������ֵ�������ȡ7����ȡ������һ��֡��ǰ����զ�죿

void readDetail(FILE *fp, Ethernet origin, int locate)
{
    if (!feof(fp)) //���ڵݹ麯������ʱ�ж��Ƿ��Ѿ������ļ�β
    {
        int k = 0;
        unsigned char IFAA[7];
        origin[0].Count = locate + 1; //��¼֡��
        number = locate + 1;          //��¼֡����ûɶ��,������������Է� BUG
        for (k = 0; k < sizeof(origin[locate].QDM); k++)
            fread(&origin[locate].QDM[k], 1, 1, fp); //��ȡǰ����
        fread(&origin[locate].Define, 1, 1, fp);     //��ȡ֡ǰ�����
        for (k = 0; k < sizeof(origin[locate].Daddre); k++)
            fread(&origin[locate].Daddre[k], 1, 1, fp); //��ȡĿ��MAC
        for (k = 0; k < sizeof(origin[locate].Saddre); k++)
            fread(&origin[locate].Saddre[k], 1, 1, fp); //��ȡԴַMAC
        for (k = 0; k < sizeof(origin[locate].Mode); k++)
            fread(&origin[locate].Mode[k], 1, 1, fp);

        //��ȡ���ݶ�
        int Dnum = 0; //��¼���ݶ�λ����������ֵ�õ���

        while (!feof(fp))
        {
            for (k = 0; k < sizeof(origin[locate].QDM); k++)
                fread(&IFAA[k], 1, 1, fp);
            if (!(IFaa(IFAA, AA))) //�����ȡ������һ֡��ǰ���룬��֡�Ŀ�ʼ
            {
                // ����һ֡ǰ�ĵ�һλ��Ϊ��֡��У����
                Dnum -= 1;
                origin[locate].Check = origin[locate].Detail[Dnum];
                //����ֵ��У�������

                origin[locate].Detail[Dnum] = '\0';
                //fseek(fp, -8, SEEK_CUR); //ָ���˻ص�У��ֵǰ
                //fread(&origin[locate].Check, 1, 1, fp);
                //��֡�ĸ�������һ��������д��
                fseek(fp, -7, SEEK_CUR);
                origin[locate].length = Dnum;
                readDetail(fp, origin, ++locate);
            }
            else //��ȡ�����ַ�����ǰ����
            {
                if (feof(fp)) //����Ѿ���ȡ�����ļ�ĩβ,��ʱIFAA����6λ���ݣ����һλ���ļ�βָ��
                {
                    //printf("���λ��:");
                    for (k = 0; k < 5; k++)
                    {
                        //1-5λ��ֵ��������
                        origin[locate].Detail[Dnum] = IFAA[k];
                        //printf("%c ", origin[locate].Detail[Dnum]);
                        Dnum++;
                    }
                    origin[locate].length = Dnum;
                    //�����;���Ǹ�ֵ�ˣ����printf���������������Ϊ���ļ�ָ��ĩβ�����⴦�����
                    //��һ��BUG����ֻ��ʾ��֡�����������Ҳ��printfʱ��ѭ����������һ�Σ��˷������ʱ�䡣��������������
                    //printf("\nУ������:");
                    for (k = 5; k < 6; k++)
                    {
                        // ��IFAA��6λ��ֵ��У����
                        origin[locate].Check = IFAA[k];
                        //printf("%X", origin[locate].Check);
                        return;
                    }
                }
                origin[locate].Detail[Dnum] = IFAA[0];
                fseek(fp, -6, SEEK_CUR); //���ļ�ָ��ƫ�ƻ�ȥ6λ����Ϊֻд����һλ,һ��ֻд��һ���ֽڣ�7���еĵ�һ����
                Dnum++;
            } //��Ѷ�ȡ����7���ֽڵ�һ���������ݶΣ�����һ�������ȡ������һ֡��ǰ���룬ǰ����Ҳ���ᱻд�����ݶ���
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
        printf("\n��ţ�%d\n", i + 1);
        printf("ǰ���룺");
        for (j = 0; j < sizeof(origin[i].QDM); j++)
        {
            printf("%X ", origin[i].QDM[j]);
        }
        printf("\n֡ǰ�������%X", origin[i].Define);
        printf("\nĿ�ĵ�ַDA��");
        for (j = 0; j < sizeof(origin[i].Daddre); j++)
        {
            printf("%X ", origin[i].Daddre[j]);
        }
        printf("\nԴ��ַSA��");
        for (j = 0; j < sizeof(origin[i].Saddre); j++)
        {
            printf("%X ", origin[i].Saddre[j]);
        }
        printf("\n�����ֶΣ�");
        for (j = 0; j < sizeof(origin[i].Mode); j++)
        {
            printf("%X ", origin[i].Mode[j]);
        }
        printf("\n�����ֶΣ�");
        for (j = 0; j < origin[i].length; j++)
        {
            printf("%c", origin[i].Detail[j]);
        }
        printf("\nCRCУ�飺%X", origin[i].Check);
        //
        if (origin[i].Current == 0)
            printf("\nCRC����֡����ӦΪ%X", origin[i].RCheck);
        else
            printf("\nCRCУ��֡��ȷ��");
        printf("\n\n");
    }
}

void write(Ether origin, char *str)
{
    int k = 0;
    FILE *fpp;
    if ((fpp = fopen(str, "ab+")) == NULL)
        printf("�����ļ�ʧ�ܣ�");
    fflush(stdout);
    fflush(stdin);
    fwrite(&origin.QDM[k], sizeof(origin.QDM), 1, fpp);       //д��ǰ����
    fwrite(&origin.Define, 1, 1, fpp);                        //д��֡ǰ�����
    fwrite(&origin.Daddre[k], sizeof(origin.Daddre), 1, fpp); //д��Ŀ��MAC
    fwrite(&origin.Saddre[k], sizeof(origin.Saddre), 1, fpp); //д��ԴַMAC
    fwrite(&origin.Mode, sizeof(origin.Mode), 1, fpp);        //д��Э��ģʽ
    fwrite(&origin.Detail[k], origin.length, 1, fpp);         //д������
    fclose(fpp);
}

void Control_Data(Ether *origin)
{
    int i;
    origin->Count = 1; //���ڴ�ӡ�������ѭ��
    for (i = 0; i < sizeof(AA); i++)
        origin->QDM[i] = AA[i]; //����ǰ����
    origin->Define = Define;    //����֡ǰ�����
    for (i = 0; i < sizeof(DD); i++)
        origin->Daddre[i] = DD[i]; //����Ŀ�ĵ�ַ
    for (i = 0; i < sizeof(DD); i++)
        origin->Saddre[i] = SD[i]; //����Դ��ַ
    for (i = 0; i < sizeof(Mode); i++)
        origin->Mode[i] = Mode[i]; //����Э��
    origin->Check = Check;         //����У����
}

void ReadData(char *ptr, Ether *origin) //ptr�ļ�����origin�Ǵ�Žṹ��
{
    int i = 0;
    FILE *tp;
    if ((tp = fopen(ptr, "r")) == NULL)
        printf("���ļ�ʧ�ܣ�");
    for (i = 0; !feof(tp); i++)
        fread(&origin->Detail[i], 1, 1, tp);
    fclose(tp);
    while (i <= 46) //���벻��46�ֽڵ���Ϣ
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
    printf("����ļ�д�뵽Group�ļ���ɣ�");
}

unsigned char crc8(Ether *origin, int len)
{
    unsigned char *ptr;
    ptr = (unsigned char *)(&origin->Daddre[0]);

    unsigned char crc = 0X00; /* ����ĳ�ʼcrcֵ */

    // for (int k = 0; k < len + 14; k++, *ptr++)
    //     printf("%c ", *ptr);
    // printf("\n\n");

    for (int j = 0; j < len + 14; j++)
    {
        //printf("%X ", crc);
        crc ^= *ptr;
        ptr++;                      /* ÿ��������Ҫ������������,������ָ����һ���� */
        for (int i = 8; i > 0; --i) /* ������μ�����������һ���ֽ�crcһ�� */
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
    //     crc ^= (*ptr++);            /* ÿ��������Ҫ������������,������ָ����һ���� */
    //     for (int i = 8; i > 0; i--) /* ������μ�����������һ���ֽ�crcһ�� */
    //     {
    //         if (crc & 0x80) /* �ж����λ�Ƿ�Ϊ1 */
    //         {
    //             crc = crc << 1;
    //             crc ^= 0x07;
    //         }
    //         /* ���λΪ1������Ҫ���������һλ��Ȼ����0x31��� */
    //         /* 0x31(����ʽ��x8+x5+x4+1��100110001)�����λ����Ҫ���ֱ��ȥ�� */
    //         else
    //         {
    //             crc = crc << 1; /* ���λΪ0ʱ������Ҫ�����������������һλ */
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