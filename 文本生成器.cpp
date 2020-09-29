#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
const int MaxN=6000+100,MaxM=100+10,MOD=10007,Char_Size=26;
int n,m,tot,f[MaxM][MaxN];
char s[MaxN];
struct AC_Automata{
	int ch[MaxN][Char_Size],val[MaxN],last[MaxN],fail[MaxN],mark[MaxN];
	void insert()
	{  
        int p=0,len=strlen(s+1);  
        for (int i=1,j=s[1]-'A';i<=len;p=ch[p][j],j=s[++i]-'A') if (!ch[p][j]) ch[p][j]=++tot; 
        val[p]=1; 
		mark[p]=1; 
    }  
    void getfail()
	{  
	    int x,y,z;
	    queue<int> Q;
        fail[0]=0;   
        for (int i=0;i<Char_Size;++i) if (x=ch[0][i]) fail[x]=last[x]=0,Q.push(x);
        while (!Q.empty())
		{  
            x=Q.front(); Q.pop();  
            for (int i=0;i<Char_Size;++i) 
            {
            	if (!ch[x][i]) {ch[x][i]=x==0?0:ch[fail[x]][i]; continue;}
            	Q.push(y=ch[x][i]);
            	fail[y]=x==0?0:ch[fail[x]][i];
            	last[y]=val[fail[y]]?fail[y]:last[fail[y]];
            	mark[y]|=mark[fail[y]];
			}
        }  
    }  
    void solve()
    {
    	int ans1=1,ans2=0;
    	f[0][0]=1;
    	for (int i=1;i<=m;++i)  
            for (int j=0;j<=tot;++j) if (!mark[j])  
                for (int k=0;k<Char_Size;++k) //if (ch[j][k])
                    f[i][ch[j][k]]=(f[i][ch[j][k]]+f[i-1][j])%MOD;  
        for (int i=0;i<=tot;++i) if (!mark[i]) ans2=(ans2+f[m][i])%MOD;  
        for (int i=1;i<=m;++i) ans1=(ans1*Char_Size)%MOD;  
        printf("%d\n",(ans1-ans2+MOD)%MOD);   
	}
} T;
int main()
{
	freopen("test.in","r",stdin);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) {scanf("%s",s+1); T.insert();} 
	T.getfail();
	T.solve();
	return 0;
}
