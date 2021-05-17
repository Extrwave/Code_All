#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define OK 1
#define TURE 1
#define ERROR 0
#define FALSE -1

typedef int Status;
typedef int Elemtype;

typedef struct Node //新结点，然后定义一个指向结点的指针
{
    Elemtype data;
    struct Node *next;
} Node, *LinkStackPtr;

typedef struct
{
    LinkStackPtr top; //Stack
    int count;
} LinkStack;

Status InitStack(LinkStack *S)//    初始化栈
{
    S->top = (LinkStackPtr)malloc(sizeof(Node));
    if (!S->top)
        return ERROR;
    S->top = NULL;
    S->count = 0;
    return OK;
}

Status NPush(LinkStack *S, Elemtype e)//int型数字入栈
{
    LinkStackPtr p = (LinkStackPtr)malloc(sizeof(Node));
    p->data = e;
    p->next = S->top;
    S->top = p;
    S->count++;
    return OK;
}

Status CPush(LinkStack *S, char e)//char型运算符入栈
{
    LinkStackPtr p = (LinkStackPtr)malloc(sizeof(Node));
    p->data = e;
    p->next = S->top;
    S->top = p;
    S->count++;
    return OK;
}

Status NPop(LinkStack *S, Elemtype *e)//int型数字出栈
{
    if (S->count == 0)
        return ERROR;
    LinkStackPtr p; //p作用在于free掉已占用得内存空间
    *e = S->top->data;
    p = S->top; //将要删除节点地址赋予p，方便后面调用free函数
    S->top = S->top->next;
    free(p);
    S->count--;
    return OK;
}

Status CPop(LinkStack *S, char *e)//char型运算符出栈
{
    if (S->count == 0)
        return ERROR;
    LinkStackPtr p; //p作用在于free掉已占用得内存空间
    *e = S->top->data;
    p = S->top;
    S->top = S->top->next;
    free(p);
    S->count--;
    return OK;
}

Status visit(Elemtype c)//访问输出结果数值
{
    printf("%d ", c);
    return OK;
}

int StackLength(LinkStack S)//栈的长度，没用上，来源于以前写的栈的基本操作
{
    return S.count;
}

Status Gettop(LinkStack S)//获取栈的顶部元素
{
    if (S.top == NULL)
        return ERROR;
    else
        return S.top->data;
}

//引用实验指导书里的运算符优先关系比较
int getIndex(char theta) //获取theta所对应的索引
{
    int index = 0;
    switch (theta)
    {
    case '+':
        index = 0;
        break;
    case '-':
        index = 1;
        break;
    case '*':
        index = 2;
        break;
    case '/':
        index = 3;
        break;
    case '(':
        index = 4;
        break;
    case ')':
        index = 5;
        break;
    case '#':
        index = 6;
    default:
        break;
    }
    return index;
}

char getPriority(char theta1, char theta2) //获取theta1与theta2之间的优先级
{
    const char priority[][7] = //算符间的优先级关系
        {
            {'>', '>', '<', '<', '<', '>', '>'},
            {'>', '>', '<', '<', '<', '>', '>'},
            {'>', '>', '>', '>', '<', '>', '>'},
            {'>', '>', '>', '>', '<', '>', '>'},
            {'<', '<', '<', '<', '<', '=', '0'},
            {'>', '>', '>', '>', '0', '>', '>'},
            {'<', '<', '<', '<', '<', '0', '='},
        };

    int index1 = getIndex(theta1);
    int index2 = getIndex(theta2);
    return priority[index1][index2];
}

//判断读取的字符是不是运算符
Status In(char A, char B[])
{
    int i;
    for (i = 0; i < 7; i++)
    {
        if (A == B[i])
            return OK;
    }
    return ERROR;
}

//计算出出栈的表达式的值
Status Count(int i, int j, char op)
{
    int result;
    switch (op)
    {
    case '+':
        result = i + j;
        break;
    case '-':
        result = i - j;
        break;
    case '*':
        result = i * j;
        break;
    case '/':
        result = i / j;
        break;
    }
    return result;
}

int main()
{
    char operall[7] = {'+', '-', '*', '/', '#', '(', ')'};//将运算符做成一数组，用于后续判断字符是否为运算符
    char ch, x, op;
    int count1, count2, val, n;
    char damn = '#';
    //构建和初始化栈
    LinkStack(oper);
    LinkStack(number);
    InitStack(&oper);
    InitStack(&number);
    CPush(&oper, damn);//将#作为栈底元素

    printf("Please Input Operator end with #:\n");
    ch = getchar();//获取表达式，并以#号结束
    while (ch != '#' || Gettop(oper) != '#')
    {
        if (!In(ch, operall))//判断是否为运算符
        {
            NPush(&number, ch-'0');//将char型数字，转换成对应的int型值
            ch = getchar();
        }
        else
        {
            switch (getPriority(Gettop(oper), ch))
            {
            case '<':
                CPush(&oper, ch);
                ch = getchar();
                break;
            case '=':
                CPop(&oper, &x);
                ch = getchar();
                break;
            case '>':
                CPop(&oper, &op);
                NPop(&number, &count2);
                NPop(&number, &count1);
                val=Count(count1,count2,op);        //减去'0' 获得对应的int值
                NPush(&number, val);
                break;
            }
        }
    }
    printf("%d\n", Gettop(number));
    system("pause");
    return val;
}
