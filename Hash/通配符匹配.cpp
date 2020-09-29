#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#define ULL unsigned long long
using namespace std;
const int MaxN=100000+10,MaxP=15,X=13131;
int n,cnt=0;
char s[MaxN],c[MaxN];
bool dp[MaxP][MaxN];
int pos[MaxP];
ULL h1[MaxN],h2[MaxN],XL[MaxN];
void Init()
{
	freopen("3507.in","r",stdin);
	scanf("%s",s+1); 
	int Len=strlen(s+1); s[++Len]='?';
	for (int i=1;i<=Len;++i) if (s[i]=='?'||s[i]=='*') pos[++cnt]=i;
	for (int i=1;i<=Len;++i) h1[i]=(h1[i-1]*X+s[i]);
	XL[0]=1; for(int i=1;i<MaxN;++i) XL[i]=XL[i-1]*X;
}
inline ULL get1(int l,int r) {return h1[r]-h1[l-1]*XL[r-l+1];}
inline ULL get2(int l,int r) {return h2[r]-h2[l-1]*XL[r-l+1];}
void Solve()
{
	cin>>n;
	for (int i=1;i<=n;++i)
	{
		scanf("%s",c+1); 
		int Len=strlen(c+1); c[++Len]='#';
		for (int i=1;i<=Len;++i) h2[i]=(h2[i-1]*X+c[i]);
		memset(dp,0,sizeof(dp)); dp[0][0]=1;
		for (int i=0;i<cnt;++i)
		{
			if (s[pos[i]]=='*') {for (int j=1;j<=Len;++j) if (dp[i][j-1]) dp[i][j]=1;}
			for (int j=0;j<=Len;++j) if (dp[i][j]&&get1(pos[i]+1,pos[i+1]-1)==get2(j+1,j+pos[i+1]-pos[i]-1))
			{
				if (s[pos[i+1]]=='?') dp[i+1][j+pos[i+1]-pos[i]]=1; else dp[i+1][j+pos[i+1]-pos[i]-1]=1;
			}
		}
		if (dp[cnt][Len]) puts("YES"); else puts("NO");
	}
}
int main()
{
	Init();
	Solve();
	return 0;
}
