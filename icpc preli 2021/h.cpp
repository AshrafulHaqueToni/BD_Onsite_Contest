// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 200005
#define ll long long
#define mod 1000000007 //998244353
 
char ch[2][mx];
int n,m,ii,k;

namespace Segment_Tree
{
    const int N=200005;
    int Tree[2][N*4][27];
    int Lazy[2][N*4][27];

    void Relax(bool fos,int ti,int node,int be,int en)
    {
        if(Lazy[fos][node][ti]==-1)return;

        Tree[fos][node][ti]=Lazy[fos][node][ti]*(en-be+1);
        if(be!=en)
        {
           Lazy[fos][node*2][ti]=Lazy[fos][node][ti];
           Lazy[fos][node*2+1][ti]=Lazy[fos][node][ti];
        }
        Lazy[fos][node][ti]=-1;
    }

    void init(int fos,int node,int be,int en)
    {
        for(int i=0;i<26;i++)Lazy[fos][node][i]=-1;
        if(be==en)
        {
            for(int i=0;i<26;i++)Tree[fos][node][i]=0;
            Tree[fos][node][ch[fos][be-1]-'a']=1;
            return;
        }
        int mid=(be+en)/2;
        init(fos,node*2,be,mid);
        init(fos,node*2+1,mid+1,en);
        for(int i=0;i<26;i++)
           Tree[fos][node][i]=Tree[fos][node*2][i]+Tree[fos][node*2+1][i];
    }


    void Rupdate(int fos,int ti,int node,int be,int en,int i,int j,int val)
    {
        Relax(fos,ti,node,be,en);
        if(be>j || en<i)return ;
        if(be>=i && en<=j)
        {
            Lazy[fos][node][ti]=val;
            Relax(fos,ti,node,be,en);
            return;
        }
        int mid=(be+en)/2;
        Rupdate(fos,ti,node*2,be,mid,i,j,val);
        Rupdate(fos,ti,node*2+1,mid+1,en,i,j,val);
        Tree[fos][node][ti]=Tree[fos][node*2][ti]+Tree[fos][node*2+1][ti];
    }

    int query(int fos,int ti,int node,int be,int en,int i,int j)
    {
        Relax(fos,ti,node,be,en);
        if(be>j || en<i)return 0;
        if(be>=i && en<=j)return Tree[fos][node][ti];
        int mid=(be+en)/2;
        return query(fos,ti,node*2,be,mid,i,j)+query(fos,ti,node*2+1,mid+1,en,i,j);
    }
}
using namespace Segment_Tree;
 
void solve()
{
    scanf("%s%s",ch[0],ch[1]);
    n=strlen(ch[0]);
    m=strlen(ch[1]);
    init(0,1,1,n);
    init(1,1,1,m);
    int q;
    scanf("%d",&q);
    while(q--){
        int ti,l1,l2,r1,r2;
        char c;
        scanf("%d",&ti);
        if(ti==1){
            scanf("%d%d %c",&l1,&r1,&c);
            for(int i=0;i<26;i++){
                Rupdate(0,i,1,1,n,l1,r1,0);
            }
            Rupdate(0,(c-'a'),1,1,n,l1,r1,1);
        }
        else if(ti==2){
            scanf("%d%d %c",&l2,&r2,&c);
            for(int i=0;i<26;i++){
                Rupdate(1,i,1,1,m,l2,r2,0);
            }
            Rupdate(1,(c-'a'),1,1,m,l2,r2,1);
        }
        else
        {
            scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
            ll len1=r1-l1+1;
            ll len2=r2-l2+1;
            ll re=(len2+1)*(len1+1);
            for(int i=0;i<26;i++){
                ll from1=query(0,i,1,1,n,l1,r1);
                ll from2=query(1,i,1,1,m,l2,r2);
                re-=from1*from2;
            }
            printf("%lld\n",re );
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
