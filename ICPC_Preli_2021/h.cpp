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
    vector<int>Tree[2][N*4];
    vector<int>dummy(26);
    int Lazy[2][N*4];

    void Relax(bool fos,int node,int be,int en)
    {
        if(Lazy[fos][node]==-1)return;

        int ti=Lazy[fos][node];

        for(int i=0;i<26;i++)Tree[fos][node][i]=0;

        Tree[fos][node][ti]=(en-be+1);
        if(be!=en)
        {
           Lazy[fos][node*2]=Lazy[fos][node];
           Lazy[fos][node*2+1]=Lazy[fos][node];
        }
        Lazy[fos][node]=-1;
    }

    void init(int fos,int node,int be,int en)
    {

        Lazy[fos][node]=-1;
        Tree[fos][node].resize(26);
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


    void Rupdate(int fos,int node,int be,int en,int i,int j,int val)
    {
        Relax(fos,node,be,en);
        if(be>j || en<i)return ;
        if(be>=i && en<=j)
        {
            Lazy[fos][node]=val;
            Relax(fos,node,be,en);
            return;
        }
        int mid=(be+en)/2;
        Rupdate(fos,node*2,be,mid,i,j,val);
        Rupdate(fos,node*2+1,mid+1,en,i,j,val);
        for(int i=0;i<26;i++)
           Tree[fos][node][i]=Tree[fos][node*2][i]+Tree[fos][node*2+1][i];
    }

    vector<int> query(int fos,int node,int be,int en,int i,int j)
    {
        Relax(fos,node,be,en);
        if(be>j || en<i)return dummy;
        if(be>=i && en<=j)return Tree[fos][node];
        int mid=(be+en)/2;
        auto a=query(fos,node*2,be,mid,i,j);
        auto b=query(fos,node*2+1,mid+1,en,i,j);
        for(int i=0;i<26;i++)a[i]+=b[i];
        return a;
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
            
            Rupdate(0,1,1,n,l1,r1,c-'a');
        }

        else if(ti==2){
            scanf("%d%d %c",&l2,&r2,&c);

            Rupdate(1,1,1,m,l2,r2,c-'a');
        }
        else
        {
            scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
            
            ll re=(ll)(r1-l1+2)*(r2-l2+2);
           // cout<<re<<endl;

            auto a=query(0,1,1,n,l1,r1);
            auto b=query(1,1,1,m,l2,r2);

            for(int i=0;i<26;i++){
                re-=(ll)a[i]*b[i];
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
