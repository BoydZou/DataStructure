#include<stdio.h>
typedef struct node
{
	int num;   //��ɫ 
	int flag;  //����õ�Ԫ�Ƿ����� 
}A;

int main()
{
	int n,m;
	int i,j;
	A a[30][30];
	scanf("%d %d",&n,&m); 
	for(i=0;i<n;i++)   //��ʼ�� 
	{
		for(j=0;j<m;j++)
		{
			scanf("%d",&(a[i][j].num));
			a[i][j].flag=0;
		}
	}    
	for(i=1;i<n;i++)   //�ж�һ�����̱�Ե�ĵ�0�к͵�m-1��������� 
	{
		if(a[i][0].num==a[i-1][0].num&&a[i][0].num==a[i+1][0].num)  //�жϵ�0�е�������������ӱ�� 
		{
			a[i][0].flag=1;
			a[i-1][0].flag=1;
			a[i+1][0].flag=1;
		}
		if(a[i][m-1].num==a[i-1][m-1].num&&a[i][m-1].num==a[i+1][m-1].num)  //�жϵ�m-1�е�������������ӱ�� 
		{
			a[i][m-1].flag=1;
			a[i-1][m-1].flag=1;
			a[i+1][m-1].flag=1;
		}
		
	}
	for(j=1;j<m;j++)   //�ж�һ�����̱�Ե�ĵ�0�к͵�n-1��������� 
	{
		if(a[0][j].num==a[0][j-1].num&&a[0][j].num==a[0][j+1].num)    //�жϵ�0�е�������������ӱ�� 
		{
			a[0][j].flag=1;
			a[0][j-1].flag=1;
			a[0][j+1].flag=1;
		}
		if(a[n-1][j].num==a[n-1][j-1].num&&a[n-1][j].num==a[n-1][j+1].num)  //�жϵ�n-1�е�������������ӱ�� 
		{
			a[n-1][j].flag=1;
			a[n-1][j-1].flag=1;
			a[n-1][j+1].flag=1;
		}
	} 
	 
	
	
	for(i=1;i<n-1;i++)   //�ж������м��������� 
	{
		for(j=1;j<m-1;j++)
		{
			if(a[i][j].num==a[i][j-1].num && a[i][j].num==a[i][j+1].num)
			{
				a[i][j].flag=1;
				a[i][j-1].flag=1;
				a[i][j+1].flag=1;
			}
			if(a[i][j].num==a[i-1][j].num && a[i][j].num==a[i+1][j].num)
			{
				a[i][j].flag=1;
				a[i-1][j].flag=1;
				a[i+1][j].flag=1;
				
		    }  
		}
	}
	for(i=0;i<n;i++)   //��������ǵ����� 
	{
		for(j=0;j<m;j++)
		{
			if(a[i][j].flag)
			  a[i][j].num=0;
		}
	}
	
	
	for(i=0;i<n;i++)   //������ 
	{
		for(j=0;j<m;j++)
		{
			printf("%d ",a[i][j].num);
		}
		printf("\n");
	}
	
	return 0;
 } 
