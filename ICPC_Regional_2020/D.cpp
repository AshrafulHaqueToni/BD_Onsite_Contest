// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 100005
#define ll long long
#define mod 998244353
 


int par[mx];
int n,m,ii,k;
int Size[mx];
int pow_cal[mx];

int Findparent(int x)
{
    return (x==par[x])?x:(par[x]=Findparent(par[x]));
}

void Union(int x,int y)
{
    int px=Findparent(x);
    int py=Findparent(y);
    if(px==py)return;
    if(Size[px]>Size[py])
    {
        Size[px]+=Size[py];
        par[py]=px;
    }
    else
    {
        Size[py]+=Size[px];
        par[px]=py;
    }
}

void initialize()
{
    for(int i=0;i<=n;i++)par[i]=i,Size[i]=1;
}

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

set<int>st[mx],compo[mx];

 
void solve()
{
    int q;
    scanf("%d%d",&n,&q);
    initialize();

    for(int i=1;i<=q;i++){
        int l,r;
        scanf("%d%d",&l,&r);
        st[l].insert(r);
        compo[l].insert(r);
    }


    for(int l=1;l<=n;l++){
        for(int r:st[l]){
            Union(l,r);
            if(l+1<r-1){
                int p=Findparent(r-1);
                if(compo[l+1].find(p)==compo[l+1].end()){
                    compo[l+1].insert(p);
                    st[l+1].insert(r-1);
                }
            }
        }
        st[l].clear();
        compo[l].clear();
    }

    int total_compo=0;
    for(int i=1;i<=n;i++){
        if(Findparent(i)==i)total_compo++;
    }
    printf("Case %d: %d\n",++ii,pow_cal[total_compo] );
}
 
int main()
{
    int t=1;
    pow_cal[0]=1;
    for(int i=1;i<mx-2;i++)pow_cal[i]=mul(pow_cal[i-1],26);
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
