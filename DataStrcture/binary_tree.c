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