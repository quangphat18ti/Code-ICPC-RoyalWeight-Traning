/**
Link: https://judge.yosupo.jp/problem/maximum_independent_set

Đề:
Cho đồ thị N đỉnh, M cạnh vô hướng
Tìm tập đỉnh độc lập (mỗi đỉnh không có cạnh trực tiếp nối tới nhau) lớn nhất
*/

#include<bits/stdc++.h>
using namespace std;

#define all(_x) _x.begin(), _x.end()
#define fi first
#define se second
#define sz(_s) int(s.size())

#define setBit(x , i) (x | (1LL << i))
#define getBit(x , i) ((x >> i) & 1)
#define offBit(x , i) (x & ~(1LL << i))
#define getPow2(x) (1 << x)
#define countBit(x) __builtin_popcountll(x)


typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pii> vii;
typedef vector<vector<int>> dsk;

const int MAXN = 45;

int n, m;
dsk adj;
int n1, n2;
int bit[MAXN][2];

class DpBitMask{
public:
    vector<int> f;
    vector<int> mask_off;
    vector<int> mask_on;
    int n;

    vector<int> node;
    int group;

    ~DpBitMask() {
        f.clear();
        mask_off.clear();
        mask_on.clear();
        node.clear();
    }

    void init(vector<int> &_node, int _group) {
        node = _node;
        n = node.size();
        group = _group;

        f.assign(getPow2(n), 0);

        mask_on.assign(getPow2(n), 0);

        mask_off.resize(getPow2(n));
        mask_off[0] = getPow2(n) - 1;
    }

    void solve(){
        for(int i = 1; i < getPow2(n); ++i) {
            for(int j = 0; j < n; j++) {
                if(!getBit(i, j)) continue;
                
                int oldMask = i ^ getPow2(j);
                if(getBit( mask_off[oldMask], j )) {
                    if(f[i] < f[oldMask] + 1) {
                        f[i] = f[oldMask] + 1;
                        mask_off[i] = mask_off[oldMask] & bit[node[j]][group];
                        mask_on[i] = setBit(mask_on[oldMask], j);
                    }
                }
                else {
                    if(f[i] < f[oldMask]) {
                        f[i] = f[oldMask];
                        mask_off[i] = mask_off[oldMask];
                        mask_on[i] = mask_on[oldMask];
                    }
                }
            }
        }
    }
};
DpBitMask dp1, dp2;

int findGroup(int s) {
    return s >= n/2;
}
int findStt(int s) {
    return s - findGroup(s) * (n/2);
}

void input_data(){
    cin >> n >> m;
    n1 = n/2;
    n2 = n - n/2;

    adj.assign(n, vi(0));
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);       
    }       
}

void printBit(int bit, int k){
    for(int i = 0; i < k; ++i) cout << getBit(bit, i); cout << endl;
}

void process() {
    // bit[i][0] là trạng thái của i với nhóm 0
    // bit[i][1] là trạng thái của i với nhóm 1

    // Khởi tạo tất cả các bit đều bật
    for(int i = 0; i < n; ++i) {
        bit[i][0] = getPow2(n1) - 1;
        bit[i][1] = getPow2(n2) - 1;
    }    

    // Nếu u gặp v thì tắt bit bằng STT của v trong nhóm
    for(int u = 0; u < n; ++u) {

        for(int v : adj[u]) {
            int vGroup = findGroup(v);
            int vStt = findStt(v);
            bit[u][vGroup] = offBit(bit[u][vGroup], vStt); // tắt bit thứ Stt(v)
        }
    }
} 

void dpBitMask() {   
    vector<int> nodeN2;
    for(int i = n/2 ; i < n; ++i) nodeN2.push_back(i);
    dp2.init(nodeN2, 1);
    dp2.solve();
}

void solve() {
    int ans = -1;
    int bit1, bit2;

    for(int i = 0; i < getPow2(n1); ++i) {
        int mask1 = getPow2(n1) - 1;
        int mask2 = getPow2(n2) - 1;
        for(int j = 0; j < n1; ++j) {
            if(getBit(i, j)) {
                mask1 &= bit[j][0];
                mask2 &= bit[j][1];
            }
        }

        if(i != (i & mask1)) {
            continue;
        }

        int res = countBit(i) + dp2.f[mask2];
        if(ans < res) {
            ans = res;
            bit1 = i;
            bit2 = mask2;
        }
    }

    cout << ans << endl;
    for(int i = 0; i < n1; i++) if(getBit(bit1, i)) cout << i << ' ';
    for(int i = 0; i < n2; i++) {
        if(getBit(dp2.mask_on[bit2], i)) cout << dp2.node[i] << ' ';
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t; t = 1;
    //cin >> t;
    while(t--) {
        input_data();
        process();
        dpBitMask();
        solve();
    }
}

