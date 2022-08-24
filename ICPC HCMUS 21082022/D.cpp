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

const int MAX_TRIE_NODE = 26;

int n, k;

class Trie_node{
    public:
        Trie_node* child[MAX_TRIE_NODE];
        int contain;

        Trie_node() {
            contain = 0;
            for(int i = 0; i < MAX_TRIE_NODE; i++) child[i] = NULL;
        }
};

class Trie_tree{
    private:
        Trie_node* root;

        vector<int> update_contain(Trie_node* u) {
            vector<int> vec_contain;

            u -> contain = 0;
            for(int i = 0; i < MAX_TRIE_NODE; i++) {
                Trie_node* v = u->child[i];
                if(!v) continue;
                u->contain += v->contain;
                vec_contain.push_back(v->contain);
            }

            return vec_contain;
        }

    public:
        Trie_tree() {
            root = new Trie_node();
        }

        void add_string_to_trie(string &s) {
            Trie_node* now = root;
            ++now->contain;
            for(char &k : s) {
                int nxt = k - 'a';
                if(now -> child[nxt] == NULL) {
                    now->child[nxt] = new Trie_node();
                }
                now = now->child[nxt];
                ++now->contain;
            }
        }

        void dfs(Trie_node* u, int& ans) {
            if(!u) return;
            if(u->contain <= k) return;

            for(int i = 0; i < MAX_TRIE_NODE; i++) {
                Trie_node* v = u->child[i];
                if(!v) continue;
                dfs(v, ans);
            }
            vector<int> vec_contain = update_contain(u);

            sort(all(vec_contain));
            int sum_contain = 0;
            for(int& contain : vec_contain){
                if(sum_contain + contain > k) ++ans;
                else sum_contain += contain;
            }

            u->contain = sum_contain;
        }

        int solve() {
            int ans = 0;

            dfs(root, ans);
            if(root->contain > 0) ++ans;
            cout << ans << endl;
        }

};
Trie_tree trie;

void initData(){
    cin >> n >> k; cin.ignore();
    trie = Trie_tree();
    for(int i = 1; i <= n; i++) {
        string s; cin >> s;
        trie.add_string_to_trie(s);
    }
}

void solve() {
    trie.solve();
}

int main() {
//   freopen("input.txt", "r", stdin);
//   freopen("output.txt", "w", stdout);
    int t = 1;
    //cin >> t;
    while(t--) {
        initData();
        solve();
    }
}

