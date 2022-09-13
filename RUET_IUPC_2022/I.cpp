// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 205
#define ll long long
#define mod 1000000007 //998244353
 
bool dp[mx][2005][mx];
int vis[mx][2005][mx];
pair<int,int>p[11][11];
char ch[mx];
int n,m,ii,k;

vector<vector<bool>>digit={{1,1,1,1,1,1,0},{0,1,1,0,0,0,0},{1,1,0,1,1,0,1},{1,1,1,1,0,0,1},
{0,1,1,0,0,1,1},{1,0,1,1,0,1,1},{1,0,1,1,1,1,1},{1,1,1,0,0,0,0},{1,1,1,1,1,1,1},{1,1,1,1,0,1,1}};

bool func(int pos,int stick,int move){
    if(move<0)return false;
    if(pos==n){
        return stick==1000;
    }
    if(vis[pos][stick][move]==ii)return dp[pos][stick][move];
    vis[pos][stick][move]=ii;
    bool re=false;
    int val=ch[pos]-'0';
    for(int i=9;i>=0;i--){
        auto[need,need_mov]=p[i][val];
        re|=func(pos+1,stick+need,move-need_mov);
        if(re)return dp[pos][stick][move]=true;
    }
    return dp[pos][stick][move]=false;
}
 
void solve()
{
    scanf("%s%d",ch,&m);
    n=strlen(ch);
    printf("Case %d:\n",++ii);
    while(m--){
        
       scanf("%d",&k);
       int stick=1000;
       int move=k+k;

       for(int pos=0;pos<n;pos++){

          int val=ch[pos]-'0';

          for(int i=9;i>=0;i--){

            auto[need,need_mov]=p[i][val];

            if(func(pos+1,stick+need,move-need_mov)){
                printf("%d",i);
                stick+=need;
                move-=need_mov;
                break;
            }

          }
       }
       printf("\n");
    }

    

 
}
 
int main()
{
    int t=1;

    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            int need_mov=0;
            int need=0;

            for(int l=0;l<7;l++){
                if(digit[i][l]==digit[j][l])continue;
                need+=digit[i][l];
                need-=digit[j][l];
                need_mov++;
            }
            p[i][j]={need,need_mov};
        }
    }

    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
