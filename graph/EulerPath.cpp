//Name of task: Mail Delivery by Euler Cycle + something
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
    For(i,(int)a.size()) cout<<a[a.size() - 1 - i]<<' ';
    cout << endl;
}

struct edge{
    int x,y;
    bool mark = false;
    edge(int x, int y){
        this->x = x;
        this->y = y;
    }
};

const int N = (int)1e5 + 1;
stack<edge*> eds[N]; 
vector<int> res;
vector<edge*> edss;
int n, m;

void dfs(int v){
    while(!eds[v].empty()){
        edge *e = eds[v].top();
        eds[v].pop();
        
        if(e->mark) continue;
        e->mark = true;

        if(e->x != v) {
            dfs(e->x);
            res.pb(e->x);
        }
        else {
            dfs(e->y);
            res.pb(e->y);
        }
    }
}

void solve(){
    cin >> n >> m;
    For(i,m){
        int x, y;
        cin >> x >> y;
        edge *e = new edge(x,y);
        eds[x].push(e);
        eds[y].push(e);
        edss.pb(e);
    }
    bool good = true;
    For(i,n){
            int v = i + 1;
            if(eds[v].size()%2){
                good = false;
                break;
            }
        }
    dfs(1);
    if(good){
        for(edge* e: edss){
            if(!e->mark){
                good = false;
                break;
            }
        }
    }
    if(!good || res[0] != 1){
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    cout << 1 << " ";
    printRev(res);
}
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t=1;
    //cin >> t;
    while(t--) solve();

    return 0;
}