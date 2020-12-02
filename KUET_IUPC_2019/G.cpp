// Created by ash_98

#include<bits/stdc++.h>
using namespace std;


#define mx 30005
#define ll long long
#define mod 1000000007

int dist[mx],cycle[mx],vis[mx],vis1[mx],dist1[mx];
int n,m,ii,k;

vector<pair<int,int>>g[mx];
int val,last;

void dfs(int u,int p,int tot)
{
   //cout<<u<<" "<<p<<" "<<tot<<endl;
   dist1[u]=tot;
   vis[u]=ii;
   for(auto it:g[u])
   {
   	  int v=it.first;
   	  int w=it.second;
   	  if(v==p)continue;
   	  tot+=w;
   	  val=max(val,tot);
   	  if(vis[v]==ii)
   	  {
   	    cycle[ii]=1;	
   	  	continue;
   	  }
   	  dfs(v,u,tot);
   }
}

void chk(int u,int p)
{
	vis1[u]=ii;
	last=u;
	for(auto it:g[u])
	{
		if(it.first==p || vis1[it.first]==ii)continue;
        chk(it.first,u);
	}
}


void solve()
{
	scanf("%d%d",&n,&m);
    ii=0;
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		g[x].push_back({y,z});
		g[y].push_back({x,z});
	}

	int q;
	scanf("%d",&q);

	for(int i=1;i<=n;i++)
	{
		   if(vis[i]==0)
		   {
		   	   ii++;
		   	   chk(i,-1);
		   	   val=0;
		   	   dfs(last,-1,0);
		   	   dist[ii]=val;
		   }		
			
	}


	printf("Case %d:\n",++k );

	for(int i=1;i<=q;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if(vis[x]!=vis[y])printf("-1\n");
		else
		{
			int re=abs(dist1[x]-dist1[y]);
			if(cycle[vis[x]])
			{
				int ace=dist[vis[x]]-re;
				re=min(re,ace);
			}
			printf("%d\n",re );
		}
	} 

	for(int i=1;i<=n;i++)g[i].clear(),dist[i]=0,dist1[i]=0,cycle[i]=0,vis1[i]=0,vis[i]=0;

}

int main()
{
	int t=1;
	scanf("%d",&t);
	while(t--)solve();
	return 0;
}