#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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

string t="bessie";
int dp [6];
int fin=0; //finished substrings
int ans=0;

signed main(){
    
    string s;
    cin>>s;
    for(int i=0;i<sz(s);i++) {
        //when adding character i, update dp
        dp[0]++;
        for(int j=5;j>=0;j--) {
            if(t[j]==s[i]) {
                if(j==5) {
                    fin+=dp[j];
                    dp[0]+=dp[j];
                    dp[j]=0;
                }else {
                    dp[j+1]+=dp[j];
                    dp[j]=0;
                }
            }
        }
        ans+=fin;
    }
    cout<<ans<<"\n"; 
}
