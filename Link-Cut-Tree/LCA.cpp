#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;
const int MaxN=50000+10,MOD=201314;
struct Q {int z,s,next;} q[MaxN*2];
struct Link_Cut_Tree {
	int cnt,stack[MaxN];
	int s[MaxN][2],fa[MaxN],val[MaxN],tag[MaxN],size[MaxN];
	LL sum[MaxN];
	bool rev[MaxN];
	#define ls s[x][0]
    #define rs s[x][1]
    bool Check(int x) {return s[fa[x]][0]==x||s[fa[x]][1]==x;}
    void Mark(int x,int w) {tag[x]+=w; val[x]+=w; (sum[x]+=size[x]*w)%=MOD;}
    void Pushdown(int x) {
	    if (rev[x]) rev[x]=0,rev[ls]^=1,rev[rs]^=1,swap(ls,rs);
	    if (tag[x]) {if (ls) Mark(ls,tag[x]); if (rs) Mark(rs,tag[x]); tag[x]=0;}
	}
	void Update(int x) {
	    size[x]=size[ls]+size[rs]+1; 
		sum[x]=sum[ls]+sum[rs]+val[x];
		sum[x]%=MOD;
    }
    void Rotate(int x) {
		int f=fa[x],k=s[f][1]==x; fa[x]=fa[f];
		if (Check(f)) s[fa[f]][s[fa[f]][1]==f]=x;
		if (s[f][k]=s[x][!k]) fa[s[f][k]]=f;
		Update(s[fa[f]=x][!k]=f);
	}
	void Splay(int x) {
		for (stack[cnt=1]=x;Check(x);x=fa[x]) stack[++cnt]=fa[x];
		while (cnt) Pushdown(stack[cnt--]); 
	    for (x=stack[1];Check(x);Rotate(x)) 
		   if (Check(fa[x])) Rotate(s[fa[x]][1]==x^s[fa[fa[x]]][1]==fa[x]?x:fa[x]); 
		Update(x);
	}
	void Access(int x) {for (int last=0;x;Splay(x),rs=last,Update(last=x),x=fa[x]);}
	void Evert(int x) {Access(x); Splay(x); rev[x]^=1;}
	void Link(int x,int y) {Evert(x); fa[x]=y;}
	void Add(int x,int y,int z) {Evert(x); Access(y); Splay(y); Mark(y,z);}
	int Query(int x,int y) {Evert(x); Access(y); Splay(y); return sum[y];}
} LCT;
inline int Read() 
{
    int x=0,f=1; char ch=getchar(); 
    while (ch<'0'||ch>'9') {if (ch=='-') f=-f; ch=getchar();}
    while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
inline void writeln(int x)
{
	if (x<0) putchar('-'),x=-x; 
	if (!x) putchar('0'); else 
	{
	    int len=0; char s[30]; 
	    while (x) s[++len]=x%10+'0',x/=10;
	  	while (len) putchar(s[len--]);
	} 
	putchar('\n');
}
int n,m,tot=1,first[MaxN],ans[MaxN];
int main()
{
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	n=Read(); m=Read(); 
	for (int i=2;i<=n;++i) LCT.Link(Read()+1,i);
	for (int i=1;i<=m;++i) 
	{
		int l=Read()+1,r=Read()+1,z=Read()+1;
		q[++tot].z=z,q[tot].s=-1,q[tot].next=first[l-1],first[l-1]=tot;
		q[++tot].z=z,q[tot].s=1,q[tot].next=first[r],first[r]=tot;
	}
	for (int i=1;i<=n;++i) 
	{
		LCT.Add(1,i,1);
		for (int j=first[i];j;j=q[j].next) ans[j>>1]+=LCT.Query(q[j].z,1)*q[j].s;
	}
	for (int i=1;i<=m;++i) writeln((ans[i]+MOD)%MOD);
	return 0;
}

