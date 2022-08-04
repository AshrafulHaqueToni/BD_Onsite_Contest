// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 305
#define ll long long
#define mod 1000000007 //998244353
 
int cupon[10005];
vector<pair<int,int>>g[mx];
ll dis[mx][10005];
int n,m,ii,k;
int s,d;
 
void solve()
{
    scanf("%d%d%d",&n,&m,&k);
    scanf("%d%d",&s,&d);
    for(int i=1;i<=k;i++)scanf("%d",&cupon[i]);
    sort(cupon+1,cupon+k+1);
    reverse(cupon+1,cupon+k+1);
    for(int i=1;i<=m;i++){
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        if(x==y)continue;
        g[x].emplace_back(y,w);
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=k;j++)dis[i][j]=1e15;
    }
    priority_queue<pair<ll,pair<int,int>>>pq;
    pq.push({0,{s,0}});
    dis[s][0]=0;
    while(!pq.empty()){
        ll cost=-pq.top().first;
        auto[u,use]=pq.top().second;
        pq.pop();
        if(dis[u][use]<cost)continue;

        for(auto[v,w]:g[u]){
            ll tot=w+cost;
            if(use<k)tot-=cupon[use+1];
            int cur=use+(use<k);
            
            if(dis[v][cur]>tot){
                dis[v][cur]=tot;
                pq.push({-tot,{v,cur}});
            }
        }
    }
    ll re=1e15;
    for(int i=0;i<=k;i++)re=min(re,dis[d][i]);
    if(re>=1e15)re=-1;
    printf("%lld\n",re);
    for(int i=1;i<=n;i++)g[i].clear();

 
}
 
int main()
{
    int t=1;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
