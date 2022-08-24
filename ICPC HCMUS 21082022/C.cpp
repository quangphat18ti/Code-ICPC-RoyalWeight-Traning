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

// const int MAXN = ;

bool is_num(char &k) {
    return k>='0' && k <= '9';
}

int get_integer(string &s, int pos) {
    int len_s = sz(s);
    int ans = 0;
    while(pos < len_s && is_num(s[pos])){
        ans = ans*10 + s[pos] - '0';
        ++pos;
    }
    return ans;
}

int get_year(string &s) {
    if(s[0] == 'A') {
        return get_integer(s, 3);
    }
    else 
        return -get_integer(s, 0);
} 

void solve() {
    string s;
    getline(cin, s);
    int year1 = get_year(s);
    getline(cin, s);
    int year2 = get_year(s);

    if(year1 > year2) swap(year1, year2);
    int ans = year2 - year1;
    if(year1 < 0 && year2 > 0) --ans;
    cout << ans << endl;
}
void nhap(){
}


int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int t = 1; 
    // cin >> t; 
    while(t--) {
        nhap();
        solve();
    }
}

