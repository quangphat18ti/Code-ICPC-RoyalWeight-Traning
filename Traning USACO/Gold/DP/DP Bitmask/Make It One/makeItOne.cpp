/**
 * LINK: https://codeforces.com/contest/1043/problem/F
 * Đề:
 * _ Cho mảng A có N phần tử
 * _ Tìm subset nhỏ nhất sao cho có GCD() = 1
*/

/**
 * Nhận xét 0 (tiên quyết):
 *      + Với mỗi lần thực hiện GCD thì ta phải thu hẹp ít nhất 1 ước nguyên tố của số đó.
 *      + Vì vậy, độ dài chuỗi subset dài nhất là 7.
 *      + Như vậy ta có thể thực hiện quy hoạch động 7 * n
 * 
 * Nhận xét 1: Dựa vào nhận xét 0, ta có thể:
 *      + Đại diện 1 giá trị a[i] với mảng các ước nguyên tố của nó
 *      + Chỉ gộp 2 phần tử nếu có 2 mảng giá trị này khác nhau hay tích các ước nguyên tố của nó là khác nhau
 * 
 * Nhận xét 2: Nếu dãy có tồn tại a và b mà tích các ước nguyên tố của nó bằng nhau thì ta không cần phải gộp chúng
 *      + Như vậy, ta sẽ biến đổi dãy về thành dãy mà các số có tích các ước nguyên tố là khác nhau
 * 
 * Nhận xét 4: Ta có thể quy hoạch động F[i][j] là cách để tạo ra gcd = j từ i số
 *      + Ta sẽ cập nhật tiến, có nghĩa là lấy F[i][j] đi cập nhật cho các F[i + 1][k]
*/

/**
 * Cách cài đặt nhận xét 4: Lấy F[i][j] đi cập nhật
 *      + Với mỗi lần nhận thêm số, ta phải xóa đi 1 tập các ước nguyên tố của nó. (Ít nhất là 1)
 *      + Vì vậy ta sẽ duyệt qua tất cả các tập subset của các ước nguyên tố j, ta tìm xem có tồn tại 1 số nào mà không có chứa các ước
 *          nguyên tố đó trong giá trị của hay không.  
 *          - Nếu có thì ta sẽ cập nhật lên F[i + 1][k] (Với k = j trừ đi subset)
 *      + Cách kiểm tra xem có tồn tại ít nhất 1 số không có chứa subset đó không là ....  
 *          - Đếm xem có bao nhiêu số có chứa ít nhất 1 trong các phần tử trong subset đó. --> Bao hàm loại trừ
 *          - Nếu số lượng <= n thì có tồn tại
 * 
 *      + Vì sao 
 * 
 * Câu hỏi đặt ra:
 *      + Như vậy, có hiện tượng chọn trùng số hay không?   --> Tự giải thích
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

#define setBit(x , i) (x | (1LL << i))
#define getBit(x , i) ((x >> i) & 1)
#define offBit(x , i) (x & ~(1LL << i))
#define getPow2(x) (1 << x)
#define countBit(x) __builtin_popcountll(x)

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pii> vii;

const int MAX_VAL = 3e5;

int n;
vector<int> a;
vector<int> prime;
int Count[MAX_VAL];
bool f[10][MAX_VAL + 5];

template<class T>
ostream& operator << (ostream& out, const vector<T> &a) {
    for(T x : a) out << x << ' '; 
    return out;
}

vector<int> SieveOfEratosthence(int maxVal) { // sàng nguyên tố
    vector<int> prime(maxVal + 1, 0);
    for(int i = 2; i <= sqrt(maxVal); ++i) {
        if(prime[i]) continue;
        for(int j = i * i; j <= maxVal; j += i) {
            if(!prime[j]) prime[j] = i;
        }
    }

    for(int i = 2; i <= maxVal; ++i) 
        if(prime[i] == 0) prime[i] = i;

    return prime;
}

vector<int> findPrimeDivisors(int s){
    vector<int> ans;
    if(s < 2) return  ans;
    while(s > 1) {
        int tam = prime[s];
        ans.push_back(tam);
        while(s % tam == 0) s /= tam;
    } 
    return ans;
}

vector<int> findSubsetProduct(const vector<int>& a){
    int n = sz(a);
    vector<int> f(getPow2(n)); f[0] = 1;

    for(int i = 1; i < getPow2(n); ++i) {
        for(int j = 0; j < n; ++j) {
            if(!getBit(i, j)) continue;
            
            int oldMask = i ^ getPow2(j);
            f[i] = f[oldMask] * a[j];
            break;
        }
    }

    return f;
};

void initData(){
    cin >> n;
    a.resize(n);
    for(int& x : a) cin >> x;
}   

void process() {
    auto updateCountArr = [&](const vector<int> &a){
        vector<int> subset = findSubsetProduct(a);
        trav(x, subset) Count[x]++;
    };

    for(int i = 0; i < n; ++i) {
        vector<int> primeDivisors = findPrimeDivisors(a[i]);
        updateCountArr(primeDivisors);
    }
}

int calc(const vector<int>& a) { /// calc(a) trả về số lượng các số có chứa ít nhất 1 trong các ước nguyên tố trong a
    int ans = 0;
    int n = sz(a);
    for(int i = 1; i < getPow2(n); ++i) {
        int product = 1;
        for(int j = 0; j < n; ++j) if(getBit(i, j)) product *= a[j];

        int val = Count[product];
        if(countBit(i) % 2) ans += val;
        else ans -= val;
    }
    return ans;
}

bool isExistElementNotContainSubset(const vector<int>& a) {
    return n - calc(a);
}

void solve() {
    trav(x, a) f[1][x] = 1;
    for(int i = 1; i < 7; ++i) {
        for(int gcd = 1; gcd <= MAX_VAL; ++gcd) {
            if(!f[i][gcd]) continue;

            vector<int> primeDivisors = findPrimeDivisors(gcd);

            int m = sz(primeDivisors);
            for(int mask = 0; mask < getPow2(m) - 1; ++mask) { /// mask[i] == 1 thì ước nguyên tố i được giữ lại sau khi gcd
                vector<int> val;
                for(int i = 0; i < m; ++i) if(!getBit(mask, i)) val.push_back(primeDivisors[i]);

                if(isExistElementNotContainSubset(val)){
                    int newGcd = 1;
                    for(int i = 0; i < m; ++i) if(getBit(mask, i)) {
                        newGcd *= primeDivisors[i];
                    }
                    f[i + 1][newGcd] = true;
                }
            }
        }
    }

    for(int i = 1; i <= 7; ++i) {
        if(f[i][1] == true) {
            cout << i << endl;
            return;
        }
    }

    cout << -1 << endl;
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
        prime = SieveOfEratosthence(MAX_VAL);
        process();
        solve();
    }
}

