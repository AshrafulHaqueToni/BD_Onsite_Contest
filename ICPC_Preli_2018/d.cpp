// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;

#define ll long long

#define pii pair<ll,int>

ll Mul(ll a,ll b,ll Mod){
    ll Ans=0;
    while(b){
        if(b&1) {Ans+=a; if(Ans>=Mod) Ans-=Mod;}
        a+=a; if(a>=Mod) a-=Mod;
        b>>=1;
    }
    return Ans;
}

ll bigMod(ll n,ll r,ll Mod){
    if(r==0) return 1LL;
    ll ret=bigMod(n,r/2,Mod);
    ret=Mul(ret,ret,Mod);
    if(r%2==1) ret=Mul(ret,n,Mod);
    return ret;
}

//Miller-Rabin
bool witness(ll wit,ll n){
  if(wit>=n) return false;

  int s=0; ll t=n-1;
  while(t%2==0) s++,t/=2;

  wit=bigMod(wit,t,n);
  if(wit==1 || wit==n-1) return false;

  for(int i=1;i<s;i++){
    wit=Mul(wit,wit,n);
    if(wit==1) return true;
    if(wit==n - 1) return false;
  }
  return true;
}

//Is n prime?
bool Miller(ll n){
  if(n==2) return true;
  if(n%2==0 || n<2) return false;
  if(witness(2,n) || witness(7,n) || witness(61,n)) return false;
  return true;
}

int tc,sz;
vector<int>digit;
bool f;
int d[]={7,5,3,2};

void func(int pos,bool small,ll val){
    if(f)return;

    if(pos==sz){
        if(val>=2 and Miller(val)){
            printf("%lld\n",val);
            f=true;
        }
        return;
    }

    for(int i=0;i<=3;i++){
        if(f)return;
        if(small or digit[pos]>=d[i]){
            func(pos+1,small|(d[i]<digit[pos]),val*10+d[i]);
        }
    }
}
 
void solve()
{
    ll num;
    scanf("%lld",&num);
    printf("Case %d: ",++tc );
    digit.clear();
    ll val=num;
    f=false;
    while(val){
        digit.push_back(val%10);
        val/=10;
    }
    reverse(digit.begin(),digit.end());
    sz=digit.size();
    func(0,0,0);
    func(1,1,0);
}
 
int main()
{
    int t=1;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
