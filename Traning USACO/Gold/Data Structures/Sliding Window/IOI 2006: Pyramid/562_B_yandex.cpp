#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define db double
#define nhat "562_B_yandex"
const int mm = 1e3 + 5;
int n, m, a, b, c, d;
int val[mm][mm];
int bi[mm][mm],sum[mm][mm];
int p[mm][mm];
struct point
{
    int x, y;
};
ostream & operator << (ostream &out, point A)
{
    out<<A.y<<' '<<A.x;
}
void nhap()
{
    cin>>m>>n>>b>>a>>d>>c;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
        {
            cin >> sum[i][j];
            sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
}
deque<int> dq[mm];
int getSum(point A, point C)
{
    return sum[C.x][C.y] - sum[C.x][A.y - 1] - sum[A.x - 1][C.y] + sum[A.x - 1][A.y - 1];
}
void khoiTao()
{
    for(int j = d + 1; j <= m; j++)
        while(dq[j].size()) dq[j].pop_back();
    for(int i = c + 1; i <= n; i++)
        for(int j = d + 1; j <= m; j++)
            p[i][j] = getSum({i - c + 1, j - d + 1}, {i, j});
}
void solve(point &day, point &phong)
{
    int re = 0;
    for(int i = c + 1; i <= n; i++)
    {
        for(int j = d + 1; j < m; j++)
            while(dq[j].size() && dq[j].front() <= i - a + c) dq[j].pop_front();
        if(i >= a)
        {
            deque<int> tam;
            for(int j = d + 1; j <= m; j++)
            {
                if(j < b)
                {
                    while(dq[j].size() && tam.size() && p[dq[tam.back()].front()][tam.back()] >= p[dq[j].front()][j]) tam.pop_back();
                    tam.push_back(j);
                    continue;
                }
                while(tam.size() && tam.front() <= j - b + d) tam.pop_front();
                int sum1 = getSum({i - a + 1, j - b + 1}, {i, j});
                if(sum1 - p[dq[tam.front()].front()][tam.front()] > re)
                {
                    re = sum1 - p[dq[tam.front()].front()][tam.front()];
                    day = {i - a + 1, j - b + 1};
                    phong = {dq[tam.front()].front() - c + 1, tam.front() - d + 1};
                }
//                cout<<p[dq[tam.front()].front()][tam.front()]<<endl;
                while(dq[j].size() && tam.size() && p[dq[tam.back()].front()][tam.back()] >= p[dq[j].front()][j]) tam.pop_back();
                tam.push_back(j);
//                cout<<i<<' '<<j<<endl;
            }
        }
        for(int j = d + 1; j < m; j++)
        {
            while(dq[j].size() && p[dq[j].back()][j] >= p[i][j]) dq[j].pop_back();
            dq[j].push_back(i);
        }
    }
}
void xuLi()
{
    khoiTao();
    point day, phong;
    solve(day, phong);
    cout << day << endl << phong;
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

