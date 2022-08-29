// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 2000005
#define ll long long
#define mod 1000000007 //998244353

ll fact[mx],inv[mx];

ll bigmod(ll b,ll e)
{
    ll ans=1;
    while(e){
        if(e&1)ans=(ans*b)%mod;
        e>>=1;
        b=b*b%mod;
    }
    return ans;
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
 

int n,h,w,k;
 
void solve()
{
    scanf("%d%d",&h,&w);
    scanf("%d%d",&n,&k);

    vector<pair<int,int>>block(n);
    for(auto &it:block)scanf("%d%d",&it.first,&it.second);
    block.emplace_back(h,w);
    sort(block.begin(),block.end());
   

    vector<vector<int>>dp(n+1,vector<int>(n+5,0));

    for(int i=0;i<n+1;i++){
        int r=block[i].first;
        int c=block[i].second;
        for(int magic=0;magic<=n+1;magic++)
        {
            dp[i][magic]=nCr(r+c-2,r-1);
            for(int v=0;v<magic;v++){
                dp[i][magic]=sub(dp[i][magic],dp[i][v]);
            }
            for(int j=0;j<i;j++){
                auto[x,y]=block[j];
                if(y>c)continue; 
                int dx=r-x;
                int dy=c-y;
                dp[i][magic]=sub(dp[i][magic],mul(nCr(dx+dy,dx),dp[j][magic]));
            }
        }
        
    }



    int ans=nCr(h+w-2,h-1);


    for(int i=k+1;i<=n+1;i++){
 
        ans=sub(ans,dp[n][i]);
    }

    printf("%d\n",ans );

 
}
 
int main()
{
    int t=1;
    fact_cal();

    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
