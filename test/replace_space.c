#include <stdio.h>
#include <malloc.h>

char * replcace_space(char *str) 
{
    char *s = str;
    char *rs = NULL, *rstr = NULL;
    int len = 0;
    
    if (str == NULL) {
        return NULL;
    }

    while (*s != '\0') {
        if (*s == ' ') {
            len += 3;
        } else {
            len++;
        }
        s++;
    }

    rstr = malloc(len+1);

    for (s = str, rs = rstr; *s != '\0'; s++) {
        if (*s == ' ') {
            *rs = '%';
            rs++;
            *rs = '2';
            rs++;
            *rs = '0';
            rs++;
        } else {
            *rs = *s;
            rs++;
        }
        
    }
    
    return rstr;
}

int main(void)
{
    char *str = " We are Happy. ";
    printf("%s\n", replcace_space(str));
    return 0;
}
