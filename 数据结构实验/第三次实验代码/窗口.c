#include <stdio.h>
#include <stdlib.h>
typedef struct win
{
	int x1;
	int y1;
	int x2;
	int y2;
	int num;
	struct win * next;
}WIN,*p;
struct point
{
	int x;
	int y;
};
int main ()
{
	p head,t,s,r;
	int N,M,i,x,y,IN;
	head = (p)malloc(sizeof(WIN));
	head->next = NULL;
	head->x1 = 0;
	head->x2 = 0;
	head->y1 = 0;
	head->y2 = 0;
	head->num = 0;
	scanf("%d %d",&N,&M);
	for(i=0;i<N;i++)  //��ʼ��������ĸ�����ͷ�ڵ� 
	{
		s = (p)malloc(sizeof(WIN));
		scanf("%d %d %d %d",&(s->x1),&(s->y1),&(s->x2),&(s->y2));
		s->num = i+1;
		s->next = head->next;
		head->next = s;
	}
	t = head->next;
	r = head;
	struct point B[M];
	for(i=0;i<M;i++)
	{
		scanf("%d %d",&B[i].x,&B[i].y);
	}
	for(i=0;i<M;i++)
	{
		IN = (B[i].x >= t->x1 && B[i].x <= t->x2 && B[i].y >= t->y1 && B[i].y <= t->y2) ? 1 : 0;  //�ж��Ƿ����ڵ�ǰ���� 
		while(t!=NULL && !IN)  //δ���ڵ�ǰ�����������ѭ�� 
		{
			r = t;
			t = t->next;
			if(t!=NULL)
			{
				IN = (B[i].x >= t->x1 && B[i].x <= t->x2 && B[i].y >= t->y1 && B[i].y <= t->y2) ? 1 : 0;////�ж��Ƿ����ڵ�ǰ����  
			}
		}
		if(!t)
		{	
			printf("IGNORED\n"); 
		}
		else 
		{
			printf("%d\n",t->num);
			r->next = t->next;
			t->next = head->next;   //�ı䴰�ڲ��� 
			head->next = t;
		}
		t = head->next;
		r = head;
	}
	return 0;
} 
