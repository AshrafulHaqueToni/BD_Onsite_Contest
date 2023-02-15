// Created by ash_98
#include<bits/stdc++.h>
using namespace std;
 
#define mx 5005
#define ll long long
#define mod 1000000007 //998244353
 
int ar[mx];
int n,m,ii,k;

ll distl[mx][mx],distr[mx][mx];
ll tmp[mx];
ll dist[mx][mx];
ll dp[mx][305];

void solve()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)scanf("%d",&ar[i]);
    if(k>=n){
        printf("-1\n");
        return;
    }
    for(int i=1;i<=n;i++){
       // cout<<i<<endl;
        distl[i][i]=0;
        distr[i][i]=0;

        ll tot=0;
        ll sum=0;
        for(int j=i-1;j>=1;j--){
            ll val=ar[j+1]-ar[j];
            sum+=val;
            distl[i][j]=distl[i][j+1]+sum;
            //cout<<distl[i][j]<<" ";
        }
      //  cout<<endl;
        tot=0;
        sum=0;
        for(int j=i+1;j<=n;j++){
            ll val=ar[j]-ar[j-1];
            sum+=val;
            distr[i][j]=distr[i][j-1]+sum;
        }   
    }

    for(int i=1;i<=n;i++){
        dist[i][i]=0;
        for(int j=i-1;j>=2;j--){
            int be=j,en=i;
            int mid=(en+be+1)/2;
            ll val=distl[mid][j]+distr[mid][i];
            if(mid>j){
                val=min(val,distl[mid-1][j]+distr[mid-1][i]);
            }
            if(mid<i){
                val=min(val,distl[mid+1][j]+distr[mid+1][i]);
            }
           /* while(be<=en){
                int mid1=(be+be+en)/3;
                int mid2=(be+en+en)/3;
                ll d1=distl[mid1][j]+distr[mid1][i];
                ll d2=distl[mid2][j]+distr[mid2][i];
                //cout<<i<<" "<<d1<<" "<<d2<<endl;
                if(d1>=d2){
                    val=min(val,d2);
                    be=mid1+1;
                }
                else{
                    val=min(val,d1);
                    en=mid2-1;
                }
            }*/
           // cout<<i<<" "<<j<<" "<<val<<endl;
            dist[j][i]=val;
        }
        dist[1][i]=distr[1][i];
    }

    /*for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            cout<<i<<" "<<j<<" "<<dist[i][j]<<endl;
        }
    }*/

    for(int i=1;i<=n;i++){
        for(int j=0;j<=k;j++)dp[i][j]=1e18;
    }
    dp[1][0]=0;

    for(int i=2;i<=n;i++){
        for(int j=0;j<=k;j++)dp[i][j]=dp[i-1][j];
        for(int j=i-1;j>=1;j--){
            int how=i-j;
            if(how>k)break;
            int rem=k-how;
            for(int l=0;l<=rem and j>l;l++){
                dp[i][how+l]=min(dp[i][how+l],dp[j-1][l]+dist[j][i]);
            }
        }
        
    }
    
    printf("%lld\n",dp[n][k]);
 
}
 
int main()
{
    int t=1;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
