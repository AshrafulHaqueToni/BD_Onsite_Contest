// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 200005
#define ll long long
#define mod 1000000007 //998244353
 

int n,m,ii,k;
ll fact[mx],inv[mx];

ll bigmod(ll e,ll x)
{
    if(!x)
    {
        if(e)return 1;
        return 0;
    }
    ll p=bigmod(e,x/2);
    p=(p*p)%mod;
    if(x%2)p=(p*e)%mod;
    return p;
}

int add(int a,int b)
{
    a+=b;
    if(a>=mod)a-=mod;
    return a;
}
int sub(int a,int b)
{
    a-=b;
    if(a<0)a+=mod;
    return a;
}
int mul(int a,int b)
{
    ll re=a;
    re*=b;
    if(re>=mod)re%=mod;
    return re;
}

void fact_cal()
{
    fact[0]=1;
    inv[0]=1;
    for(int i=1;i<=mx-3;i++)
    {
        fact[i]=(fact[i-1]*i)%mod;
    }
    inv[mx-3]=bigmod(fact[mx-3],mod-2);
    for(int i=mx-4;i>=1;i--)inv[i]=(inv[i+1]*(i+1))%mod;
}

int nCr(int nn,int r)
{
    if(nn<r)return 0;
    return mul(fact[nn],mul(inv[nn-r],inv[r]));
}

vector<int>g[mx];
int vis[mx];
int len;

map<pair<int,int>,bool>mp;
vector<int>cycle;

void dfs(int u,int p)
{
    if(len)return;
    vis[u]=1;
    cycle.push_back(u);

    for(int v:g[u])
    {
        if(len)return;
        if(v==p)continue;

        if(vis[v]==1)
        {
           
            while(!cycle.empty())
            {
                len++;
             

                if(cycle.back()==v)break;
                cycle.pop_back();
            }
    
            continue;
        }
        else if(vis[v]==0) dfs(v,u);
    }

    vis[u]=2;
    if(len)return;
    cycle.pop_back();
}
 
void solve()
{
    scanf("%d%d",&n,&k);
    len=0;
    mp.clear();
    cycle.clear();

    for(int i=1;i<=n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        g[x].push_back(y);
        g[y].push_back(x);
        if(x>y)swap(x,y);
        if(mp.count({x,y}))
        {
            len=2;
        }
        mp[{x,y}]=1;
        if(x==y)len=1;
    }

    if(len==0)dfs(1,-1);

    //cout<<len<<endl;
    int re=nCr(n,k);
    int one_cycle_edge=mul(nCr(n-1,k-1),n-k);
    re=add(re,mul(one_cycle_edge,len));
    
    printf("%d\n",sub(1,mul(re,bigmod(mul(nCr(n,k),nCr(n,k)),mod-2))));

    for(int i=1;i<=n;i++)g[i].clear(),vis[i]=0;

 
}
 
int main()
{
    int t=1;
    fact_cal();
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
