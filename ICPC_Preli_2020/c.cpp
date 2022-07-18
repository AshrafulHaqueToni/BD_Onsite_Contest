// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

 
#define mx 200005
#define ll long long
#define mod 1000000007 //998244353
#define base 998244353

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
    return mul(a,bigmod(b,mod-2));
}
void pre(){
    P[mx-5]=1;
    for(int i=mx-6;i>=1;i--)P[i]=mul(base,P[i+1]);
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

int queryl(int node,int be,int en,int l,int r){
    if(be>=l and en<=r)return Tree[node][0];
    if(be>r or en<l)return 0;
    int mid=(be+en)/2;
    return add(queryl(node*2,be,mid,l,r),queryl(node*2+1,mid+1,en,l,r));
}


int queryr(int node,int be,int en,int l,int r){
    if(be>=l and en<=r)return Tree[node][1];
    if(be>r or en<l)return 0;
    int mid=(be+en)/2;
    return add(queryr(node*2,be,mid,l,r),queryr(node*2+1,mid+1,en,l,r));
}

void solve()
{
    scanf("%s",ch);
    ordered_set s[27];
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

            int samne=divi(queryl(1,1,n,x,y),P[x]);
            int piche=divi(queryr(1,1,n,x,y),P[n-y+1]);

            if(samne==piche){
                printf("0\n");
                continue;
            }

            if(ch[x-1]!=ch[y-1]){
                samne=divi(queryl(1,1,n,x+1,y),P[x+1]);
                piche=divi(queryr(1,1,n,x+1,y),P[n-y+1]);
                
                if(samne==piche){
                    printf("%d\n",x);
                    continue;
                }
                samne=divi(queryl(1,1,n,x,y-1),P[x]);
                piche=divi(queryr(1,1,n,x,y-1),P[n-y+2]);
              
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
                samne=divi(queryl(1,1,n,x,x+mid),P[x]);
                piche=divi(queryr(1,1,n,y-mid,y),P[n-y+1]);
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
            //cout<<del<<endl;
            int val=ch[del-1]-'a';

            be=1,en=s[val].order_of_key(del);

            int back=0;

            while(be<=en){
                int mid=(be+en)/2;
                int idx=*s[val].find_by_order(mid-1);
                if(idx<x){
                    be=mid+1;
                    continue;
                }
                int gap=del-idx;
                if(gap==mid){
                    back=mid;
                    en=mid-1;
                }
                else be=mid+1;
            }
           // cout<<back<<endl;
            samne=divi(queryl(1,1,n,del+1,y-got),P[del+1]);
            piche=divi(queryr(1,1,n,del+1,y-got),P[n-y+got+1]);
           // cout<<del+1<<" "<<y-got<<endl;
          //  cout<<queryl(1,1,n,del+1,y-got)<<" "<<samne<<endl;
            if(samne==piche){
                printf("%d\n",del-back);
                continue;
            }

            samne=divi(queryl(1,1,n,del,y-got-1),P[del]);
            piche=divi(queryr(1,1,n,del,y-got-1),P[n-y+got+2]);

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
            s[val].erase(s[val].find(x));
            ch[x-1]=c;
            s[c-'a'].insert(x);
            update(1,1,n,x);
        }
    }

 
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
