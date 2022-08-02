// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 200005
#define ll long long
#define mod 1000000007 //998244353
 
int ar[mx];
int n,m,ii,k;
ll Time;

pair<int,int>get_pos(int id){
    int extra=Time%(ar[id]+ar[id]);
    if(extra<=ar[id])return {extra,1};
    extra=ar[id]+ar[id]-extra;
    return {extra,2};
}

void Traverse(int i,pair<int,int>pos1,pair<int,int>pos2){
    if(ar[i-1]>=ar[i]){

        if(pos2.second==1){

            int dif=ar[i]-pos2.first;
            Time+=dif;

            pos1.first+=dif;
            dif=ar[i]-pos1.first;

            Time+=(dif+1)/2;
        }
        else{
            int dif=pos2.first-pos1.first;
            Time+=(dif+1)/2;
        }
    }
    else{

        int need=0;
        if(pos2.second==1){
            need=ar[i]-pos2.first+ar[i]-ar[i-1];
        }
        else need=pos2.first-ar[i-1];

        Time+=need;
        pos1=get_pos(i-1);

        int dif=ar[i-1]-pos1.first;
        Time+=(dif+1)/2;
        if(pos1.second==2){
            Time+=pos1.first;
        }
    }
    Time++;
}
 
void solve()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&ar[i]);
    Time=0;
    for(int i=2;i<=n;i++){
        pair<int,int>pos1=get_pos(i-1);
        pair<int,int>pos2=get_pos(i);
        if(pos1.first>=pos2.first){
            Time++;
            continue;
        }
        if(pos1.second==1){
            Traverse(i,pos1,pos2);
        }
        else{
            Time+=pos1.first;
            pos1=get_pos(i-1);
            pos2=get_pos(i);
            Traverse(i,pos1,pos2);
        }
    }

    printf("Case %d: %lld\n",++ii,Time );


 
}
 
int main()
{
    int t=1;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
