// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 200005
#define ll long long
#define mod 1000000007 //998244353
 

char ch[mx];
int n,m,ii,k;

int add(int a,int b)
{
    a+=b;
    if(a>=mod)a-=mod;
    return a;
}
int sub(int a,int b)
{
    a-=b;
    if(a<0)a+=mod;
    return a;
}
int mul(int a,int b)
{
    ll re=a;
    re*=b;
    if(re>=mod)re%=mod;
    return re;
}

ll pre[mx];

pair<int,int>cur[11];
bool together[11];
deque<int>pos[11];
ll re[11];
int zerobat;

void pre_cal()
{
    ll val=1;
    pre[1]=val;
    for(int i=2;i<=mx-3;i++)
    {
        val=mul(val,10);
        pre[i]=add(pre[i-1],val);
    }
}

void print_ans()
{
    int ans=0;

    for(int i=0;i<10;i++)
    {
        if(together[i])
        {
            ans=add(ans,mul(i,sub(pre[n-cur[i].first+1],pre[n-cur[i].second])));
        }
        else
        {
            ans=add(ans,re[i]);
        }
    }
    printf("%d\n",ans);
}
void solve()
{
    scanf("%s",ch);
    n=strlen(ch);
    zerobat=0;

    for(int i=0;i<n;i++)
    {
        k=ch[i]-'0';
        pos[k].push_back(i+1);

        re[k]=add(re[k],mul(k,sub(pre[n-i],pre[n-i-1])));
    }
    
    scanf("%d",&m);
    printf("Case %d:\n",++ii);

    while(m--)
    {
        scanf("%d",&k);

        if(together[k])
        {
            int len=cur[k].second-cur[k].first+1;

            for(int i=0;i<10;i++)
            {
                if(i==k)continue;

                if(together[i] and cur[i].first>cur[k].second)
                {
                    cur[i]={cur[i].first-len,cur[i].second-len};
                }

            }
            cur[k]={n-len+1,n};

            if(together[0] and cur[0].first==1+zerobat)
            {
                zerobat+=cur[0].second-cur[0].first+1;
                pos[0].clear();
                together[0]=0;
            }

            

            print_ans();
            
        }
        else
        {
            int len=pos[k].size();

            if(len==0)
            {
                print_ans();
            }
            else
            {
                for(int i=0;i<10;i++)
                {
                    if(i==k)continue;

                    if(together[i])
                    {
                        cur[i]={cur[i].first-len,cur[i].second-len};

                        if(i==0 and cur[0].first==1+zerobat)
                        {
                            zerobat+=cur[0].second-cur[0].first+1;
                            pos[0].clear();
                            together[0]=0;
                        }
                    }
                    else
                    {
                        re[i]=0;
                        for(int &a:pos[i])
                        {
                            int sft=lower_bound(pos[k].begin(),pos[k].end(),a)-pos[k].begin();
                            a-=sft;
                            re[i]=add(re[i],mul(i,sub(pre[n-a+1],pre[n-a])));
                        }
                        if(i==0)
                        {
                            while(!pos[i].empty() and pos[i][0]==1+zerobat)
                            {
                                zerobat++;
                                pos[i].pop_front();
                            }
                        }
                    }
                }

                together[k]=1;

                cur[k]={n-len+1,n};

                



                print_ans();

            }

        }
    }
    for(int i=0;i<10;i++)
    {
        pos[i].clear();
        re[i]=0;
        together[i]=0;
        cur[i]={0,0};
    }
 
}
 
int main()
{
    int t=1;
    pre_cal();
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}