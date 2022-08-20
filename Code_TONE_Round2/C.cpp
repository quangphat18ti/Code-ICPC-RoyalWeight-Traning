#include<bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()

int n, m;
vector<int> a;

struct Range{
    int left, right, len;
    Range(int l, int r) {
        left = l;
        right = r;
        len = right - left - 1;
        if(len < 0) len += n;
    }

    bool operator < (Range &a) {
        return len > a.len;
    }
};
vector<Range> rangeArr;

void initData() {
    cin >> n >> m;
    a.clear();
    for(int i = 0; i < m; i++) {
        int x; cin >> x;
        a.push_back(x);
    }
}

void findRange(vector<int> &a) {
    sort(a.begin(), a.end());
    rangeArr.clear();
    for(int i = 0; i < m; i++) {
        rangeArr.push_back(Range(a[i], a[(i+1) % m]));
    }
    sort(rangeArr.begin(), rangeArr.end());
}

void solve() {
    int ans = 0;
    int step = 0;
    for(Range r : rangeArr) {
        r.len -= step*2;
        if(r.len <= 0) break;
        if(r.len <= 2) ++ans, ++step;
        else ans += r.len - 1, step += 2;
    }
    cout << n - ans << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t; cin >> t;
    while(t--) {
        initData();
        findRange(a);
        solve();
    }
}
