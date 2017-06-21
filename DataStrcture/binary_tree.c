#include<stdio.h>
#include<malloc.h>

struct binary_tree{
    int data;
    struct binary_tree *left;
    struct binary_tree *right;
};

typedef struct binary_tree node;

int create_tree(node **tree)
{
    int number;
    scanf("%d", %number);
    if(ch == -1)
    {
        *tree = NULL;
        return 0;
    }
    else
    {
        *tree = (node *)malloc(sizeof(node));
        if(tree = NULL)
        {
            printf("malloc failed\n");
            return 0;
        }
        else
        {
            (*tree)->data = number;
            printf("输入%d的左子节点："，number);
            create_tree(&((*tree)->left));
            printf("输入%d的右子节点:", number);
            create_tree(&((*tree)->right));
        }
    }
    return 1;
}

void insert_tree(node ** tree, int val)
{
    node * temp = NULL;
    if(!(*tree)){
        temp = (node *)malloc(sizeof(node));
        temp->left = NULL;
        temp->right = NULL;
        *tree = temp;
    }

    if(val <= (*tree)->data){
        insert_tree(&(*tree)->left, val);
    }else if(val > (*tree)->data){
        insert_tree(&(*tree)->right,val);
    }
}

void delete_tree(node *tree)
{
    if(tree){
        delete_tree(tree->left);
        delete_tree(tree->right);
        free(tree);
    }    
}

void pre_order_tree(node *tree)
{
    if(tree){
        printf("%d\n", tree->data);
        pre_order_tree(tree->left);
        pre_order_tree(tree->right);
    }
}

void mid_order_tree(node *tree)
{
    if(tree){
        mid_order_tree(tree->left);
        printf("%d\n", tree->data);
        mid_order_tree(tree->right);
    }
}

void post_order_tree(node *tree)
{
    if(tree){
        post_order_tree(tree->left);
        printf("%d\n", tree->data);
        post_order_tree(tree->right);
    }
}

int is_equal(node tree1, node tree2){  
    if(!tree1 && !tree2){      //都为空就相等  
        return 1;  
    }  
    if(tree1 && tree2 && tree1->data == tree2->data){      //有一个为空或数据不同就不判断了  
        if(is_equal(tree1->lchild,tree2->lchild))  
            if(is_equal(tree1->rchild,tree2->rchild)){  
                return 1;  
            }  
    }  
    return 0;  
} 

int get_height_tree(node tree)
{
    int height, left, right;
    if(!tree){
        return 0;
    }
    left = get_height_tree(tree->left);
    right = get_height_tree(tree->right);
    height = (left->right? left : right) + 1;
    return height;
}

int get_leaf_count(node *tree)
{
    static int count;
    if(node == NULL)
    {
        if(node->left == NULL && node->right == NULL)
            count++;
        get_leaf_count(node->left);
        get_leaf_count(node->right);
    }
    return count;
}

int main()
{
    node * root = NULL;
    node * tmp = NULL;
    
    insert(&root,9);

    printf("Pre Order Display:\n");
    preOrderTree(root);
    printf("Mid Order Display:\n");
    midOrderTree(root);
    printf("Post Order Display:\n");
    postOrderTree(root);

    deltree(root);
    return 0;
}