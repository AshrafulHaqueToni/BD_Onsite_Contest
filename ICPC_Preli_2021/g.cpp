// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 30105
#define ll long long
#define mod 1000000007 //998244353
 
int ar[mx];
vector<int>g[mx];
vector<pair<int,int>>a,b;
int n,m,ii,k;
ll pre1[mx],pre2[mx];
int pos[mx];
int grp[mx];

void dfs(int u,int p,int ti){
    if(ti)b.push_back({ar[u],u});
    else a.push_back({ar[u],u});
    for(int v:g[u]){
        if(v==p)continue;
        dfs(v,u,ti^1);
    }
}
 
void solve()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&ar[i]);
    for(int i=1;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        g[x].push_back(y);
        g[y].push_back(x);
    }

    a.clear();
    b.clear();

    dfs(1,-1,0);

    sort(a.begin(),a.end());
    sort(b.begin(),b.end());

    int id1=0;

    for(auto it:a){
        grp[it.second]=1;
        pos[it.second]=id1++;
        pre1[id1]=pre1[id1-1]+it.first;
    }
    id1=0;
    for(auto it:b){
        grp[it.second]=2;
        pos[it.second]=id1++;
        pre2[id1]=pre2[id1-1]+it.first;
    }

    ll re=-1e15;
    int idx=1;
    for(int i=1;i<=n;i++){
        if(grp[i]==1){
            int p=pos[i];
           // cout<<p<<" "<<i<<endl;
            ll sum1=((ll)ar[i]*(p+1))-pre1[p+1];
            int sz=a.size();
            ll sum2=(pre1[sz]-pre1[p+1])-((ll)ar[i]*(sz-(p+1)));
            ll ans=sum1-sum2;
           //cout<<ans<<endl;

            if(b.empty()){
                if(re<ans){
                    re=ans;
                    idx=i;

                }
                continue;
            }
            sz=b.size();
            if(b.back().first<=ar[i]){
                ll val=((ll)ar[i]*sz)-pre2[sz];
                ans-=val;
            }
            else if(b[0].first>ar[i]){
                ll val=pre2[sz]-((ll)ar[i]*sz);
                ans+=val;
            }
            else{

                int be=0,en=sz-1;
                p=-1;
                while(be<=en){
                    int mid=(be+en)/2;
                    if(b[mid].first<=ar[i]){
                        p=mid;
                        be=mid+1;
                    }
                    else en=mid-1;
                }

                sum1=((ll)ar[i]*(p+1))-pre2[p+1];
      
                sum2=(pre2[sz]-pre2[p+1])-((ll)ar[i]*(sz-(p+1)));

                ans-=sum1;
                ans+=sum2;

            }
          //  cout<<ans<<endl;

            if(re<ans){
                re=ans;
                idx=i;

            }

        }
        else{
            int p=pos[i];
            ll sum1=((ll)ar[i]*(p+1))-pre2[p+1];
            int sz=b.size();
            ll sum2=(pre2[sz]-pre2[p+1])-((ll)ar[i]*(sz-(p+1)));
            ll ans=sum1-sum2;
           // cout<<ans<<endl;

            if(a.empty()){
                if(re<ans){
                    re=ans;
                    idx=i;

                }
                continue;
            }
            sz=a.size();
            if(a.back().first<=ar[i]){
                ll val=((ll)ar[i]*sz)-pre1[sz];
                ans-=val;
            }
            else if(a[0].first>ar[i]){
                ll val=pre1[sz]-((ll)ar[i]*sz);
                ans+=val;
            }
            else{

                int be=0,en=sz-1;
                p=-1;
                while(be<=en){
                    int mid=(be+en)/2;
                    if(a[mid].first<=ar[i]){
                        p=mid;
                        be=mid+1;
                    }
                    else en=mid-1;
                }

                sum1=((ll)ar[i]*(p+1))-pre1[p+1];
      
                sum2=(pre1[sz]-pre1[p+1])-((ll)ar[i]*(sz-(p+1)));

                ans-=sum1;
                ans+=sum2;

            }

            if(re<ans){
                re=ans;
                idx=i;

            }
        }
    }
   // cout<<re<<endl;
    printf("Case %d: %d\n",++ii,idx);
    for(int i=1;i<=n;i++)g[i].clear();


 
}
 
int main()
{
    int t=1;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
