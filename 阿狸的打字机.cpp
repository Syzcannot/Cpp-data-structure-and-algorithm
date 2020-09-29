#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
const int MaxN=100000+100,Char_Size=26;
int m,tot,cnt,dfn,pos[MaxN],d[MaxN],l[MaxN],r[MaxN],t[MaxN];
vector<int> q[MaxN],e[MaxN],a[MaxN];
inline bool eoln(char ch) {return 'a'<=ch&&ch<='z'||ch=='B'||ch=='P';}
inline void insert(int x,int y) {e[x].push_back(y); ++d[y];}
inline int Read()
{
    int x=0,f=1; char ch=getchar(); 
    while (ch<'0'||ch>'9') {if (ch=='-') f=-f; ch=getchar();}
    while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
inline void Writeln(int x)
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
struct AC_Automata{
	int tire[MaxN][Char_Size],fa[MaxN],fail[MaxN];
    void build()
    {
        int now=0;
        for (char ch=getchar();eoln(ch);ch=getchar())
        {
            if (ch=='B') now=fa[now];
            if (ch=='P') {pos[++cnt]=now; q[now].push_back(cnt);}
            if ('a'<=ch&&ch<='z')
            {
                if (!tire[now][ch-'a']) {tire[now][ch-'a']=++tot; fa[tot]=now;}
                now=tot;
            }
        }
    }
    void getfail()
    {
        int x,y,z;
        queue<int> Q;
        fail[0]=0;
        for (int i=0;i<Char_Size;++i) if (x=tire[0][i]) {Q.push(x); fail[x]=0;}
        while (!Q.empty())
        {
            x=Q.front(); Q.pop();
            for (int i=0;i<Char_Size;++i) if (y=tire[x][i])
            {
                Q.push(y);
                z=fail[x];
                while (z&&!tire[z][i]) z=fail[z];
                if (fail[y]=tire[z][i]) insert(fail[y],y);
                //cout<<x<<' '<<fail[x]<<"    "<<y<<' '<<fail[y]<<endl;
            }
        }
    }
} T;
struct Rec{int x,ans;} qry[MaxN];
inline void Add(int x,int y)
{
	if (!x) return;
	while (x<=dfn) {t[x]+=y; x+=x&-x;}
}
inline int sum(int x)
{
	int ret=0;
	while (x>0) {ret+=t[x]; x-=x&-x;}
	return ret;
}
inline int Ask(int s,int t) {return sum(t)-sum(s-1);}
inline void Query(int x)
{
	for (int i=0;i<a[x].size();++i)
	{
		int y=qry[a[x][i]].x;
		qry[a[x][i]].ans=Ask(l[pos[y]],r[pos[y]]);
	}
}
void getdfn(int x)
{
	//cout<<x<<endl;
    l[x]=++dfn;
    for (int i=0;i<e[x].size();++i) getdfn(e[x][i]);
    r[x]=dfn;
}
void dfs(int x)
{
    Add(l[x],1);
    for (int i=0;i<q[x].size();++i) Query(q[x][i]);
    for (int i=0;i<Char_Size;++i) if (T.tire[x][i]) dfs(T.tire[x][i]);
    Add(l[x],-1);
}
void init()
{
    m=Read();
    for (int i=1;i<=m;++i)
    {
        int x=Read(),y=Read();
        qry[i].x=x;
        a[y].push_back(i);
    }
}
void solve()
{
    for (int i=1;i<=tot;++i) if (!d[i]) getdfn(i);
    //cout<<1<<endl;
    dfs(0);
    for (int i=1;i<=m;++i) Writeln(qry[i].ans);
}
int main()
{
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
    T.build();
    T.getfail();
    init();
    solve();
    return 0;
}
