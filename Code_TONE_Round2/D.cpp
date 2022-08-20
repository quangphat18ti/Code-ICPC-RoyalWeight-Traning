#include<bits/stdc++.h>
using namespace std;

#define all(_x) _x.begin(), _x.end()
#define fi first
#define se second
#define sz(_s) int(s.size())

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pii> vii;
typedef vector<vector<int>> vvi;

//const int MAXN = ;

int n, m;

void nhap(){
    cin >> n >> m;
}

void solve() {
    vector<pair<ll,int>> vec_sum;
    for(int i = 1; i <= n; i++) {
        ll sum = 0;
        for(int j = 1; j <= m; j++){
            ll x; cin >> x;
            sum += x * j;
        }
        vec_sum.push_back({sum, i});
    }

    sort(all(vec_sum));
    cout << vec_sum.back().second << ' ';
    cout << vec_sum.back().first - vec_sum[0].first << endl;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int t; cin >> t;
    while(t--) {
        nhap();
        solve();
    }
}
