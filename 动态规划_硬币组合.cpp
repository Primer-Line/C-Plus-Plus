#include<stdio.h>
#include<stdlib.h>
int main()
{
	int n,*dp,i,k;
	printf("输入N:\n");
	scanf("%d",&n);
	if(n<0)exit(-1);
	dp=(int*)malloc((n+1)*sizeof(int));
	dp[0]=0;
	dp[1]=1;
	dp[2]=2;
	k=2;
	for(i=3;i<=n;i++)
	{
		//这个if语句是为了判断i+1的值是否是2的幂次方，如果是，那么dp[i]一定是1，因为所有能出现的数字已经出现过一次，不能再分解，如15 = 8 + 4 + 2 +1
		if(!(i&(i+1)))dp[i]=1;		
		else if(i==(k<<1))//k表示的是上一个2的幂次方
		{
			dp[i]=dp[k]+1;
			k=i;
		}
		else if(i>k&&i<(k<<1))//i是在上一个2的幂次方和下一个2的幂次方之间
		{
			if(i==(k+(k<<1))/2-1)dp[i]=2;// (8+16)/2-1=11
			else if(i==k+k/4-1||i==(k<<1)-k/4-1)dp[i]=3;
			else
			{
				if(!(i%2))dp[i]=dp[k];//偶数
				else dp[i]=dp[k]-1;//奇数
			}
		}
	}
	printf("%d\n",dp[n]);
	free(dp);
	return 0;
}
