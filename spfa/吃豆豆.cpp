#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;
const int MaxN=2000+10,INF=1000000000;
struct Point {
    int x,y;
	bool operator < (const Point &A) const{return x==A.x?y<A.y:x<A.x;} 
}  p[MaxN];
struct Edge {int to,cap,cost,next;} e[MaxN*MaxN];
int n,tot,s,t,cnt=1;
int l[MaxN],r[MaxN],first[MaxN*2],d[MaxN*2],pre[MaxN*2],a[MaxN*2];
bool ex[MaxN*2];
inline void Add(int u,int v,int cap,int cost)
{
	e[++cnt].to=v; e[cnt].cap=cap; e[cnt].cost=cost;
	e[cnt].next=first[u]; first[u]=cnt;
	
	e[++cnt].to=u; e[cnt].cap=0; e[cnt].cost=-cost;
	e[cnt].next=first[v]; first[v]=cnt;
}
void Init()
{
	freopen("1930.in","r",stdin);
	cin>>n;
	for (int i=1;i<=n;++i) cin>>p[i].x>>p[i].y;
    sort(p+1,p+n+1);
    int S=++tot,T=++tot;
    for (int i=1;i<=n;++i)
    {
    	l[i]=++tot; r[i]=++tot;
    	Add(l[i],r[i],1,1); Add(l[i],r[i],1,0);
    	Add(S,l[i],1,0); Add(r[i],T,1,0);
    }
    for (int i=1;i<n;++i)
    {
    	int min_y=INF;
    	for (int j=i+1;j<=n;++j) if (p[j].y>=p[i].y&&min_y>p[j].y) Add(r[i],l[j],2,0),min_y=p[j].y;
    }
    s=++tot; t=T; Add(s,S,2,0);
}
queue<int> Q;
void Solve()
{
	int cost=0,flow=0;
	for (;;)
	{
		for (int i=1;i<=tot;++i) d[i]=-INF,inq[i]=0,pre[i]=0,a[i]=INF;
		d[s]=0; Q.push(s);
		while (!Q.empty())
		{
			int u=Q.front(); Q.pop(); ex[u]=0;
			for (int i=first[u];i;i=e[i].next)
			{
				int v=e[i].to;
				if (e[i].cap&&d[u]+e[i].cost>d[v])
				{
					d[v]=d[u]+e[i].cost;
					pre[v]=i; a[v]=min(a[u],e[i].cap);
					if (!ex[v]) {Q.push(v); ex[v]=1;}
				}
			}
		}
		if (d[t]==-INF) break;
		int del=a[t]; flow+=del;
		for (int k=t;pre[k];k=e[pre[k]^1].to)
		{
			e[pre[k]].cap-=del; e[pre[k]^1].cap+=del;
			cost+=e[pre[k]].cost*del;
		}
	}
	cout<<cost<<endl;
}
int main()
{
	Init(); 
	Solve();
	return 0;
}
