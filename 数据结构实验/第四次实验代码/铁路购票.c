#include <stdio.h>
#include <stdlib.h>

int main()
{
	int num[100];
	int i,flag,m;
	for(i=0;i<100;i++)
	{
		num[i] = 1;   //������λδ���� 
	}
	int length = 100;
	int n,j,k,t,count;
	scanf("%d",&n);
	int p[n];
	for(i=0;i<n;i++)
	{
		scanf("%d",&p[i]);
	}
	for(i=0;i<n;i++)
	{
		if(p[i] < 1 || p[i] > 5)
		{
			printf("���벻�Ϸ���һ�ι�Ʊֻ����1��5��,���������빺��Ʊ��");
			i--; 
		}
		else if(p[i]>length)
		{
			printf("��Ʊ���㣬ʣ��Ʊ��Ϊ��%d�ţ����������빺��Ʊ��");
			i--;
		}
		else 
		{
			flag = 0;
			for(j=0;j<20;j++) //�ж�ĳ���Ƿ������� 
			{
				k=0;
				while(k<6-p[i])  //ÿ�α���p[i]�����ŵ���λ��ÿ��Ҫ������ô��� 
					{
						for(t=0;t<p[i];t++)  //�ж��Ƿ�������p[i]����λΪ��
						{
							if(num[5*j+k+t] != 1)
							{
								flag = 0;
								break; 
							}
							flag = 1;
						}
						if(flag) //˵����ʱ��j+1�����������򣬲��ٱ���
						{
							break; 
						}
						k++;
					}
				if(flag)  //���������˳� 
				{
					break;
				}
			}
			if(flag)  //������ 
				{
					for(t=0;t<p[i];t++)
					{
						printf("%d ",5*j+k+t+1);
						num[5*j+k+t] = 0;   //��λ������ 
					}
					length -= p[i];
					printf("\n");
				}
			else   //û������ʣ�� 
			{
				for(m=0;m<100;m++)
				{
					count = 0;
					if(count<p[i])   //����p[i]��Ʊ 
						{
							if(num[m] == 1)
							{
								printf("%d ",m+1);
								num[m] = 0;  //������ 
								count++;
							}
						}
					else
					{
						length -= p[i];  //�ı�ʣ��Ʊ�� 
						printf("\n");
						break;
					} 
				} 
			}
		}
	}
	system("pause"); 
	return 0; 
}
