#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define mx 1000005
int ar[mx],dp[mx];
int n,m;

void solve(int ii)
{
    memset(dp,0,sizeof dp);
    scanf("%d%d",&n,&m);
    ar[0]=0;ar[n+1]=m;
    for(int i=1;i<=n;i++)scanf("%d",&ar[i]);

    sort(ar,ar+n+2);

    for(int i=1;i<=n+1;i++)
    {
        int diff=ar[i]-ar[i-1];

        for(int j=1;j<diff;j++)
        {
            dp[j]+=(diff/j)-(diff%j==0);
        }
    }
   // for(int i=1;i<=m;i++)printf("%d ",dp[i]);
   // printf("\n");
    int q;
    scanf("%d",&q);
    printf("Case %d:\n",ii);
    while(q--)
    {
        int val;
        scanf("%d",&val);

        int lo=1,high=m;

        int ans=lo;

        while(lo<=high)
        {
            int mid=(lo+high)/2;

            if(dp[mid]<=val)
            {
                high=mid-1;
                ans=mid;
            }
            else lo=mid+1;
            //cout<<lo<<" "<<high<<endl;
        }

        printf("%d\n",ans);
    }
}
int main()
{
    int t;
    scanf("%d",&t);

    for(int i=1;i<=t;i++)solve(i);

    return 0;
}
