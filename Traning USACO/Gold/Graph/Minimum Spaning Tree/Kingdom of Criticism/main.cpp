/*
Link: https://codeforces.com/contest/1725/problem/K
Đề bài:
_ Cho 1 mảng A có N phần tử nguyên dương <= 1e9

_ Có 3 truy vấn như sau:
    + 1 k w: a[k] = w
    + 2 k: Xuất a[k]
    + 3 l r: Tất cả các giá trị của A không thuộc đoạn [l -> r]  (r - l + 1 chẵn)

_ Trong đó truy vấn 3:
    + 1 lượt bạn có thể tăng hoặc giảm giá trị của 1 a[i] đi 1
    + Bạn cần thực hiện ít bước nhất có thể, và dễ dàng chứng minh được chỉ có 1 cách thỏa.
    + Bạn chỉ cần biết giá trị cuối cùng của mảng chứ không nhất thiết phải biết sử dụng bao nhiêu cách.
*/


/*
Nhận xét 1:
    + Với mỗi đoạn l -> r thì các giá trị:
        _ l -> mid: Giảm xuống l - 1  (Nhóm 1)
        _ mid + 1 -> r: Tăng lên r + 1 (Nhóm 2)
    + Như vậy, ta sẽ tách 1 truy vấn 3 thành 2 truy vấn tách biệt nhau

Nhận xét 2: Khi rơi vào truy vấn 2
    + Mình chỉ cần quan tâm với truy vấn 1 gần nhất
    + Nếu có truy vấn 1 đè lên nó thì ta cũng không cần phải quan tâm tới truy vấn 3 gần nhất

Nhận xét 3:
    + Khi cần truy cập vào thằng u thì ta lần lượt thực hiện:
        _ Tìm kiếm truy vấn 1 gần nhất
        _ Tìm kiếm truy vấn 3 từ truy vấn 1 đó đổ đi.
        _ Như vậy nó sẽ liên quan với 1 chuỗi 3 liên tiếp nào đó và dựa vào truy vấn 1 gần nhất, ta có
        thể tìm thấy điểm bắt đầu của 1 chuỗi 3 đó.

Câu hỏi:
    + Khi có vị trí truy vấn 1 mới nhất
    + Làm sao để tìm truy vấn 3 gần nhất ảnh hưởng tới nó.

    => Nó tương tự như cách connect
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

int n;
vector<int> a;
vector<int> query1; // id query1 in queries

struct Query{
    int l, r, val;
    int id;
};
vector<Query> queries;

// set<val, id> of Query
set<pair<int,int>> heap;
int n_heap = 0;

int q;

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

    int get_val(int x) {
        int id = get(x);
        return queries[id].val;
    }

    // Nối cạnh x -> y
    void unite(int x, int y) {
        par[x] = y;
    }
};
DSU dsu;

void initData(){
    cin >> n;
    for(int i = 0; i < n; ++i) {
        int x; cin >> x;
        a.push_back(x);
    }
}

void add_query1_to_queries(int pos, int val, vector<Query>& queries, vector<int> &query1) {
    queries.push_back({pos, pos, val, n_heap++});
    Query query = queries.back();
    heap.insert({query.val, query.id});
    query1[pos] = query.id;
}

void process() {
    query1.resize(n);
    for(int i = 0; i < n; ++i) {
        add_query1_to_queries(i, a[i], queries, query1);
    }
}

void solve1() {
    int pos, val; 
    cin >> pos >> val; 
    --pos;

    add_query1_to_queries(pos, val, queries, query1);

}

void solve2() {
    //pos
    int p; cin >> p; --p;

    int nearest_query1 = query1[p];

    // get answer
    cout << dsu.get_val(nearest_query1) << endl;
}

void connect(const Query &q) {
    auto ptr = heap.lower_bound({q.l, -1});
    while(ptr != heap.end() && ptr -> first <= q.r) {
        dsu.unite(ptr -> second, q.id);
        auto temp = ptr;
        ++ptr;
        heap.erase(temp);    
    }

    heap.insert({q.val, q.id});
}

void solve3() {
    int l, r; cin >> l >> r;
    int mid = (r + l) >> 1;

    queries.push_back({l, mid, l - 1, n_heap++});
    connect(queries.back());

    queries.push_back({mid + 1, r, r + 1, n_heap++});
    connect(queries.back());
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
        process();
        
        int q; cin >> q;
        dsu.init(q*2 + n);
        while(q--) {
            int type; cin >> type;

            if(type == 1) solve1();
            else if(type == 2) solve2();
            else if(type == 3) solve3();
        }
    }
}

