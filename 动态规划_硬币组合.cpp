#include<stdio.h>
#include<stdlib.h>
int main()
{
	int n,*dp,i,k;
	printf("����N:\n");
	scanf("%d",&n);
	if(n<0)exit(-1);
	dp=(int*)malloc((n+1)*sizeof(int));
	dp[0]=0;
	dp[1]=1;
	dp[2]=2;
	k=2;
	for(i=3;i<=n;i++)
	{
		//���if�����Ϊ���ж�i+1��ֵ�Ƿ���2���ݴη�������ǣ���ôdp[i]һ����1����Ϊ�����ܳ��ֵ������Ѿ����ֹ�һ�Σ������ٷֽ⣬��15 = 8 + 4 + 2 +1
		if(!(i&(i+1)))dp[i]=1;		
		else if(i==(k<<1))//k��ʾ������һ��2���ݴη�
		{
			dp[i]=dp[k]+1;
			k=i;
		}
		else if(i>k&&i<(k<<1))//i������һ��2���ݴη�����һ��2���ݴη�֮��
		{
			if(i==(k+(k<<1))/2-1)dp[i]=2;// (8+16)/2-1=11
			else if(i==k+k/4-1||i==(k<<1)-k/4-1)dp[i]=3;
			else
			{
				if(!(i%2))dp[i]=dp[k];//ż��
				else dp[i]=dp[k]-1;//����
			}
		}
	}
	printf("%d\n",dp[n]);
	return 0;
}