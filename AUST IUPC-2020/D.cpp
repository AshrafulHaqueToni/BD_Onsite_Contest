// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 1000005
#define ll long long
#define mod 998244353
 

int n,m,ii,k;
ll pre[mx];

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

ll add(ll a,ll b)
{
    a+=b;
    if(a>=mod)a-=mod;
    return a;
}
ll sub(ll a,ll b)
{
    a-=b;
    if(a<0)a+=mod;
    return a;
}
ll mul(ll a,ll b)
{
    ll re=a;
    re*=b;
    if(re>=mod)re%=mod;
    return re;
}

ll fact[mx],inv[mx];

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


void func()
{
    pre[0]=1;
    ll val=1;
    for(int i=1;i<=mx-3;i++)
    {
        val=mul(val,2);
        pre[i]=mul(pre[i-1],sub(val,1));
    }
}
 
void solve()
{
    scanf("%d%d",&n,&k);
    if(k<n)
    {
        printf("0\n");
        return;
    }
    ll nn=n;
    nn*=(n-1);
    nn/=2;

    ll bat=1;
    if(k>n)bat=bigmod(pre[k-n],mod-2);

    ll re=mul(pre[k],bat);

    re=mul(re,bigmod(2,nn));

    re=mul(re,inv[n]);

    printf("%lld\n",re);
 
}
 
int main()
{
    int t=1;
    func();
    fact_cal();
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
