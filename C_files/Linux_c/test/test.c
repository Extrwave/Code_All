
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
                    printf("UNKNOWN ERROR !\n"); //未知错误
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

//4.14日计划
//增加length函数，计算链表的长度，方便后续的插入及删除的索引选择， √
//（插入）增加默认头插                                          √
//（删除）增加默认头部删除                                      √
//上述两个用0作为默认值                                         √
//查阅win移植linux需要修改的地方

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
    if (p->next == NULL) //头结点没有数据，所以看next
    {
        printf("no items to delete !");
        return;
    }
    lenth = length(p);
    Electron *p1 = p->next; //p1为需要删除得点
    Electron *p2 = p;       //用于删除点的上一位
    printf("The table's length :%d \n", lenth);
    printf("Please input the sequence(\"0\" is default) of need delete:");
    fflush(stdin);
    scanf("%d", &sequence);
    if (sequence >= 0 && sequence <= lenth)
    {
        if (sequence == 0)
        {
            p1 = p->next;       //记录到第一个节点
            p->next = p1->next; //将删除位置上一节点的next指向下一节点的head
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
                p2 = p2->next; //p2记录为删除点的上一个节点
            }
            p2->next = p1->next; //将删除位置上一节点的next指向下一节点的head
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
    while (p->next != NULL) //因为考虑到头结点没有数据
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
        p1 = (Electron *)malloc(sizeof(Electron)); //生成的节点
        //0 默认头插
        if (sequence == 0)
        {
            p1->next = p2->next;
            p2->next = p1; //完成链表的插入

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
            p2->next = p1; //完成链表的插入

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
    int number = -1; //因为头结点不算是一个数据
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