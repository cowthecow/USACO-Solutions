
const int MAXN=201;

int n,m;
char grid [MAXN][MAXN];
int status [MAXN];

int solve_2p () {
    //use status array, it is n long
    int ans=0;
    int l=1;
    for(int r=1;r<=n;r++) {
        if(status[r]==2||status[r]==3) {
            l=r+1;
        }
        if(status[r]==0) {
            while(l<r&&status[l]==1) {
                l++;
            }
            ans=max(ans, r-l+1);
        }
    }
    return ans;
}

signed main(){

    setIO("fortmoo");
    //bruteforce though pairs of columns
    //for each pair of columns, check each row, some can go through, some can't
    //for each pair of columns, the rows can return the following:

    //edge block: we can't go through this at all because the muddy area is on the edge column
    //center block: we can't use this as border, but we can go through (muddy inside rect)
    //no block: full clean, we can use it as border

    cin>>n>>m;

    for(int i=1;i<=n;i++) {
        string s;
        cin>>s;
        for(int j=1;j<=m;j++) {
            grid[i][j]=s[j-1];
        }
    }

    int ans=0;
    for(int l=1;l<=m;l++) {
        fill(status, status+n+1, 0);

        for(int r=l;r<=m;r++) {
            //sweep the r pointer
            for(int v=1;v<=n;v++) {
                if(status[v]==2) { //formerly muddy right-edge now is enclosed
                    status[v]=1;
                }
                if(grid[v][r]=='X') {
                    if(r==l) {
                        status[v]=3; //perm impossible
                    }else {
                        if(status[v]!=3)
                            status[v]=2;
                    }
                }
            }

            ans=max(ans, (r-l+1)*solve_2p());
        }
        //a good subarray must be bordered by 0s, and can only inclose 1s
    }
    cout<<ans<<"\n";
}
