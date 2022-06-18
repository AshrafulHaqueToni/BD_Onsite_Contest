#include<bits/stdc++.h>
using namespace std;

#define mx 100005
#define ll long long
#define mod 10000

int ar[mx];
ll have[(1<<20)+5];
ll ans_val[25];

int n,m,ii,k;

bool dp[(1<<20)+5];
vector<int>ans[21];
ll weight[1<<20+5];


bool chk(int N,int pos)
{
    return (bool)(N &(1<<pos));
}


int mul(int a,int b)
{
    ll re=a;
    re*=b;
    if(re>=mod)re%=mod;
    return re;
}



void solve()
{
    int seed;
    scanf("%d%d%d",&n,&m,&seed);
    ii++;
    memset(ans_val,-1,sizeof(ans_val));

    for(int i=0;i<(1<<n);i++){
        dp[i]=0;
        have[i]=0;

        if(i==0)weight[i]=1;
        else weight[i]=mul(weight[i-1],seed);
    }

    for(int i=1;i<=m;i++)
    {
        scanf("%d",&ar[i]);
        have[ar[i]]++;
        dp[ar[i]]=1;

    }

    for(int i=0;i<n;i++)
    {
        for(int mask=(1<<n)-1;mask>=0;mask--)
        {
            if(!chk(mask,i)){
                have[mask]+=have[mask^(1<<i)];
                dp[mask]|=dp[mask^(1<<i)];
            }
        }
    }

    for(int i=(1<<n)-1;i>0;i--)
    {
        if(!dp[i])continue;
       
        for(int j=0;j<n;j++)
        {
            if(chk(i,j))
            {
                ll cur=weight[i]*have[i];

                if(ans_val[j+1]<cur)
                {
                    ans_val[j+1]=cur;
                    ans[j+1].clear();
                    ans[j+1].push_back(i);
                }
                else if(ans_val[j+1]==cur)ans[j+1].push_back(i);
            }
        }
    }

    printf("Case %d:\n",ii );
    for(int i=1;i<=n;i++)
    {
        if(ans[i].empty())
        {
            printf("0 0\n");
        }
        else
        {
            sort(ans[i].begin(),ans[i].end());
            printf("%lld",ans_val[i]);
            
            for(int mask:ans[i])printf(" %d",mask);

            printf("\n");

        }
        ans[i].clear();
    }


}

int main()
{
    int t=1;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
