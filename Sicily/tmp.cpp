#include<iostream>
#include <string.h>
using namespace std;

 
long dp[10001];

char ch[10001];


int work(char a[])

{

    int temp;

    int len;

    len=strlen(a);

    int i;

    dp[0]=1;

    temp=(ch[0]-'0')*10+(ch[1]-'0');

    if(temp>0&&temp<=26&&ch[1]!='0')

           dp[1]=2;

    else

           dp[1]=1;

    for(i=2;i<len;i++)

    {

           temp=(ch[i-1]-'0')*10+(ch[i]-'0');

           if(ch[i]=='0')

                  dp[i]=dp[i-2];

          

           else if(temp>0&&temp<=26&&ch[i-1]!='0')

                  dp[i]=dp[i-1]+dp[i-2];

           else

                  dp[i]=dp[i-1];

    }

    return dp[len-1];

}

 

int main ()
{

    while(cin>>ch)

    {

           if(ch[0]=='0')

                  break;

           cout<<work(ch)<<endl;

    }

    return 0;

}

