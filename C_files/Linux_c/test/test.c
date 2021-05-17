
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    long number;
    int vaule;
    char address[128];
    struct Node *next;
} Electron;

void insert(Electron *p);
void delete (Electron *p);
void display();
void ui();
int back();
int length(Electron *p);
Electron *creat();

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
//����win��ֲlinux��Ҫ�޸ĵĵط�

int back()
{
    char b = 'w';
    while (b != 'q')
    {
        printf("Please press \"q\" to quit , and any key to continue:");
        fflush(stdin);
        b = getchar();
        if (b == 'q')
            return 0;
        else
        {
            printf("Input continue !\n");
            return 1;
        }
    }
}

Electron *creat()
{
    Electron *head;
    head = (Electron *)malloc(sizeof(Electron));
    head->next = NULL;
    return head;
}

void delete (Electron *p)
{
    int lenth;
    int sequence, con;
    if (p->next == NULL) //ͷ���û�����ݣ����Կ�next
    {
        printf("no items to delete !");
        return;
    }
    lenth = length(p);
    Electron *p1 = p->next; //p1Ϊ��Ҫɾ���õ�
    Electron *p2 = p;       //����ɾ�������һλ
    printf("The table's length :%d \n", lenth);
    printf("Please input the sequence(\"0\" is default) of need delete:");
    fflush(stdin);
    scanf("%d", &sequence);
    if (sequence >= 0 && sequence <= lenth)
    {
        if (sequence == 0)
        {
            p1 = p->next;       //��¼����һ���ڵ�
            p->next = p1->next; //��ɾ��λ����һ�ڵ��nextָ����һ�ڵ��head
            printf("\t%ld\t%d\t%s has been delete !\n", p1->number, p1->vaule, p1->address);
            free(p1);
        }
        else if (sequence < 1)
        {
            printf("Input Error !");
        }
        else
        {
            for (int i = 1; i < sequence; i++)
            {
                p1 = p1->next;
                p2 = p2->next; //p2��¼Ϊɾ�������һ���ڵ�
            }
            p2->next = p1->next; //��ɾ��λ����һ�ڵ��nextָ����һ�ڵ��head
            printf("\t%ld\t%d\t%s has been delete !\n", p1->number, p1->vaule, p1->address);
            free(p1);
        }
        con = back();
        if (con)
            insert(p);
        return;
    }
    else
    {
        printf("Input error !");
        con = back();
        if (con)
            delete (p);
        return;
    }
}

void display(Electron *p)
{
    while (p->next != NULL) //��Ϊ���ǵ�ͷ���û������
    {
        printf("\t%ld\t%d\t%s\n", p->next->number, p->next->vaule, p->next->address);
        p = p->next;
    }
    printf("Electronic Table is all !");
    printf("Any key to quit !");
    fflush(stdin);
    getchar();
    return;
}

void insert(Electron *p)
{
    int lenth;
    int sequence, con;
    Electron *p1, *p2;
    p2 = p;
    lenth = length(p);
    printf("The table's length :%d \n", lenth);
    printf("Please input the insert (\"0\" is default) sequence :");
    fflush(stdin);
    scanf("%d", &sequence);
    if (sequence >= 0 && sequence <= lenth)
    {
        p1 = (Electron *)malloc(sizeof(Electron)); //���ɵĽڵ�
        //0 Ĭ��ͷ��
        if (sequence == 0)
        {
            p1->next = p2->next;
            p2->next = p1; //�������Ĳ���

            printf("Please enter the number:");
            fflush(stdin);
            scanf("%ld", &p1->number);
            printf("Please enter the vaule:");
            fflush(stdin);
            scanf("%d", &p1->vaule);
            printf("Please enter the address:");
            fflush(stdin);
            scanf("%s", p1->address);
            printf("\t%ld\t%d\t%s has been inserted !\n", p1->number, p1->vaule, p1->address);
        }
        else if (sequence < 0)
        {
            printf("Input Error !");
        }
        else
        {
            for (int i = 0; i < sequence; i++)
            {
                p2 = p2->next;
            }

            p1->next = p2->next;
            p2->next = p1; //�������Ĳ���

            printf("Please enter the number:");
            fflush(stdin);
            scanf("%ld", &p1->number);
            printf("Please enter the vaule:");
            fflush(stdin);
            scanf("%d", &p1->vaule);
            printf("Please enter the address:");
            fflush(stdin);
            scanf("%s", p1->address);
            printf("\t%ld\t%d\t%s has been inserted !\n", p1->number, p1->vaule, p1->address);
        }
        con = back();
        if (con)
            insert(p);
        return;
    }
    else
    {
        printf("Input error !\n");
        con = back();
        if (con)
            insert(p);
        return;
    }
}

int length(Electron *p)
{
    int number = -1; //��Ϊͷ��㲻����һ������
    while (p != NULL)
    {
        p = p->next;
        number++;
    }
    return number;
}

void ui()
{
    system("cls");
    printf("------------Electronic SYstem---------\n\n\n");
    printf("\t1.Insert");
    printf("\t2.Delete\n\n");
    printf("\t3.Display");
    printf("\t4.Exit\n\n\n");
    printf("powerd by GL & TXH\n");
}