#include <stdio.h>
#include <malloc.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct node *insert(struct node *node, int key)
{
    if (node == NULL) {
        node = malloc(sizeof(struct node));
        node->data = key;
        node->left = node->right = NULL;
    } else {
        if (key < node->data) {
            node->left = insert(node->left, key); 
        } else if (key > node->data) {
            node->right = insert(node->right, key);
        }
    }

    return node;
}

struct node *build_binary_search_tree(struct node *node, int *arr, int low, int high) 
{
    if (low > high) {
        return NULL;
    }

    int mid = (low + high) >> 1;
        
    node = malloc(sizeof(struct node));
    node->data = arr[mid];
    node->left = node->right = NULL;

    node->left  = build_binary_search_tree(node->left,  arr, low, mid - 1);
    node->right = build_binary_search_tree(node->right, arr, mid + 1, high); 
       
    return node;
}

void preorder_traversal(struct node *node)
{
    if (node == NULL) {
        return;
    }
    
    printf("%d ", node->data);
    preorder_traversal(node->left);
    preorder_traversal(node->right);
}

void inorder_traversal(struct node *node)
{
    if (node == NULL) {
        return;
    }

    inorder_traversal(node->left);
    printf("%d ", node->data);
    inorder_traversal(node->right);
}

void postorder_traversal(struct node *node)
{
    if (node == NULL) {
        return;
    }

    postorder_traversal(node->left);
    postorder_traversal(node->right);
    printf("%d ", node->data);
}

void mirror_tree(struct node *node)
{
    if (node == NULL) {
        return;
    }

    struct node *tmp = node->left;
    node->left = node->right;
    node->right = tmp;

    mirror_tree(node->left);
    mirror_tree(node->right);
}

int main(void)
{
    int arr[] = {1,2,3,4,5,6,7,8,9};
    int len = sizeof(arr)/sizeof(int);

    struct node *tree = build_binary_search_tree(NULL, arr, 0, len-1);

    preorder_traversal(tree);
    printf("\n");
    inorder_traversal(tree);
    printf("\n");
    postorder_traversal(tree);
    printf("\n");

    mirror_tree(tree);
    preorder_traversal(tree);
    printf("\n");
    inorder_traversal(tree);
    printf("\n");
    postorder_traversal(tree);
    printf("\n");
    
    
    return 0;
}