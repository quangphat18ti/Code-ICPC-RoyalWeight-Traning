#include<bits/stdc++.h>
using namespace std;

#define all(_x) _x.begin(), _x.end()
#define fi first
#define se second
#define sz(_s) int(s.size())
#define pb push_back

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pii> vii;

const int MAXN = 1e5 + 5;
const int INF = 1e9 + 5;

int n, m;
vector<pii> adj[MAXN];
vector<int> dist_1, dist_n;
vector<int> min_1, min_n;
vector<int> trace_min_1, trace_min_n; 
vector<int> max_1, max_n;
vector<int> trace_max_1, trace_max_n; 

struct Edge{
    int u, v, w;
    void print() {
        cout << "Edge(" << u << " -> " << v << ") = " << w << endl; 
    }
};
vector<Edge> edges;

ostream& operator << (ostream& out, vector<int> &st) {
    out << st.size() - 1 << endl;
    for(int u : st) out << u << ' '; cout << endl;
    return out;
}

void build_adj(vector<Edge> &edges) {
    for(int i = 1; i <= n; i++) adj[i].clear();

    for(Edge tam : edges) {
        adj[tam.u].push_back({tam.v, tam.w});
    }
}

void init_data() {
    cin >> n >> m;

    edges.clear();
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
        edges.push_back({v, u, w});
    }

    build_adj(edges);
}

void bfs(int start, vector<int>& dist) {
    dist.assign(n + 1, -1);
    dist[start] = 0;

    queue<int> que;
    que.push(start);
    while(que.size()){
        int u = que.front(); que.pop();
        for(pii edge : adj[u]) {
            int v = edge.first;
            if(dist[v] == -1) {
                dist[v] = dist[u] + 1;
                que.push(v);
            }
        }
    }
}

vector<Edge> build_another_graph(vector<Edge> edges, vi &dist_start,vi &dist_end, int end) {
    vector<Edge> ans;
    for(Edge &e : edges){
        if(dist_start[e.u] + dist_end[e.v] + 1 == dist_start[end]) ans.push_back(e);
    }
    return ans;
}

void get_edge(int st, vi &f, vi& tr, int initVal, bool(*cmp)(int,int), int(*get)(int, int)) {
    f.assign(n + 1, initVal);
    tr.assign(n + 1, -1);
    queue<int> que; que.push(st); 
    while(!que.empty()) {
        int u = que.front(); que.pop();
        for(auto &[v, weight] : adj[u]) {
            int val = get(f[v], get(f[u], weight));
            if(cmp(val, f[v])) {
                if(tr[v] == -1) que.push(v);
                f[v] = val;
                tr[v] = u;
            } 
        }
    }
}

void build_max_min() {
    auto cmp_min = [](int a, int b) -> bool { return a < b; };
    auto cmp_max = [](int a, int b) -> bool { return a > b; };
    auto get_min = [](int a, int b) -> int { return (a < b)?a:b; };
    auto get_max = [](int a, int b) -> int { return (a > b)?a:b; };


    vector<Edge> temp_edges = build_another_graph(edges, dist_1, dist_n, n); /// build graph from 1 -> n
    build_adj(temp_edges);
    get_edge(1, min_1, trace_min_1, INF, cmp_min, get_min); // get min from 1
    get_edge(1, max_1, trace_max_1, -INF, cmp_max, get_max); // get max from 1

    temp_edges = build_another_graph(edges, dist_n, dist_1, 1);  /// build graph from n -> 1
    build_adj(temp_edges);
    get_edge(n, min_n, trace_min_n, INF, cmp_min, get_min);  // get min from n
    get_edge(n, max_n, trace_max_n, -INF, cmp_max, get_max); // get max from m
}

vector<int> truyvet(int u, vector<int> &trace){
    vector<int> ans;
    while(u!=-1){
        ans.push_back(u);
        u = trace[u];
    }
    return ans;
}

void concat(vector<int> &a, vector<int> b) {
    for(int &u : b) a.push_back(u);
}

void solve() {
    vector<Edge> temp_edges = build_another_graph(edges, dist_1, dist_n, n); /// build graph from 1 -> n
    
    int ans = -INF; 
    for(auto &[u, v, w] : temp_edges) {
        ans = max(ans, max(max_1[u], w) - min(min_n[v], w));
        ans = max(ans, max(max_n[v], w) - min(min_1[u], w));
    }
    // cout << ans << endl;

    for(auto &[u, v, w] : temp_edges) {
        if(ans == max(max_1[u], w) - min(min_n[v], w)) {
            vector<int> st1 = truyvet(u, trace_max_1); reverse(all(st1));
            vector<int> st2 = truyvet(v, trace_min_n);
            concat(st1, st2);
            cout << st1 << endl;
            return;
        }
        else if(ans == max(max_n[v], w) - min(min_1[u], w)){
            vector<int> st1 = truyvet(u, trace_min_1); reverse(all(st1));
            vector<int> st2 = truyvet(v, trace_max_n); 
            concat(st1, st2);
            cout << st1 << endl;
            return;
        }
    }
}

int main() {
//   freopen("input.txt", "r", stdin);
//   freopen("output.txt", "w", stdout);
    int t = 1;
    //cin >> t;
    while(t--) {
        init_data();
        bfs(1, dist_1);
        bfs(n, dist_n);
        build_max_min();
        solve();
    }
}

