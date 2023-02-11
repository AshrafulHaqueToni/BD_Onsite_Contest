// Created by ash_98
#include<bits/stdc++.h>
using namespace std;
 
#define mx 105
#define ll long long
#define mod 1000000007 //998244353
 

char ch[3][mx];
int n,m,ii,k;
int dp[mx][mx];
int vis[mx][mx];

int func(int st,int en){
    if(st>=en)return 0;
    if(vis[st][en]==ii)return dp[st][en];
    vis[st][en]=ii;
    set<int>s;
    for(int i=st;i<en;i++){
        bool f=0;
        if(ch[0][i]!='X' and ch[1][i]!='X' and ch[0][i+1]!='X' and ch[1][i+1]!='X'){
            f=1;
        }
        if(ch[2][i]!='X' and ch[1][i]!='X' and ch[2][i+1]!='X' and ch[1][i+1]!='X'){
            f=1;
        }
        if(f){

            s.insert(func(st,i-1)^func(i+2,en));
            //cout<<st<<" "<<en<<" "<<func(st,i-1)<<" "<<func(i+1,en)<<endl;
        }
    }
    int val=0;
    while(s.find(val)!=s.end())val++;
    //cout<<st<<" "<<en<<" "<<val<<endl;
    return dp[st][en]=val;

}

void solve()
{
    scanf("%d%s%s%s",&n,ch[0],ch[1],ch[2]);
    ii++;
    int val=func(0,n-1);
  //  cout<<val<<endl;

    printf("Case %d: ",ii);
    if(val)printf("Jhinuk\n");
    else printf("Grandma\n");
 
}
 
int main()
{
    int t=1;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
