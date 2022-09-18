#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define db double
#define nhat "566_A_yandex"
const int mm = 250 + 5;
const int oo = 1e9 + 7;
int n, m, q, k;
int s[mm][mm];
int fx[mm][mm], fn[mm][mm];
void nhap()
{
    cin >> n >> m >> q >> k;
    for(int i = 1; i <= q; i++)
    {
        int x, y; cin >> x >> y;
        s[x][y]++;
    }
    for(int i = 0; i <= n + 1; i++)
        for(int j = 0; j <= m + 1; j++)
            fx[i][j] = oo,
            fn[i][j] = oo;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
}
int ctro[mm];
int getSum(int i, int j, int u, int v)
{
    return s[u][v] - s[u][j - 1] - s[i - 1][v] + s[i - 1][j - 1];
}
void khoiTaoConTro(int val)
{
    for(int i = 1; i <= n; i++) ctro[i] = val;
}
void xayFx()
{
    for(int i = 1; i <= n; i++)
    {
        khoiTaoConTro(1);
        for(int j = 1; j <= m; j++)
        {
            fx[i][j] = min(fx[i - 1][j], fx[i][j - 1]);
            for(int z = i; z >= 1; z--)
            {
                while(getSum(z, ctro[z], i, j) >= k) ctro[z]++;
                if(getSum(z, ctro[z] - 1, i, j) == k)
                    fx[i][j] = min(fx[i][j], 2 * (i - z + 1 + j - ctro[z] + 2));
            }
//            cout<<i<<' '<<j<<' '<<fx[i][j]<<endl;
        }
    }
}
void xayFn()
{
    for(int i = n; i >= 1; i--)
    {
        khoiTaoConTro(m);
        for(int j = m; j >= 1; j--)
        {
            fn[i][j] = min(fn[i + 1][j], fn[i][j + 1]);
            for(int z = i; z <= n; z++)
            {
                while(getSum(i, j, z, ctro[z]) >= k) ctro[z]--;
                if(getSum(i, j, z, ctro[z] + 1) == k)
                    fn[i][j] = min(fn[i][j], 2 * (z - i + 1 + ctro[z] - j + 2));
            }
        }
    }
}
void xuLi()
{
    xayFx();
    xayFn();
    int re = oo;
    for(int i = 1; i < n; i++) re = min(re, fx[i][m] + fn[i + 1][1]);
    for(int j = 1; j < m; j++) re = min(re, fx[n][j] + fn[1][j + 1]);
    if(re - oo) cout << re;
    else cout << "NO";
}
int main()
{
//    freopen(nhat".inp","r",stdin);
//    freopen(nhat".out","w",stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t; t=1;
    for(int i=1;i<=t;i++){
    nhap();
    xuLi();}
}

