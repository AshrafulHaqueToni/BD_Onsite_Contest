// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 100005
#define ll long long


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
 

char ch[mx];
int n,m,ii,k;

vector<int>Tree1[mx*4],Tree2[mx*4];

void init(int node,int be,int en){
    Tree1[node].clear();
    Tree2[node].clear();
    if(be==en){
        Tree1[node].push_back(LCP[be]);
        Tree2[node].push_back(n-sa[be]);
        return;
    }
    int mid=(be+en)/2;
    init(node*2,be,mid);
    init(node*2+1,mid+1,en);
    merge(Tree1[node*2].begin(),Tree1[node*2].end(),Tree1[node*2+1].begin(),Tree1[node*2+1].end(),back_inserter(Tree1[node]));
    merge(Tree2[node*2].begin(),Tree2[node*2].end(),Tree2[node*2+1].begin(),Tree2[node*2+1].end(),back_inserter(Tree2[node]));
}

int query(int node,int be,int en,int i,int j,int val){
    if(be>j or en<i)return 0;
    if(be>=i and en<=j){
        int sz=Tree1[node].size();
        int small=lower_bound(Tree1[node].begin(),Tree1[node].end(),val)-Tree1[node].begin();
        return sz-small;
    }
    int mid=(be+en)/2;
    return query(node*2,be,mid,i,j,val)+query(node*2+1,mid+1,en,i,j,val);
}

int query1(int node,int be,int en,int i,int j,int val){
    if(be>j or en<i)return 0;
    if(be>=i and en<=j){
        int small=lower_bound(Tree2[node].begin(),Tree2[node].end(),val)-Tree2[node].begin();
        return small;
    }
    int mid=(be+en)/2;
    return query1(node*2,be,mid,i,j,val)+query1(node*2+1,mid+1,en,i,j,val);
}


int ST[mx][20],ST1[mx][20];
int Jump_LOG[mx];

void Build_Sparse()
{
    for(int i=1;i<=n;i++)ST[i][0]=LCP[i],ST1[i][0]=sa[i];

    for(int j=1;(1<<j)<=n;j++)
    {
        for(int i=1;(i+(1<<j)-1)<=n;i++)
        {
           ST[i][j]=min(ST[i][j-1],ST[i+(1<<(j-1))][j-1]);
           ST1[i][j]=min(ST1[i][j-1],ST1[i+(1<<(j-1))][j-1]);
        }
    }
}

int query_sa(int i,int j){
    int boro_lav=Jump_LOG[j-i+1];
    return min(ST1[i][boro_lav],ST1[j-(1<<boro_lav)+1][boro_lav]);
}

int query_lcp(int i,int j)
{
    int boro_lav=Jump_LOG[j-i+1];
    return min(ST[i][boro_lav],ST[j-(1<<boro_lav)+1][boro_lav]);
}
 
void solve()
{
    scanf("%s",ch);
    n=strlen(ch);
    string s=ch;
    buildSA(s,sa,n+1,130);
    buildLCP(s,sa,n);
    Build_Sparse();
    init(1,1,n);
    scanf("%d",&m);
    while(m--){
        int len;
        scanf("%d%d",&len,&k);
        int be=1,en=n;
        int got=-1;
        while(be<=en){
            int mid=(be+en)/2;
            int bad=query(1,1,n,1,mid,len)+query1(1,1,n,1,mid,len);
            if(mid-bad>=k){
                got=mid;
                en=mid-1;
            }
            else be=mid+1;

        }
        if(got==-1)printf("Not found\n");
        else{
            be=got+1,en=n;
            int jabe=got;
            while(be<=en){
                int mid=(be+en)/2;
                if(query_lcp(got+1,mid)>=len){
                    jabe=mid;
                    be=mid+1;
                }
                else en=mid-1;
            }

            printf("%d\n",query_sa(got,jabe));
        }
    }


 
}
 
int main()
{
    int t=1;
    for(int i=2;i<=mx-3;i++)Jump_LOG[i]=Jump_LOG[i-1]+!(i&(i-1));
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
