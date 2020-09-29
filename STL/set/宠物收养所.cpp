#include<set>
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int MOD=1000000;
int n,flag,opt,x,ans;
set<int> S;
inline int Read() 
{
    int x=0,f=1; char ch=getchar(); 
    while (ch<'0'||ch>'9') {if (ch=='-') f=-f; ch=getchar();}
    while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
inline int abs(int x) {return x>0?x:-x;}
inline void update(int x) {x=abs(x)%MOD; ans=(ans+x)%MOD;}
int main()
{
	n=Read();
	for (int i=1;i<=n;++i)
	{
		int opt=Read(),x=Read();
		if ((!S.size())||(opt==flag)) {flag=opt; S.insert(x); continue;}
		set<int>::iterator p=S.lower_bound(x),q;
		if (p==S.begin()||p==S.end()) {if (p==S.end()) --p; update(*p-x); S.erase(*p);}
		else
		{
			q=p; q--;
			if (abs(*p-x)<abs(*q-x)) update(*p-x),S.erase(*p); else update(*q-x),S.erase(*q);
		}
	}
    printf("%d\n",ans);
    return 0;
}
