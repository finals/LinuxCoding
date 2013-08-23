#include <iostream>
using namespace std;

long long combine(long long n, long long m)
{
    long long  result = 1;
    int i;

    for (i = 1; i <= m; ++i) {
        result = result*(n - i +1) / i;
    }
    return result;
}

int main()
{
    long long n, m, k;
    while(cin>>n>>m, m+n) {
        k = n > m ? m:n;
        cout<<combine(n+m, k)<<endl;
    }
    
    return 0;
}
