/* SOJ problem 1001 AlphaCode.*/

#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE 10000

char ch[ARRAY_SIZE];
long dp[3];

int count_decode_alpha(char c[])
{
    int temp = 0;
    int i = 0;
    int len = strlen(c);
    dp[0] = dp[1] = dp[2] = 1;

    for ( i = 1; i < len; ++i ) {
        dp[0] = dp[1];
        dp[1] = dp[2];
        temp = (ch[i-1]-'0')*10 + (ch[i]-'0');
        if ( '0' == ch[i] )
            dp[2] = dp[0];
        else if ( temp >= 10 && temp <= 26 )
            dp[2] = dp[1] + dp[0];
        else 
            dp[2] = dp[1];
        
    }
    return dp[2];
}

int main()
{
    while(scanf("%s", ch) != EOF) {
        
        if ('0' == ch[0])
            break;
        printf("%d\n", count_decode_alpha(ch));

    }
    
    return 0;
}

