// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 100005
#define ll long long
#define mod 1000000007 //998244353
 
int ar[mx];
int n,m,ii,k,p,q,sx,sy,dx,dy,s,d;
vector<pair<int,ll>>g[mx];
ll Move[10];
int obstacle[mx];
int xx[]={-1,-1,-1,0,0,1,1,1};
int yy[]={-1,0,1,-1,1,-1,0,1};
ll re;
ll dist[mx][10];




void brute()
{
    priority_queue<pair<ll,pair<int,int>>>pq;
 
    dist[s][8]=0;

    pq.push({0,{s,8}});

    while(!pq.empty()){

        auto[w,tt]=pq.top();
        auto[id,last]=tt;
        pq.pop();
        w*=-1;
      //  cout<<w<<" "<<id<<endl;
        if(dist[id][last]<w)continue;
        int x=id/m;
        int y=id%m;
        x++;
        if(y==0)y=m,x--;

       // cout<<x<<" "<<y<<endl;

        for(int i=0;i<8;i++){
            int nx=x,ny=y;
            while(1){
                nx+=xx[i];
                ny+=yy[i];
                int id1=(nx-1)*m+ny;
                //cout<<nx<<" "<<ny<<" "<<i<<endl;
                if(nx<=0 or ny<=0 or nx>n or ny>m or obstacle[id1]==1)break;

                ll ex=Move[i];
                if(last==i)ex=0;

                if(dist[id1][i]>w+ex){
                    dist[id1][i]=w+ex;
                    pq.push({-dist[id1][i],{id1,i}});
                }
                else break;
            }
        }
        for(auto[id1,w1]:g[id]){
            if(dist[id1][8]>w+w1){
                dist[id1][8]=w+w1;
                pq.push({-dist[id1][8],{id1,8}});
            }
        }

    }
}
 
void solve()
{
    scanf("%d%d%d%d",&n,&m,&p,&q);
    
    scanf("%d%d%d%d",&sx,&sy,&dx,&dy);
    for(int i=0;i<8;i++)scanf("%lld",&Move[i]);

    s=(sx-1)*m+sy;
    d=(dx-1)*m+dy;

   // cout<<s<<" "<<d<<endl;

    for(int i=1;i<=p;i++){
        int x1,x2,y1,y2;
        ll w;
        scanf("%d%d%d%d%lld",&x1,&y1,&x2,&y2,&w);
        int x=(x1-1)*m+y1;
        int y=(x2-1)*m+y2;
        g[x].push_back({y,w});
    }
    for(int i=1;i<=q;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        x=(x-1)*m+y;
        obstacle[x]=1;
    }



    for(int i=1;i<=(n*m);i++){
        for(int j=0;j<=8;j++){
            dist[i][j]=1e18;
        }
    }
   // cout<<dist[d]<<endl;
    
    brute();
   

    ll re=1e18;
    for(int i=0;i<=8;i++)re=min(re,dist[d][i]);
    if(re>1e17)re=-1;

    printf("Case %d: %lld\n",++ii,re);

    for(int i=1;i<=(n*m);i++){
        g[i].clear();
        obstacle[i]=0;
    }

 
}
 
int main()
{
    int t=1;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
