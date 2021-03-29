// Created by ash_98
 
#include<bits/stdc++.h>
using namespace std;
 
#define mx 200005
#define ll long long
#define mod 1000000007
 
int ar[mx];
char ch[mx];
int n,m,ii,k;
int Trie[mx*26][26];
map<vector<int>,int>mp[mx*26],Smart;
int st=1;


void Insert(vector<int>freq,int id)
{
	int cur=1;
	m=strlen(ch);
	for(int i=0;i<m;i++)
	{
		int ace=ch[i]-'a';
		if(!Trie[cur][ace])Trie[cur][ace]=++st;
		cur=Trie[cur][ace];
		int val=mp[cur][freq];
		if(val<ar[id])mp[cur][freq]=ar[id];
	}
}

int re;

void query(int cur,vector<int>freq,int len)
{
	   if(len>strlen(ch))return;
    	if(Trie[cur][ch[len-1]-'a'])
    	{
    		re=max(re,len+mp[Trie[cur][ch[len-1]-'a']][freq]);
    	//	cout<<re<<endl;
    		query(Trie[cur][ch[len-1]-'a'],freq,len+1);
    	}
    
}
void solve()
{
	scanf("%d",&n);
	st=1;
	for(int i=1;i<=n;i++)scanf("%d",&ar[i]);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",ch);
		m=strlen(ch);
		vector<int>freq(26);
		for(int j=0;j<m;j++)freq[ch[j]-'a']++;
		Insert(freq,i);
	    if(Smart[freq]<ar[i])Smart[freq]=ar[i];
	}
	int q;
	scanf("%d",&q);
	while(q--)
	{
		scanf("%s",ch);
		m=strlen(ch);
		vector<int>freq(26);
		for(int j=0;j<m;j++)freq[ch[j]-'a']++;
		re=Smart[freq];
	   // cout<<re<<endl;
	    query(1,freq,1);
	    printf("%d\n",re);
	}
	Smart.clear();
	for(int i=1;i<=st;i++)mp[i].clear();
	memset(Trie,0,sizeof(Trie));
}
 
int main()
{
	int t=1;
	scanf("%d",&t);
	while(t--)solve();
	return 0;
}
