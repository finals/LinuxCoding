#include <stdio.h>

typedef struct policy {
    int id;
} policy_t;

int main(int argc, char *argv[])
{
    policy_t policy;
    policy_t *p = &policy;
    policy_t **pp;

    p->id = 111;

    printf("before stap set, p->id: %d\n", p->id);

    pp = &p;

    printf("after stap set, p->id: %d, (*pp)->id: %d\n", p->id, (*pp)->id);

    return 0;
}

