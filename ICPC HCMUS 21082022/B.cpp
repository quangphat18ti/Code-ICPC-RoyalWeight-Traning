#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define db double
#define nhat "B"
const int mm=305;
int n,m;
int a[mm][mm];
void nhap()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            char x; cin>>x;
            a[i][j]=(x=='#')?1:0;
        }
}
void xoaQ(int i,int j)
{
    a[i][j]=a[i][j+1]=a[i][j+2]=0;
    a[i+1][j]=a[i+1][j+2]=0;
    a[i+2][j]=a[i+2][j+1]=a[i+2][j+2]=0;
    a[i+3][j+2]=0;
    a[i+4][j+2]=0;
}
void xoaF(int i,int j)
{
    a[i][j]=a[i][j+1]=a[i][j+2]=0;
    a[i+1][j]=0;
    a[i+2][j]=a[i+2][j+1]=0;
    a[i+3][j]=0;
    a[i+4][j]=0;
}
void xuli()
{
    int re1=0,re2=0;
    for(int j=1;j<=m;j++)
    {
        int d=0;
        for(int i=1;i<=n;i++)
        {
            if(a[i][j]) d++;
            else if(d==3) xoaQ(i-d,j),re1++,d=0;
            if(d==5) xoaF(i-d+1,j),re2++,d=0;
//            for(int l=1;l<=n;l++,cout<<endl)
//                for(int r=1;r<=m;r++) cout<<a[l][r];cout<<endl;
        }
        if(d==5) xoaF(n-d+1,j),re2++,d=0;
    }
    cout<<re1<<' '<<re2;
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
