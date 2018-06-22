#include <stdio.h>
#include <string.h>
#include <malloc.h>

void swap(char *s, int left, int right)
{
    if (left == right) return;

    char tmp = s[left];
    s[left] = s[right];
    s[right] = tmp;
}

void permutation(char *s, int left, int right)
{
    int i = left;
    if (s == NULL) {
        return;
    }

    if (left == right) {
        printf("%s\n", s);
        return;
    } else {
        for (i = left; i < right; ++i) {
            if (left != i && s[left] == s[i]) continue;
            swap(s, left, i);
            permutation(s, left+1, right);
            swap(s, left, i);
        }
    }
}

void combination(char *s, int len)
{
    int n = 1 << len; //2^len
    int i = 0, j = 0;

    for (i = 1; i < n; i++) {

        for (j = 0; j < len; j++) {
            if (i & (1<<j)) {
                printf("%c", s[j]);
            }
        }
        printf("\n");
    }
    
}

void combination2(char *str)
{
	if(str == NULL)
		return ;
	int len = strlen(str);
	int n = 1<<len;
	for(int i=1;i<n;i++)    //从 1 循环到 2^len -1
	{
		for(int j=0;j<len;j++)
		{
			int temp = i;
			if(temp & (1<<j))   //对应位上为1，则输出对应的字符
			{
				printf("%c",*(str+j));
			}
		}
		printf("\n");
	}
}


#define STR "abc"
#define STRLEN (strlen(STR))

int main(void)
{
    char *s = malloc(STRLEN+1);
    strcpy(s, STR);
    s[STRLEN] = '\0';
    //permutation(s, 0, STRLEN);
    combination(s, STRLEN);
    //combination2(s);
    free(s);
    return 0;
}
