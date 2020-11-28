// Created by ash_98

#include<bits/stdc++.h>
using namespace std;

#define mx 15
#define ll long long
#define mod 1000000007

int ar[mx][mx];
char ch[mx];
int n,m,ii,k;

void solve()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
      for(int j=1;j<=n;j++)scanf("%d",&ar[i][j]);
    }
    int re=0;
    if(n>=10)
    {
       for(int i=1;i<=n;i++)
       {
         set<int>s;
         for(int j=1;j<=n;j++)s.insert(ar[i][j]);
          if(s.size()==10)re++;
       }
       for(int i=1;i<=n;i++)
       {
         set<int>s;
         for(int j=1;j<=n;j++)s.insert(ar[j][i]);
          if(s.size()==10)re++;
       }
    }
    if(n>=5)
    {
      for(int i=1;i<=n-4;i++)
      {
          for(int j=1;j<=n-1;j++)
          {
            set<int> s;
            for(int l=i;l<=i+4;l++)
            {
              for(int x=j;x<=j+1;x++)
              {
                s.insert(ar[x][l]);
              }
            }
            if(s.size()==10)re++;
            //cout<<"aci\n";
          }
      }
       for(int i=1;i<=n-4;i++)
      {
          for(int j=1;j<=n-1;j++)
          {
            set<int> s;
            for(int l=i;l<=i+4;l++)
            {
              for(int x=j;x<=j+1;x++)
              {
                s.insert(ar[l][x]);
              }
            }
            if(s.size()==10)re++;
          }
      }
    }
    printf("Case %d: %d\n",++ii,re );
}

int main()
{
  int t=1;
  scanf("%d",&t);
  while(t--)solve();
  return 0;
}
