#include <stdio.h>

void hanoi(char A, char B, char C, int n)
{
    if ( 1 == n)
        printf("Move disk %d from %c to %c\n", n, A, C);
    else {
        hanoi(A, C, B, n-1);
        printf("Move disk %d from %c to %c\n", n, A, C);
        hanoi(B, A, C, n-1);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    hanoi('A', 'B', 'C', n);
    return 0;
}
