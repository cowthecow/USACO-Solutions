#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double
#define vi vector<int>
#define pb push_back
#define sz(a) a.size()
#define pii pair<int,int>
#define fi first
#define se second
#define all(a) a.begin(), a.end()

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

const int MAXN=1e5+5;

int n;
vi adj [MAXN];
int chain [MAXN];
int ch_max=0;

bool dfs(int v, int p) {
    multiset<int> childs;

    for(int to:adj[v]) {
        if(to==p)   
            continue;
        if(!dfs(to, v))
            return false;
        childs.insert(chain[to]+1);
    }

    vi small_left;
    vi big_left;
    int pot_child=0;
    while(!childs.empty()) {
        int x=*childs.begin();
        childs.erase(childs.begin());

        if(x>=ch_max) {
            big_left.pb(x);
            continue;
        }
        auto lp=childs.lower_bound(ch_max-x);
        if(lp!=childs.end()) {
            childs.erase(lp);
            pot_child=max(pot_child,x);
        }else {
            small_left.pb(x);
        }
    }

    if(sz(small_left)>=2) {
        return false;
    }else if(sz(small_left)==1) {
        chain[v]=small_left[0];
    }else {
        if(big_left.empty()) {
            chain[v]=pot_child; //we can unpair a child and use it over 0
        }else {
            chain[v]=*max_element(all(big_left));
        }
    }
    if(v==1&&!small_left.empty()) {
        return false;
    }
    return true;
}

bool check(int len) {
    ch_max=len;
    fill(chain, chain+n+1, 0);
    return dfs(1,-1);
}

void solve() {
    //in earlier problem at each strand of tree
    //we can group up two at a tiem
    //what is optimal way of grouping such that the current strand is still maximized in length

    //if k works, k-1 also works, monotonic so add a bin search on top
    
    cin>>n;
    for(int i=1;i<=n-1;i++) {
        int u,v;
        cin>>u>>v;

        adj[u].pb(v);
        adj[v].pb(u);
    }

    int lo=1, hi=n-1;
    int ans=-1;

    while(lo<=hi) {
        int mid=(lo+hi)/2;

        if(check(mid)) {
            ans=mid;
            lo=mid+1;
        }else {
            hi=mid-1;
        }
    }

    cout<<ans<<"\n";
}

signed main() {

    setIO("deleg");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin>>t;

    while(t>0) {
        solve();
        t--;
    }
}
