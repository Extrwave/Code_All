#include<stdio.h>
#include<stdlib.h>
#include "math.h"  

typedef char TElemtype;
typedef int Status;

typedef struct BiTNode                       //二叉树的结构定义
{
    TElemtype data;                          //数据域
    struct BiTNode *lchild,*rchild;         //左孩子，右孩子指针域
}BiTNode,*BiTree;

/*Status visit(TElemtype e)
{
    printf("%c ",e);
    return 1;
}

Status Value(BiTree p)
{
	return p->data;
}*/

Status InitBiTree(BiTree *T)
{
    *T=NULL;
    return 1;
}

void DestroyBiTree(BiTree *T)
{
    if(*T)
    {
        if((*T)->lchild)
        DestroyBiTree(&(*T)->lchild);
        if((*T)->rchild)
        DestroyBiTree(&(*T)->rchild);
        free(*T);
        *T=NULL;
    }
}

void CreatBiTree(BiTree *T)
{
    TElemtype ch;
    scanf("%c",&ch);
    if(ch=='#')
    {
        *T=NULL;
    }
    else
    {
        *T=(BiTree)malloc(sizeof(BiTNode));
        if(!*T)
            exit(OVERFLOW);
        (*T)->data=ch;                          //根节点
        CreatBiTree(&(*T)->lchild);             //左子树
        CreatBiTree(&(*T)->rchild);             //右子树
    }
}

//遍历二叉树！！！！！
void PreOrder(BiTree T)
{
    if(T==NULL)
        return;
    printf("%c ",T->data);
    PreOrder(T->lchild);
    PreOrder(T->rchild);
}

void InOrder(BiTree T)
{
    if(T==NULL)
        return;
    InOrder(T->lchild);
    printf("%c ",T->data);
    InOrder(T->rchild);
}

void PosOrder(BiTree T)
{
    if(T==NULL)
        return;
    PosOrder(T->lchild);
    PosOrder(T->rchild);
    printf("%c ",T->data);
}

int main()
{
    BiTree Tree;
    InitBiTree(&Tree);
    printf("Begin to creat BiTree (char or #==NULL)\n");
    printf("\nPlease input all Node: ");
    CreatBiTree(&Tree);
    printf("\nPRR:");
    PosOrder(Tree);
    printf("\nI N:");
    InOrder(Tree);
    printf("\nPOS:");
    PosOrder(Tree);

    DestroyBiTree(&Tree);
    if(!Tree)
        printf("\nCLEAR SUCCESS !");
    return 0;
}