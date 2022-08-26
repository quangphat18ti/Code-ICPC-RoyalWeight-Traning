#include<bits/stdc++.h>
using namespace std;

#define all(_x) _x.begin(), _x.end()
#define fi first
#define se second
#define sz(_s) int(s.size())

typedef double db;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pii> vii;

const int MAXN = 1e5 + 5;
const db INF = 1e18;

int n;
db L, V;
db a[MAXN];
db dp1[MAXN], dp2[MAXN], dp3[MAXN];

void initData(){
    cin >> n >> L >> V;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
}

db calc(db time_wait, int id) {
    return dp3[n] - dp3[id - 1] + dp2[id - 1] + dp1[id - 1] *  time_wait;
} 

void solve() {
    for(int i = 1; i <= n; ++i) {
        dp3[i] = dp3[i - 1] + L/a[i];  /// only Jane move
        dp2[i] = dp2[i - 1] + 2.0*L/(V + a[i]);  // both Jane and Julia move
        dp1[i] = dp1[i - 1] + (V - a[i]) / (a[i] + V); // the cost of waiting 1 time
    }

    db ans = calc(0, n + 1);
    for(int i = 1; i <= n; i++) {
        ans = min(ans, calc(L/a[i], i));
    }
    ans /= n;
    cout << setprecision(10) << fixed << ans << endl; 
}

int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    int t = 1; 
    //cin >> t;
    while(t--) {
        initData();
        solve();
    }
}

