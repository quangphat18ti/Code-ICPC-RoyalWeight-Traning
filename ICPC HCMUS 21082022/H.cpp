#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define db double
#define nhat "H"
#define pb push_back
const int mm=2e5+5;
const int oo=1e9+7;
int n,m,k;
struct ii
{
    int v,w;
};
vector<ii> e[mm],en[2][mm];
void nhap()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int x,y,z; cin>>x>>y>>z;
        e[x].pb({y,z});
        e[y].pb({x,z});
    }
}

int dd[mm],dd1[mm];
queue<int> q;
void bfs(int s)
{
    for(int i=1;i<=n;i++) dd[i]=oo;
    dd[s]=0;
    q.push(s);
    while(q.size())
    {
        int u=q.front(); q.pop();
        for(ii c:e[u])
            if(dd[c.v]>dd[u]+1)
                dd[c.v]=dd[u]+1,q.push(c.v);
    }
}
void ddnn_1_n()
{
    bfs(1);
    for(int i=1;i<=n;i++) dd1[i]=dd[i];
    bfs(n);
    k=dd1[n];
}
void build()
{
    for(int i=1;i<=n;i++)
        for(ii j:e[i])
            if(dd1[i]+1+dd[j.v]==k)
                en[0][i].pb(j),en[1][j.v].pb({i,j.w});
}

struct val
{
    int mi,tvmi;
    int ma,tvma;
};val st[2][mm];
int kt[2][mm];
void loang(int s,int id)
{
    q.push(s); kt[id][s]=1;
    while(q.size())
    {
        int u=q.front(); q.pop();
        for(ii nx:en[id][u])
        {
            if(!kt[id][nx.v]) kt[id][nx.v]=1,q.push(nx.v);
            if(st[id][nx.v].ma<max(st[id][u].ma,nx.w))
                st[id][nx.v].tvma=u,st[id][nx.v].ma=max(st[id][u].ma,nx.w);
            if(st[id][nx.v].mi>min(st[id][u].mi,nx.w))
                st[id][nx.v].tvmi=u,st[id][nx.v].mi=min(st[id][u].mi,nx.w);
        }
    }
}
void tim_min_max_1_n()
{
    for(int i=1;i<=n;i++)
        for(int j=0;j<2;j++)
            st[j][i]={oo,-oo},kt[j][i]=0;
    loang(1,0);
    loang(n,1);
}

int kq[mm];
void xuli()
{
    ddnn_1_n();
    build();
    tim_min_max_1_n();
    int re=-oo,jj,cc=0;
    for(int i=2;i<n;i++)
    {
        if(re<st[0][i].ma-st[1][i].mi)
            re=st[0][i].ma-st[1][i].mi,jj=i;
        if(re<st[1][i].ma-st[0][i].mi)
            re=st[1][i].ma-st[0][i].mi,jj=i,cc=1;
    }
    if(k==1)
    {
        cout<<"1\n1 "<<n;
        return;
    }
    cout<<k<<endl;
    if(!cc)
    {
        int tam=jj,r=0;
        while(tam!=1) kq[++r]=tam,tam=st[0][tam].tvma;
        kq[++r]=tam;
        for(int i=r;i>=1;i--) cout<<kq[i]<<' ';
        while(jj!=n) jj=st[1][jj].tvmi,cout<<jj<<' ';
    }
    else
    {
        int tam=jj,r=0;
        while(tam!=1) kq[++r]=tam,tam=st[0][tam].tvmi;
        kq[++r]=tam;
        for(int i=r;i>=1;i--) cout<<kq[i]<<' ';
        while(jj!=n) jj=st[1][jj].tvma,cout<<jj<<' ';
    }
}
int main()
{
//    freopen(nhat".inp","r",stdin);
//    freopen(nhat".out","w",stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t; t=1; while(t--){
    nhap();
    xuli();}
}
