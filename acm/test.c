#include <stdio.h>
#include <string.h>

void swap_char(char *a, char *b)
{
    char t = *a;
	*a = *b;
	*b = t;
}

/* k ��ʾ��ǰѡȡ���ڼ�������m��ʾ���ж����� */
void AllRange(char *pszStr, int k, int m)
{
	if(k == m) {
        static int s_i = 1;
        printf("The%3d : %s\n", s_i++, pszStr);
	}
	else {
		for (int i = k; i < m; ++i){
			swap_char(pszStr+k, pszStr+i);
			AllRange(pszStr, k + 1, m); //�ݹ�����k+1��m
			swap_char(pszStr+k, pszStr+i); //�ָ��ֳ�
		}
	}
}

int main()
{
    char str[] = "1234";
	AllRange(str,0,strlen(str));
	return 0;
}

