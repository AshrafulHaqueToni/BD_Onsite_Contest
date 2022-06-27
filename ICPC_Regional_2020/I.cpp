// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 50005
#define ll long long
#define mod 1000000007 //998244353
 

int cost[mx];
ll pre[mx];
int n,m,ii,k;
ll dp[mx];
vector<pair<int,int>>gl[mx],gr[mx];

namespace Segment_Tree
{
    const int N=50005;
    ll Tree[N*4];
    ll Lazy[N*4];


    void Relax(int node,int be,int en)
    {
        if(!Lazy[node])return;

        Tree[node]+=Lazy[node];
        if(be!=en)
        {
           Lazy[node*2]+=Lazy[node];
           Lazy[node*2+1]+=Lazy[node];
        }
        Lazy[node]=0;
    }

    void init(int node,int be,int en)
    {
        Lazy[node]=0;
        if(be==en)
        {
            Tree[node]=0;
            return;
        }
        int mid=(be+en)/2;
        init(node*2,be,mid);
        init(node*2+1,mid+1,en);
        Tree[node]=max(Tree[node*2],Tree[node*2+1]);
    }

    void Rupdate(int node,int be,int en,int i,int j,ll val)
    {
        Relax(node,be,en);
        if(be>j || en<i)return ;
        if(be>=i && en<=j)
        {
            Lazy[node]+=val;
            Relax(node,be,en);
            return;
        }
        int mid=(be+en)/2;
        Rupdate(node*2,be,mid,i,j,val);
        Rupdate(node*2+1,mid+1,en,i,j,val);
        Tree[node]=max(Tree[node*2],Tree[node*2+1]);
    }

    ll query(int node,int be,int en,int i,int j)
    {
        Relax(node,be,en);
        if(be>j || en<i)return 0;
        if(be>=i && en<=j)return Tree[node];
        int mid=(be+en)/2;
        return max(query(node*2,be,mid,i,j),query(node*2+1,mid+1,en,i,j));
    }
}

using namespace Segment_Tree;

void solve()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        int val,x,y;
        scanf("%d%d%d",&val,&x,&y);
        pre[x]+=val;
        pre[y+1]-=val;
        gr[y].emplace_back(val,x);
        gl[x].emplace_back(val,y);
    }
    ll tot=0;
    ll re=0;
    init(1,1,m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&cost[i]);
        tot+=pre[i];

        if(i>1)
        {
            for(auto[val,y]:gl[i])
            {
                Rupdate(1,1,m,1,i-1,val);
            }
        }

        for(auto[val,x]:gr[i-1])
        {
            if(x==1)continue;
            Rupdate(1,1,m,1,x-1,-val);
        }
        dp[i]=dp[i-1];

        dp[i]=max(dp[i],tot-cost[i]);

       // cout<<query(1,1,m,1,1)<<" ";

        dp[i]=max(dp[i],query(1,1,m,1,i-1)-cost[i]);

        Rupdate(1,1,m,i,i,dp[i]);
        re=max(re,dp[i]);

        //cout<<dp[i]<<" ";
    }
   // cout<<endl;


    for(int i=0;i<=m+1;i++)
    {
        pre[i]=0;
        dp[i]=0;
        gl[i].clear();
        gr[i].clear();

    }
    printf("Case %d: %lld\n",++ii,re );
 
}
 
int main()
{
    int t=1;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
