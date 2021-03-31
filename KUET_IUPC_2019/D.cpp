// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 1000005
#define ll long long
#define mod 1000000007
 
int ar[mx];
char ch[mx];
int n,m,ii,k;
int bame[mx],dane[mx];
 
void solve()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&ar[i]);
	ar[0]=mod;
	ar[n+1]=mod;
	stack<int>stk;
	stk.push(0);
	for(int i=1;i<=n;i++)
	{
		while(ar[stk.top()]<=ar[i])stk.pop();
		bame[i]=stk.top();
		stk.push(i);
	}
	while(!stk.empty())stk.pop();
	stk.push(n+1);
	for(int i=n;i>=1;i--)
	{
		while(ar[stk.top()]<=ar[i])stk.pop();
		dane[i]=stk.top();
		stk.push(i);
	}
	ll re=0;
	for(int i=1;i<=n;i++)
	{
		if(bame[i]==0 && dane[i]==n+1)continue;
		if(bame[i]>0)
		{
			int id=bame[i]-1;
			while(id>0 && ar[id]<=ar[i])id=bame[id];
			ll len=i-id-1+dane[i]-i;
			re=max(re,len*(ar[bame[i]]-ar[i]));
		}
		if(dane[i]<n+1)
		{
			int id=dane[i]+1;
			while(id<=n && ar[id]<=ar[i])id=dane[id];
			ll len=id-i-1+i-bame[i];
			re=max(re,len*(ar[dane[i]]-ar[i]));
		}
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
