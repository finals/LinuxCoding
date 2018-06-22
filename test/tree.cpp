#include <iostream>
#include <deque>
#include <list>
#include <vector>

using namespace std;

struct node {
    int data;
    struct node *left;
    struct node *right;
};

class btree {
public:
    struct node *root;

    struct node * build(int *arr, int low, int high);
    void convert_to_list(struct node *node, list<int> *l);
    void find_path(struct node *node, vector<int> *v, int expect, int cursum);
};

struct node * btree::build(int *arr, int low, int high)
{
    if (low > high) return NULL;

    int mid = (low + high) >> 1;

    struct node *node = new(struct node);
    node->data = arr[mid];
    node->left = node->right = NULL;

    node->left  = build(arr, low, mid-1);
    node->right = build(arr, mid+1, high);

    return node;
}

void btree::convert_to_list(struct node *node, list<int> *l)
{
    if (node == NULL) return;

    convert_to_list(node->left, l);
    l->push_back(node->data);
    convert_to_list(node->right, l);
}

void btree::find_path(struct node *node, vector<int> *path, int expect, int cursum)
{
    if (node == NULL) return;

    cursum += node->data;
    path->push_back(node->data);

    if (node->left == NULL && node->right == NULL && cursum == expect) {
        for (vector<int>::iterator it = path->begin(); it != path->end(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
    }

    find_path(node->left, path, expect, cursum);
    find_path(node->right, path, expect, cursum);

    path->pop_back();
}

int main(void)
{
    int arr[] = {1,2,3,4,5,6,7,8,9};
    int len = sizeof(arr)/sizeof(int);
    list<int> l;
    btree bt;

    bt.root = bt.build(arr, 0, len-1);
    /*
    bt.convert_to_list(bt.root, &l);

    for (list<int>::iterator iter=l.begin(); iter != l.end(); ++iter) {
         cout << *iter << " ";
    }
    cout << endl;
    */

    vector<int> path;
    bt.find_path(bt.root, &path, 0, 0);
}

