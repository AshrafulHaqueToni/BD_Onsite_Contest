// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx (1<<18)+5
#define ll long long
#define mod 1000000007 //998244353
#define base 998244353
 

int P[mx],inv[mx];
int pre[mx],cur[mx];

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

ll bigmod(ll b,ll e)
{
    ll ans=1;
    while(e){
        if(e&1)ans=(ans*b)%mod;
        e>>=1;
        b=b*b%mod;
    }
    return ans;
}

struct Hash_Main
{
    
    Hash_Main(){}
    Hash_Main(const char* s){
        int sz=strlen(s);
        for(int i=1;i<=sz;i++){
            cur[i]=mul(P[i],(int)(s[i-1]-'a'+1));
            pre[i]=cur[i];
            pre[i]=add(pre[i],pre[i-1]);
        }
    }
   
    inline int Range_Hash(int l,int r) /// 1 base index
    {
        int re=pre[r];
        re=sub(pre[r],pre[l-1]);
       // cout<<re<<endl;
        re=mul(re,inv[l]);
        return re;
    }

};

map<int,int>mp;
int ii;


char ch[mx];
 
void solve()
{
    scanf("%s",ch);
    Hash_Main h(ch);
    int n=strlen(ch);
    mp.clear();

    for(int bit=0;bit<=18;bit++){
        int len=1<<bit;
        if(len>n)break;
      // cout<<len<<endl;
        for(int i=0;i<=n-len;i++){
           // cout<<i<<" "<<i+len-1<<endl;
            mp[h.Range_Hash(i+1,i+len)]++;
        }
    }
   // cout<<ch<<endl;
   // cout<<ch[0]<<ch[1]<<ch[2]<<ch[3]<<" "<<ch[5]<<ch[6]<<ch[7]<<ch[8]<<endl;
   // cout<<h.Range_Hash(1,4)<<" "<<h.Range_Hash(6,9)<<endl;

    int q;
    scanf("%d",&q);
    printf("Case %d:\n",++ii );
    while(q--){
        scanf("%s",ch);
        int m=strlen(ch);
        for(int i=0;i<m;i++){
            cur[i]=mul(P[i],(int)(ch[i]-'a'+1));
            pre[i]=cur[i];
            if(i)pre[i]=add(pre[i-1],pre[i]);
        }

        int val=pre[m-1];
       // cout<<val<<endl;
        ll re=mp[val];
        
        for(int i=0;i<m;i++){
            int cc=ch[i]-'a'+1;
            int val1=0;
            if(i)val1=pre[i-1];
            int val3=0;
            if(i+1<m)val3=sub(pre[m-1],pre[i]);
            int j=1;
            for(char c='a';c<='p';c++,j++){
                if(ch[i]==c)continue;
                re+=mp[add(val3,add(val1,mul(P[i],j)))];

            }
        }
        printf("%lld\n",re);

    }
 
}
 
int main()
{
    int t=1;
    P[0]=1;
    inv[0]=1;
    for(int i=1;i<=mx-2;i++){
        P[i]=mul(P[i-1],base);
        inv[i]=bigmod(P[i],mod-2);
    }
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
