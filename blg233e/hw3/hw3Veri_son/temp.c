#include <stdio.h>
void test(int j, int k)
{
	int x[4]={83,72,68,67};
	int i;
	for(i=0;i<4;i++)
		printf("%d ",4-(x[i]%j)%k);
	return;
}

int main()
{
	int x[4]={83,72,68,67};
	int y[4]={0,0,0,0};
	
	int i,j,k;
	
	for(i=2;i<=100;i++)
	{
		for(k=2;k<i;k++){
			for(j=0;j<4;j++)
				y[j]=(x[j]%i)%k;
			if(y[3]-y[2]==y[1]-y[0])
			printf("i:%d k:%d \t | %d %d %d %d \n",i,k,y[0],y[1],y[2],y[3]);
		}
	}
	printf("\n\n\n");
	test(23,10);
	return 0;
}

// 4-(x%23)%10
