#include<stdio.h>
#include<malloc.h>

struct binary_tree{
    int data;
    struct binary_tree *left;
    struct binary_tree *right;
};

typedef struct binary_tree node;

void insert(node ** tree, int val)
{
    node * temp = NULL;
    if(!(*tree)){
        temp = (node *)malloc(sizeof(node));
        temp->left = NULL;
        temp->right = NULL;
        *tree = temp;
    }

    if(val <= (*tree)->data){
        insert(&(*tree)->left, val);
    }else if(val > (*tree)->data){
        insert(&(*tree)->right,val);
    }
}

void deltree(node *tree)
{
    if(tree){
        deltree(tree->left);
        deltree(tree->right);
        free(tree);
    }    
}

void preOrderTree(node *tree)
{
    if(tree){
        printf("%d\n", tree->data);
        preOrderTree(tree->left);
        preOrderTree(tree->right);
    }
}

void midOrderTree(node *tree)
{
    if(tree){
        midOrderTree(tree->left);
        printf("%d\n", tree->data);
        midOrderTree(tree->right);
    }
}

void postOrderTree(node *tree)
{
    if(tree){
        postOrderTree(tree->left);
        printf("%d\n", tree->data);
        postOrderTree(tree->right);
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

int main()
{
    node * root = NULL;
    node * tmp = NULL;
    
    insert(&root,9);
    insert(&root,4);
    insert(&root,15);
    insert(&root,6);
    insert(&root,12);
    insert(&root,17);
    insert(&root,2);

    printf("Pre Order Display:\n");
    preOrderTree(root);
    printf("Mid Order Display:\n");
    midOrderTree(root);
    printf("Post Order Display:\n");
    postOrderTree(root);

    deltree(root);
    return 0;
}