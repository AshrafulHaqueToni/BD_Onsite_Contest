// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 2005
#define ll long double
#define mod 1000000007 //998244353
 
ll ar[mx],br[mx];
int n,ii;

 
void solve()
{
    ll sx=0,sy=0,ssqx=0;
    ll sxy=0;
    for(int i=1;i<=n;i++){
        scanf("%LF%LF",&ar[i],&br[i]);
        sx+=ar[i];
        sy+=br[i];
        ssqx+=ar[i]*ar[i];
        sxy+=ar[i]*br[i];
    }
    ll m=((n*sxy)-(sx*sy))/((n*ssqx)-(sx*sx));
  //  cout<<m<<endl;
    ll a0=-m,b0=1,c0=sy-(m*sx);
   // cout<<a0<<" "<<b0<<" "<<c0<<endl;
    ll p=ssqx,q=sxy,r=sx,o=sy;
   // cout<<p<<" "<<q<<" "<<r<<" "<<o<<endl;
    ll a1=m*n,b1=-n,c1=o-(2*m*r),d1=r,e1=(m*n*p)+(m*p)-(m*r*r)-(n*q)-q+(r*o);
   // cout<<a1<<" "<<b1<<" "<<c1<<" "<<d1<<" "<<e1<<endl;
    ll A=a1-((b1*a0)/b0);
    ll B=c1-((b1*c0)/b0)-((d1*a0)/b0);
    ll C=e1-((d1*c0)/b0);
    printf("Case %d: ",++ii );
    if(A==0)
    {
        ll X1=-C/B;
        ll Y1=-((a0*X1)+c0)/b0;
        printf("%0.3LF %0.3LF\n",X1,Y1);
        return;


    }
   // cout<<A<<" "<<B<<" "<<C<<endl;

    ll D=(B*B)-(4*A*C);
    D=sqrtl(D);

    ll X1=(-B+D)/(2*A);
    ll X2=(-B-D)/(2*A);

    ll Y1=-((a0*X1)+c0)/b0;
    ll Y2=-((a0*X2)+c0)/b0;

    printf("%0.3LF %0.3LF\n",X1,Y1);

   // printf("%0.3LF %0.3LF\n",X2,Y2);
 
}
 
int main()
{
    int t=1;
   // scanf("%d",&t);
    while(1){
        scanf("%d",&n);
        if(n==0)return 0;
        solve();
    }

    return 0;
}
