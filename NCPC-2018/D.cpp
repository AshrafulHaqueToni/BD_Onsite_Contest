// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 2005
#define ll long long
#define mod 1000000007 //998244353
 

int n,m,ii,k,tc;
vector<pair<int,int>>g[405];
vector<pair<pair<int,int>,int>>query[405];
int vis[405][mx];
int ans[505];
int dist[405];

void func(int u,int cost)
{
    if(cost>2000)return;
    if(vis[u][cost]==ii)return;
    vis[u][cost]=ii;
    for(auto[v,w]:g[u])
    {
        func(v,cost+w);
    }
}

void dijkstra(int rot)
{
    priority_queue<pair<int,int>>pq;
    dist[rot]=0;
    pq.push({0,rot});
    while(!pq.empty())
    {
        auto[w,u]=pq.top();
        w*=-1;
        pq.pop();
        if(dist[u]<w)continue;
        for(auto[v,c]:g[u])
        {
            if(dist[v]>w+c){
                dist[v]=w+c;
                pq.push({-dist[v],v});
            }
        }
    }
}
 
void solve()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        g[x].emplace_back(y,z);
        g[y].emplace_back(x,z);
    }
    int q;
    scanf("%d",&q);
    for(int i=1;i<=q;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        query[x].push_back({{y,z},i});
    }
    printf("Case %d:\n",++tc);

    for(int i=1;i<=n;i++)
    {
        if(!query[i].empty())
        {
            ii++;
            func(i,0);
            for(int j=1;j<=n;j++)dist[j]=mod;
            dijkstra(i);
            
            for(auto it:query[i])
            {
                auto[y,z]=it.first;
                int id=it.second;
                int be=z,en=z;
                int re=-1;
                while(be>=0 or en<=2000)
                {
                    if(be>=0 and vis[y][be]==ii)
                    {
                        re=z-be;
                        break;
                    }
                    if(en<=2000 and vis[y][en]==ii)
                    {
                        re=en-z;
                        break;
                    }
                    be--;
                    en++;
                }
                if(dist[y]!=mod)
                {
                    if(re==-1)re=abs(z-dist[y]);
                    else re=min(re,abs(z-dist[y]));
                }
                ans[id]=re;
            }

        }
    }
    for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
    for(int i=1;i<=n;i++)
    {
        g[i].clear();
        query[i].clear();
    }

 
}
 
int main()
{
    int t=1;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
