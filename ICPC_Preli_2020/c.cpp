// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

 
#define mx 200105
#define ll long long
#define mod 1000003 //998244353
#define base 31
int inv[mod+5];

ll bigmod(ll e,ll x)
{
    if(!x)
    {
        if(e)return 1;
        return 0;
    }
    ll p=bigmod(e,x/2);
    p=(p*p)%mod;
    if(x%2)p=(p*e)%mod;
    return p;
}
 
int P[mx];
char ch[mx];
int n,m,ii,k;

int add(int a,int b)
{
    a+=b;
    if(a>=mod)a-=mod;
    return a;
}
int sub(int a,int b)
{
    a-=b;
    if(a<0)a+=mod;
    return a;
}

int mul(int a,int b)
{
    ll re=a;
    re*=b;
    if(re>=mod)re%=mod;
    return re;
}

int divi(int a,int b){
    return mul(a,inv[b]);
}
void pre(){
    P[mx-5]=1;
    for(int i=mx-6;i>=1;i--)P[i]=mul(base,P[i+1]);
    for(int i=0;i<mod;i++)inv[i]=bigmod(i,mod-2);
}

int Tree[mx*4][2];

void init(int node,int be,int en){
    if(be==en){
        Tree[node][0]=mul((ch[be-1]-'a'+1),P[be]);
        Tree[node][1]=mul((ch[be-1]-'a'+1),P[n-be+1]);
        return;
    }
    int mid=(be+en)/2;
    init(node*2,be,mid);
    init(node*2+1,mid+1,en);
    Tree[node][0]=add(Tree[node*2][0],Tree[node*2+1][0]);
    Tree[node][1]=add(Tree[node*2][1],Tree[node*2+1][1]);
}

void update(int node,int be,int en,int pos){
    if(pos>en or pos<be)return;
    if(be==en){
        Tree[node][0]=mul((ch[be-1]-'a'+1),P[be]);
        Tree[node][1]=mul((ch[be-1]-'a'+1),P[n-be+1]);
        return;
    }
    int mid=(be+en)/2;
    update(node*2,be,mid,pos);
    update(node*2+1,mid+1,en,pos);
    Tree[node][0]=add(Tree[node*2][0],Tree[node*2+1][0]);
    Tree[node][1]=add(Tree[node*2][1],Tree[node*2+1][1]);
}


pair<int,int> query(int node,int be,int en,int l,int r){
    if(be>=l and en<=r)return {Tree[node][0],Tree[node][1]};
    if(be>r or en<l)return {0,0};
    int mid=(be+en)/2;
    pair<int,int>a=query(node*2,be,mid,l,r);
    pair<int,int>b=query(node*2+1,mid+1,en,l,r);
    return {add(a.first,b.first),add(a.second,b.second)};
}
ordered_set s[27];

void solve()
{
    scanf("%s",ch);
    
    n=strlen(ch);

    init(1,1,n);
    
    for(int i=1;i<=n;i++){
        s[ch[i-1]-'a'].insert(i);
    }

    int q;
    scanf("%d",&q);
    printf("Case %d:\n",++ii);

    while(q--){
        int ti,x;
        scanf("%d%d",&ti,&x);

        if(ti==1){
            int y;
            scanf("%d",&y);

            pair<int,int>a=query(1,1,n,x,y);

            int samne=divi(a.first,P[x]);
            int piche=divi(a.second,P[n-y+1]);

            if(samne==piche){
                printf("0\n");
                continue;
            }

            if(ch[x-1]!=ch[y-1]){
                a=query(1,1,n,x+1,y);
                samne=divi(a.first,P[x+1]);
                piche=divi(a.second,P[n-y+1]);
                
                if(samne==piche){
                    printf("%d\n",x);
                    continue;
                }
                a=query(1,1,n,x,y-1);
                samne=divi(a.first,P[x]);
                piche=divi(a.second,P[n-y+2]);
              
                if(samne==piche){
                    printf("%d\n",y);
                    continue;
                }
                else
                {
                    printf("-1\n");
                    continue;
                }
            }

            int be=1,en=(y-x+2)/2;
            int got=1;

            while(be<=en){
                int mid=(be+en)/2;
                a=query(1,1,n,x,x+mid);
                pair<int,int>b=query(1,1,n,y-mid,y);
                samne=divi(a.first,P[x]);
                piche=divi(b.second,P[n-y+1]);
                if(samne==piche){
                    got=mid+1;
                    be=mid+1;
                }
                else{
                    en=mid-1;
                }
            }
            //cout<<got<<endl;



            int del=x+got;

            a=query(1,1,n,del+1,y-got);

            samne=divi(a.first,P[del+1]);
            piche=divi(a.second,P[n-y+got+1]);

        
            if(samne==piche){

                int val=ch[del-1]-'a';

                be=s[val].order_of_key(x)+1,en=s[val].order_of_key(del);
                int have=en;

                int back=0;

                while(be<=en){
                    int mid=(be+en)/2;
                    int idx=*s[val].find_by_order(mid-1);
                    if(idx<x){
                        be=mid+1;
                        continue;
                    }
                    int gap=del-idx;
                    int pres=have-mid+1;
                    if(gap==pres){
                        back=gap;
                        en=mid-1;
                    }
                    else be=mid+1;
                }
                printf("%d\n",del-back);
                continue;
            }

            a=query(1,1,n,del,y-got-1);

            samne=divi(a.first,P[del]);
            piche=divi(a.second,P[n-y+got+2]);

            if(samne==piche){
                printf("%d\n",y-got);
                continue;
            }

            printf("-1\n");


        }
        else
        {
            char c;
            scanf(" %c",&c);
            int val=ch[x-1]-'a';
            s[val].erase(x);
            ch[x-1]=c;
            s[c-'a'].insert(x);
            update(1,1,n,x);
        }
    }

    for(int i=0;i<26;i++)s[i].clear();
}
/*

1
abcccba
3
1 3 6
2 3 c
1 3 6
*/
 
int main()
{
    int t=1;
    pre();
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
