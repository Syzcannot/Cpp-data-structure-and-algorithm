#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
const int maxn=100000+100,inf=1000000000;
int n,cnt=0,root;
struct rec{int v,pos;}a[maxn];
int c[maxn],son[maxn][2],fa[maxn],minv[maxn],v[maxn],pos[maxn],size[maxn];
bool rev[maxn];
inline int read()
{
    int x=0,f=1; char ch=getchar();
    while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
    while (ch>='0'&&ch<='9') {x=x*10+ch-'0'; ch=getchar();}
    return x*f;
}
inline bool cmp(rec a,rec b) {return a.v<b.v||(a.v==b.v&&a.pos<b.pos);}
void discretize()
{
	sort(a+1,a+n+1,cmp); 
	c[1]=c[n+2]=inf;
	for (int i=1;i<=n;++i) c[a[i].pos]=i;
}
void init()
{
	n=read(); 
	for (int i=1;i<=n;++i) {a[i].v=read(); a[i].pos=i+1;} 
	discretize(); 
}
inline void update(int x)
{
	int k; minv[x]=v[x]; pos[x]=x;
	if ((k=son[x][0])&&minv[k]<minv[x]) {minv[x]=minv[k]; pos[x]=pos[k];}
	if ((k=son[x][1])&&minv[k]<minv[x]) {minv[x]=minv[k]; pos[x]=pos[k];}
	size[x]=size[son[x][0]]+size[son[x][1]]+1;
}
inline int getnew(int k)
{
	int x=++cnt;
	son[x][0]=son[x][1]=fa[x]=0; minv[x]=v[x]=c[k]; pos[x]=x; rev[x]=false;
	return x;
}
inline int build(int l,int r)
{
	int mid=(l+r)>>1,x=getnew(mid); 
	if (l<mid) {int k=son[x][0]=build(l,mid-1); fa[k]=x;}
	if (mid<r) {int k=son[x][1]=build(mid+1,r); fa[k]=x;}
	update(x);
	return x;
}
inline void normal(int k)
{
    if (rev[k])
    {
       rev[k]=false;
       int l=son[k][0],r=son[k][1];
       if (l) rev[l]=!rev[l]; 
	   if (r) rev[r]=!rev[r];
	   swap(son[k][0],son[k][1]);
    }  
}
inline int findth(int k)
{
	int i=root;
	for (;;)
	{
		normal(i);
		int l=son[i][0],r=son[i][1];
		if (size[l]+1==k) return i;
		if (size[l]<k) {k=k-size[l]-1; i=r;} else i=l; 
	}
}
inline void rotate(int x)
{
	int y=fa[x],k; if (x==son[y][0]) k=0; else k=1;
	son[y][k]=son[x][k^1];
	if (son[x][k^1]) fa[son[x][k^1]]=y;
	if (y==root) {root=x; fa[x]=0;}
	else
	{
		fa[x]=fa[y];
		if (y==son[fa[y]][0]) son[fa[y]][0]=x; else son[fa[y]][1]=x;
	}
	son[x][k^1]=y; fa[y]=x;
	update(y); update(x);
}
inline void splay(int k,int s)
{
    int i=k,father;
    if (k==s) return;
	while (fa[i]!=s) 
	{
		father=fa[i];
		if (fa[father]==s) {normal(father); normal(i); rotate(i);}
		else
		{
			normal(fa[father]); normal(father); normal(i);
			if ((father==son[fa[father]][0]&&i==son[father][0])||(father==son[fa[father]][1]&&i==son[father][1])) {rotate(father); rotate(i);} else {rotate(i); rotate(i);}
		}
	}
	rotate(i);
}
inline int getpos(int l,int r)
{
	int x=findth(l), y=findth(r+2);
	splay(x,root); splay(y,son[x][1]);
	int z=son[y][0];
	return pos[z];
}
inline void move(int l,int r)
{
	int x=findth(l),y=findth(r+2);
	splay(x,root); splay(y,son[x][1]);
	int z=son[y][0];
	rev[z]=!rev[z];
}
void solve()
{
	root=build(1,n+2); 
	for (int i=1;i<=n;++i)
	{
		int x=getpos(i,n);  
        splay(x,root);
        int ans=size[son[x][0]];
        printf("%d",ans); if (i!=n) printf(" "); else printf("\n");
        move(i,ans);
	}
}
int main()
{
	init();
	solve();
	return 0;
}
