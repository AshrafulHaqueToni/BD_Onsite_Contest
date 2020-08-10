#include<bits/stdc++.h>
using namespace std;

#define mx 20005
#define ll long long

void IO()
{
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
}


int m,n,k,ii,q;
vector<pair<int,int>>g[mx];
int sub[mx];
ll tot;
multiset<pair<ll,int>>s;

void dfs(int u,int p)
{
    sub[u]++;
    for(auto it:g[u])
    {
        int v=it.first;
        int w=it.second;
        if(v==p)continue;
        dfs(v,u);
        sub[u]+=sub[v];
    }
    for(auto it:g[u])
    {
        int v=it.first;
        int w=it.second;
        if(v==p)continue;
        ll val1=sub[v];
        ll val2=n-sub[v];
        ll val=(val2*val1)*w;
        tot+=val;
        if(val<0)
        {
            s.insert({(-val2*val1),-w});
        }
    }
}

void solve()
{
    scanf("%d",&n);
    tot=0;
    for(int i=1;i<n;i++)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        g[x].push_back({y,w});
        g[y].push_back({x,w});
    }
    dfs(1,-1);
    ll re=0;
    if(tot<0)
    {
        auto it=s.begin();
        while(it!=s.end())
        {
            ll val=it->first;
            int w=it->second;
            val*=-1;
            ll tem=0-tot;
            ll cnt=tem/val;
            if(tem%val!=0)cnt++;
            if(cnt>w)cnt=w;
            tot+=val*cnt;

            re+=cnt;
            if(tot>=0)break;
            it++;
        }
    }
    printf("Case %d: %lld\n",++ii,re );
    s.clear();
    for(int i=1;i<=n;i++)
    {
        g[i].clear();
        sub[i]=0;
    }

}

int main()
{
    //IO();
    int t=1;
    scanf("%d",&t);
    while(t--)
    {
        solve();
    }
    return 0;
}
