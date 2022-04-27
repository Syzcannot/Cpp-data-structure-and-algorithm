#include<bits/stdc++.h>
using namespace std;
int dp[1000005][20];
int n;
void work()
{
    int i,j;
    for(j=1;1<<j<=n;j++)
        for(i=1;i+(1<<j)-1<=n;i++)//i+(1<<j)-1<=n是为了保证区间左端点不超出总数n
            dp[i][j]=min(dp[i][j-1],dp[i+(1<<j-1)][j-1]);//实质是动态规划
}

int question(int a,int b)
{
    int x=int (log(b-a+1)/log(2));
    //注意y-z要加一才为区间长度
    return min(dp[a][x],dp[b-(1<<x)+1][x]);
    //分别以左右两个端点为基础，向区间内跳1<<x的最小/大值;
}
int main()
{
    cin>>n;//输入数据总数
    int i,a,b,k;
    for(i=1;i<=n;i++)
        cin>>dp[i][0];//数据输入加初始化，即从i开始向右走2的0次方的区间中的最大值，（注意i到i的长度为一）。
    work();//预处理
    cin>>k;//输入询问次数k
    for(i=1;i<=k;i++)
    {
        int a,b;
        cin>>a>>b;
        cout<<question(a,b)<<endl;
    }
    return 0;
}

