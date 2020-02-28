#include<bits/stdc++.h>
using namespace std;
#define mx 100005

vector<int>g[mx];
set<pair<int,int>>vv;
vector<int>v;
bool ans[mx];
int st[mx],en[mx];
int n,y,cnt;


bool cmp(int a,int b)
{
    return en[a]<en[b];
}

void dfs(int u,int p)
{
    st[u]=cnt++;
    for(auto it:g[u])
    {
        if(it!=p)
        {
            v.push_back(it);
            dfs(it,u);

        }
    }
    en[u]=cnt++;
}

void solve(int ii)
{
    cnt=1;
    for(int i=1; i<=n; i++)
    {
        st[i]=0;
        en[i]=0;
        ans[i]=false;
        g[i].clear();
    }

    v.clear();
    vv.clear();

    scanf("%d",&n);
    for(int i=1; i<n; i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    for(int i=1; i<=n; i++)
        sort(g[i].begin(),g[i].end());

    dfs(1,-1);

    v.push_back(1);
    sort(v.begin(),v.end(),cmp);

    for(int i=0; i<v.size(); i++)
    {
        vv.insert({en[v[i]],v[i]});
    }

    int q;
    scanf("%d",&q);
    printf("Case %d:\n",ii);
    while(q--)
    {
        int ty,x;
        scanf("%d%d",&ty,&x);
        if(ty==1)
        {
            scanf("%d",&y);
            if(ans[x]==false && y)
            {
                pair<int,int>tem= {st[x],n+1};

                auto it=vv.upper_bound(tem);
                auto it1=it;

                while(y)
                {
                    pair<int,int>itt=*it;
                    //cout<<itt.first<<" "<<itt.second<<endl;
                    y--;
                    ans[itt.second]=true;
                    it++;
                    if(itt.second==x)break;
                }
                //it--;
                vv.erase(it1,it);

            }

        }
        else
        {
            if(ans[x])
                printf("1\n");
            else
                printf("0\n");
        }
    }
}
int main()
{
    int t=1;
    scanf("%d",&t);
    for(int i=1; i<=t; i++)
        solve(i);
    return 0;
}
