// Created by ash_98

#include<bits/stdc++.h>
using namespace std;


#define mx 10005
#define ll long long
#define mod 1000000007

int ar[mx];
char ch[mx];
int n,m,ii,k,LOG;
bitset<mx> Tree[mx];
int par[mx][20];
int depth[mx];
vector<int> g[mx];

void dfs(int u,int p,int lvl,bitset<mx>bt)
{
    par[u][0]=p;
    depth[u]=lvl;
    bt[u]=true;
    Tree[u]=bt;

    for(auto v:g[u])
    {
        if(v==p)continue;
        dfs(v,u,lvl+1,bt);
    }
}

void init(int root)
{
	bitset<mx>bt;
    dfs(root,-1,1,bt);

    for(int j=1;j<LOG;j++)
    {
        for(int i=1;i<=n;i++)
        {
            if(par[i][j-1]!=-1)
            {
                par[i][j]=par[par[i][j-1]][j-1];
            }
            else par[i][j]=-1;
        }
    }
}

 int lca(int u,int v)
{
    if(depth[u]<depth[v])swap(u,v);
    int log=1;
    while(1)
    {
        int next=log+1;
        if(depth[u]<(1<<next))break;
        log++;
    }

    for(int i=log;i>=0;i--)
    {
        if(depth[u]-(1<<i)>=depth[v])
        {
            u=par[u][i];
        }
    }
    if(u==v)return u;

    for(int i=log;i>=0;i--)
    {
        if(par[u][i]!=-1 && par[u][i]!=par[v][i])
        {
            u=par[u][i];
            v=par[v][i];
        }
    }
    return par[v][0];
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
	LOG=log2(n)+1;
    
	init(1);

	printf("Case %d:\n",++ii );
	scanf("%d",&m);
	while(m--)
	{
		int k;
		scanf("%d",&k);
		bitset<mx>tem;
		//memset(tem,true,sizeof(tem));
		tem.set();
		for(int i=1;i<=k;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			int p=lca(x,y);
			bitset<mx>a=Tree[x]|Tree[y];
			//cout<<a<<endl;
			if(p!=1)a^=Tree[par[p][0]];
			//cout<<a<<endl;
			tem&=a;
		}
		//cout<<tem<<endl;
		printf("%d\n",(int)tem.count());
	}

	for(int i=1;i<=n;i++)
	{
		Tree[i].reset();
		g[i].clear();
	}

}

int main()
{
	int t=1;
	scanf("%d",&t);
	while(t--)solve();
	return 0;
}