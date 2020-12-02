// Created by ash_98

#include<bits/stdc++.h>
using namespace std;

#define mx 100005
#define ll long long
#define mod 1000000007

char ch[mx];
int n,m,ii,k;

namespace Segment_Tree
{
	const int N=100005;
	int Tree[N*4];
	int Lazy[mx*4];
	int ar[N];

	void Relax(int node,int be,int en)
	{
		if(!Lazy[node])return;

		Tree[node]+=Lazy[node];
		if(be!=en)
		{
			Lazy[node*2]+=Lazy[node];
			Lazy[node*2+1]+=Lazy[node];
		}
		Lazy[node]=0;
	}

	void init(int node,int be,int en)
	{
		Lazy[node]=0;
        if(be==en)
        {
        	Tree[node]=ar[be];
        	return;
        }
        int mid=(be+en)/2;
        init(node*2,be,mid);
        init(node*2+1,mid+1,en);
        Tree[node]=Tree[node*2]|Tree[node*2+1];
	}

	void update(int node,int be,int en,int pos,int val)
	{
		Relax(node,be,en);
		if(be> pos || en<pos)return;
		if(be==en)
		{
			Tree[node]+=val;
			return;
		}
		int mid=(be+en)/2;
		update(node*2,be,mid,pos,val);
		update(node*2+1,mid+1,en,pos,val);
		Tree[node]=max(Tree[node*2],Tree[node*2+1]);
	}

	void Rupdate(int node,int be,int en,int i,int j,int val)
	{
		Relax(node,be,en);
		if(be>j || en<i)return ;
		if(be>=i && en<=j)
		{
			Lazy[node]+=val;
			Relax(node,be,en);
			return;
		}
		int mid=(be+en)/2;
		Rupdate(node*2,be,mid,i,j,val);
		Rupdate(node*2+1,mid+1,en,i,j,val);
		Tree[node]=max(Tree[node*2],Tree[node*2+1]);
	}

	int query(int node,int be,int en,int i,int j)
	{
		//Relax(node,be,en);
		if(be>j || en<i)return 0;
		if(be>=i && en<=j)return Tree[node];
		int mid=(be+en)/2;
		return query(node*2,be,mid,i,j)|query(node*2+1,mid+1,en,i,j);
	}

	void dbg_test(int node,int be,int en)
	{
		if(be==en)return;
		int mid=(be+en)/2;
		dbg_test(node*2,be,mid);
		dbg_test(node*2+1,mid+1,en);
	}
}

using namespace Segment_Tree;

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
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&ar[i]);
	init(1,1,n);
    for(int i=1;i<=m;i++)
    {
    	int x,y;
    	scanf("%d%d",&x,&y);
    	int val=query(1,1,n,x,y);
    	ll len=bigmod(2,y-x);
    	ll re=(val*len)%mod;
    	printf("%lld\n",re );

    }
}

int main()
{
	int t=1;
	//scanf("%d",&t);
	while(t--)solve();
	return 0;
}