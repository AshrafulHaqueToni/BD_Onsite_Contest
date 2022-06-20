#include<bits/stdc++.h>
using namespace std;

#define mx 300005
#define ll long long
#define inf 1e9+9

int ar[mx];

int ST[mx][22];
int Jump_LOG[mx];

void Build_Sparse(int n)
{
    for(int i=1;i<=n;i++)ST[i][0]=ar[i];

    for(int j=1;(1<<j)<=n;j++)
    {
        for(int i=1;(i+(1<<j)-1)<=n;i++)
        {
           ST[i][j]=min(ST[i][j-1],ST[i+(1<<(j-1))][j-1]);
        }
    }
}

int query(int i,int j)
{
    int boro_lav=Jump_LOG[j-i+1];
    return min(ST[i][boro_lav],ST[j-(1<<boro_lav)+1][boro_lav]);
}

int ii;
ll ans[mx];

void solve()
{
    int n,q;
    scanf("%d%d",&n,&q);
    vector<pair<int,int>>v;
    for(int i=1;i<=n;i++)scanf("%d",&ar[i]),v.push_back({ar[i],i});

    vector<pair<int,int>>offline;

    for(int i=1;i<=q;i++)
    {
        int x;
        scanf("%d",&x);
        offline.push_back({x,i});
    }
    sort(offline.begin(),offline.end());

    ll re=0;


    Build_Sparse(n);
   
    set<int>s;
    s.insert(0);
    s.insert(n+1);

    re=(ll)n*query(1,n);


    sort(v.begin(),v.end());

    int id=0;

    for(auto it:offline)
    {
        int val=it.first;
        int pos=it.second;

        while(id<n and v[id].first<=val)
        {
            int a=v[id].first;
            int b=v[id].second;

            auto it=s.lower_bound(b);
            int r=*it-1;
            it--;
            int l=*it+1;



            ll len=(r-l+1);
            re-=len*query(l,r);

            s.insert(b);
         
            if(b-l>0)
            {
               re+=(ll)(b-l)*query(l,b-1);
            }
            if(r-l>0)
            {
                re+=(ll)(r-b)*query(b+1,r);
            }

            id++;
            //cout<<re<<" "<<pos<<" "<<id<<endl;
        }

        ans[pos]=re;
    }

    printf("Case %d:\n",++ii);
    for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);


}

int main(){
    int t;
    for(int i=2;i<=mx-5;i++)Jump_LOG[i]=Jump_LOG[i-1]+!(i&(i-1));
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
