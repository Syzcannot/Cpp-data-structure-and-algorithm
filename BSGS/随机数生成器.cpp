#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<map>
#define LL long long
using namespace std;
int T;
LL P,a,b,x1,t;
void Exgcd(LL a,LL b,LL &d,LL &x,LL &y)
{
    if(!b) {d=a; x=1,y=0;}
      else {Exgcd(b,a%b,d,y,x); y-=x*(a/b);}
}
inline LL Pow(LL a,LL b,LL P)
{
	a%=P; LL ans=1;
	while (b)
	{
		if (b&1) ans=ans*a%P;
		b>>=1; a=a*a%P;
	}
	return ans;
}
map<LL,int> mp;
inline LL Bsgs(LL a,LL b,LL P)
{
    a%=P;
	if (!a)
	{
		if (!b)return 1;
		return -1; 
	}
	LL m=sqrt(P)+1,inv=Pow(a,P-1-m,P),now=1;
	mp.clear();mp[1]=0;
	for(int i=1;i<m;++i)
	{
		now=now*a%P;
		if (!mp.count(now)) mp[now]=i;
	}
	for(int i=0;i<m;++i)
	{
		if (mp.count(b)) return i*m+mp[b];
        b=b*inv%P;
	}
	return -1;
}
inline LL calc1()
{
	LL x,y,d,z=(t-x1+P)%P;
	Exgcd(b,P,d,x,y);
	if (z%d) return -1;
	x=x*(z/d)%P;
	if (x<0) x+=P;
	return x+1;
}
inline LL calc2()
{
	LL c=Pow(a-1,P-2,P),A=(x1+b*c)%P,C=(t+b*c)%P,x,y,d;
	Exgcd(A,P,d,x,y);
	if (C%d) return -1;
	x=x*(C/d)%P;
	if (x<0) x+=P;
	LL ans=Bsgs(a,x,P);
	return ans==-1?ans:ans+1;
}
inline LL Solve()
{
	if (x1==t) return 1;
	if (a==0)
	{
		if (b==t) return 2;
		return -1;
	}
	if (a==1) return calc1(); else return calc2();
}
int main()
{
	cin>>T;
	while (T--)
	{
		cin>>P>>a>>b>>x1>>t;
		cout<<Solve()<<endl;
	}
	return 0;
}
