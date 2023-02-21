// Created by ash_98
#include<bits/stdc++.h>
using namespace std;
 
#define mx 100005
#define ll long long

int dis[18][mx],vis[mx];
int p[mx],sub[mx],lvl[mx];
vector<int>g[mx];
bool active[mx];

/* p[u] = parent of u in centroid tree
dis[x][u] = distance from u to a parent of u at level x of centroid tree
if u is in subtree of centroid c, then dis[lvl[c]][u] = dist(c, l)
If (x, y) edge exist, then x must be in g[y] and y must be in g[x]*/
/* we can do more pre work in dfs function*/

void dfs(int l,int u,int par)
{
    if(par!=-1)dis[l][u]=dis[l][par]+1;
    for(int v:g[u])
        if(v!=par && !vis[v])dfs(l,v,u);
}
int centroid(int u,int par,int r)
{
    for(int v:g[u])
        if(v!=par && !vis[v] && sub[v]>r)return centroid(v,u,r);
    return u;
}
void pre_cal(int u,int par)
{
    sub[u]=1;
    for(int v:g[u])
        if(v!=par && !vis[v])pre_cal(v,u),sub[u]+=sub[v];
}
void decompose(int u,int par)
{
    pre_cal(u,-1);
    int tem=centroid(u,-1,sub[u]>>1);
    vis[tem]=1,p[tem]=par,lvl[tem]=0;
    if(par!=-1)lvl[tem]=lvl[par]+1;
    dfs(lvl[tem],tem,-1);
    for(int v:g[tem])
        if(v!=par && !vis[v])decompose(v,tem);
}
priority_queue<pair<int,int>>re[mx];
ll memo[mx];
int ar[mx];

void update(int u,int tm)
{
    for(int v=u;v!=-1;v=p[v]){
        while(!re[v].empty() and active[ar[-re[v].top().second]]==0)re[v].pop();
        re[v].push({-dis[lvl[v]][u],-tm});
    }
}

int cur_node;
ll somoy;

void query(int u)
{
    int d=-1,req=-1;
    for(int v=u;v!=-1;v=p[v]){
        while(!re[v].empty() and active[ar[-re[v].top().second]]==0)re[v].pop();
        if(!re[v].empty()){
            auto[dd,id]=re[v].top();
            dd*=-1;
            id*=-1;
            int d_path=dd+dis[lvl[v]][u];
            if(req==-1){
                d=d_path;
                req=id;
            }
            else if(d>d_path){
                d=d_path;
                req=id;
            }
            else if(d==d_path){
                if(id<req){
                    d=d_path;
                    req=id;
                }
            }
        }
    }

    cur_node=ar[req];
    active[cur_node]=0;
    somoy=max(somoy,memo[req])+d;
    return ;
}

int ii,n;
 
void solve()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    decompose(1,-1);
    int q;
    printf("Case %d:",++ii );
    scanf("%d",&q);
    vector<int>v;
    for(int i=0;i<q;i++){
        ll ti;
        int u;
        scanf("%lld%d",&ti,&u);
        v.push_back(u);
        memo[i]=ti;
        ar[i]=u;
    }
    cur_node=1;
    somoy=0;
    int i=0;
    int available=0;
    while(i<q or available>0){
        while(i<q and somoy>=memo[i]){
            update(v[i],i);
            active[v[i]]=1;
            i++;
            available++; 
        }
        if(available==0 and i<q){
            update(v[i],i);
            active[v[i]]=1;
            i++;
            available++;
        }
        if(available==0)break;
        if(available){
            query(cur_node);
            available--;
            printf(" %d",cur_node );
        }
    }
    printf("\n");

    for(i=1;i<=n;i++){
        while(!re[i].empty())re[i].pop();
        g[i].clear();
        vis[i]=0;
        sub[i]=0;
        p[i]=0;
        for(int j=0;j<18;j++)dis[j][i]=0;
        lvl[i]=0;
    }
}
 
int main()
{
    int t=1;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
