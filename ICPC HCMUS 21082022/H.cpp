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

void get_min_edge(int start, vector<int> &f, vector<int> &trace) {
    f.assign(n + 1, INF);
    trace.assign(n + 1, -1);

    set<pii> min_set;
    min_set.insert({f[start], start});

    while(min_set.size()) {
        pii tam = *min_set.begin();
        min_set.erase(min_set.begin());
        int u = tam.second;
        if(tam.first != f[u]) continue;

        for(pii nxt : adj[u]) {
            int v = nxt.first;
            int weight = nxt.second;

            if(min(weight, f[u]) < f[v]) {
                trace[v] = u;
                f[v] = min(weight, f[u]);
                min_set.insert({f[v], v});
            }
        } 
    }
}

void get_max_edge(int start, vector<int> &f, vector<int> &trace) {
       f.assign(n + 1, -INF);
       trace.assign(n + 1, - 1);
       auto cmp = [](pii a, pii b) {return a.first > b.first;};
       set<pii, decltype(cmp)> max_set(cmp);

       max_set.insert({f[start], start});
       while(max_set.size()) {
            pii tam = *max_set.begin();
            max_set.erase(max_set.begin());

            int u = tam.second;
            if(tam.fi != f[u]) continue;

            for(pii nxt : adj[u]) {
                int v = nxt.first;
                int weight = nxt.second;

                if(f[v] < max(f[u], weight)) {
                    trace[v] = u;
                    f[v] = max(f[u], weight);
                    max_set.insert({f[v], v});
                }
            }
       }
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
    vector<Edge> temp_edges = build_another_graph(edges, dist_1, dist_n, n);
    build_adj(temp_edges);
    get_min_edge(1, min_1, trace_min_1);
    get_max_edge(1, max_1, trace_max_1);


    temp_edges = build_another_graph(edges, dist_n, dist_1, 1);
    build_adj(temp_edges);
    get_min_edge(n, min_n, trace_min_n);
    get_max_edge(n, max_n, trace_max_n);

    int ans = -INF; 
    for(int i = 1; i <= n; i++) {
        ans = max(ans, max_n[i] - min_1[i]);
        ans = max(ans, max_1[i] - min_n[i]);
    }

    for(int i = 1; i <= n; i++) {
       if(max_n[i] - min_1[i] == ans) {
            vector<int> arr = truyvet(i, trace_min_1);
            reverse(all(arr)); arr.pop_back();
            concat(arr, truyvet(i, trace_max_n));   
            cout << arr << endl;
            return;
       } 
       
       if(max_1[i] - min_n[i] == ans) {
            vector<int> arr = truyvet(i, trace_max_1);
            reverse(all(arr)); arr.pop_back();
            concat(arr, truyvet(i, trace_min_n));
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
        solve();
    }
}

