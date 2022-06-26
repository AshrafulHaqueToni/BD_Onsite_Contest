// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 50005
#define ll long long
#define mod 1000000007 //998244353
 
int ar[mx],br[mx];
int n,m,ii,k;

int dp[mx][12];
int vis[mx][12];

int suf[mx];

int dp1[mx][12];
int vis1[mx][12];

int func(int cur,int how)
{
    if(vis[cur][how]==ii)return dp[cur][how];
    vis[cur][how]=ii;

    int re=1;
    int li=cur+how+1;
    for(int i=cur+1;i<=li and i<=n ;i++)
    {
        if(br[i]>=br[cur])
        {
            re=max(re,1+func(i,how-i+cur+1));
        }
    }

    return dp[cur][how]=re;
}

vector<pair<int,int>>b;

int calc(int val)
{
    int be=0,en=n-1;
    int got=n;
    while(be<=en)
    {
        int mid=(be+en)/2;
        if(b[mid].first>=val)
        {
            got=mid;
            en=mid-1;
        }
        else be=mid+1;
    }
    return suf[got];
}



int func1(int cur,int how)
{
    if(vis1[cur][how]==ii)return dp1[cur][how];
    vis1[cur][how]=ii;

    int re=calc(ar[cur]);
    int li=cur+how+1;

    for(int i=cur+1;i<=li and i<=n ;i++)
    {
        if(ar[i]>=ar[cur])
        {
            re=max(re,func1(i,how-i+cur+1));
        }
    }

    return dp1[cur][how]=re+1;
}
 
void solve()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)scanf("%d",&ar[i]);
    for(int i=1;i<=n;i++)scanf("%d",&br[i]);
    b.clear();

    ii++;
   
    
    for(int i=n;i>=1;i--)
    {
        int tot=0;
        for(int j=0;j<=k;j++)
        {
            tot=max(tot,func(i,j));
        }
        //int tot=func(i,k);

        //cout<<i<<" "<<tot<<endl;
        b.emplace_back(br[i],tot);
        //cout<<tot<<endl;
    }
    //cout<<func(1,2)<<endl;

    sort(b.begin(),b.end());
    suf[n]=0;
    int re=0;

    for(int i=n-1;i>=0;i--)
    {
        suf[i]=max(suf[i+1],b[i].second);

    }
    re=suf[0];

    for(int i=n;i>=1;i--)
    {
        re=max(re,func1(i,k));
    }

    printf("Case %d: %d\n",ii,re);

 
}
 
int main()
{
    int t=1;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
