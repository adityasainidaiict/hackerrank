#include <iostream>
#include <bitset>
using namespace std;
int main() 
{
    char in;
    bitset<26> A;
    while(cin>>in) A.flip(in-'a');
    if(A.count()<=1) cout<<"YES";
    else cout<<"NO";
    return 0;
}
