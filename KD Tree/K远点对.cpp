#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#define LL long long
#define ls node[now].s[0]
#define rs node[now].s[1]
using namespace std;
priority_queue<LL,vector<LL>,greater<LL> > H; 
const int MaxN=100000+100;
struct KD_Tree{int d[2],x[2],y[2],s[2];} node[MaxN];
int n,k,root,dms,X,Y;
inline int Read()
{
    int x=0,f=1; char ch=getchar(); 
    while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
    while (ch>='0'&&ch<='9') {x=x*10+ch-'0'; ch=getchar();}
    return x*f;
}
inline bool cmp(KD_Tree A,KD_Tree B) {return A.d[dms]<B.d[dms];}  
inline void Update(int x,int s)
{
	if (node[s].x[0]<node[x].x[0]) node[x].x[0]=node[s].x[0];
	if (node[s].x[1]>node[x].x[1]) node[x].x[1]=node[s].x[1];
	if (node[s].y[0]<node[x].y[0]) node[x].y[0]=node[s].y[0];
	if (node[s].y[1]>node[x].y[1]) node[x].y[1]=node[s].y[1];
}
int Build(int l,int r,int d)
{
	int now=(l+r)>>1; dms=d; 
	nth_element(node+l,node+now,node+r+1,cmp);
	if (l<now) ls=Build(l,now-1,d^1),Update(now,ls);
	if (now<r) rs=Build(now+1,r,d^1),Update(now,rs);
	return now;
}
inline LL Sqr(LL x) {return x*x;}
inline LL Calc(int x) {return max(Sqr(node[x].x[0]-X),Sqr(node[x].x[1]-X))+max(Sqr(node[x].y[0]-Y),Sqr(node[x].y[1]-Y));}
void Query(int now)
{
	LL dl=Calc(ls),dr=Calc(rs),d=Sqr(node[now].d[0]-X)+Sqr(node[now].d[1]-Y);
	if (d>H.top()) {H.pop(); H.push(d);}
	if (dl>dr)
	{
		if (ls&&dl>H.top()) Query(ls);  
        if (rs&&dr>H.top()) Query(rs);  
	}
	else 
	{
        if (rs&&dr>H.top()) Query(rs);  
        if (ls&&dl>H.top()) Query(ls);  
	}
}
int main()
{
	freopen("test.in","r",stdin);
	n=Read(),k=Read();
	for (int i=1;i<=n;++i)
	{
		node[i].d[0]=node[i].x[0]=node[i].x[1]=Read();
		node[i].d[1]=node[i].y[0]=node[i].y[1]=Read();
	}
	root=Build(1,n,0);
	for (int i=1;i<=(k<<1);i++) H.push(0);  
	for (int i=1;i<=n;++i)
	{
		X=node[i].d[0],Y=node[i].d[1];
		Query(root);
	}
	cout<<H.top()<<endl;
	return 0;
}
