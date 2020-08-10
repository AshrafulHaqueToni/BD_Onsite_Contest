#include<bits/stdc++.h>
using namespace std;

#define mx 200005
#define ll long long

void IO()
{
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
}


int m,n,k,ii,q;
int ar[mx];


void solve()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&ar[i]);
    scanf("%d",&q);
    while(q--)
    {
        int x;
        scanf("%d",&x);
        int gc=0;
        for(int i=1;i<=n;i++)
        {
            if(ar[i]%x==0)
            {
                gc=__gcd(ar[i],gc);
                if(gc<=x)break;
            }
        }
        if(gc==x)printf("Y\n");
        else printf("N\n");
    }

}

int main()
{
   // IO();
    int t=1;
    //scanf("%d",&t);
    while(t--)
    {
        solve();
    }
    return 0;
}
