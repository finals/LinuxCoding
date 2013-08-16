#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s, t;
    bool flag;

    while(cin>>s>>t) {
        int i=0, j= 0;
        while(s[i] && t[j]) {
            if( s[i] == t[j] ) {
                ++i;
                ++j;
            }
            else
                ++j;
        }
        if (i == s.size())
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;
    }
    
    return 0;
}
