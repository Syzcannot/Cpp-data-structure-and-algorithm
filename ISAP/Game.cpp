#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
const int MaxN=200+10,MaxM=20000+10,INF=1e9;
struct Edge{int from,to,cap,next;} e[MaxM*6];
int n,m,s,t,cnt=1,tot,pos[MaxN][MaxN],first[MaxM],d[MaxM],num[MaxM],belong[MaxM],ans[MaxM],cur[MaxM],p[MaxM];
bool vis[MaxM];
char ch;
inline void Add(int u,int v,int cap)
{
	e[++cnt].from=u,e[cnt].to=v,e[cnt].cap=cap; e[cnt].next=first[u],first[u]=cnt;
	e[++cnt].from=v,e[cnt].to=u,e[cnt].cap=0;   e[cnt].next=first[v],first[v]=cnt;
}
void Check(int x,int d)  
{   
    vis[x]=1;  
    if (belong[x]==d) ans[x]=1;  
    for (int i=first[x];i;i=e[i].next) if(e[i].cap==d&&!vis[e[i].to]) Check(e[i].to,d);  
}  
inline int Aug()
{
	int x=t,a=INF;
	while (x!=s)
	{
		int now=p[x];
		a=min(a,e[now].cap);
		x=e[now].from;
	}
	x=t;
	while (x!=s)
	{
		int now=p[x];
		e[now].cap-=a;
		e[now^1].cap+=a;
		x=e[now].from;
	}
	return a;
}
int Sap()
{   
    int flow=0;
    for (int i=1;i<=tot;++i) d[i]=1,cur[i]=first[i];
	d[t]=0; num[0]=1,num[1]=tot-1;
	int u=s;
	while (d[s]<tot)
	{
		if (u==t) {flow+=Aug(); u=s;}
		bool flag=0;
		for (int i=cur[u];i;i=e[i].next) if (e[i].cap&&d[u]==d[e[i].to]+1) 
		{
		    flag=1; 
			cur[u]=i; 
			p[u=e[i].to]=i;
			break;
		}
        if (!flag)
        {
        	if (--num[d[u]]==0) break;
        	int mn=tot-1;
        	for (int i=first[u];i;i=e[i].next) if (e[i].cap) mn=min(mn,d[e[i].to]);
        	++num[d[u]=mn+1];
        	cur[u]=first[u];
        	if (u!=s) u=e[p[u]].from;
		}
	}
	return flow;
}
int main()
{
	freopen("test.in","r",stdin);
	cin>>n>>m;
	for (int i=1;i<=n;++i) for (int j=1;j<=m;++j)
	{
	  	for (ch=getchar();ch!='.'&&ch!='#';ch=getchar());
		if (ch=='.') pos[i][j]=++tot;
	}
	s=++tot,t=++tot;
	for (int i=1;i<=n;++i) for (int j=1;j<=m;++j) if (pos[i][j])
	{
	  	if ((i+j)&1) 
		{
			belong[pos[i][j]]=1;
			Add(s,pos[i][j],1);
			for (int k=0;k<4;++k)
			{
				int x=i+dx[k],y=j+dy[k];
				if (pos[x][y]) Add(pos[i][j],pos[x][y],1);
			}
		}
		else belong[pos[i][j]]=0,Add(pos[i][j],t,1);
	}
	//cout<<cnt<<" "<<tot<<endl;
	if (Sap()*2==tot-2) puts("LOSE");
	else
	{
		puts("WIN");
		memset(vis,0,sizeof vis); Check(s,1);  
        memset(vis,0,sizeof vis); Check(t,0);  
        for (int i=1;i<=n;++i) for (int j=1;j<=m;++j) if (ans[pos[i][j]]) printf("%d %d\n",i,j);
	}
	return 0;
}
