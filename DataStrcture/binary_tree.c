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

#define MAXSIZE 100

typedef struct binary_tree{
    int data;
    struct binary_tree *left;
    struct binary_tree *right;
}node;

typedef struct seqstack{
    node *data[MAXSIZE];
    int tag[MAXSIZE];  //为后续遍历准备的
    int top;           //top为数组的下标
}seqstack;

void CreateTree(node **tree)
{
    int number;
    scanf("%d", &number);
    if(number == -1)
    {
        *tree = NULL;
        return ;
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

    return ;
}

//插入节点
void InsertTree(node ** tree, int value)
{
    node * temp = NULL;
    if(*tree == NULL)
    {
        temp = (node *)malloc(sizeof(node));
        temp->left = NULL;
        temp->right = NULL;
        temp->data = value;
        *tree = temp;
        
        return ; //退出函数，防止死循环
    }
    
    if(value <= (*tree)->data)
        InsertTree(&(*tree)->left, value);
    else 
        InsertTree(&(*tree)->right, value);
    
}

void DeleteTree(node *tree)
{
    if(tree){
        DeleteTree(tree->left);
        DeleteTree(tree->right);
        free(tree);
    }    
}

//前序遍历二叉树
void PreOrderTree(node *tree)
{
    if(tree){
        printf("%d ", tree->data);
        PreOrderTree(tree->left);
        PreOrderTree(tree->right);
    }
}

//中序遍历二叉树
void MidOrderTree(node *tree)
{
    if(tree){
        MidOrderTree(tree->left);
        printf("%d ", tree->data);
        MidOrderTree(tree->right);
    }
}

//后续遍历二叉树
void PostOrderTree(node *tree)
{
    if(tree){
        PostOrderTree(tree->left);
        PostOrderTree(tree->right);
        printf("%d ", tree->data);
    }
}

void NodePush(seqstack *stack, node *tree)
{
    if(stack->top == MAXSIZE)
        printf("The stack is full\n");
    else{
        stack->top++;
        stack->data[stack->top] = tree;
    }
}

node *NodePop(seqstack *stack)
{
    if(stack->top == -1)
        return NULL;
    else{
        stack->top--;
        return stack->data[stack->top+1];
    }
}

//非递归前序遍历
void PreOrderTree2(node *tree)
{
    seqstack stack;
    stack.top = -1;    //表示栈为空
    if(tree == NULL)
        printf(" The tree is empty!\n");
    
    while(tree || stack.top!=-1){
        while(tree){                  //只要节点不为空就入栈，与左右节点无关
            printf("%d ", tree->data);
            NodePush(&stack, tree);
            tree = tree->left;
        }
        tree = NodePop(&stack);
        tree = tree->right;
    }
}

//非递归中序遍历
void MidOrderTree2(node *tree)
{
    seqstack stack;
    stack.top = -1;
    if(tree == NULL)
        printf("The tree is empty!\n");
    
    while(tree || stack.top!=-1){
        while(tree){
            NodePush(&stack, tree);
            tree = tree->left;
        }
        tree = NodePop(&stack);
        printf("%d ", tree->data);
        tree = tree->right;
    }
}

//非递归后续遍历,需要访问两次根节点
void PostOrderTree2(node *tree)
{
    seqstack stack;
    stack.top = -1;
    if(tree == NULL)
        printf("The tree is empty!\n");
    
    while(tree || stack.top!=-1){
        while(tree){
            NodePush(&stack, tree);
            stack.tag[stack.top] = 0;    //设置访问根节点标记，0为第一次，1为第二次访问
            tree = tree->left;
        }
        if(stack.tag[stack.top] == 0){  //第一次访问根节点时，专向同层右节点
            tree = stack.data[stack.top];  //左走到底时tree为空
            stack.tag[stack.top] = 1;
            tree = tree->right;
        }
        else{
            while(stack.tag[stack.top] == 1){   //找到栈中下一个第一次访问的节点，退出循环时并没有pop，所有为其左子节点
                tree = NodePop(&stack);
                printf("%c ", tree->data);
            }
            tree = NULL;  //必须将tree置为空，跳过走左，直接向右走
        }
    }
}

// 判断一棵二叉树是否为平衡二叉树
// 平衡二叉树的定义: 如果任意节点的左右子树的深度相差不超过1，那这棵树就是平衡二叉树
// 算法思路：递归判断每个节点的左右子树的深度是否相差大于1，如果大于1，说明该二叉树不
//           是平衡二叉树，否则继续递归判断
int IsBalanceBinaryTree(node *tree)
{
	int leftDepth = 0;
	int rightDepth = 0;
	int distance = 0; 

	if (tree != NULL)
	{
		leftDepth = GetHeightTree(tree->left);   // 获取左子树的深度
		rightDepth = GetHeightTree(tree->right); // 获取右子树的深度
		distance = leftDepth > rightDepth ? leftDepth - rightDepth : rightDepth - leftDepth;

		return distance > 1 ? 0 : IsBalanceBinaryTree(tree->left) && IsBalanceBinaryTree(tree->right);
	}
}

//计算二叉树的高度
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

//计算节点数
int GetNodeCount(node *tree)
{
    int count = 0;
    if(tree == NULL)
        return 0;
    else
        count = 1 + GetNodeCount(tree->left) + GetNodeCount(tree->right);
    
    return count;
}

//计算叶子节点数(度为0)
int GetLeafCount1(node *tree)
{
    int count = 0;
    if(tree == NULL)
        return 0;
    
    
    if(tree->left == NULL && tree->right == NULL)
        return 1;
    else
        count = GetLeafCount1(tree->left) + GetLeafCount1(tree->right);

    return count;
}

int GetLeafCount2(node *tree)
{
    static int count;
    if(tree != NULL)
    {
        if(tree->left == NULL && tree->right == NULL)
            count++;
        GetLeafCount2(tree->left);
        GetLeafCount2(tree->right);
    }
    return count;
}

// 获取度为1的结点的个数
int GetCountOfOneDegree(node *tree)
{
	static int count; //static 变量自动赋值0

	if (tree != NULL)
	{
		if ((tree->left != NULL && tree->right == NULL) || (tree->left == NULL && tree->right != NULL))
		{
			count++;
		}

		GetCountOfOneDegree(tree->left);
        GetCountOfOneDegree(tree->right);
	}

	return count;
}


//计算满节点数--度为2的节点
int GetFullNodeCount1(node *tree)
{
    int count = 0;
    if(tree == NULL)
        return 0;

    if(tree->left!=NULL && tree->right!=NULL)
        return 1;
    else 
        count =GetFullNodeCount1(tree->left) + GetFullNodeCount1(tree->right);
    return count;
}
//对于二叉树而言，有一个公式：度为2的结点个数等于度为0的结点个数减去1。 即：n(2)=n(0)-1
//故可以这样：
int GetFullNodeCount2(node *tree)
{
    return GetLeafCount1(tree) > 0 ? GetLeafCount1(tree) - 1 : 0; 
}

int main()
{
    node * root = NULL;
    int select_number;
    int input_number;

    printf("输入整数，构造二叉树，输入-1退出\n");
    CreateTree(&root);
    printf("二叉树创建成功\n");

    while(1){
    printf("请选择：1)插入一个节点 2)前序遍历 3)中序遍历 4)后续遍历 5)得到树的高度 6)叶子节点数 7)节点数 8)满节点数 9)退出: ");
    scanf("%d", &select_number);

    switch(select_number){
        case 1: 
            printf("请输入一个整数：");
            scanf("%d", &input_number);
            InsertTree(&root,input_number);
            break;
        case 2:
            PreOrderTree(root);
            printf("\n");
            PreOrderTree2(root);
            break;
        case 3:
            MidOrderTree(root);
            printf("\n");
            MidOrderTree2(root);
            break;
        case 4:
            PostOrderTree(root);
            printf("\n");
            PostOrderTree2(root);
            break;
        case 5:
            printf("二叉树的高度是:%d\n", GetHeightTree(root));
            break;
        case 6:
            printf("二叉树的叶子节点数是：%d\n", GetLeafCount1(root));
            printf("二叉树的叶子节点数是：%d\n", GetLeafCount2(root));
            break;
        case 7:
            printf("二叉树的节点数是：%d\n", GetNodeCount(root));
            break;
        case 8:
            printf("二叉树的满节点数是:%d\n", GetFullNodeCount1(root));
            printf("二叉树的满节点数是:%d\n", GetFullNodeCount2(root));
            break;
        case 9:
            DeleteTree(root);
            exit(0);
        default:
            printf("请选择正确选项！\n");
    }
    }

    return 0;
}