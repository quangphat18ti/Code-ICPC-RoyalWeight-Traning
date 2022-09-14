/**
 *		Author:		Duck
 *		created:	13-09-2022	22:22:01
**/


/*
-duyet phan tap
-duyet 20 cai dau tien luu vao g1[]
-duyet 20 cai sau luu vao g2[]

-trang thai g2[i] lay duoc g1[1011] ==> se lay duoc g1[1001] hoac g1[1010]...
--> toi uu cac trang thai g1[] voi so luong bit tu be -> lon
-vd: g1[1011] = max(g1[1011] , g1[1010])...

-voi moi trang thai g2[i] se tim duoc dung 1 trang thai g1[j] thoa (so bit cua j la lon nhat)
-ma g1[j] da duoc toi uu 
==> ket qua se la max(g2[i] + g1[j tim duoc])
*/

#include <bits/stdc++.h>
#define ll long long
#define se second
#define fi first
#define fd(i, a, b) for (ll i = a; i >= b; i--)
#define fu(i, a, b) for (ll i = a; i <= b; i++)
#define SZ(x) ((int)(x).size())
#define fastIO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define setbit(x , i) (x | (1LL << i))
#define getbit(x , i) ((x >> i) & 1LL)
#define offbit(x , i) (x & ~(1LL << i))
#define __builtin_popcount __builtin_popcountll

using namespace std;

const ll N = (ll)45;
const ll M = (ll)2e6;
typedef pair<ll , ll> pi;

vector<ll> a[N];
ll n , b[N][N] , m;
pi g1[M] , g2[M];
ll re1[N] , re2[N] , re12[N];

void input()
{
    freopen("input.txt" , "r" , stdin);
    freopen("out.txt" , "w" , stdout);
}

void mem()
{
    //bit[i] == 1 ==> co the lay thang i
    fu(i,20,39)
    {
        ll mask = (1LL << 20) - 1;
        fu(j,0,19)
        {
            if(b[i][j] == 1)
            {
                mask = offbit(mask , j);
            }
        }
        re12[i] = mask;
    }
    fu(i,0,19)
    {
        ll mask = (1LL << 20) - 1;
        fu(j,0,19)
        {
            if(b[i][j] == 1)
            {
                mask = offbit(mask , j);
            }
        }
        re1[i] = mask;
    }
    fu(i,20,39)
    {
        ll mask = (1LL << 20) - 1;
        fu(j,20,39)
        {
            if(b[i][j] == 1)
            {
                mask = offbit(mask , j-20);
            }
        }
        re2[i] = mask;
    }
}

void maximize(pi &res , pi x)
{
    if(x.fi > res.fi)
        res = x;
    return ;
}

pi dp(ll mask , ll limit , pi *f , ll base , ll canreach , ll *re)
{
    if(__builtin_popcount(mask) >= limit)
        return pi(limit , mask);
    
    if(f[mask] != pi(0 , 0))
        return f[mask];

    pi temp;
    pi res = pi(__builtin_popcount(mask) , mask);
    //first: amount
    //se: bitmask

    fu(i,0,limit-1)
    {
        //co the lay duoc i
        if(getbit(mask , i) == 0 && getbit(canreach , i) == 1)
        {
            temp = dp(setbit(mask , i) , limit , f , base , canreach & re[i+base] , re);
            maximize(res , temp);
        }
    }

    return f[mask] = res;
}

void dissHead()
{
    dp(0 , min(20LL , n) , g1 , 0 , (1LL << 20) - 1 , re1);
    fu(i,0,(1LL << 20) - 1)
    {
        ll mask = i;
        fu(j,0,19)
        {
            maximize(g1[setbit(mask , j)] , g1[i]);
        }
    }
}

void dissTail()
{
    dp(0 , max(0LL , n - 20) , g2 , 20 , (1LL << 20) - 1 , re2);
    //tim j thoa

    pi res = pi(0 , 0);
    fu(i,0,(1LL << 20) - 1)
    {
        ll mask = i , canreach = ((1LL << 20) - 1);
        fu(j,0,19)
        {
            if(getbit(mask , j) == 1)
            {
                canreach = canreach & re12[j+20];
            }
        }
        pi temp = pi(g2[i].fi + g1[canreach].fi , (g2[i].se << 20) | g1[canreach].se);
        maximize(res , temp);
    }
    cout << res.fi << "\n";
    fu(i,0,39)
    {
        if(getbit(res.se , i) == 1)
            cout << i << " ";
    }
}

int main()
{
    fastIO;
    cin >> n >> m;
    fu(i,1,m)
    {
        ll x , y;
        cin >> x >> y;
        b[x][y] = 1;
        b[y][x] = 1;
    }   

    mem();
    dissHead();
    dissTail();
}
/* stuff you should look for
4 4
0 1
1 2
2 3
3 0
*/