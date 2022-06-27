#include<bits/stdc++.h>
using namespace std;
 

#define mx 200005
#define ll long long
ll ar[mx];
int n,m,ii;

void solve()
{
    scanf("%d",&n);
    vector<pair<ll,int>>v;
    for(int i=1;i<=n;i++)scanf("%lld",&ar[i]),v.emplace_back(ar[i],i);
    
    int q;
    scanf("%d",&q);

    sort(v.begin(),v.end());

    printf("Case %d:\n",++ii );

    while(q--)
    {
        
        ll x;
        scanf("%lld",&x);

        set<int>os;
        queue<pair<ll,int>>qu;

        vector<pair<int,pair<int,int>>>ans;

        for(auto it:v)
        {
            ll a=it.first;
            int i=it.second;

            while(!qu.empty())
            {
                auto it1=qu.front();
                ll val=it1.first;
                int id=it1.second;
                if(a-val>=x and a>val)
                {
                    os.insert(id);
                    qu.pop();
                }
                else break;
            }

            qu.push({a,i});

            if(os.size())
            {
                auto it=os.lower_bound(i);

                if(it!=os.end())
                {
                    if(it==os.begin())
                    {
                        ans.push_back({abs(i-*it),{i,*it}});
                    }
                    else
                    {
                        int d1=abs(*it-i);
                        int A=*it;
                        it--;
                        int d2=abs(*it-i);
                        int B=*it;

                        if(d1>d2)
                        {
                            ans.push_back({abs(i-B),{i,B}});
                        }
                        else if(d1<d2) ans.push_back({abs(i-A),{i,A}});
                        else
                        {
                            ll p1=ar[i]-ar[A];
                            ll p2=ar[i]-ar[B];
                            if(p1==p2)
                            {
                                ans.push_back({abs(i-B),{i,B}});
                            }
                            else if(p1>p2)ans.push_back({abs(i-A),{i,A}});
                            else ans.push_back({abs(i-B),{i,B}});
                        }

                    }
                }
                else
                {
                    it--;
                    ans.push_back({abs(i-*it),{i,*it}});
                }
            }
        }

        sort(ans.begin(),ans.end());


        printf("%d %d\n",ans[0].second.first-1,ans[0].second.second-1);
    }
    
}

int main()
{
    int t=1;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
