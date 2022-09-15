// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 1005
#define ll long long
#define mod 1000000007 //998244353
 
set<string>sentences;
map<int,string>name;
map<string,int>id;
char ch[mx][mx];
int mask_val[mx];
int n,m,ii,k,idx;
vector<int>g[mx];

int dp[mx][(1<<14)+1];
int vis[mx][(1<<14)+1];

int func(int pos,int mask){
    if(pos==idx)return 0;
    if(vis[pos][mask]==ii)return dp[pos][mask];
    vis[pos][mask]=ii;
    int re=func(pos+1,mask);

    if(mask_val[pos] and (mask_val[pos] & mask)==0){
        re=max(re,1+func(pos+1,mask|mask_val[pos]));
    }
    return dp[pos][mask]=re;
}


 
void solve()
{
    sentences.clear();
    name.clear();
    id.clear();

    scanf("%d",&n);

    for(int i=0;i<n;i++){
        scanf("%s",ch[i]);
        string s="";
        int len=strlen(ch[i]);
        for(int j=0;j<len;j++){
            if(ch[i][j]=='.'){
                sentences.insert(s);
                s="";
            }
            else s+=ch[i][j];
        }
        sentences.insert(s);
    }

    scanf("%d",&k);

    idx=0;
    for(string s:sentences){
        id[s]=idx;
        name[idx]=s;
        idx++;
    }

    for(int i=0;i<n;i++){
        string s="";
        int len=strlen(ch[i]);
        for(int j=0;j<len;j++){
            if(ch[i][j]=='.'){
                g[id[s]].push_back(i);
                s="";
            }
            else s+=ch[i][j];
        }
        g[id[s]].push_back(i);
    }

    for(int i=0;i<idx;i++){
        int mask=0;
        for(int j:g[i])mask|=(1<<j);
        mask_val[i]=mask;
        g[i].clear();
    }

    vector<int>ans;

    int baki=k;

    ii++;

    int mask=0;

    for(int i=0;i<idx and baki>0;i++){
        if((mask & mask_val[i])>0 or mask[mask_val]==0)continue;
        if(func(i+1,mask|mask_val[i])>=baki-1){
            ans.push_back(i);
            mask|=mask_val[i];
            baki--;
        }
    }

    printf("Case %d: ",ii);

    if(baki>0){
        printf("impossible\n");
    }
    else{
        for(int i=0;i<k;i++){
            for(char c:name[ans[i]]){
                printf("%c",c);
            }
            if(i+1==k)printf("\n");
            else printf(".");
        }
    }





 
}
 
int main()
{
    int t=1;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
