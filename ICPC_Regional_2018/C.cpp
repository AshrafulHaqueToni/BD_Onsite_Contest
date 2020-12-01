// Created by ash_98

#include<bits/stdc++.h>
using namespace std;

#define mx 1000005
#define ll long long
#define mod 10000007

bitset<mx>is_composite;
vector<int>prime;
int phi[mx];


void seive(int n)
{
    phi[1]=1;

    for(int i=2;i<=n;i++)
    {
        if(!is_composite[i])
        {
            prime.push_back(i);
            phi[i]=i-1;              ///i is prime
        }

        for(int j=0;j<prime.size() && i*prime[j]<=n;j++)
        {
            is_composite[i*prime[j]]=true;

            if(i%prime[j]==0)
            {
                phi[i*prime[j]]=phi[i]*prime[j];   ///prime[j] divides i
                break;
            }
            else
            {
                phi[i*prime[j]]=phi[i]*phi[prime[j]];  ///prime[j] do not divide i
            }
        }
    }
}

/// sndd(p_1^e_1 * p_2^e_2 *...* p_k^e_k) = sndd(p_1^e_1) * sndd(p_2^e_2) * ... * sndd(p_k^e_k)
/// Also sndd(p_1^e_1) = (e_1+2)*(e_1+1)/2 =  (1+2+3+4..+k+1) = (k+2) C 2

void solve()
{
	int n;
	scanf("%d",&n);
	ll re=1;
	if(n==0)exit(0);
	int sz=prime.size();
	for(int i=0;i<sz && prime[i]<=n;i++)
	{
		ll cnt=0;
		ll val=prime[i];
		while(val<=n)
		{
			cnt+=n/val;
			val*=prime[i];
		}
		ll val1=((cnt+2)*(cnt+1))/2;
		val1%=mod;
		re=(re*val1)%mod;

	}
	printf("%lld\n",re );
}

int main()
{
	int t=1;
	//scanf("%d",&t);
	seive(mx-5);
	while(1)solve();
	return 0;
}
