// Created by ...
#include<bits/stdc++.h>
using namespace std;


#define mx 100005
#define ll long long 
#define mod 1000000007

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
ll dp[mx][5];
int vis[mx][5];

ll func(int idx,int color)
{
	//cout<<idx<<" "<<color<<endl;
	if(idx==n)
		{
			
			return 1;
		}
	if(vis[idx][color]==ii)return dp[idx][color];
	vis[idx][color]=ii;
	ll re=0;
	if(ch[idx]=='W')
	{
		if(idx==0)
		{
			if(idx+1<n)
			{
				for(int i=0;i<3;i++)
				{
					if(i==0 && ch[idx+1]!='G')re=(re+func(idx+1,0))%mod;
					if(i==1 && ch[idx+1]!='R')re=(re+func(idx+1,1))%mod;
					if(i==2 && ch[idx+1]!='B')re=(re+func(idx+1,2))%mod;
				}
			}
			else
			{
				re=3;
			}
		}
		else
		{
			if(idx+1<n)
			{
				for(int i=0;i<3;i++)
				{
					if(i==0 && ch[idx+1]!='G' && color!=0)re=(re+func(idx+1,0))%mod;
					if(i==1 && ch[idx+1]!='R' && color!=1)re=(re+func(idx+1,1))%mod;
					if(i==2 && ch[idx+1]!='B' && color!=2)re=(re+func(idx+1,2))%mod;
				}
			}
			else
			{
				re=2;
			}
		}
	}
	else if(ch[idx]=='G')re=func(idx+1,0);
	else if(ch[idx]=='R')re=func(idx+1,1);
	else re=func(idx+1,2);
	return dp[idx][color]=re;
}

void solve()
{
   scanf("%s",ch);
   n=strlen(ch);
   ii++;
   printf("Case %d: %lld\n",ii,func(0,0));
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
