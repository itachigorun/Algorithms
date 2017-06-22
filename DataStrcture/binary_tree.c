/*
（1）结点的度。结点所拥有的子树的个数称为该结点的度。
（2）叶结点。度为0 的结点称为叶结点，或者称为终端结点。
（3）分枝结点。度不为0 的结点称为分支结点，或者称为非终端结点。一棵树的结点除叶结点外，其余的都是分支结点。
（4）左孩子、右孩子、双亲。树中一个结点的子树的根结点称为这个结点的孩子。这个结点称为它孩子结点的双亲。具有同一个双亲的孩子结点互称为兄弟。
（5）路径、路径长度。如果一棵树的一串结点n1,n2,…,nk 有如下关系：结点ni 是ni+1的父结点（1≤i<k）,就把n1,n2,…,nk 称为一条由n1 至nk 的路径。这条路径的长度是k-1。
（6）祖先、子孙。在树中，如果有一条路径从结点M 到结点N，那么M 就称为N的祖先，而N 称为M 的子孙。
（7）结点的层数。规定树的根结点的层数为1，其余结点的层数等于它的双亲结点的层数加1。
（8）树的深度。树中所有结点的最大层数称为树的深度。
（9）树的度。树中各结点度的最大值称为该树的度。
（10）满二叉树。在一棵二叉树中，如果所有分支结点都存在左子树和右子树，并且所有叶子结点都在同一层上，这样的一棵二叉树称作满二叉树
（11）完全二叉树。一棵深度为k 的有n 个结点的二叉树，对树中的结点按从上至下、从左到右的顺序进行编号，如果编号为i（1≤i≤n）的结点与满二叉树中编号为i 的结点在二叉树中的位置相同，则这棵二叉树称为完全二叉树。完全二叉树的特点是：叶子结点只能出现在最下层和次下层，且最下层的叶子结点集中在树的左部。显然，一棵满二叉树必定是一棵完全二叉树，而完全二叉树未必是满二叉树。

*/
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

struct binary_tree{
    int data;
    struct binary_tree *left;
    struct binary_tree *right;
};

typedef struct binary_tree node;

void CreateTree(node **tree)
{
    int number;
    scanf("%d", &number);
    if(number == -1)
    {
        *tree = NULL;
        printf("程序退出！");
        exit(0);
    }
    else
    {
        *tree = (node *)malloc(sizeof(node));
        if(tree == NULL)
        {
            printf("malloc failed\n");
            return ;
        }
        else
        {
            (*tree)->data = number;
            printf("输入%d的左子节点：", number);
            CreateTree(&((*tree)->left));
            printf("输入%d的右子节点:", number);
            CreateTree(&((*tree)->right));
        }
    }

    printf("二叉树创建成功\n");
    return ;
}

void InsertTree(node ** tree, int val)
{
    node * temp = NULL;
    if((*tree) == NULL){
        temp = (node *)malloc(sizeof(node));
        temp->left = NULL;
        temp->right = NULL;
        *tree = temp;
    }

    if(val <= (*tree)->data)
        InsertTree(&(*tree)->left, val);
    else 
        InsertTree(&(*tree)->right, val);
    
}

void DeleteTree(node *tree)
{
    if(tree){
        DeleteTree(tree->left);
        DeleteTree(tree->right);
        free(tree);
    }    
}

void PreOrderTree(node *tree)
{
    if(tree){
        printf("%d\n", tree->data);
        PreOrderTree(tree->left);
        PreOrderTree(tree->right);
    }
}

void MidOrderTree(node *tree)
{
    if(tree){
        MidOrderTree(tree->left);
        printf("%d\n", tree->data);
        MidOrderTree(tree->right);
    }
}

void PostOrderTree(node *tree)
{
    if(tree){
        PostOrderTree(tree->left);
        Printf("%d\n", tree->data);
        PostOrderTree(tree->right);
    }
}

void SearchValue(node *tree, int number)
{
    if(tree == NULL)
    {
        printf("该树为空\n");
        return ;
    }
    else
    {
        if(number < tree->data)
            SearchValue(tree->left, number);
        else if(number > tree->data)
            SearchValue(tree->right, number);
        else
        {
            printf("找到该值!\n");
            return ;
        }
    }
}

int GetHeightTree(node *tree)
{
    int height, left, right;
    if(tree == NULL){
        return 0;
    }
    left = GetHeightTree(tree->left);
    right = GetHeightTree(tree->right);
    height = (left > right? left: right) + 1;
    return height;
}

int GetLeafCount(node *tree)
{
    static int count;
    if(tree != NULL)
    {
        if(tree->left == NULL && tree->right == NULL)
            count++;
        GetLeafCount(tree->left);
        GetLeafCount(tree->right);
    }
    return count;
}

int main()
{
    node * root = NULL;
    int select_number;
    int input_number;

    printf("输入整数，构造二叉树，输入-1退出\n");
    CreateTree(&root);

    while(1){
    printf("请选择：1)插入一个节点 2)前序遍历 3)中序遍历 4)后续遍历 5)退出: ");
    scanf("%d", &select_number);

    switch(select_number){
        case 1: 
            scanf("%d", &input_number);
            InsertTree(&root,input_number);
            break;
        case 2:
            PreOrderTree(root);
            break;
        case 3:
            MidOrderTree(root);
            break;
        case 4:
            PostOrderTree(root);
            break;
        case 5:
            DeleteTree(root);
            break;
        default:
            printf("请选择正确选项！\n");
    }
    }

    return 0;
}