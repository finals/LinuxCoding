#include <stdio.h>
#include <string.h>

void reverse(char *s, int size)
{
    if (size <= 0) return;

    char *start = s, *end = s + size;
    char tmp;

    while (start < end) {
       tmp = *start;
       *start = *end;
       *end = tmp;

       start++;
       end--;
    }
}

void reverse_sentense(char *s, int size)
{
    if (size <= 0) return;

    reverse(s, strlen(s) - 1);

    int i = 0;
    int start = 0, end = 0;

    while (i <= size) {
        if (s[i] == ' ') {
            end = i - 1;
            reverse(s+start, end-start);
            start = i + 1;
        }
        ++i;
    }
}

void left_rotate(char *s, int k)
{
    int size = strlen(s);

    k = k % size;

    reverse(s, k-1);
    reverse(s+k, size-k-1);
    reverse(s, size-1);
}

int main(void)
{
    //char s[] = "I am a Student.";

    //reverse_sentense(s, strlen(s));

    char s[] = "abcdefg";

    left_rotate(s, 3);

    printf("reverse: %s\n", s);
    
    return 0;
}

