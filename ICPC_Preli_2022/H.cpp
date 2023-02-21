// Created by ash_98
#include<bits/stdc++.h>
using namespace std;
 
#define mx 100005
#define ll long long

int dis[18][mx],vis[mx];
int p[mx],sub[mx],lvl[mx];
vector<int>g[mx],ng[mx];
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
    if(par!=-1)lvl[tem]=lvl[par]+1,ng[par].push_back(tem);
    dfs(lvl[tem],tem,-1);
    for(int v:g[tem])
        if(v!=par && !vis[v])decompose(v,tem);
}
set<pair<pair<int,ll>,int>>re[mx];

void update(int u,ll tm)
{
   // cout<<u<<" "<<tm<<endl;
    for(int v=u;v!=-1;v=p[v]){
        re[v].insert({{dis[lvl[v]][u],tm},u});
    }
}

pair<ll,int> query(int u,ll tm)
{
    int ans=-1,d=-1;
    ll req=-1;
    for(int v=u;v!=-1;v=p[v]){
        if(!re[v].empty()){
            auto[it,node]=*re[v].begin();
            if(ans==-1){
                ans=node;
                d=it.first+dis[lvl[v]][u];
                req=it.second;
            }
            else if(d>it.first+dis[lvl[v]][u]){
                ans=node;
                d=it.first+dis[lvl[v]][u];
                req=it.second;
            }
            else if(d==it.first+dis[lvl[v]][u]){
                if(it.second<req){
                    ans=node;
                    d=it.first+dis[lvl[v]][u];
                    req=it.second;
                }
            }
        }
    }
    active[ans]=0;

    for(int v=ans;v!=-1;v=p[v]){
        re[v].erase(re[v].find({{dis[lvl[v]][ans],req},ans}));
    }
    return {max(tm+d,req+d),ans};
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
    vector<pair<ll,int>>v;
    for(int i=0;i<q;i++){
        int ti,u;
        scanf("%d%d",&ti,&u);
        v.push_back({ti,u});
    }
    int cur_node=1;
    ll somoy=0;
    int i=0;
    int available=0;
    while(i<q or available>0){
        while(i<q and somoy>=v[i].first){
            update(v[i].second,v[i].first);
            active[v[i].second]=1;
            i++;
            available++; 
        }
        if(available==0 and i<q){
            update(v[i].second,v[i].first);
            active[v[i].second]=1;
            i++;
            available++;
        }
        if(available==0)break;
        if(available){
            pair<ll,int>a=query(cur_node,somoy);
            cur_node=a.second;
            somoy=a.first;
            available--;
            printf(" %d",cur_node );
        }
    }
    printf("\n");

    for(i=1;i<=n;i++){
        active[i]=0;
        re[i].clear();
        g[i].clear();
        ng[i].clear();
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
