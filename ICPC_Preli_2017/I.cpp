// Created by ash_98

#include<bits/stdc++.h>
using namespace std;

#define mx 100005
#define ll long long
#define mod 1000000007

int ar[mx];
char ch[mx];
int n,m,ii,k;

void solve()
{
   string a,b;
   cin>>a>>b;
   if(a=="0")
   {
      printf("Case %d: 0\n",++ii );
      return;
   }
   if(b=="0")
   {
      printf("Case %d: 1\n",++ii );
      return;
   }
   n=a.size();
   ll val=0;
   for(int i=0;i<n;i++)val+=(a[i]-'0');
   while(val>=10)
   {
      ll koto=0;
      while(val>0)koto+=val%10,val/=10;
      val=koto;
   }
   ll val1=0;
   n=b.size();
   for(int i=0;i<n;i++)val1=(val1*10+(b[i]-'0'))%6;
    ll re=1;
   for(int i=0;i<val1;i++)re*=val;
    while(re>=10)
   {
      ll koto=0;
      while(re>0)koto+=re%10,re/=10;
      re=koto;
   }
   if(val==9 || (val==3 && b>"1") || (val==6 && b>"1"))
   {
     printf("Case %d: 9\n",++ii );
      return;
   }
   printf("Case %d: %lld\n",++ii,re );


}

int main()
{
  int t=1;
  scanf("%d",&t);
  while(t--)solve();
  return 0;
}
