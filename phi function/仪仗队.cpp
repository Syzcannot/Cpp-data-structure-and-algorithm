#include<iostream>
int n,ans;
int phi[40010];
int main()
{
	std::cin>>n; 
	for (int i=2;i<n;ans+=phi[i++]) if (!phi[i])
	{
		phi[i]=i-1;
		for (int j=2;j<=n/i;++j)
		{
			if (!phi[i*j]) phi[i*j]=i*j;
			phi[i*j]=phi[i*j]/i*(i-1);
		}
	}
	std::cout<<ans*2+3<<std::endl;
}
