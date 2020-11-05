#include<stdio.h>
#include<stdlib.h>
#define True 1
#define False 0

typedef int Boolean;
typedef struct Node
{
    int key;
    struct Node* left;
    struct Node* right;
}bNode;

/*  
    BST查找: 递归
    @return null - 查找失败, or *bNode
 */
bNode* search(bNode* p, int key)
{

    while (p!=NULL)
    {
        if(key>p->key)
            p = p->right;
        else if(key<p->key)
            p = p->left;
        else
            return p;
    }
    return NULL;
}

Boolean insert_t(bNode* root, int key){
    bNode* parent = NULL;
    bNode* curr = root;
    if(search(root,key)) return False;

    //initialise
    bNode* p = (bNode*)malloc(sizeof(bNode));
    p->key=key;
    p->left=p->right=NULL;

    while(curr)
    {
        parent=curr;//precursor
        if(key<curr->key)
            curr=curr->left;
        else
            curr=curr->right;
    }
    //loop end, find the right position for insertion

    if(key<parent->key)
        parent->left=p;
    else
        parent->right=p;
}

bNode* create_t(bNode* root, int a[], int n)
{
    root=(bNode*)malloc(sizeof(bNode));
    root->key=a[0];
    root->left=root->right=NULL;
    for(int i=1;i<n;
    i++)
    {
        insert_t(root, a[i]);
    }
    return root;
}

//遍历：中序
void inOrder(bNode *p)
{
    if(p==NULL) return;
    inOrder(p->left);
    printf("%d ", p->key);
    inOrder(p->right);
}

int main()
{
    int a[10] = {62,88};
    bNode* root=NULL;
    root=create_t(root, a, 2);
    // int a[10] = {62,88,58,47,35,73,51,99,37,93};
    inOrder(root);
    return 0;
}
