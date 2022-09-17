/*
Link: http://www.usaco.org/index.php?page=viewproblem2&cpid=625
Link submiss: https://usaco.guide/problem-solutions/
*/


/*
Tóm tắt đề:
- Cho 1 bảng A*B (Bắt đầu từ 0*0)
- Cho n thanh bắt ngang cắt từ (a[i],0) -> (a[i], B);
- Cho m thanh dọc cắt từ (0, b[i]) -> (A, b[i])

- Hỏi chi phí nhỏ nhất để cắt bớt cạnh để các con bò có thể di chuyển bên trong vòng bảng
*/

/*
Nhận xét 1: Bảng được chia thành nhiều khu và mỗi khu là 1 hình chữ nhật.

Nhận xét 2: Mỗi cạnh dọc sẽ hợp với tất cả các cạnh ngang trên mỗi hàng
    => Thứ tự sắp xếp các cạnh sẽ không làm ảnh hưởng tới bài toán. 
    => Để dễ xử lý thì ta sắp xếp các cạnh theo thứ tự tăng dần về độ lớn (Cả chiều dọc và ngang)

Nhận xét 3: Không thể chỉ chọn chiều dọc hoặc chiều ngang để giải quyết bài toán.
    => Ưu tiên chọn 1 hàng và 1 cột min nhất

Nhận xét 4: Khi tô được 1 cột và hàng đầu tiên thì ta có nhận xét sau:
    + Giải quyết các ô còn lại theo chiều từ trên xuống và từ trái qua phải.
    + Như vậy, nếu cạnh ngang hay dọc, cái nào nhỏ hơn thì mình lấy.
*/

#include<bits/stdc++.h>
using namespace std;

#define all(_x) _x.begin(), _x.end()
#define fi first
#define se second
#define sz(_s) int(s.size())
#define mp make_pair
#define trav(a, x) for(auto& a: x)

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pii> vii;

typedef vector<vector<pair<int,int>>> dsk;

int A, B;
int n, m;
vector<int> a, b;

template<class T>
ostream& operator << (ostream& out, const vector<T> &a) {
    for(T val : a) out << val << ' ';
    return out;
}

void get_input(vector<int> &a, int n, int val_end) {
    a.push_back(0);
    for(int i = 0; i < n; ++i) {
        int x; cin >> x;
        a.push_back(x);
    }

    sort(all(a));
    a.push_back(val_end);
}   

void calc_side(vector<int> &a, int &n) {
    ++n;
    for(int i = 0; i < n; ++i) a[i] = a[i + 1] - a[i];
    a.resize(n);
    sort(all(a));
}

void initData(){
    cin >> A >> B;
    
    cin >> n >> m;
    get_input(a, n, B);
    get_input(b, m, A);

    calc_side(a, n);
    calc_side(b, m);
}

ll solve() {
    ll ans = 0;

    // Chọn 1 hàng và cột min nhất
    ans += 1ll * a[0] * (m - 1) + 1ll * b[0] * (n - 1); 
    
    int i = 1, j = 1;
    while(i < n && j < m) {
        if(a[i] < b[j]) {
            ans += 1ll * a[i] * (m - j);
            ++i;
        }
        else {
            ans += 1ll * b[j] * (n - i);
            ++j;
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    freopen("fencedin.in", "r", stdin);
    freopen("fencedin.out", "w", stdout);

    int t = 1; 
    //cin >> t;
    while(t--) {
        initData(); 
        cout << solve() << endl;
    }
}
