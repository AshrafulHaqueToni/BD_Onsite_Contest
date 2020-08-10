#include<bits/stdc++.h>
using namespace std;

#define mx 100005
#define ll long long
#define mod 132021913
ll ar[mx];
ll ace[mx];
int m,n,k,ii,dek;

ll bigmod(ll e,ll x)
{
    if(!x)return 1;
    ll p=bigmod(e,x/2);
    p=(p*p)%mod;
    if(x%2)p=(p*e)%mod;
    return p;
}

void solve()
{
    scanf("%d",&n);
    int boro=0;
    for(int i=1; i<=n; i++)
    {
        scanf("%d",&m);
        ar[m]++;
        boro=max(boro,m);
    }
    ll re=0;

    for(int i=boro; i>=1; i--)
    {
        ll sumsq=0;
        ll sqsum=0;
        for(int j=i; j<=boro; j+=i)
        {
            sumsq+=ar[j]*j;
            sqsum+=ar[j]*j*j;
            sumsq%=mod;
            sqsum%=mod;
        }
        sumsq*=sumsq;
        sumsq%=mod;
        ll val=(sumsq-sqsum)%mod;
        if(val<0)val+=mod;
        val*=bigmod(2,mod-2);
        val%=mod;
        for(int j=i; j<=boro; j+=i)
        {
            val=(val-ace[j])%mod;
            if(val<0)val+=mod;
        }
        ace[i]=val;
        re+=(val*bigmod(i,mod-2))%mod;
        re%=mod;

    }
    printf("Case %d: %lld\n",++ii,re);
    for(int i=1; i<=boro; i++)ace[i]=0,ar[i]=0;

}

int main()
{
    // #ifndef ONLINE_JUDGE
    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);
    // #endif
    int t=1;
    scanf("%d",&t);
    while(t--)
    {
        solve();
    }
    return 0;
}
