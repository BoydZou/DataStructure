#include <stdio.h>
# include<stdlib.h>

typedef struct student
{
	int num;
	struct student * next;
} ST,*st;
int main()
{
	int m,n,i,p,q;
	int k,t;
	st head,base,temp,P;
	scanf("%d",&n);
	scanf("%d",&m);
	head = (ST*)malloc(sizeof(ST));
	head->num = 0;
	head->next = NULL;
	temp = head;
	for(i=1;i<=n;i++)  //��ʼ�� 
	{
		base = (st)malloc(sizeof(ST));
		base->num = i;
		base->next = NULL;
		temp->next = base;
		temp = base;
	}
	int j; 
	for(t=0;t<m;t++)
	{
		k=1;
		temp = head;
		P = head->next;
		scanf("%d %d",&p,&q);
		while(P->num != p) //Pָ����Ҫ�ƶ���ͬѧλ�� ,tempָ����ǰ��һλͬѧ��λ�� 
		{
			temp = P;
			P = P->next;
			k++;
		}  
		temp->next = P->next;  //��Ҫ�ƶ���ͬѧ���� 
		if(q>0)          //����ƶ���qΪ�ƶ�λ�� 
		{
			for(i=0;i<q;i++)  //�ƶ����λ�� 
			{
				temp = temp->next; 
			}
			P->next = temp->next; //������� 
			temp->next = P; 
		}
		else if(q<0)     // ��ǰ�ƶ� 
		{
			temp = head;
			j = k + q;
			for(i=1;i<j;i++) // jΪ�ƶ����λ��  
			{
				temp = temp->next;
			}
			P->next = temp->next; //������� 
			temp->next = P;
		}
	}
	P = head->next;
	while(P)  
	{
		printf("%d ",P->num);
		P = P->next;
	}
	return 0;
} 
