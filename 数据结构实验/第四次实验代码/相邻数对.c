#include <stdio.h>
#include <stdlib.h>
int main()
{
	int n,i,count=0,j,value;
	int *a;
	scanf("%d",&n);
	a = (int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(i=1;i<n;i++)   //��������Ϊ����ʱ�临�Ӷȿɲ��ÿ��� 
	{
		if(a[i] < a[i-1])
		{
			j = i-1;
			value = a[i];
			while(j >= 0 && value < a [j])
			{
				a[j+1] = a[j];
				j--;
			}
			a[j+1] = value; 
		}
	} 
	for(i=0;i<n-1;i++)
	{
		if((a[i+1] - a[i]) == 1)  //˵��Ϊ��������
		{
			count++;
			printf("(%d,%d)\n",a[i],a[i+1]); 
		
		} 
	}
	printf("%d",count);
	return 0;
} 
