#include "electable.h"

int main(void)
{
    int select, iif;
    Electron *table;
    table = creat();
    while (1)
    {
        ui();
        iif = 1;
        printf("Please enter a number to select:");
        while (iif)
        {
            fflush(stdin);
            scanf("%d", &select);
            if (select == 1 || select == 2 || select == 3 || select == 4)
            {
                iif = 0;
                switch (select)
                {
                case 1:
                    insert(table);
                    break;
                case 2:
                    delete (table);
                    break;
                case 3:
                    display(table);
                    break;
                case 4:
                    exit(0);
                    break;
                default:
                    printf("UNKNOWN ERROR !\n"); //δ֪����
                    fflush(stdin);
                    getchar();
                    exit(0);
                }
            }
            else
            {
                printf("Input error, please enter again:");
                iif = 1;
            }
        }
    }
}

//4.14�ռƻ�
//����length��������������ĳ��ȣ���������Ĳ��뼰ɾ��������ѡ�� ��
//�����룩����Ĭ��ͷ��                                          ��
//��ɾ��������Ĭ��ͷ��ɾ��                                      ��
//����������0��ΪĬ��ֵ                                         ��
