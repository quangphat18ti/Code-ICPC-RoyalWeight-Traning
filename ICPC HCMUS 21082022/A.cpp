#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define db double
#define nhat "A"
const int mm=305;
int st[mm];
void nhap()
{

}
ll tinh(ll x)
{
    for(ll i=x/2;i>=1;i--)
        if(__gcd(x,i)==1) return i;
}
void xuli()
{
    int t; cin>>t;
    for(int i=1;i<=t;i++)
    {
        ll x;
        cin>>x; cout<<tinh(x)<<endl;
    }
}
int main()
{
//    freopen(nhat".inp","r",stdin);
//    freopen(nhat".out","w",stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    nhap();
    xuli();
}
