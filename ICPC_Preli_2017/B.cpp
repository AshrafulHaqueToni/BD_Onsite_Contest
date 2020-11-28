// Created by ash_98

#include<bits/stdc++.h>
using namespace std;



#define mx 200005
#define ll long long
#define mod 1000000007

int ar[mx];
char ch[mx];
int n,m,ii,k;

ll fact[mx],inv[mx];

ll bigmod(ll e,ll x)
{
    if(!x)return 1;
    ll p=bigmod(e,x/2);
    p=(p*p)%mod;
    if(x%2)p=(p*e)%mod;
    return p;
}

void fact_cal()
{
    fact[0]=1;
    for(int i=1;i<=mx-3;i++)
    {
        fact[i]=(fact[i-1]*i)%mod;
    }

}


void solve()
{
  vector<pair<int,int>>v;
  scanf("%d%d",&n,&m);
  
  for(int i=1;i<=m;i++)
  {
    int x,y;
    scanf("%d%d",&x,&y);
    v.push_back({x+1,y});

  }
  if(n<=m)
  {
    printf("Case %d: 0\n",++ii );
    return;
  }

  v.push_back({n+1,n});
  ll re=1;
  int last=0,val=1;
  for(auto it:v)
  {
     int cur=it.first;
     int val1=it.second;

     int gap=cur-last-1;
     int ace=val1-val+1;

     //debug(),dbg(gap),dbg(ace),dbg(cur),dbg(val1);

     if(gap>0)
     {
        
        //if(ace>gap)swap(ace,gap);
        ll val3=fact[ace+gap-1]*(bigmod(fact[gap]*fact[ace+gap-1-gap]%mod,mod-2))%mod;
        
       // debug(),dbg(ace),dbg(gap),dbg(val3);
        re=(re*val3)%mod;
     }
     last=cur;
     val=val1;
  }
  printf("Case %d: %lld\n",++ii,re );
}

int main()
{
  int t=1;
  fact_cal();
  scanf("%d",&t);
  while(t--)solve();
  return 0;
}
