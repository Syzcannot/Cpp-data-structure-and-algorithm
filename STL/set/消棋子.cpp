#include<cstdio>
#include<algorithm>
#include<iostream>
#include<set>
#include<queue>
#define mk(a,b) make_pair(a,b)
using namespace std;
const int maxn=100000+100;
typedef pair<int,int> Pii;
Pii A[maxn],B[maxn],C[maxn],D[maxn];
set<Pii> line[maxn],row[maxn];
bool del[maxn];
int r,c,n,m,cnt=0;
struct Node{int x,y; char F1,F2;} s[maxn];
queue <int> Q;
inline int read_int()
{
    int x=0,f=1; char ch=getchar();
    while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
    while (ch>='0'&&ch<='9') {x=x*10+ch-'0'; ch=getchar();}
    return x*f;
}
inline char read_char()
{
    char ch=getchar();
    while (ch<'A'||ch>'Z') ch=getchar();
    return ch;
}
inline void write_int(int x)
{
	const int maxl=25;
	if (!x) {putchar('0'); return;} if (x<0) {putchar('-'); x=-x;}
	char st[maxl]; int len=0;
	while (x) {st[++len]=x%10+'0'; x/=10;}
	while (len) putchar(st[len--]);
}
void init()
{
	freopen("3519.in","r",stdin);
	r=read_int(); c=read_int(); n=read_int();
	for (int i=1;i<=n;++i)
	{
		int a,b,c,d;
		a=read_int(); b=read_int(); c=read_int(); d=read_int();
		A[i].first=a; B[i].first=b; C[i].first=c; D[i].first=d;
        A[i].second=B[i].second=C[i].second=D[i].second=i;
	}
}
void clear()
{
    for (int i=0;i<=r;++i) {line[i].clear(); line[i].insert(mk(0,0)); line[i].insert(mk(maxn,0));}
    for (int i=0;i<=c;++i) {row[i].clear(); row[i].insert(mk(0,0)); row[i].insert(mk(maxn,0));}
    for (int i=1;i<=n;++i) 
    {
        line[A[i].first].insert(B[i]);
        line[C[i].first].insert(D[i]);
        row[B[i].first].insert(A[i]); 
        row[D[i].first].insert(C[i]);
    }
}
void solve_1()
{
	clear();
	int x,y,ans=0; char F1,F2; Pii Find1,Find2;
	m=read_int();
	for (int i=1;i<=m;++i)
	{
		int flag1=0,flag2=0;
		x=read_int(); y=read_int(); F1=read_char(); F2=read_char();
		Find1=*line[x].lower_bound(mk(y,0));
		if (Find1.first==y) continue;
		
		if (F1=='U') {Find1=*(--row[y].lower_bound(mk(x,0)));   flag1=(Find1.second==0)?0:1;}
        if (F1=='D') {Find1=*(row[y].upper_bound(mk(x,maxn)));  flag1=(Find1.second==0)?0:1;}
        if (F1=='L') {Find1=*(--line[x].lower_bound(mk(y,0)));  flag1=(Find1.second==0)?0:2;}
        if (F1=='R') {Find1=*(line[x].upper_bound(mk(y,maxn))); flag1=(Find1.second==0)?0:2;}

        if (F2=='U') {Find2=*(--row[y].lower_bound(mk(x,0)));   flag2=(Find2.second==0)?0:1;}
        if (F2=='D') {Find2=*(row[y].upper_bound(mk(x,maxn)));  flag2=(Find2.second==0)?0:1;}
        if (F2=='L') {Find2=*(--line[x].lower_bound(mk(y,0)));  flag2=(Find2.second==0)?0:2;}
        if (F2=='R') {Find2=*(line[x].upper_bound(mk(y,maxn))); flag2=(Find2.second==0)?0:2;}     

        if (flag1&&flag2&&Find1.second==Find2.second)
        {
            ++ans;
            if (flag1==1) {row[y].erase(Find1); line[Find1.first].erase(mk(y,Find1.second));}
            if (flag1==2) {line[x].erase(Find1); row[Find1.first].erase(mk(x,Find1.second));}
            if (flag2==1) {row[y].erase(Find2); line[Find2.first].erase(mk(y,Find2.second));}
            if (flag2==2) {line[x].erase(Find2); row[Find2.first].erase(mk(x,Find2.second));}
        }
	}
	write_int(ans); putchar('\n');
}
inline void Print(int x,int y,char ch1,char ch2)
{
	write_int(x); putchar(' '); write_int(y); putchar(' ');
	putchar(ch1); putchar(' '); putchar(ch2); 
}
inline void ins(int x,int y,char ch1,char ch2) {s[++cnt]=(Node){x,y,ch1,ch2};}
inline void recheck(int x, int y, int id)
{
    Pii Find1,Find2;
    Find1=*(line[x].lower_bound(mk(y,0)));
    if (Find1.first==y) return;

    Find1=*(--row[y].lower_bound(mk(x,0))); 
    Find2=*(row[y].upper_bound(mk(x,maxn)));
    if (Find1.second==id&&Find1.second==Find2.second&&!del[id])
    {
        del[id]=true; Q.push(id); ins(x,y,'U','D');
        row[y].erase(Find1); line[Find1.first].erase(mk(y,Find1.second));
        row[y].erase(Find2); line[Find2.first].erase(mk(y,Find2.second));
        return;
    }

    Find1=*(--line[x].lower_bound(mk(y,0)));
    Find2=*(line[x].upper_bound(mk(y,maxn)));
    if (Find1.second==id&&Find1.second==Find2.second&&!del[id])
    {
        del[id]=true; Q.push(id); ins(x,y,'L','R');
        line[x].erase(Find1); row[Find1.first].erase(mk(x,Find1.second)); 
        line[x].erase(Find2); row[Find2.first].erase(mk(x,Find2.second)); 
        return;
    }

    Find1=*(--row[y].lower_bound(mk(x,0))); 
    Find2=*(line[x].upper_bound(mk(y,maxn)));
    if (Find1.second==id&&Find1.second==Find2.second&&!del[id])
    {
        del[id]=true; Q.push(id); ins(x,y,'U','R');
        row[y].erase(Find1); line[Find1.first].erase(mk(y,Find1.second));
        line[x].erase(Find2); row[Find2.first].erase(mk(x,Find2.second));
        return;
    }

    Find1=*(--row[y].lower_bound(mk(x,0))); 
    Find2=*(--line[x].lower_bound(mk(y,0)));
    if (Find1.second==id&&Find1.second==Find2.second&&!del[id])
    {
        del[id]=true; Q.push(id); ins(x,y,'U','L');
        row[y].erase(Find1); line[Find1.first].erase(mk(y,Find1.second));
        line[x].erase(Find2); row[Find2.first].erase(mk(x,Find2.second));
        return;
    }

    Find1=*(row[y].upper_bound(mk(x,maxn))); 
    Find2=*(line[x].upper_bound(mk(y,maxn)));
    if (Find1.second==id&&Find1.second==Find2.second&&!del[id])
    {
        del[id]=true; Q.push(id); ins(x,y,'D','R');
        row[y].erase(Find1); line[Find1.first].erase(mk(y,Find1.second));
        line[x].erase(Find2); row[Find2.first].erase(mk(x,Find2.second));
        return;
    }

    Find1=*(row[y].upper_bound(mk(x,maxn)));
    Find2=*(--line[x].lower_bound(mk(y,0))); 
    if (Find1.second==id&&Find1.second==Find2.second&&!del[id])
    {
        del[id]=true; Q.push(id); ins(x,y,'D','L');
        row[y].erase(Find1); line[Find1.first].erase(mk(y,Find1.second)); 
        line[x].erase(Find2); row[Find2.first].erase(mk(x,Find2.second));
        return;
    }
}
void get_start()
{
	for (int i=1;i<=n;++i) del[i]=false;
    for (int i=1;i<=n;++i)
    {
        int x1=A[i].first,y1=B[i].first,x2=C[i].first,y2=D[i].first;
        if (x1==x2) {recheck(x1,(y1+y2)>>1,i); continue;}
        if (y1==y2) {recheck((x1+x2)>>1,y1,i); continue;}
        recheck(x1,y2,i); recheck(x2,y1,i);
    }
}
inline void GotoCheck(int Id)
{
    int x1=A[Id].first,y1=B[Id].first,x2=C[Id].first,y2=D[Id].first;
    if (x1==x2) {recheck(x1,(y1+y2)>>1,Id); return;}
    if (y1==y2) {recheck((x1+x2)>>1,y1,Id); return;}
    recheck(x1,y2,Id); recheck(x2,y1,Id);
}
inline void Check(int x, int y)
{
    Pii Find;   
    Find=*(--row[y].lower_bound(mk(x,0)));   if (Find.second) GotoCheck(Find.second);
    Find=*(row[y].upper_bound(mk(x,maxn)));  if (Find.second) GotoCheck(Find.second);
    Find=*(--line[x].lower_bound(mk(y,0)));  if (Find.second) GotoCheck(Find.second);
    Find=*(line[x].upper_bound(mk(y,maxn))); if (Find.second) GotoCheck(Find.second);
}
void solve_2()
{
	clear();
	//for (int i=1;i<=r;++i) cout<<row[i].size()<<endl;
	get_start();
	while(!Q.empty())
    {
        int i=Q.front(); Q.pop();
        int x1=A[i].first,y1=B[i].first,x2=C[i].first,y2=D[i].first;
        Check(x1,y1);
        Check(x2,y2);
    }
    write_int(cnt); putchar('\n');
    for (int i=1;i<=cnt;++i) {Print(s[i].x,s[i].y,s[i].F1,s[i].F2); putchar('\n');}
}
int main()
{
	init();
	solve_1();
	solve_2();
	return 0;
}
