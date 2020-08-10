#include<bits/stdc++.h>
using namespace std;

#define mx 105
#define ll long long

void IO()
{
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
}


int m,n,k,ii,q;
char ch[mx][mx];
int visit[mx][mx];
int re;

void dfs(int i,int j)
{
    re++;
    visit[i][j]=ii;
    if(j>0 && ch[i][j]!='D' && ch[i][j]!='B' && visit[i][j-1]!=ii)dfs(i,j-1);
    if(j<=m-3 && ch[i][j+1]!='D' && ch[i][j+1]!='B' && visit[i][j+1]!=ii)dfs(i,j+1);
    if(i<=n-3 && ch[i+1][j]!='R' && ch[i+1][j]!='B' && visit[i+1][j]!=ii)dfs(i+1,j);
    if(i>0 && ch[i][j]!='R' && ch[i][j]!='B' && visit[i-1][j]!=ii)dfs(i-1,j);

}

void solve()
{
    scanf("%d%d",&n,&m);
    ++ii;
    re=0;
    for(int i=0;i<n;i++)
    {
        scanf("%s",ch[i]);
    }
    for(int i=0;i<m-1;i++)
    {
        if(ch[0][i]!='R' && ch[0][i]!='B' && visit[0][i]!=ii)dfs(0,i);
    }
    printf("Case %d: %d\n",ii,re );

}

int main()
{
   //IO();
    int t=1;
    scanf("%d",&t);
    while(t--)
    {
        solve();
    }
    return 0;
}
