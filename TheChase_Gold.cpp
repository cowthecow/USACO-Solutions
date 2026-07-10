#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define int long long
#define vi vector<int>
#define vvi vector<vector<int>>
#define pii pair<int,int>
#define sz(s) s.size()
#define all(x) x.begin(), x.end()
#define pb push_back
#define fi first
#define se second

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int INF=1e18;

void solve() {    

    int n,f;
    cin>>n>>f;

    vi indeg (n+1);
    vi to (n+1);
    vector<vi> from (n+1);

    for(int i=1;i<=n;i++) {
        cin>>to[i];
        indeg[to[i]]++;
        from[to[i]].pb(i);
    }
    
    vi fstart (n+1, 0);
    vi fdist (n+1, INF); //when does the last farmer catch up
    vi farmers (f);
    for(int i=0;i<f;i++) {
        cin>>farmers[i];
        fdist[farmers[i]]=0;
        fstart[farmers[i]]=1;
    }
    
    queue<int> Q;
    for(int i=1;i<=n;i++)
        if(!indeg[i])
            Q.push(i);

    while(!Q.empty()) {
        int v=Q.front();
        Q.pop();

        indeg[to[v]]--;
        fdist[to[v]]=min(fdist[to[v]], fdist[v]+1);

        if(!indeg[to[v]]) {
            Q.push(to[v]);
        }
    }

    vector<vi> cycles;
    vi vis (n+1, 0);
    for(int i=1;i<=n;i++) {
        if(indeg[i]&&!vis[i]) {
            vi cur;

            int st=i;
            cur.pb(st);
            vis[st]=1;

            int ptr=to[st];
            while(ptr!=st) {
                vis[ptr]=1;
                cur.pb(ptr);
                ptr=to[ptr];
            }
            cycles.pb(cur);
        }
    }

    vi cydist (n+1);
    vi cyst (n+1);

    set<int> banned;
    set<int> unban;
    set<int> comp;

    auto findban=[&](int v, int st, int dist, int m, auto&&findban) -> void{
        comp.insert(v);
        cyst[v]=st;
        cydist[v]=dist;

        if(fstart[v]) {
            banned.insert(((dist-st)%m+m)%m);
        }
        for(int f:from[v]) {
            //all vis nodes are cycle node
            if(vis[f])
                continue;
            findban(f, st, dist+1, m, findban);
        }
    };

    vi ans (n+1, -1);

    for(vi cycle:cycles) {
        int m=sz(cycle);
        for(int t=0;t<2;t++) {
            for(int i=0;i<m;i++) {
                fdist[cycle[i]]=min(fdist[cycle[i]], fdist[cycle[(i-1+m)%m]]+1);
            }
        }

        //find all the banned, dist[u]-pos[u]
        banned.clear();
        comp.clear();
        unban.clear();
        for(int i=0;i<m;i++) {
            findban(cycle[i], i, 0, m, findban);
        }

        for(int i=0;i<m;i++) {
            if(banned.find(i)==banned.end())
                unban.insert(i);
        }

        for(int j:comp) {
            if(fdist[j]==INF) {
                ans[j]=INF;
                continue;
            }
            if(unban.empty()) {
                ans[j]=-1;
                continue;
            } 

            int opt=fdist[j]+(cydist[j]-cyst[j]);
            opt=((opt%m)+m)%m;

            int diff=INF;
            //find the closest unbanned to be under opt, if nothing, take the closed under opt+m
            if(unban.upper_bound(opt)!=unban.begin()) {
                diff=opt-*prev(unban.upper_bound(opt));
            }else {
                diff=(opt+m)-*prev(unban.upper_bound(opt+m));
            }

            if(fdist[j]>=diff)
                ans[j]=fdist[j]-diff;

            // cout<<j<<":"<<opt<<"\n";
            // cout<<"options:";
            // for(int x:unban) cout<<x<<" ";
            // cout<<"\n";

            // for(int check=fdist[j];check>=0;check--) {
            //     //if we wait check, will we end up meeting
            //     int rhs=(cydist[j]-cyst[j])+check;
            //     rhs=(rhs%m+m)%m;

            //     if(banned.find(rhs)==banned.end()) {
            //         ans[j]=check;
            //         break;
            //     }
            // }
        }
    }

    for(int i=1;i<=n;i++) {
        if(ans[i]==INF)
            cout<<-2<<"\n";
        else
            cout<<ans[i]<<"\n";
    }

}


signed main () {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int t=1;
    // cin>>t;

    while(t>0) {
        solve();
        t--;
    }
}
