// Created by ash_98

#include<bits/stdc++.h>
using namespace std;


#define mx 40005
#define ll long long
#define mod 1000000007

int Tem_val[mx],re[100005],parent[mx];
char ch[mx];
int n,m,ii,k;

vector<pair<int,pair<int,int> > >g;


int Findparent(int x)
{
    return (x==parent[x])?x:(parent[x]=Findparent(parent[x]));
}

void Union(int x,int y)
{
    Tem_val[Findparent(y)]+=Tem_val[Findparent(x)];
    parent[Findparent(x)]=parent[Findparent(y)];
}

void kruskal(int tar)
{
    int cnt=0;
    for(int i=k;i<m;i++)
    {
      int u=g[i].second.first;
      int v=g[i].second.second;
      int w=g[i].first;
      k=i;
      if(w<tar)break;

      if(Findparent(u)!=Findparent(v)){
        Union(u,v);
        if(cnt==n-1)break;
      }
    }
}

void initialize()
{
    for(int i=1;i<=n;i++)parent[i]=i,Tem_val[i]=1;
    Tem_val[1]=0;
}


void solve()
{
   scanf("%d%d",&n,&m);
   k=0;
   for(int i=1;i<=m;i++)
   {
       int x,y,z;
       scanf("%d%d%d",&x,&y,&z);
       g.push_back({z,{x,y}});
   }
   initialize();
   sort(g.rbegin(),g.rend());
  
   int q;
   scanf("%d",&q);
 
   printf("Case %d:\n",++ii );

   vector<pair<int,int>>query;
   for(int i=1;i<=q;i++)
   {
      int x;
      scanf("%d",&x);
      query.push_back({x,i});
   }
   sort(query.rbegin(),query.rend());

   for(int i=0;i<q;i++)
   {
       kruskal(query[i].first);
       re[query[i].second]=Tem_val[Findparent(1)];
   }

   for(int i=1;i<=q;i++)printf("%d\n",re[i]);

   g.clear();

}

int main()
{
  int t=1;
  scanf("%d",&t);
  while(t--)solve();
  return 0;
}