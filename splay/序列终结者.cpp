#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
const int MaxN=50000+10;
struct SPLAY{
	int root,cnt;
    int s[MaxN][2],fa[MaxN],val[MaxN],mx[MaxN],tag[MaxN],size[MaxN],rev[MaxN];
	#define ls s[x][0]
    #define rs s[x][1]
	int Build(int l,int r) {
		int mid=(l+r)>>1,x=++cnt; 
	    if (l<mid) ls=Build(l,mid-1);
	    if (mid<r) rs=Build(mid+1,r);
	    size[x]=size[ls]+size[rs]+1;
	    return x;
	}
	void Init(int n) {root=Build(1,n+2);}
	void Pushdown(int x) {
		if (tag[x]!=0) {
			if (ls) tag[ls]+=tag[x],val[ls]+=tag[x],mx[ls]+=tag[x];
			if (rs) tag[rs]+=tag[x],val[rs]+=tag[x],mx[rs]+=tag[x];
			tag[x]=0;
		}
		if (rev[x]) {
			rev[x]=0;
			if (ls) rev[ls]^=1; 
			if (rs) rev[rs]^=1;
			swap(ls,rs);
		}
	}
	void Normal(int x) {if (fa[x]) Normal(fa[x]); Pushdown(x);}
	void Update(int x) {
		mx[x]=val[x];
	    if(ls&&mx[ls]>mx[x]) mx[x]=mx[ls]; 
		if(rs&&mx[rs]>mx[x]) mx[x]=mx[rs];
		size[x]=size[ls]+size[rs]+1;
	}
	void Rotate(int x) {
		int f=fa[x],k=s[f][1]==x; fa[x]=fa[f];
		if (fa[f]) s[fa[f]][s[fa[f]][1]==f]=x; else root=x;
		if (s[f][k]=s[x][!k]) fa[s[f][k]]=f;
		Update(s[fa[f]=x][!k]=f);
	}
	void Splay(int x,int S) { 
	    if (x==S) return;
		for (Normal(x);fa[x]!=S;Rotate(x)) 
		  if (fa[fa[x]]!=S) Rotate(s[fa[x]][1]==x^s[fa[fa[x]]][1]==fa[x]?x:fa[x]);
		Rotate(x);
		Update(x);
	}
	int Findth(int k) {
		for (int x=root;;) {
			Pushdown(x);
			if (size[ls]+1==k) return x;
			if (size[ls]>=k) x=ls; else k-=size[ls]+1,x=rs;
		}
	}
	void Add(int l,int r,int v) {
		int x=Findth(l),y=Findth(r+2),z;
		Splay(x,root); Splay(y,rs);
		tag[z=s[y][0]]+=v; val[z]+=v; mx[z]+=v;
	}
	void Rev(int l,int r) {
		int x=Findth(l),y=Findth(r+2);
		Splay(x,root); Splay(y,rs);
		rev[s[y][0]]^=1; 
	}
	int Query(int l,int r) {
		int x=Findth(l),y=Findth(r+2);
		Splay(x,root); Splay(y,rs);
		return mx[s[y][0]]; 
	}
} T;
inline int getc() {
    static const int L = 1 << 15;
    static char buf[L], *S = buf, *T = buf;
    if (S == T) {
        T = (S = buf) + fread(buf, 1, L, stdin);
        if (S == T)
            return EOF;
    }
    return *S++;
}
inline int Read() 
{
    int x=0,f=1; char ch=getc(); 
    while (ch<'0'||ch>'9') {if (ch=='-') f=-f; ch=getc();}
    while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getc();
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
int n,m,p,x,y,z;
int main()
{
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	n=Read(); m=Read();
	T.Init(n);
	for (int i=1;i<=m;++i)
	{
		p=Read();
		if (p==1) {x=Read(),y=Read(),z=Read(); T.Add(x,y,z); continue;}
		if (p==2) {x=Read(),y=Read(); T.Rev(x,y); continue;}
		if (p==3) {x=Read(),y=Read(); writeln(T.Query(x,y)); continue;}
	}
	return 0;
}
