// Created by ash_98
#include<bits/stdc++.h>
using namespace std;
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

// Pattern Subtring hisbe ace kina
bool Pattern(string &text,string &pat)
{
    int lo=1,hi=text.size();
    while(lo<=hi)
    {
        int mid=(lo+hi)/2;
        int ok=0;
        for(int i=0;i<pat.size();i++)
        {
            if(text[i+sa[mid]]>pat[i]) {ok=1;break;}
            if(text[i+sa[mid]]<pat[i]) {ok=-1;break;}
        }
        if(!ok) return true;
        if(ok>0) hi=mid-1;
        else lo=mid+1;
    }
    return false;
}
pair<int,int> Patterntern_occurence(string Text ,string Pattern)
{
    int n=Text.size();
    int m=Pattern.size();
    int be=1,en=n;

    while(be<en)
    {
        int mid = (en+be)/2;
        int ok=0;
        for(int i=0;i<m;i++)
        {
            if(Text[i+sa[mid]]>Pattern[i]){ok=1;break;}
            if(Text[i+sa[mid]]<Pattern[i]){ok=-1;break;}
        }
        if(ok+1) en=mid;
        else be=mid+1;
    }

    bool ok = 1;
    for(int i=0;i<m;i++) if(Text[i+sa[be]]!=Pattern[i]){ok=0;break;}
    if(!ok) return {-1,-1};

    pair<int,int> re;
    re.first=be;
    be=1,en=n;
    while(be<en)
    {
        int mid = (en+be)/2;
        int ok=0;
        for(int i=0;i<m;i++)
        {
            if(Text[i+sa[mid]]>Pattern[i]){ok=1;break;}
            if(Text[i+sa[mid]]<Pattern[i]){ok=-1;break;}
        }
        if(ok>0) en=mid;
        else be=mid+1;
    }

    ok = 1;
    for(int i=0;i<m;i++) if(Text[i+sa[en]]!=Pattern[i]){ok=0;break;}
    if(!ok) en--;
    re.second=en;

    return re;
}

#define ll long long
#define mod 1000000007
int ii;
char ch[mx];
ll Freq[mx];
ll ADD[mx],SUB[mx];
ll pre[mx];
ll dp[mx];
ll Helper[mx];

ll add(ll a,ll b)
{
     a+=b;
     if(a>=mod)a-=mod;
     return a;
}

ll sub(ll a,ll b)
{
     a-=b;
     if(a<0)a+=mod;
     return a;
}

ll mul(ll a,ll b)
{
     a*=b;
     a%=mod;
     return a;
}

void Pre_cal()
{
     Helper[0]=1;
     for(int i=1;i<=mx-5;i++)
     {
          Helper[i]=mul(Helper[i-1],26);
          dp[i]=add(Helper[i],dp[i-1]);
     }
}

void solve()
{
     scanf("%s",ch);
     int n=strlen(ch);
     buildSA(ch,sa,n+1,130); //Important
     buildLCP(ch,sa,n);

     for(int i=1;i<=n;i++)
     {
          int hi=n-sa[i];
          int lo=LCP[i]+1;
          if(hi>=lo)ADD[lo]++,SUB[hi]++;
     }

     ll tot=0;
     for(int i=1;i<=mx-5;i++)
     {
          tot=add(tot,ADD[i]);
          Freq[i]=tot;
          tot=sub(tot,SUB[i]);
          ADD[i]=0;
          SUB[i]=0;
     }
     
     for(int i=1;i<=n;i++)
     {
          pre[i]=add(pre[i-1],Freq[i]);
     }
     int q;
     scanf("%d",&q);
     printf("Case %d:\n",++ii );
     for(int i=1;i<=q;i++)
     {
          int l,r;
          scanf("%d%d",&l,&r);
          ll re=sub(dp[r],dp[l-1]);
          re=sub(re,sub(pre[r],pre[l-1]));
          printf("%lld\n",re );

     }

}
 
int main()
{
     int t=1;
     Pre_cal();
     scanf("%d",&t);
     while(t--)solve();
     return 0;
}
