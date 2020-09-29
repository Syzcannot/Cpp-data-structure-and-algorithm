#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int MaxN=50000+10,MaxM=100000+10,MaxS=MaxN+MaxM;
struct Edge {int x,y,a,b;} e[MaxM];
struct Link_Cut_Tree {
	int fa[MaxS],s[MaxS][2],val[MaxS],mx[MaxS];
	bool rev[MaxS];
	#define ls s[x][0]
    #define rs s[x][1]
	bool Check(int x) {return s[fa[x]][0]==x||s[fa[x]][1]==x;}
	void Update(int x) {mx[x]=x; if(val[mx[ls]]>val[mx[x]]) mx[x]=mx[ls]; if(val[mx[rs]]>val[mx[x]]) mx[x]=mx[rs];}
	void Normal(int x) {if (Check(x)) Normal(fa[x]); if (rev[x]) rev[x]=0,rev[ls]^=1,rev[rs]^=1,swap(ls,rs);}
	void Rotate(int x) {
		int f=fa[x],k=s[f][1]==x; fa[x]=fa[f];
		if (Check(f)) s[fa[f]][s[fa[f]][1]==f]=x;
		if (s[f][k]=s[x][!k]) fa[s[f][k]]=f;
		Update(s[fa[f]=x][!k]=f);
	}
	void Splay(int x) {int f; for (Normal(x);Check(x);Rotate(x)) if (Check(f=fa[x])) Rotate(s[f][1]==x^s[fa[f]][1]==f?x:f); Update(x);}
	void Access(int x) {for (int last=0;x;Splay(x),rs=last,last=x,x=fa[x]);}
	void Evert(int x) {Access(x); Splay(x); rev[x]^=1;}
	void Link(int x,int y) {Evert(x); fa[x]=y;}
	void Cut(int x,int y) {Evert(x); Access(y); Splay(y); fa[x]=s[y][0]=0;}
	int Query(int x,int y) {Evert(x); Access(y); Splay(y); return mx[y];}
} LCT;
int n,m,cnt,x,y,z,a,b,ans=1000000000,p[MaxN];
inline int Read()
{
    int x=0,f=1; char ch=getchar(); 
    while (ch<'0'||ch>'9') {if (ch=='-') f=-f; ch=getchar();}
    while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
inline bool Cmp(const Edge& x,const Edge& y) {return x.a<y.a||x.a==y.a&&x.b<y.b;}
inline void Add(int x,int y,int a,int b) {e[++cnt].x=x,e[cnt].y=y,e[cnt].a=a,e[cnt].b=b;}
int Find(int x) {return x==p[x]?x:p[x]=Find(p[x]);}
int main()
{  
    freopen("test.in","r",stdin);
    n=Read(); m=Read();
	for (int i=1;i<=m;++i) {x=Read(),y=Read(),a=Read(),b=Read(); if (x!=y) Add(x,y,a,b);}
	sort(e+1,e+cnt+1,Cmp);
	for (int i=1;i<=n;++i) p[i]=i;
	for (int i=1;i<=cnt;++i) 
	{
		LCT.val[i+n]=e[i].b; x=e[i].x; y=e[i].y;
	    if (Find(x)!=Find(y)) LCT.Link(x,i+n),LCT.Link(i+n,y),p[p[x]]=y;
		  else {z=LCT.Query(x,y)-n; if (e[i].b<e[z].b) LCT.Cut(e[z].x,z+n),LCT.Cut(z+n,e[z].y),LCT.Link(x,i+n),LCT.Link(i+n,y);}
	    if (Find(1)==Find(n)) {z=LCT.Query(1,n)-n; if (ans>e[i].a+e[z].b) ans=e[i].a+e[z].b;}
	}
	if (Find(1)!=Find(n)) puts("-1"); else printf("%d\n",ans);
	return 0;
}
