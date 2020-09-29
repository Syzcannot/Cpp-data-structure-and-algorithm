#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int P=10007,MaxN=10010;
int T,n,m,inv[MaxN],fac[MaxN];
void Prepare()
{
	fac[0]=1;  
    for (int i=1;i<P;++i) fac[i]=fac[i-1]*i%P; 
    inv[0]=inv[1]=1;  
    for (int i=2;i<P;++i) inv[i]=(P-P/i)*inv[P%i]%P;    
    for (int i=2;i<P;++i) inv[i]=inv[i-1]*inv[i]%P;  
}
int Lucas(int n,int m) 
{
	if (n<m) return 0;
	if (n<P&&m<P) return fac[n]*inv[m]%P*inv[n-m]%P;  
    return Lucas(n%P,m%P)*Lucas(n/P,m/P)%P;
}
int main()
{
	Prepare();
	cin>>T;
	while (T--)
	{
		cin>>n>>m;
		cout<<Lucas(n,m)<<endl;
	}
	return 0;
}
