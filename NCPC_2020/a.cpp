// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

 
#define mx 1000005

int wa[mx],wb[mx],wv[mx],Ws[mx];
//(1-indexed) sa[i] = starting position (0...n-1) of ith lexicographically smallest suffix in s
//(0-indexed) Rank[i] = lexicographical rank of s[i....n-1] ((i+1)th suffix by position)
//LCP[i] = longest common prefix of sa[i] & sa[i-1]
int sa[mx],Rank[mx],LCP[mx];

int cmp(int *r,int a,int b,int l) {return r[a]==r[b] && r[a+l]==r[b+l];}

//Suffix Array (O(nlogn))
//m = maximum possible ASCII value of a string character (alphabet size)
//also, m = maximum number of distinct character in string (when compressed)
void buildSA(string s,int* sa,int n,int m){
    int i,j,p,*x=wa,*y=wb,*t;
    for(i=0; i<m; i++) Ws[i]=0;
    for(i=0; i<n; i++) Ws[x[i]=s[i]]++;
    for(i=1; i<m; i++) Ws[i]+=Ws[i-1];
    for(i=n-1; i>=0; i--) sa[--Ws[x[i]]]=i;
    for(j=1,p=1; p<n; j<<=1,m=p){
        for(p=0,i=n-j; i<n; i++) y[p++]=i;
        for(i=0; i<n; i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=0; i<n; i++) wv[i]=x[y[i]];
        for(i=0; i<m; i++) Ws[i]=0;
        for(i=0; i<n; i++) Ws[wv[i]]++;
        for(i=1; i<m; i++) Ws[i]+=Ws[i-1];
        for(i=n-1; i>=0; i--) sa[--Ws[wv[i]]]=y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1; i<n; i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j) ? p-1 : p++;
    }
}

//Kasai's LCP algorithm (O(n))
void buildLCP(string s,int *sa,int n){
    int i,j,k=0;
    for(i=1; i<=n; i++) Rank[sa[i]]=i;
    for(i=0; i<n; LCP[Rank[i++]]=k)
        for(k?k--:0, j=sa[Rank[i]-1]; s[i+k]==s[j+k]; k++);
    return;
}

int ST[mx][22];
int Jump_LOG[mx];

void Build_Sparse(int n)
{
    for(int i=1;i<=n;i++)ST[i][0]=LCP[i];

    for(int i=2;i<=n;i++)Jump_LOG[i]=Jump_LOG[i-1]+!(i&(i-1));

    for(int j=1;(1<<j)<=n;j++)
    {
        for(int i=1;(i+(1<<j)-1)<=n;i++)
        {
           ST[i][j]=min(ST[i][j-1],ST[i+(1<<(j-1))][j-1]);
        }
    }
}

int query(int i,int j)
{
    int boro_lav=Jump_LOG[j-i+1];
    return min(ST[i][boro_lav],ST[j-(1<<boro_lav)+1][boro_lav]);
}

int n,m,ii;
char ch[mx];

ordered_set os;
int ans[mx];
vector<pair<int,int>>add[mx],rem[mx];
 
void solve()
{
    scanf("%s",ch);
    string s=ch;
    n=s.size();
    buildSA(s,sa,n+1,130);
    buildLCP(s,sa,n);
    Build_Sparse(n);
    int q;
    scanf("%d",&q);
    
    //for(int i=1;i<=n;i++) cout<<sa[i]<<" "; cout<<endl;
   // for(int i=0;i<n;i++) cout<<Rank[i]<<" "; cout<<endl;
   // for(int i=1;i<=n;i++) cout<<LCP[i]<<" ";cout<<endl;
    for(int x=1;x<=q;x++)
    {
        int a,b,c,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        int len1=b-a+1;
        int len=d-c+1;
        if(len>len1)continue;
        int p=Rank[c-1];

        int lft=p;
        int rgt=lft;

        int be,en;
        be=1,en=lft-1;

        while(be<=en)
        {
            int mid=(be+en)/2;
            if(query(mid+1,p)>=len)
            {
                lft=mid;
                en=mid-1;
            }
            else be=mid+1;
        }

        be=rgt+1,en=n;

        while(be<=en)
        {
            int mid=(be+en)/2;
            if(query(p+1,mid)>=len)
            {
                rgt=mid;
                be=mid+1;
            }
            else en=mid-1;
        }
        //cout<<p<<" "<<lft<<" "<<rgt<<endl;
        int exlen=len1-len;
        add[rgt].emplace_back(a+exlen+1,x);
        rem[rgt].emplace_back(a,x);

        add[lft-1].emplace_back(a,x);
        rem[lft-1].emplace_back(a+exlen+1,x);

        //cout<<a<<" "<<a+exlen<<endl;

    }
    for(int i=1;i<=n;i++)
    {
        os.insert(sa[i]+1);
        //cout<<sa[i]<<endl;
        for(auto[x,id]:add[i])
        {
            ans[id]+=os.order_of_key(x);
        }
        for(auto[x,id]:rem[i])
        {
            ans[id]-=os.order_of_key(x);
        }
    }
    for(int i=1;i<=q;i++)printf("%d\n",ans[i]),ans[i]=0;
    for(int i=0;i<=n;i++)
    {
        add[i].clear();
        rem[i].clear();
    }
    os.clear();

 
}
 
int main()
{
    int t=1;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
