#include<bits/stdc++.h>
#define ll long long 
#define fi first 
#define se second 
#define fu(i,a,b) for(ll i=a ; i <= b ; i++)
#define fd(i,a,b) for(ll i=a ; i >= b ; i--)
using namespace std;
const ll N = (ll)2e5+5;
const ll inf = (ll)1e15;
typedef pair<ll , ll> pi;
typedef pair<ll , pi> pii;
typedef pair<pi , pi> piii;
vector<pi> a[N];
pii b[N] , c[N] , edge[N];
ll n , m , min_dis = inf , trace1[N] , trace2[N];
void diss(ll s , ll t , pii *gg , ll *trace)
{
    priority_queue<piii , vector<piii> , greater<piii> > q;
    fu(i,1,n)
    {
        ///distance , min , max
        gg[i] = pii(inf , pi(inf , -inf));
    }
    gg[s] = pii(0 , pi(inf , -inf));
    q.push(piii(pi(0 , s) , pi(inf , -inf)));

    while ((int)q.size())
    {
        piii temp = q.top();
        q.pop();

        ll du = temp.fi.fi;
        ll u = temp.fi.se;
        ll mi = temp.se.fi;
        ll ma = temp.se.se;
        
        if(pii(du , pi(mi , ma)) != gg[u] || u == t)
            continue;

        for(auto i:a[u])
        {
            ll v = i.fi;
            ll uv = i.se;

            if(du + 1 < gg[v].fi)
            {
                gg[v] = pii(du + 1 , pi(min(uv , mi) , max(uv , ma)));
                trace[v] = u;
                q.push(piii(pi(gg[v].fi , v) , gg[v].se));
            }
            else if(du + 1 == gg[v].fi && (max(ma , uv) > gg[v].se.se || min(mi , uv) < gg[v].se.fi))
            {
                gg[v] = pii(du + 1 , pi(min({gg[v].se.fi , uv , mi}) , max({gg[v].se.se , uv , ma})));
                trace[v] = u;
                q.push(piii(pi(gg[v].fi , v) , gg[v].se));
            }
            // cout << "dij" << v << " " << gg[v].fi << " " << gg[v].se.fi << " " << gg[v].se.se << "\n";
        }
    }
    // cout << "\n";
    min_dis = min(min_dis , gg[t].fi);
    return ;
}

void maximize(ll &x , ll y , ll &vt1 , ll &vt2 , ll u , ll v)
{
    if(y > x)
    {
        x = y;
        vt1 = u;
        vt2 = v;
    }
    return ;
}
void doit(ll u , ll v , ll val , ll &res , ll &vt1 , ll &vt2)
{
    if(b[u].fi + c[v].fi + 1 != min_dis)
        return ;
    ll mi1 = min(b[u].se.fi , val) , mi2 = min(c[v].se.fi , val);
    ll ma1 = max(b[u].se.se , val) , ma2 = max(c[v].se.se , val);
    // cout << u << " " << v << " " << ma1 << " " << mi1 << " " << ma2 <<" " << mi2 << "\n";
    maximize(res , max(ma1 - mi2 , ma2 - mi1) , vt1 , vt2 , u , v);
}
void sol()
{
    ll res = -1 , vt1 = -1 , vt2 = -1;
    fu(i,1,m)
    {
        ll u = edge[i].se.fi;
        ll v = edge[i].se.se;
        doit(u , v , edge[i].fi , res , vt1 , vt2);
        doit(v , u , edge[i].fi , res , vt1 , vt2);

    }
    // fu(i,1,n)
    // {
    //     /// b : 1 --> n
    //     /// c : n --> 1
    //     if(b[i].fi + c[i].fi == min_dis)
    //     {
    //         if(b[i].fi == 0)


    //         maximize(res , b[i].se.se - c[i].se.fi , vt , i);
    //         maximize(res , c[i].se.se - b[i].se.fi , vt , i);
    //     }
    // }
    // ll vtt = vt;
    vector<ll> path;
    path.push_back(vt1);
    while (trace1[vt1] != 0)
    {
        path.push_back(trace1[vt1]);
        vt1 = trace1[vt1];
    }
    reverse(path.begin() , path.end());

    // vt = vtt;
    path.push_back(vt2);
    while (trace2[vt2] != 0)
    {
        path.push_back(trace2[vt2]);
        vt2 = trace2[vt2];
    }
    
    cout << (int)path.size()-1 << "\n";
    for(auto i:path)
        cout << i << " ";
    // cout << vt << "\n";
    return ;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    fu(i,1,m)
    {
        ll x , y , z;
        cin >> x >> y >> z;
        edge[i] = pii(z , pi(x , y));
        a[x].push_back(pi(y , z));
        a[y].push_back(pi(x , z));
    }

    diss(1 , n , b , trace1);
    diss(n , 1 , c , trace2);
    
    // cout << min_dis << "\n";
    sol();

}
/*
6 6
1 2 1
2 3 3
3 6 5
6 4 2
4 5 4
5 1 7
*/