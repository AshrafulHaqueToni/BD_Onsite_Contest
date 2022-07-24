// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 

#define ll long long int
#define N 1<<16

void fwht_xor (ll *a, int dir = 0) {
  for (int h = 1; h < N; h <<= 1) {
    for (int i = 0; i < N; i += h << 1) {
      for (int j = i; j < i + h; ++j) {
        ll x = a[j], y = a[j + h];
        a[j] = x + y, a[j + h] = x - y;
        if (dir) a[j] >>= 1, a[j + h] >>= 1;
      }
    }
  }
}

ll A[N+5],B[N+5];
vector<pair<int,int>>g[100005];
int tc,n;

void dfs(int u,int p,int val){
    A[val]++;
    for(auto[v,w]:g[u]){
        if(v==p)continue;
        dfs(v,u,val^w);
    }
}
 
void solve()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        g[x].emplace_back(y,z);
        g[y].emplace_back(x,z);
    }
    dfs(1,-1,0);
    for(int i=1;i<=n;i++){
        g[i].clear();
    }
    fwht_xor(A);
    for(int i=0; i<N; i++) B[i] = A[i] * A[i],A[i]=0;
    fwht_xor(B,1);
    printf("Case %d:\n",++tc);
    B[0]-=n;
    for(int i=0;i<N;i++){
        printf("%lld\n",B[i]>>1);
    }
}
 
int main()
{
    int t=1;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
