// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 200005
#define ll long long
#define mod 1000000007 //998244353
 
 
void solve()
{
    ll l1,l2,p,q;
    char c;
    scanf("%lld%lld%lld %c%lld",&l1,&l2,&p,&c,&q);
    if(l1==0 and l2==0 and p==0 and q==0)exit(0);

    ll x = p*p*(l1-1)-(l2*q*q)+(q*q);

    x*=2;

    x/=p*(q-p);

    ll re=(l1*2+x-2);
    
    printf("%lld\n",re );
 
}
 
int main()
{
    int t=1;
    //scanf("%d",&t);
    while(1)solve();
    return 0;
}
