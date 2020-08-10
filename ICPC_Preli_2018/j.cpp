#include<bits/stdc++.h>
using namespace std;

#define mx 200005
#define ll long long

vector<int>g[mx];
vector<pair<int,int>>ans;
int m,n,k,ii,dek;

void dfs(int u,int p,int ti)
{
    if(ti>0)
    {

        if(ti%2==1)
        {
            ans.push_back({p,u});
        }
        else ans.push_back({u,p});
    }
    for(int v:g[u])
    {
        if(v==p)continue;
        dfs(v,u,ti+1);
    }
}

void solve()
{
    scanf("%d",&n);
    for(int i=1; i<n; i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(1,-1,0);
    printf("Case %d:\n",++ii);
    for(auto it:ans)
    {
        printf("%d %d\n",it.first,it.second );
    }
    for(int i=1; i<=n; i++)g[i].clear();
    ans.clear();
}

int main()
{
    int t=1;
    scanf("%d",&t);
    while(t--)
    {
        solve();
    }
    return 0;
}
