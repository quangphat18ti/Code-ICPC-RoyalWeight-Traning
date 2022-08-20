#include<bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()

typedef pair<int,int> pii;
typedef vector<pii> vii;
typedef long long ll;

const int MOD = 998244353;
const ll oo = 1e18;

int n, m;
vector<int> adj[1005];
vector<int> value;

struct Edge{
    int u;
    int v;
};
vector<Edge> edges;

void initData() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) adj[i].clear();

    value.clear();
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        value.push_back(x);
    }

    edges.clear();
    while(m--) {
        int u, v; cin >> u >> v; --u, --v;
        adj[u].push_back(v);
        edges.push_back({u, v});
    }
}

namespace Topo_Sort_graph{
    void dfsTopo(int u, vector<int> &visited, vector<int> &topo) {
        visited[u] = 1;
        for(auto v : adj[u]) {
            if(visited[v] == 1) {  /// u là 1 nhánh con của v
                cout << "graph contains a cycle\n";
                exit(-1);
            }
            if(!visited[v]) dfsTopo(v, visited, topo);
        }
        topo.push_back(u);
        visited[u] = 2; /// out dfs
    }

    vector<int> find_topo(int &n, vector<int> adj[1005]) {
        vector<int> topo;
        vector<int> visited = vector<int>(n);
        for(int i = 0; i < n; i++) {
            if(visited[i]) continue;
            dfsTopo(i, visited, topo);
        }
        reverse(all(topo));
        return topo;
    }
}

int check_N_Time() {
    for(int time = 1; time <= n; time++) {
        stack<int> st;
        for(int u = 0; u < n; ++u)
            if(value[u]) st.push(u);

        if(st.empty()) return time - 1;

        while(!st.empty()) {
            int u = st.top();
            st.pop();
            --value[u];
            for(int v :  adj[u])
                ++value[v];
        }
    }
    return n;
}

int solve() {
    int time = check_N_Time();
    if(time < n) return time;

    vector<int> topo_list = Topo_Sort_graph::find_topo(n, adj);
    for(int &u : topo_list) {
        for(int &v : adj[u]){
            (value[v] += value[u])%=MOD;
        }
    }

    int lowest_node = topo_list.back();
    return (value[lowest_node]+=n)%=MOD;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int t; cin >> t;
    while(t--) {
        initData();
        cout << solve() << endl;
    }
}

