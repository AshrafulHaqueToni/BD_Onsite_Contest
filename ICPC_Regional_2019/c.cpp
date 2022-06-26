// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 200005
#define ll long long
#define mod 1000000007 //998244353
 

int n,m,ii,k;

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

int sub(int a,int b)
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




 
void solve()
{
    scanf("%d%d",&n,&m);
    ll each_color_probability=sub(1,bigmod(mul(n-1,bigmod(n,mod-2)),m));
    printf("Case %d: %lld\n",++ii,mul(each_color_probability,n) );
 
}
 
int main()
{
    int t=1;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
