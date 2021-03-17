//Name of task:
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<double> vd;
typedef pair<int,int> pii;
#define lll int64_t //need to use g++ -std=c++11 or more ...
#define pb push_back
#define For(i,n) for(int i=0;i<n;i++)
#define fi first
#define se second
#define all(x) x.begin(), x.end()
template<typename T>
void enter(vector<T>& a, int n){
    For(i,n) cin >> a[i];
}
template<typename T>
void enter(T a[], int n){
    For(i,n) cin >> a[i];
}
template<typename T>
void enter(vector<T>& a){
    For(i,a.size()) cin >> a[i];
}
template<typename T>
void print(vector<T>& a){
    For(i,a.size()) cout<<a[i]<<' ';
    cout << endl;
}
template<typename T>
void print(T a[], int n){
    For(i,n) cout<<a[i]<<' ';
    cout << endl;
}
template<typename T>
void printRev(vector<T>& a){
    For(i,a.size()) cout<<a[a.size() - 1 - i]<<' ';
    cout << endl;
}
const int N = 1e5;
const int K = 18;

vector<int> g[N];
vector<int> ed;
int depth[N];
int lg[N*2 + 1];
int st[N*2][K + 1];
int fi[N];

int n, m;

void findLog(){
    lg[1] = 0;
    for(int i = 2; i <= N * 2; i++){
        lg[i] = lg[i / 2] + 1;
    }
}

void findDepth(int v, int d = 0){
    depth[v] = d;
    for(int u: g[v]){
        findDepth(u, d + 1);
    }
}

void findEulerDetour(int v){
    fi[v] = (int)ed.size();
    ed.pb(v);
    for(int u: g[v]){
        findEulerDetour(u);
        ed.pb(v);
    }
}

int f(int x, int y){
    return depth[x] > depth[y] ? y : x;
}

void bulidSpraceTable(){
    findEulerDetour(0);
    For(i, (int)ed.size()){
        st[i][0] = ed[i];
    }
    for(int j = 1; j <= K; j++){
        for(int i = 0; i + (1 << j) <= (int)ed.size(); i++){
            if(depth[st[i][j-1]] > depth[st[i + (1 << (j - 1))][j-1]]){
                st[i][j] = st[i + (1 << (j - 1))][j-1];
                continue;
            }
            st[i][j] = st[i][j-1];
        }
    }
}

int lca(int x, int y){
    int l,r;
    l = fi[x];
    r = fi[y];
    if(l > r) swap(l , r);
    int j = lg[r - l + 1];
    if(depth[st[l][j]] > depth[st[r - (1 << j) + 1][j]]) return st[r - (1 << j) + 1][j];
    return st[l][j];
}

void solve(){
    //Read
    cin >> n >> m;
    For(i,n - 1){
        int p;
        cin >> p;
        g[p].pb(i + 1);
    }
    //Find depth
    findDepth(0);
    //Build
    bulidSpraceTable();
    //Queries
    long long a1, a2;
    cin >> a1 >> a2;
    long long x,y,z;
    cin >> x >> y >> z;
    long long qr = lca(a1,a2);//query result lca(a1,a2)
    long long sums = qr;
    for(int i = 1; i < m; i++){//O(M)
        a1 = ((x * a1)%n + (y * a2 + z)%n) % n;
        a2 = ((x * a2)%n + (y * a1 + z)%n) % n;
        // cout << (a1 + qr)%n << " " << a2 << " ";
        qr = lca((a1 + qr)%n, a2);
        // cout << qr << endl;
        // cout << "------------------------" << endl;
        sums+=qr;
    }   
    cout << sums;
}
int main(){
    freopen("lca_rmq.in", "r", stdin);
    freopen("lca_rmq.out", "w", stdout);
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    //Find log
    findLog();
    int t=1;
    //cin >> t;
    while(t--) solve();

    return 0;
}