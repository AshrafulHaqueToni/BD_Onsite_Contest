// Created by ...
#include<bits/stdc++.h>
using namespace std;


#define mx 100005
#define ll long long 

void IO()
{
  #ifndef ONLINE_JUDGE
  freopen("in.txt","r",stdin);
  freopen("out.txt","w",stdout);
  #endif
}


int ar[mx];
char ch[mx];
int m,n,k,ii;

ll func(ll val)
{
	if(val==0)return 0;
	ll be=1,en=1e9;
	ll re=0,re1=0;
	while(be<=en)
	{
		ll mid=(be+en)/2;
		ll limit=mid*mid;
		if(limit<=val)
		{
			re=mid;
			be=mid+1;
		}
		else en=mid-1;
	}
	be=1,en=1e9;
	while(be<=en)
	{
		ll mid=(be+en)/2;
		ll limit=mid*mid*2;
		if(limit<=val)
		{
			re1=mid;
			be=mid+1;
		}
		else en=mid-1;
	}
	return re+re1;
}

void solve()
{
   ll a,b;
   scanf("%lld%lld",&a,&b);
   printf("Case %d: %lld\n",++ii,func(b)-func(a-1));
}

int main()
{
 //  IO();
  int t=1;
  scanf("%d",&t);
  while(t--)
  {
    solve();
  }
  return 0;
}
