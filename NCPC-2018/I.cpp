// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 200005
#define ll long long
#define mod 1000000007 //998244353
 
int ar[mx];
char ch[mx];
int n,m,ii,k;

bool func(int tar)
{
    int need=0;
    int cur=-mod;
    for(int i=1;i<=m;i++)
    {
        if(cur>=ar[i])continue;
        if(cur<=ar[i] and (ar[i]-tar)<=cur)continue;
        need++;
        cur=ar[i]+tar;

    }
    return need<=k;
}
 
void solve()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++)scanf("%d",&ar[i]);
    sort(ar+1,ar+m+1);
    int be=1,en=1e9;
    int re=en;
    while(be<=en)
    {
        int mid=(be+en)/2;
        if(func(mid))
        {
            re=mid;
            en=mid-1;
        }
        else be=mid+1;
    }
    if(func(0))re=0;
    printf("Case %d: %d\n",++ii,re);


 
}
 
int main()
{
    int t=1;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
