/**
 * 5h07: 84%
 * Link: https://oj.uz/problem/view/COCI17_sirni
 * 
 * Đề:
 * Cho mảng A có N phần tử.
 * Trọng số mỗi cặp A[i] và A[j] là: min(A[i]%A[j], A[j]%A[i])
 * Tìm cây khung nhỏ nhất liên kết N thằng.
*/

/**
 * Vấn đề đặt ra: Số đỉnh quá lớn để có thể build cạnh và DSU
 * 
 * Nhận xét 1: 
 *      + Và như vậy, các đỉnh có giá trị bằng nhau thì mình sẽ không cần xét đến nó.
 *      + Như vậy, ta sẽ chuyển bài toán về thành các giá trị khác nhau
 * 
 * Nhận xét 2:
 *      + Dễ dàng nhận thấy, vì max_val = 1e7 nên ta có thể dễ dàng lặp qua các bội số của các giá trị trong mảng A
 *      + Và ta sẽ kết nối các giá trị này lại với trọng số cạnh = 0
 * 
 * Nhận xét 3:
 *      + Cách nối cạnh tối ưu.
 *      + Với mỗi A[i], ta lặp qua các bội số của A[i]
 *      + Ta sẽ thêm các cạnh với các giá trị gần nhất với bội số này 
 *      + Như vậy thì ta không còn phải thực hiện phép mod nữa mà dễ dàng so sánh các số.
 * 
 * Nhận xét 4:
 *      + Vì ta không biết từ 1 bội số  thì ta cần nối tới bao nhiêu cạnh
 *         gần nhất.
 *      + Nên ta sẽ tìm kiếm nhị phân giá trị cạnh lớn nhất để DSU 
 *      + Hoặc tìm kiếm nhị phân số cạnh cần nối từ 1 đỉnh đi ra để hoàn chỉnh cây DSU
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * Nhận xét 5: 
 *      + .... 
 *ỉ      + Ta dễ dàng chứng minh chỉ cần xét 1 đnh gần nhất.
*/

#include<bits/stdc++.h>
using namespace std;

#define all(_x) _x.begin(), _x.end()
#define fi first
#define se second
#define sz(_s) int(_s.size())
#define mp make_pair
#define trav(a, x) for(auto& a: x)

#define fu(i, a, b) for(int i = a; i <= b; ++i)
#define fd(i, a, b) for(int i = a; i >= b; --i)
#define fr(i, n) for(int i = 0; i < n; ++i)

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pii> vii;

template<class T>
ostream& operator << (ostream& out, vector<T> &a) {
    trav(x, a) cout << x << ' ';
    return out;
}

class Edge{
public:
    int u, v, w;

    bool operator < (const Edge &A) {
        return w < A.w;
    }

    friend ostream& operator << (ostream& out, Edge &A) {
        out << A.u << ' ' << A.v << ' ' << A.w;
        return out;
    }
};


struct DSU{
    // par[u] là đỉnh đại diện cho u
    vector<int> par;
    
    // reset mảng cho n phần tử
    void init(int n){ 
        par.assign(n, -1);
    }

    // lấy ra đỉnh đại diện cho nhánh chứa x
    int get(int x) {
        return par[x] < 0 ? x : par[x] = get(par[x]);
    }

    // kiểm tra x và y có chung 1 nhánh hay không
    bool sameSet(int x, int y) {
        return get(x) == get(y);
    }

    // số phần tử nhánh liên thông của x
    int size(int x) {
        return -par[get(x)];
    }

    // Nối cạnh x y
    bool unite(int x, int y) {
        int u = get(x);
        int v = get(y);
        if(u == v) return false;

        if(par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        return true;
    }
};
vector<Edge> edges;

int n, max_val;
vector<int> a;

void initData(){
    cin >> n;
    a.resize(n);
    for(int i = 0; i < n; ++i) cin >> a[i];
    
    sort(all(a));

    a.resize(unique(all(a)) - a.begin());
    
    max_val = a.back();
    n = sz(a);
}

void build_edge() {
    for(int i = 0; i < n - 1; ++i) {
        for(int j = a[i]; j <= max_val; j += a[i]) {
            int k = lower_bound(a.begin() + i + 1, a.end(), j) - a.begin();
            if(k >= n) continue;
            if(a[k] - j > a[i]) continue;
            edges.push_back({i, k, a[k] - j});
        }
    }
}

void solve() {
    sort(all(edges));
    DSU dsu;
    dsu.init(n + 1);

    ll ans = 0;
    trav(e, edges) {
        ans += e.w * dsu.unite(e.u, e.v);
    }
    cout << ans << endl;
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
        build_edge();
        solve();
    }
}