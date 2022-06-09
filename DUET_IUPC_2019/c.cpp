#include<bits/stdc++.h>
using namespace std;

#define mx 100005
#define ll long long
#define mod 1000000007

int ar[mx];
ll have[(1<<20)+5];
int n,m,ii,k;
bool dp[(1<<20)+5];
vector<pair<ll,int>>ans[21];
ll weight[1<<20+5];
///int id= __builtin_ctz(mask); its give the position of the first one from the left
/// int tot= __builtin_popcount(mask); number of one bit .
int Set(int N,int pos)
{
    return N=N|(1<<pos);
}

int Reset(int N,int pos)
{
    return N=N & ~(1<<pos);
}

bool chk(int N,int pos)
{
    return (bool)(N &(1<<pos));
}



void solve()
{
    int seed;
    scanf("%d%d%d",&n,&m,&seed);
    ii++;

    for(int i=0;i<(1<<n);i++){
        dp[i]=0;
        have[i]=0;

        if(i==0)weight[i]=1;
        else weight[i]=weight[i-1]*seed%10000;
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
                ans[j+1].emplace_back(weight[i]*have[i],i);
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
            auto it=ans[i].back();
            vector<int>re;
            re.emplace_back(it.second);
            ans[i].pop_back();
            while(!ans[i].empty() and ans[i].back().first==it.first)
            {
                re.emplace_back(ans[i].back().second);
                ans[i].pop_back();
            }
            printf("%lld",it.first);
            sort(re.begin(),re.end());
            for(int mask:re)printf(" %d",mask);
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
