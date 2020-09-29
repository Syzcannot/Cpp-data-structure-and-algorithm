#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#define ite map<int,int>::iterator
using namespace std;
const int MaxN=100000+10;
int n,m,tot,ans1[MaxN],ans2[MaxN];
bool vis[MaxN],mark[MaxN];
vector<int> a[MaxN],b[MaxN],V,M;
inline int Read()
{
    int x=0,f=1; char ch=getchar(); 
    while (ch<'0'||ch>'9') {if (ch=='-') f=-f; ch=getchar();}
    while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
struct AC_Automata{
	int fail[MaxN],last[MaxN];
	map<int,int> tire[MaxN];
	void insert(int id)
	{  
        int p=0;  
        for (int i=1,len=Read(),x;i<=len;++i)
        {
        	x=Read();
        	if (!tire[p][x]) tire[p][x]=++tot;
			p=tire[p][x];
		}
		b[p].push_back(id);
    }  
    void getfail()
	{  
	    int x,y,z;
	    queue<int> Q;
        fail[0]=0;   
        for (ite i=tire[0].begin();i!=tire[0].end();i++) x=i->second,fail[x]=last[x]=0,Q.push(x);
        while (!Q.empty())
		{  
            x=Q.front(); Q.pop();  
            for (ite i=tire[x].begin();i!=tire[x].end();i++)
            {
            	y=i->second,z=fail[x];
            	Q.push(y);
            	while (z&&!tire[z][i->first]) z=fail[z];
            	fail[y]=tire[z][i->first];
				last[y]=b[fail[y]].size()>0?fail[y]:last[fail[y]];
			}
        }  
    }  
	void solve(int x)
	{
		V.clear(); M.clear();
		int now=0;
		for(int i=0;i<a[x].size();++i)
		{
			int c=a[x][i];
			while(now&&!tire[now][c]) now=fail[now];
			now=tire[now][c];
			for (int j=now;j;j=last[j])
			{
				if (vis[j]) break;
				vis[j]=1; V.push_back(j);
				for (int k=0;k<b[j].size();++k) if(!mark[b[j][k]])
				{
					mark[b[j][k]]=1;M.push_back(b[j][k]);
					++ans1[b[j][k]];
					++ans2[x];
				}
			}
		}
		for(int i=0;i<V.size();++i)vis[V[i]]=0;
		for(int i=0;i<M.size();++i)mark[M[i]]=0;
	}
} T;
int main()
{
	freopen("test.in","r",stdin);
	n=Read(),m=Read();
	for (int i=1,len,x;i<=n;++i)
	{
		for (len=Read();len--;a[i].push_back(x)) x=Read();
		a[i].push_back(-1);
		for (len=Read();len--;a[i].push_back(x)) x=Read();
	    //for (int j=0;j<a[i].size();++j) cout<<a[i][j]<<' '; puts("");
	}
	for (int i=1;i<=m;++i) T.insert(i);
	T.getfail();
	for (int i=1;i<=n;++i) T.solve(i);
	for(int i=1;i<=m;i++) printf("%d\n",ans1[i]);
	for(int i=1;i<=n;i++)
	{
		printf("%d",ans2[i]);
		if(i!=n) putchar(' '); else puts("");
	}
	return 0;
}
