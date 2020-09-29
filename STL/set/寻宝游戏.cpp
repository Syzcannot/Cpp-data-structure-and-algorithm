#include<set>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long 
using namespace std;
const int MaxN=100000+10,MaxD=18,INF=2000000000;
struct Edge{int to,cost,next; } e[MaxN*2];
set<int> T;
LL ans,tmp,dis[MaxN];
int n,m,cnt,x,y,z,clk,l,r,f,first[MaxN],dep[MaxN],dfn[MaxN],pos[MaxN],b[MaxD+5],fa[MaxN][MaxD+5];
bool mark[MaxN];
inline int Read() 
{
    int x=0,f=1; char ch=getchar(); 
    while (ch<'0'||ch>'9') {if (ch=='-') f=-f; ch=getchar();}
    while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
inline void writeln(LL x)
{
	if (x<0) putchar('-'),x=-x; 
	if (!x) putchar('0'); else 
	{
	    int len=0; char s[50]; 
	    while (x) s[++len]=x%10+'0',x/=10;
	  	while (len) putchar(s[len--]);
	} 
	putchar('\n');
}
inline void Add(int u,int v,int w) 
{
	e[++cnt].to=v; e[cnt].cost=w; 
	e[cnt].next=first[u]; first[u]=cnt;
}
void DFS(int u)
{
	dfn[pos[u]=++clk]=u; 
	for (int i=1;b[i]<=dep[u];++i) fa[u][i]=fa[fa[u][i-1]][i-1];
	for (int i=first[u];i;i=e[i].next) if(e[i].to!=fa[u][0])
	{
		int v=e[i].to;
		dep[v]=dep[u]+1; dis[v]=dis[u]+e[i].cost; fa[v][0]=u;
		DFS(v);
	}
}
int LCA(int x,int y)
{												
	if (dep[x]>dep[y]) swap(x,y);
	int delta=dep[y]-dep[x];
	for (int i=0;b[i]<=delta;++i) if (b[i]&delta) y=fa[y][i];
	for(int i=MaxD;i>=0;--i) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return x==y?x:fa[x][0];
}
LL Get_Dis(int x,int y) {return dis[x]+dis[y]-2*dis[LCA(x,y)];}
int main()
{
	b[0]=1; 
	for (int i=1;i<MaxD;++i) b[i]=b[i-1]<<1;
	n=Read(); m=Read();
	for (int i=1;i<n;++i) x=Read(),y=Read(),z=Read(),Add(x,y,z),Add(y,x,z);
	DFS(1);
	T.insert(INF); T.insert(-INF);
	for (int i=1;i<=m;++i)
	{
		x=Read(); f=1;
		if (mark[x]) f=-1,T.erase(pos[x]); else T.insert(pos[x]);
		mark[x]^=1;
		l=*--T.lower_bound(pos[x]); r=*T.upper_bound(pos[x]);
		if (l!=-INF) ans+=Get_Dis(x,dfn[l])*f;
		if (r!=INF) ans+=Get_Dis(x,dfn[r])*f;
		if (l!=-INF&&r!=INF) ans-=Get_Dis(dfn[l],dfn[r])*f;
		if (T.size()>2) tmp=Get_Dis(dfn[*T.upper_bound(-INF)],dfn[*--T.lower_bound(INF)]); else tmp=0;
		writeln(ans+tmp);
	}
	return 0;
}
