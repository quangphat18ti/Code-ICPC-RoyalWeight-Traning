#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define db double
#define nhat "apio09p1_dmoj"
const int mm = 1505;
const int oo = 1.5e9;
int n, m, k;
int a[mm][mm];
int s[mm][mm];
int maBT[mm][mm];
int maBD[mm][mm];
int maNT[mm][mm];
int maND[mm][mm];
int maB[mm];
int maN[mm];
int maT[mm];
int maD[mm];
void nhap()
{
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
        {
            cin >> a[i][j];
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];
        }
}
int get(int i, int j, int u, int v)
{
    return s[u][v] - s[u][j - 1] - s[i - 1][v] + s[i - 1][j - 1];
}
void xayMax()
{
    // xay huong B T
    for(int i = k; i <= n; i++)
        for(int j = k; j <= m; j++)
            maBT[i][j] = max({maBT[i][j - 1], maBT[i - 1][j], get(i - k + 1, j - k + 1, i, j)});
    // xay huong B D
    for(int i = k; i <= n; i++)
        for(int j = m - k + 1; j >= 1; j--)
            maBD[i][j] = max({maBD[i][j + 1], maBD[i - 1][j], get(i - k + 1, j, i, j + k - 1)});
    // xay huong N D
    for(int i = n - k + 1; i >= 1; i--)
        for(int j = m - k + 1; j >= 1; j--)
            maND[i][j] = max({maND[i][j + 1], maND[i + 1][j], get(i, j, i + k - 1, j + k - 1)});
    // xay huong N T
     for(int i = n - k + 1; i >= 1; i--)
        for(int j = k; j <= m; j++)
            maNT[i][j] = max({maNT[i][j - 1], maNT[i + 1][j], get(i, j - k + 1, i + k - 1, j)});
    // xay huong B
    for(int i = k; i <= n; i++)
    {
        maB[i] = maB[i - 1];
        for(int j = k; j + k <= m; j++)
            maB[i] = max(maB[i], maBT[i][j] + maBD[i][j + 1]);
        if(i >= 2 * k)
        {
            for(int j = k; j <= m; j++)
                maB[i] = max(maB[i], get(i - k + 1, j - k + 1, i, j)  + maBT[i - k][m]);
        }
    }
    // xay huong N
    for(int i = n - k + 1; i >= 1; i--)
    {
        maN[i] = maN[i + 1];
        for(int j = k; j + k <= m; j++)
            maN[i] = max(maN[i], maNT[i][j] + maND[i][j + 1]);
        if(i + 2 * k - 1 <= n)
        {
            for(int j = k; j <= m; j++)
                maN[i] = max(maN[i], get(i, j - k + 1, i + k - 1, j) + maNT[i + k][m]);
        }
    }
    // xay huong D
    for(int j = m - k + 1; j >= 1; j--)
    {
        maD[j] = maD[j + 1];
        for(int i = k; i + k <= n; i++)
            maD[j] = max(maD[j], maBD[i][j] + maND[i + 1][j]);
        if(j + 2 * k - 1 <= m)
        {
            for(int i = k; i <= n; i++)
                maD[j] = max(maD[j], get(i - k + 1, j, i, j + k - 1) + maBD[n][j + k]);
        }
    }
    // xay huong T
    for(int j = k; j <= m; j++)
    {
        maT[j] = maT[j - 1];
        for(int i = k; i + k <= n; i++)
            maT[j] = max(maT[j], maBT[i][j] + maNT[i + 1][j]);
        if(j >= 2 * k)
        {
            for(int i = k; i <= n; i++)
                maT[j] = max(maT[j], get(i - k + 1, j - k + 1, i, j) + maBT[n][j - k]);
        }
    }
}
void xuLi()
{
    xayMax();
    int re = 0;
//    for(int j = m - k + 1; j >= 1; j--) cout<<maD[j]<<endl;
    for(int i = k; i + k <= n; i++)
        for(int j = k; j + k <= m; j++)
            re = max({re, maND[i + 1][1] + maB[i], maBT[i][m] + maN[i + 1], maND[1][j + 1] + maT[j], maBT[n][j] + maD[j + 1]});
//            cout<<i<<' '<<j<<' '<<re<<' '<< maND[i + 1][1] + maB[i]<<endl;
    cout << re;
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

