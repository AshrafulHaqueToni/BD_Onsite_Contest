// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 1000005
#define ll long long
#define mod 1000000007 //998244353
 
int ar[mx];
char ch[mx];
int n,m,ii,k;

int lp[mx];
vector<int>prime;
vector<int>pf[mx];
int P_idx[mx];
priority_queue<pair<int,int>>pq[78500];
int dp[mx];

void sieve()
{
	int idx=1;
    for(int i=2;i<mx-3;i++)
    {
        if(lp[i]==0)
        {
            prime.push_back(i);
            lp[i]=i;
            P_idx[i]=idx++;
        }
        for(int j=0;j<prime.size()&&prime[j]<=lp[i]&&i*prime[j]<mx-3;j++)
            lp[i*prime[j]]=prime[j];
    }

    for(int i=2;i<mx-3;i++)
    {
        int val=i;
        while(val>1)
        {
        	int spf=lp[val];
        	while(val%spf==0)val/=spf;
        	pf[i].emplace_back(P_idx[spf]);
        }
    }
}
 
void solve()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
    	scanf("%d",&ar[i]);
    	if(i>1)
    	{
    		dp[i]=dp[i-1]+1;
    		for(int p:pf[ar[i]])
    		{
    			while(!pq[p].empty() and pq[p].top().second<i-k)pq[p].pop();
    			if(pq[p].empty())continue;
    			dp[i]=min(dp[i],-pq[p].top().first+1);
    		}
    	}
    	for(int p:pf[ar[i]])
		{
			pq[p].emplace(-dp[i],i);
		}
    }
    for(int i=1;i<=n;i++)
    {
    	for(int p:pf[ar[i]])
    	{
    		while(!pq[p].empty())pq[p].pop();
    	}
    }
    printf("Case %d: %d\n",++ii,dp[n]);

 
}
 
int main()
{
    int t=1;
    sieve();
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
