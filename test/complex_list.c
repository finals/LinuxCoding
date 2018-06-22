#include <stdio.h>
#include <malloc.h>

struct node {
    int data;
    struct node *next;
    struct node *sibling;
};

void clone(struct node *head)
{
    if (head == NULL) return;

    struct node *cur = head, *next = head->next, *tmp = NULL;
    while(cur != NULL) {
        tmp = malloc(sizeof(struct node));
        if (tmp == NULL) {
            return;
        }

        tmp->data = cur->data;
        tmp->next = next;
        cur->next = tmp;

        cur = next;
        if (next != NULL) {
            next = next->next;
        }
        tmp = NULL;
    }
}

void reconnect(struct node *head)
{
    if (head == NULL) return;

    struct node *cur = head, *clone = cur->next, *next = cur->next->next;

    while (cur != NULL) {
        if (cur->sibling != NULL) {
            clone->sibling = cur->sibling->next;
        }

        cur = next;
        clone = cur->next;
        next = cur->next->next;
    }
}

void split(struct node *head, struct node *chead) 
{
    struct node *cur = head, *clone = cur->next, *next = cur->next->next;

    chead = clone;
    while (cur != NULL) {
        cur->next = next;
        clone->next = next->next;
        cur = next;
        next = next->next->next;
    }
}

int main(void)
{

    return 0;
}

