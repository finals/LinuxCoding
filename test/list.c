#include <stdio.h>
#include <malloc.h>

struct node {
    int data;
    struct node *next;
};

struct node *build(int *arr, int len, int circle)
{
     if (arr == NULL || len <= 0) {
          return NULL;
     }

     int i = 0;
     struct node *node = NULL, *cur = NULL, *head = NULL;

     for (i = 0; i < len; ++i) {
         node = malloc(sizeof(struct node));
         if (node == NULL) {
            return NULL;
        }

        node->data = arr[i];
        node->next = NULL;
        if (cur != NULL) {
            cur->next = node;
        } else {
            head = node;
        }
        cur = node;
     }

     if (circle) {
        cur->next = head; //构成循环链表
     }

     return head;
}

void print_list(struct node *head)
{
    struct node *record_head = head;
    int flag = 0;
    while (head != NULL) {
        if (flag && head == record_head) {
            printf("head [circle]\n");
            break; //破开循环链表
        }
        flag = 1;
        if (head->next != NULL)
            printf("%d -> ", head->data);
        else 
            printf("%d\n", head->data);

        head = head->next;
    }
}

int backwards_k(struct node *head, int k) 
{
    if (head != NULL || k <= 0) {
        return -1;
    }

    struct node *first = head, *second = head;
    int i = 0;

    for (i = 0; i < k; ++i) {
        if (first->next == NULL) {
            return -1;
        }
        first = first->next;
    }

    while (first != NULL) {
        second = second->next;
        first = first->next;
    }

    return second->data;
}

int middle_list(struct node *head) 
{
    if (head == NULL) {
        return -1;
    }
    
    struct node *stepOne = head, *stepTwo = head;

    while (stepTwo->next != NULL && stepTwo->next->next != NULL) {
        stepOne = stepOne->next;
        stepTwo = stepTwo->next->next;
    }

    return stepOne->data;
}

int is_circle(struct node *head)
{
    struct node *stepOne = head, *stepTwo = head;
    int flag = 0;

    while (stepTwo->next != NULL && stepTwo->next->next != NULL) {
        if (flag && stepOne == stepTwo) {
            return 1;
        }

        flag = 1;
        stepOne = stepOne->next;
        stepTwo = stepTwo->next->next;
    }

    return 0;
}

struct node *reverse(struct node *head)
{
    struct node *next = NULL;
    struct node *rhead = NULL;
    
    while (head != NULL) {
        next = head->next;

        if (rhead == NULL) {
            rhead = head;
            rhead->next = NULL;
        } else {
            head->next = rhead;
            rhead = head;
        }

        head = next;
    }

    return rhead;
}

struct node *merge_sorted_list(struct node *head1, struct node *head2)
{
    if (head1 == NULL) {
        return head2;
    }
    if (head2 == NULL) {
        return head1;
    }
   
    struct node *merge_head = NULL, *cur = NULL;
    struct node *next1 = NULL, *next2 = NULL;

    while (head1 != NULL && head2 != NULL) {
        if (merge_head == NULL) {
            if (head1->data <= head2->data) {
                next1 = head1->next;
                merge_head = head1;
                head1 = next1;
            } else {
                next2 = head2->next;
                merge_head = head2;
                head2 = next2;
            }
            cur = merge_head;
        } else {
            if (head1->data <= head2->data) {
                next1 = head1->next;
                cur->next = head1;
                head1 = next1;
            } else {
                next2 = head2->next;
                cur->next = head2;
                head2 = next2;
            }
            cur = cur->next;      
        }
    }

    if (head1 != NULL) {
        cur->next = head1;
    }
    if (head2 != NULL) {
        cur->next = head2;
    }

    return merge_head;
}

int main(void)
{
    int i = 1, data = -2, k = 13;
    struct node *head1 = NULL, *head2 = NULL, *cur = NULL;
    int arr1[] = {1,4,5,7,9,11,13,15,17,19};
    int arr2[] = {2,4,12,16};
    
    head1 = build(arr1, sizeof(arr1)/sizeof(int), 0);
    head2 = build(arr2, sizeof(arr2)/sizeof(int), 0);

    print_list(head1);
    print_list(head2);
    print_list(merge_sorted_list(head1, head2));
    //data = backwards_k(head, k);
    //printf("backwards %d data: %d\n", k, data);
    //data = middle_list(head);
    //printf("middle data: %d\n", data);
    //data = is_circle(head);
    //printf("circle: %d\n", data);
    //cur = reverse(head);
    //print_list(cur);
    
    return 0;
}
