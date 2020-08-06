#include<bits/stdc++.h>
using namespace std;

#define mx 100005
#define ll long long 


vector<int>g[mx];
int st[mx],en[mx],id[mx];
bool ans[mx];
set<pair<int,int>>s;
int m,n,k,ii,dek;
int tt=1;

void dfs(int u,int par)
{
	st[u]=tt++;
	for(int v:g[u])
	{
		if(v==par)continue;
		dfs(v,u);
	}
	en[u]=tt++;
	s.insert({en[u],u});
}

void solve()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	for(int i=1;i<=n;i++)sort(g[i].begin(),g[i].end());
	tt=1;
	dfs(1,-1);
	printf("Case %d:\n",++ii );
	int q;
	scanf("%d",&q);
	while(q--)
	{
		int ti,u;
		scanf("%d%d",&ti,&u);
		if(ti==2)
		{
			if(ans[u]==0)printf("0\n");
			else printf("1\n");
		}
		else
		{
			int x;
			scanf("%d",&x);
			if(ans[u]==true || x==0)continue;

			int val=st[u];
			auto idx=s.upper_bound({val,n+1});
			auto it=idx;
            while(x>0)
            {
                 int sesh=idx->first;
                 ans[idx->second]=1;
                 idx++;
                 if(sesh==en[u])break;
                 x--;

            }
            s.erase(it,idx);
		}

	}
	for(int i=1;i<=n;i++)
	{
		g[i].clear();
		ans[i]=false;
		id[i]=0;
	}
	s.clear();
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
