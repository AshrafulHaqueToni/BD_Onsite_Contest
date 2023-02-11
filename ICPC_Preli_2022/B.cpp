// Created by ash_98
#include<bits/stdc++.h>
using namespace std;
 
#define mx 10000010
#define N 500005
#define ll long long
#define mod 1000000007 //998244353
 
int ar[N],br[N];
int n,m,ii,k;
int lp[mx];
vector<int>prime;
map<int,int>pf[mx];
bool Done[mx];

void seive()
{
    for(int i=2;i<mx-3;i++)
    {
        if(lp[i]==0)
        {
            prime.push_back(i);
            lp[i]=i;
        }
        for(int j=0;j<prime.size()&&prime[j]<=lp[i]&&i*prime[j]<mx-3;j++)
            lp[i*prime[j]]=prime[j];
    }

}

void koro(int val){
    if(Done[val])return;
    Done[val]=1;
    int a=val;
    while(val>1){
        int sp=lp[val];
        int cnt=0;
        while(val%sp==0){
            val/=sp;
            cnt++;
        }
        pf[a][sp]=cnt;
    }
}
 
void solve()
{
    scanf("%d",&n);
    unordered_map<int,bool>have;
    unordered_map<int,int>chk,how;
    int gc=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&ar[i]);
        koro(ar[i]);
        gc=__gcd(ar[i],gc);
        for(auto[p,cnt]:pf[ar[i]]){
            have[p]=1;  
        }
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&br[i]);
        koro(br[i]);
    }
    printf("Case %d: ",++ii);
    
    // Alice
    bool f=1;
    for(int i=1;i<=n;i++){
        for(auto[p,cnt]:pf[br[i]]){
            if(!have.count(p)){
                f=0;
                break;
            }
        }
        if(!f)break;
    }

    if(f)printf("Yes ");
    else printf("No ");

    // Bob

    f=1;

    for(int i=1;i<=n;i++){
        map<int,int>tmp;
        for(auto[p,cnt]:pf[br[i]]){
            tmp[p]=cnt;
        }
        for(auto[p,cnt]:pf[ar[i]]){
            tmp[p]-=cnt;
        }
        for(auto[p,cnt]:tmp){
            if(cnt==0)continue;
            if(gc%p!=0){
                printf("No\n");
                return;
            }
            how[p]++;
            if(!chk.count(p))chk[p]=cnt;
            else{
                if(chk[p]!=cnt){
                    printf("No\n");
                    return;
                }
            }
        }
    }

    for(auto[h,occur]:how){
        if(occur!=n){
            printf("No\n");
            return;
        }
    }

    printf("Yes\n");



 
}
 
int main()
{
    int t=1;
    seive();
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
