#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int MaxN=200000+10;
struct Point{int x,y,id;} p[MaxN],t[MaxN];
int n,st1[MaxN],st2[MaxN],top1,top2;
long long ans;
inline int Read()
{
    int x=0,f=1; char ch=getchar(); 
    while (ch<'0'||ch>'9') {if (ch=='-') f=-f; ch=getchar();}
    while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
inline bool cmp_x(Point A,Point B) {return A.x<B.x;}
inline bool cmp_y(Point A,Point B) {return A.y<B.y;}
inline int find(int x)
{
	if (t[st1[top1]].y<t[x].y) return 0;
	int l=1,r=top1;
	while (l<r)
	{
		int mid=(l+r)>>1;
		if (t[st1[mid]].y>t[x].y) r=mid; else l=mid+1;
	}
	return top1-l+1;
}
void Solve(int l,int r)
{
	if (l==r) return;
	int mid=(l+r)>>1,tot=0; top1=0,top2=0;
	for (int i=l;i<=r;++i) t[++tot].x=p[i].x,t[tot].y=p[i].y,t[tot].id=i;
	sort(t+1,t+tot+1,cmp_y);
	for (int i=1;i<=tot;++i)
	{
		if (t[i].id<=mid) 
		{
			while (top1&&t[i].x>t[st1[top1]].x) --top1;
			st1[++top1]=i;
		}
		else 
		{
			while (top2&&t[i].x<t[st2[top2]].x) --top2;
			st2[++top2]=i;
			if (top2==1) ans+=top1; else ans+=find(st2[top2-1]);
		}
	}
	Solve(l,mid); Solve(mid+1,r);
}
int main()
{
	n=Read();
	for (int i=1;i<=n;++i) p[i].x=Read(),p[i].y=Read();
	sort(p+1,p+n+1,cmp_x);
	Solve(1,n);
	cout<<ans<<endl;
	return 0;
}
