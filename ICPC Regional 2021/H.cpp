// Created by ash_98
#include<bits/stdc++.h>
using namespace std;
 
#define mx 200005
#define ll long long
#define mod 1000000007 //998244353
 

int Trie[mx*60][2];
int n,ii;
int st;
ll re,x;

void Insert(){
    int cur=1;
    for(int i=59;i>=0;i--){
        bool pres=((1LL<<i)&x);
        if(Trie[cur][pres]==0)Trie[cur][pres]=++st;
        cur=Trie[cur][pres];
    }
}

void query(){

    int cur=1;
    bool got=1;
    for(int i=59;i>=0;i--){

        int bit=i;
        bool pres=((1LL<<bit)&x);

        if(Trie[cur][pres^1]){
            ll val=(1LL<<bit);
            bit--;
            int ncur=Trie[cur][pres^1];
            while(bit>=0){
                bool npres=(1LL<<bit)&x;
                if(Trie[ncur][npres^1]){
                    val-=(1LL<<bit);
                    ncur=Trie[ncur][npres^1];
                }
                else ncur=Trie[ncur][npres];
                bit--;
            }
            re=min(re,val);
            
        }

        if(Trie[cur][pres])cur=Trie[cur][pres];
        else{
            got=0;
            break;
        }
    }
    if(got)re=0;
}

 
void solve()
{
    scanf("%d",&n);
    re=2e18;
    st=1;
    for(int i=1;i<=n;i++){
        scanf("%lld",&x);
        if(re!=0)query();
        Insert();
    }
    printf("Case %d: %lld\n",++ii,re );
    for(int i=1;i<=st;i++)Trie[i][0]=Trie[i][1]=0;
 
}
 
int main()
{
    int t=1;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
