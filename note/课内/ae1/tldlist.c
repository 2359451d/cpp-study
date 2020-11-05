/* 
    SP Exercise 1A
    Name: Yao Du
    GUID: 2359451D

    This is my own work as defined in the Academic Ethics agreement I have signed.
*/

#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "date.h"
#include "tldlist.h"
/* 
    Based on the implementation of AVL
*/

// structure which stores the number of AVL nodes, and prefered date for filtering
struct tldlist{
    long node_counts;
    long size;
    Date* begin;
    Date* end;
    TLDNode* root;//tree to store each tldnode
};

/* represents the AVL node, the order comparsion is based on date size(date_compare(Date*, Date*))
 */
struct tldnode
{
    char* tld;
    TLDNode* left;
    TLDNode* right;
    TLDNode* parent;
    long count;
    int height;
    int balance;//balance factor: -1 0 1
};

// linear iterator to traverse the AVL
struct tlditerator{
    TLDNode **next;
    long size;
    int index;
};

// prototype
TLDList *tldlist_create(Date *begin, Date *end);
void tldlist_destroy(TLDList *tld);
int tldlist_add(TLDList *tld, char *hostname, Date *d);
long tldlist_count(TLDList *tld);
TLDIterator *tldlist_iter_create(TLDList *tld);
TLDNode *tldlist_iter_next(TLDIterator *iter);
void tldlist_iter_destroy(TLDIterator *iter);
char *tldnode_tldname(TLDNode *node);
long tldnode_count(TLDNode *node);
void rebalance(TLDList* tld, TLDNode* p);


// universal variable
// TLDIterator* iterator = NULL;
// TLDList* list  = NULL;

/*
 * tldlist_create generates a list structure for storing counts against
 * top level domains (TLDs)
 *
 * creates a TLDList that is constrained to the `begin' and `end' Date's
 * returns a pointer to the list if successful, NULL if not
 */
TLDList *tldlist_create(Date *begin, Date *end)
{
    TLDList* list = (TLDList*)malloc(sizeof(TLDList));
    if(list!=NULL)
    {
        list->begin = date_duplicate(begin);
        list->end = date_duplicate(end);
        list->node_counts =0;//empty list
        list->root=NULL;//empty tree
        list->size=0;
    }
    return list;
};

/* 
    return the parent node of p or NULL
 */
// TLDNode* getParent(TLDNode* p)
// {
//     TLDNode* curr = list->root, *parent=NULL;
//     while(curr!=NULL)
//     {
//         parent=curr;
//         if(date_compare(p->date,curr->date)<0)
//             // goleft
//             curr=curr->left;
//         else if (date_compare(p->date,curr->date)>0)
//             // goright
//             curr=curr->right;
//         else{
//             // same date, check the hostname
//             if(strcmp(curr->hostname,p->hostname)==0)
//                 // same node
//                 return parent;
//             else
//                 parent=NULL;
//         }
//     }
//     return NULL;
// }

/* 
    helper func: free the given node
 */
void free_node(TLDNode* p)
{
    free(p->tld);
    free(p);
}

/* 
    remove AVL nodes
 */
void delete_node(TLDNode* p)
{
    if(p!=NULL){
        delete_node(p->left);
        delete_node(p->right);
        free_node(p);
    }
}

/* 
    helper func: initialising the node
 */

TLDNode* add_node(TLDList *tldList, char *tld, TLDNode *parent) {
  TLDNode *node = (TLDNode *) malloc(sizeof(TLDNode));
  if (node != NULL) {
    node->parent = parent;
    node->left = NULL;
    node->right = NULL;
    node->tld = tld;//hostname
    node->height = 0;
    node->balance = 0;
    node->count = 1;//how many times the tld was counted
    tldList->size++;
  }
  return node;
}

/*
 * tldlist_destroy destroys the list structure in `tld'
 *
 * all heap allocated storage associated with the list is returned to the heap
 * NOTICE: AVL DELETING SITUATION & need to maintain the AVL property during destroy process
 */
void tldlist_destroy(TLDList *tld){
    if (tld==NULL) return;
    delete_node(tld->root);
    date_destroy(tld->begin);
    date_destroy(tld->end);
    free(tld);
};

/* 
    helper func:
        search the existence of certain node with given date & hostname
        check date first, if are the same then check for hostname
    return 1: exist, -1: not exist
 */
// int search_t(TLDNode *root, char* tld, Date* date)
// {
//     while (root!=NULL)
//     {
//         if (date_compare(date,root->date)<0)
//             // gotoLeft
//             root=root->left;
//         else if (date_compare(date,root->date)>0)
//             // gotoRight
//             root=root->right;
//         else{
//             // same date, check the hostname
//             if(strcmp(root->tld,tld)==0)
//                 // node already exists
//                 return 1;
//             else
//                 return -1;            
//         }
//     }
//     return -1;
// }

/* 
    helper func:
        find the height of the tree
*/
int getHeight(TLDNode* p){
    if(p==NULL) return -1;
    return p->height;
}

/* 
    helper func:
        set the height for node
 */
void setHeight(TLDNode* p)
{
    if(p!=NULL){
        int left_h, right_h, max;
        // from current pointer p, recursively to get the height of left/right subtree
        left_h = getHeight(p->left);
        right_h = getHeight(p->right);
        max=(left_h>right_h) ? left_h : right_h;
        p->height=max+1;
    }
}

/* 
    helper func:
        set the balance factor for current node(using for different rebalance rotation)
 */
void setBalance(TLDNode* p)
{
    setHeight(p);
    p->balance = getHeight(p->right) - getHeight(p->left);// calculate the balance factor
}

/* 
    LL adjustment - right rotation
    left subtree replace its parent
    right subtree of original left subtree becomes the left subtree of original parent node
*/
TLDNode* rightRotate(TLDNode* q)
{
    TLDNode *temp = q->left;
    temp->parent = q->parent;
    // right subtree of original left subtree becomes the left subtree of original parent node
    q->left = temp->right;

    if (q->left) {
        q->left->parent = q;
    }

    temp->right = q;
    q->parent = temp;

    if (temp->parent) {
        if (temp->parent->right == q) {
        temp->parent->right = temp;
        } else {
        temp->parent->left = temp;
        }
    }
    // updating the balance factor
    setBalance(q);
    setBalance(temp);

    return temp;
}

/* 
    RR adjustment - right rotation
    right subtree replace its parent
    left subtree of original right subtree becomes the right subtree of original parent node
*/
TLDNode* leftRotate(TLDNode* q)
{
    TLDNode *temp = q->right;
    temp->parent = q->parent;

    // left subtree of original right subtree becomes the right subtree of original parent node
    q->right = temp->left;
    if (q->right) {
        q->right->parent = q;
    }

    temp->left = q;
    q->parent = temp;

    if (temp->parent) {
        if (temp->parent->right == q) {
        temp->parent->right = temp;
        } else {
        temp->parent->left = temp;
        }
    }
    // updating balance factor
    setBalance(q);
    setBalance(temp);

    return temp;
}

/* 
    LR adjustment:
        the right side of the left subtree is higher
        left rotate the left subtree first,
        then together do the right rotation
 */
TLDNode* leftRightRotate(TLDNode* q)
{
    q->left = leftRotate(q->left);//left rotate first
    return rightRotate(q);
}

/* 
    RL adjustment:
        the left side of the right subtree is higher
        right rotate the right subtree first,
        then together do the left rotation
 */
TLDNode* rightLeftRotate(TLDNode* q)
{
    q->right = rightRotate(q->right);//right rotate first
    return leftRotate(q);
}

/* 
    do different rotation to rebalance the AVL regarding different balance factor
    LL - right rotation
    RR - left rotation
    LR - left-right rotation
    RL - right-left rotation
 */
void rebalance(TLDList *tld, TLDNode* p)
{
    // calculate the balance factor for Node(generally would be the parent of newly inserted node)
    setBalance(p);//p.balance=right_h-left_h

    if(p->balance==-2){
        //left subtree is higher
        //check again the newly inserted node is at which side (by comparing height)
        if (getHeight(p->left->left) >= getHeight(p->left->right)) {
            //simple LL adjustment: right rotation
            p = rightRotate(p);
        }else{
            // LR adjustment
            p = leftRightRotate(p);
        }
    } else if (p->balance==2){
        if (getHeight(p->right->right) >= getHeight(p->right->left)){
            //simple RR adjustment: left rotation
            p = leftRotate(p);
        }else{
            // RL adjustment
            p = rightLeftRotate(p);
        }
    }

    // rebalance the nodes upwards, unless it is the root
    if(p->parent==NULL) tld->root=p;
    else rebalance(tld,p->parent);
}


/*
 * tldlist_add adds the TLD contained in `hostname' to the tldlist if
 * `d' falls in the begin and end dates associated with the list;
 * returns 1 if the entry was counted, 0 if not
 */
int tldlist_add(TLDList *tld, char *hostname, Date *d){
    // make sure the date is suitable to put into the list,i.e begin<d<end
    if(date_compare(d, tld->begin)<0) return 0;
    if(date_compare(d, tld->end)>0) return 0;

    char *token = strrchr(hostname, '.') + 1;
    char *hostname_str = (char *) calloc(strlen(token) + 1, sizeof(char));
    strcpy(hostname_str, token);

    if (tld->root != NULL) {
        TLDNode *curr = tld->root;
        while (curr != NULL) {
            // hostname already exists, end loop
            if (strcmp(curr->tld, hostname_str) == 0) {
                curr->count++;
                free(hostname_str);
                break;
            }

            int direction = strcmp(curr->tld, hostname_str);// <0 go left, >0 go right

            TLDNode *p = curr;
            if(direction>0) curr=curr->left;
            else curr=curr->right;
            // curr = (strcmp(curr->tld, hostname_str) > 0) ? curr->left : curr->right;

            // If the node is not occupied, create the node at the proper position then rebalance the tree
            if (curr == NULL) {
                if (direction > 0) {
                p->left = add_node(tld, hostname_str, p);
                } else if (direction < 0) {
                p->right = add_node(tld, hostname_str, p);
                }
                rebalance(tld, p);
            }
        }
    } else {
        // empty tree directly inserted
        tld->root = add_node(tld, hostname_str, NULL);
    }
    // Increment the node count
    tld->node_counts++;
    return 1;
}

/*
 * tldnode_count returns the number of times that a log entry for the
 * corresponding tld was added to the list
 */
long tldlist_count(TLDList *tld){
    return (tld != NULL) ? tld->node_counts : 0;
};

/* 
    preorder push elements into iterator
 */
void preOrderPush(TLDIterator *iterator, TLDNode* p, int* index){
    if (p != NULL) {
    *(iterator->next + (*index)++) = p;
    preOrderPush(iterator, p->left, index);
    preOrderPush(iterator, p->right, index);
  }
}

/*
 * tldlist_iter_create creates an iterator over the TLDList; returns a pointer
 * to the iterator if successful, NULL if not
 */
TLDIterator *tldlist_iter_create(TLDList *tld){
    if (tld == NULL) return NULL;

    TLDIterator *iter = (TLDIterator *) malloc(sizeof(TLDIterator));
    if (iter != NULL) {
        // initialise the iterator
        iter->size = tld->size;
        iter->next = (TLDNode **) malloc(sizeof(TLDNode *) * iter->size);
        iter->index = 0;
        // end iteration
        if (!iter->next) {
            free(iter);
            return NULL;
        }
        int index = 0;
        preOrderPush(iter, tld->root, &index);//pushing elements
    }
    return iter;
};

/*
 * tldlist_iter_next returns the next element in the list; returns a pointer
 * to the TLDNode if successful, NULL if no more elements to return
 */
TLDNode *tldlist_iter_next(TLDIterator *iter){
    if(iter->index >= iter->size) return NULL;
    return *(iter->next + iter->index++);
};

/*
 * tldlist_iter_destroy destroys the iterator specified by `iter'
 */
void tldlist_iter_destroy(TLDIterator *iter){
    free(iter->next);
    iter->next=NULL;
    free(iter);
    iter=NULL;
};

/*
 * tldnode_tldname returns the tld associated with the TLDNode
 */
char *tldnode_tldname(TLDNode *node){
    if(node==NULL) return "";
    return node->tld;
};

/*
 * tldnode_count returns the number of times that a log entry for the
 * corresponding tld was added to the list
 */
long tldnode_count(TLDNode *node){
    if(node==NULL) return 0;
    return node->count;
};