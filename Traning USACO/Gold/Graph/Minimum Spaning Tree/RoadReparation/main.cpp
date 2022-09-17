/*
LINK: https://cses.fi/problemset/task/1675
Tìm cây khung nhỏ nhất
*/

#include<bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define fi first
#define se second
#define sz(_s) int(s.size())
#define mp make_pair

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pii> vii;
typedef vector<vector<pair<int,int>>> dsk;

const int MAX = 1e9 + 5;

int n, m;

class Edge{
public:
    int u, v, w;

    friend istream& operator >> (istream& in, Edge &A) {
        in >> A.u >> A.v >> A.w;
        --A.u;
        --A.v;
        return in;
    }

    friend ostream& operator << (ostream& out, const Edge &A) {
        out << A.u << " -> " << A.v << " : " << A.w;
        return out;
    }
};
vector<Edge> edges;

dsk adj;

void initData(){
    cin >> n >> m;
    edges.resize(m);
    for(auto &e: edges) cin >> e;

    adj.assign(n, vii(0));
    for(auto [u, v, w] : edges) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
}

ll solve() {
    ll weight = 0;
    vector<int> min(n, MAX); // min[u] --> MST = MAX

    min[0] = 0;
    set<pair<int,int>> q;
    q.insert({0, 0});
    vector<bool> visited(n, false);

    for(int i = 0; i < n; ++i) {
        if(q.empty()) {
            return -1;
        }

        int u = q.begin() -> second;
        visited[u] = true;
        weight += q.begin() -> first;
        q.erase(q.begin());

        for(auto [v, w] : adj[u]) {
            if(!visited[v] && w < min[v]) {
                q.erase({min[v], v});
                min[v] = w;
                q.insert({min[v], v});
            }
        }
    }

    return weight;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    
    int t = 1; 
    //cin >> t;
    while(t--) {
        initData();
        ll ans = solve();
        if(ans == -1) cout << "IMPOSSIBLE\n";
        else cout << ans << endl;
    }
}