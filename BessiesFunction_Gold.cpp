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

//we find one node, and set it to 1 or 0 (whether or not it self loops)
//do dp on the other nodes
//if we make one node point to self, and that node is part of cycle, remaining will form tree?
//then we do dp on that tree

//for each cycle, we have a 0 1 0 1 alternate, or vice versa 1 0 1 0 ??
//or we DP the cycle too, yes because sometimes 0 1 1 0 1 1 is better than 1 0 1 0 1 0 or 0 1 0 1 0 1

//for every comp find a node, if that node is 0, that means the node it points to must be 1
//so for each comp, does the node have to be part of cycle  

//functional graph, each component has a cycle
//for each component, find cyclic components, then run a dp on both

const int MAXN=2e5+1;
const int INF=1e18;

int n;
int nxt [MAXN];
vi par [MAXN];
int cost [MAXN];
int vis [MAXN];
int svis [MAXN];
int indeg [MAXN];
int cycle [MAXN];

int dp [MAXN][2]; //dp 1 is cur self, dp 0 is cur not loop yet
vi comp;

//two kinds of dfs are neccesary, otherwise will overlap
//they have identical role, except they use separate dp arrays
int dfs(int v) {
    comp.pb(v);
    vis[v]=1;

    dp[v][0]=0;
    dp[v][1]=0;
    if(nxt[v]!=v)
        dp[v][1]+=cost[v];

    if(!par[v].empty()) {
        for(int to:par[v]) {
            if(vis[to])
                continue;

            dfs(to);
            dp[v][1]+=min(dp[to][0], dp[to][1]);
            dp[v][0]+=dp[to][1];
        }
    }
    
    return dp[v][1];
}

void solve() {
    cin>>n;

    for(int i=1;i<=n;i++) {
        cin>>nxt[i];
        par[nxt[i]].pb(i);
        indeg[nxt[i]]++;
    }
    queue<int> Q;
    for(int i=1;i<=n;i++) {
        cin>>cost[i];
        cycle[i]=1;
        if(indeg[i]==0)
            Q.push(i);
    }
    while(!Q.empty()) {
        int v=Q.front();
        Q.pop();
        cycle[v]=0;
        indeg[nxt[v]]--;
        if(indeg[nxt[v]]==0)
            Q.push(nxt[v]);
    }

    for(int i=1;i<=n;i++) 
        fill(dp[i], dp[i]+2, INF);
    

    //for each cycle node, visit its whole component using the prev array, dp solve for that
    int ans=0;
    for(int i=1;i<=n;i++) {
        if(cycle[i]&&!vis[i]) {
            //do the dfs now, spam the dp
            //then proceed to do dfs twice on the secondary dp array
            comp.clear();
            int cur=dfs(i);

            if(nxt[i]!=i) {
                for(int j:comp) {
                    vis[j]=0;
                    dp[j][0]=dp[j][1]=INF;
                }
                cur=min(cur, dfs(nxt[i]));
            }
            ans+=cur;
        }
    }
    cout<<ans<<"\n";
}


signed main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin>>t;

    while(t>0) {
        solve();
        t--;
    }
}
