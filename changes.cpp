#include<iostream>
#include<vector>

#define INF 10000000;

using namespace std;


int changes(int a[],int len,int value)
{
	int **dp=new int*[len+1];
	for(int i=0;i<=len;++i)
		dp[i]=new int[value+1];

	for(int i=1;i<=len;++i)
		dp[i][0]=0;

	for(int j=1;j<=value;++j)
		dp[0][j]=INF;

	for(int i=1;i<=len;++i)
		for(int j=1;j<=value;++j)
		{
			if(a[i]>j)
				dp[i][j]=dp[i-1][j];
			else
			{
				dp[i][j] = dp[i][j-a[i]]+1 < dp[i-1][j] ? dp[i][j-a[i]]+1 : dp[i-1][j];
			}
		}

	int result=dp[len][value];

	for(int i=0;i<=len;++i)
		delete dp[i];
	delete[] dp;

	return result;
}

int Changes(int change[],int len,int value)
{
	int *dp=new int[value+1]();
	for(int i=0;i<value+1;++i)
		dp[i]=INF;
	dp[0]=0;

	for(int i=1;i<=len;++i)
		for(int j=change[i];j<=value;++j)
		{
		//	dp[0]=1;
		//		if(j>change[i])
				dp[j]=dp[j-change[i]]+1 < dp[j] ? dp[j-change[i]]+1 : dp[j];
		}
	
	int result=dp[value];
	delete[] dp;
	return result;
}
int main()
{
	int a[]={0,1,5,10,25};
	int len=sizeof(a)/sizeof(a[0]);

	cout<<Changes(a,len,50)<<endl;

}


