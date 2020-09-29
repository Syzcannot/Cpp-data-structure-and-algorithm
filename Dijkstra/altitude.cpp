#include<cstdio>
#include<algorithm>
#include<iostream>
#include<queue>
using namespace std;
const int MaxN=500+10,INF=2000000000;
struct Heap_Node
{
	int d,u;
	bool operator < (const Heap_Node& rhs) const{return d>rhs.d;}
};
struct Edge{int to,cost,next;} e[MaxN*MaxN*5];
int n,now,cnt,tot,s,t,east[MaxN][MaxN],south[MaxN][MaxN],west[MaxN][MaxN],north[MaxN][MaxN],first[MaxN*MaxN*2],dis[MaxN*MaxN*2];;
bool mark[MaxN*MaxN*2];
inline int Read()
{
    int x=0,f=1; char ch=getchar(); 
    while (ch<'0'||ch>'9') {if (ch=='-') f=-f; ch=getchar();}
    while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
inline void Add(int u,int v,int cost)
{
	//cout<<u<<' '<<v<<' '<<cost<<endl;
	e[++cnt].to=v; e[cnt].cost=cost; e[cnt].next=first[u]; first[u]=cnt;
}
priority_queue<Heap_Node> Q;
void dijkstra()
{
	int u;
	for (int i=1;i<=tot;i++) {dis[i]=INF; mark[i]=0;}
	dis[s]=0; Q.push((Heap_Node){0,s});
	while (!Q.empty())
	{
		Heap_Node x=Q.top(); Q.pop();
		u=x.u;
		if (mark[u]) continue;
		mark[u]=1;
		for (int i=first[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if (dis[u]+e[i].cost<dis[v]) {dis[v]=dis[u]+e[i].cost; Q.push((Heap_Node){dis[v],v});}
		}
	}
}
int main()
{
	freopen("altitude.in","r",stdin);
	freopen("altitude.out","w",stdout);
	n=Read()+1;
	for (int i=1;i<=n;++i) for (int j=1;j<n;++j) east[i][j]=Read();
	for (int i=1;i<n;++i) for (int j=1;j<=n;++j) south[i][j]=Read();
	for (int i=1;i<=n;++i) for (int j=1;j<n;++j) west[i][j]=Read();
	for (int i=1;i<n;++i) for (int j=1;j<=n;++j) north[i][j]=Read();
	for (int i=1;i<n;++i) for (int j=1;j<n;++j)
	{
		now=(i-1)*(n-1)+j;
		if (j!=1) Add(now-1,now,south[i][j]),Add(now,now-1,north[i][j]);
    	if (i!=1) Add(now-n+1,now,west[i][j]),Add(now,now-n+1,east[i][j]);
	}
	tot=(n-1)*(n-1)+2,s=tot-1,t=tot;
	for (int i=1;i<n;++i)
	{
        now=(i-1)*(n-1)+1;
        Add(s,now,south[i][1]);
        now=i*(n-1);
        Add(now,t,south[i][n]);
    }
    for (int i=1;i<n;++i)
	{
        now=i;
        Add(now,t,east[1][i]);
        now=(n-2)*(n-1)+i;
        Add(s,now,east[n][i]);
    }
    /*for (int i=0;i<=tot;++i) dis[i]=INF,inQ[i]=0;
    dis[s]=0; Q.push(s);
    while (!Q.empty())
    {
    	int u=Q.front(); Q.pop(); inQ[u]=0;
    	for (int i=first[u];i;i=e[i].next)
    	{
    		int v=e[i].to;
    		if (dis[u]+e[i].cost<dis[v])
    		{
    			dis[v]=dis[u]+e[i].cost;
    			if (!inQ[v]) {Q.push(v); inQ[v]=1;}
			}
		}
	}*/
	dijkstra();
	cout<<dis[t]<<endl;
	return 0;
}
