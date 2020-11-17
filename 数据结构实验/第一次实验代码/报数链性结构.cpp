#include <stdio.h>
#include <stdlib.h>

typedef struct person
{
	int num;  //�˵���Ϣ
	struct person* next;
}P,*L;
int main()
{
	L head,p,temp;
	int m, n,i;
	scanf_s("%d %d", &n, &m);
	if (m >= n || m <= 0 || n <= 0) //�ж������Ƿ�Ϸ�
	{
		printf("���벻�Ϸ�");
		return -1;
	}
	head = (L)malloc(sizeof(P));
	if (!head)
	{
		printf("�ռ����ʧ��");
		return - 1;
	}
	p = head;
	for (i = 0; i < n; i++)
	{
		temp = (L)malloc(sizeof(P));
		if (temp)   //����������ʼ��������Ϣ
		{
			temp->next = NULL;
			temp->num = i + 1;
			p->next = temp;
			p = temp;
		}
	}
	L q;
	p = head->next;
	q = head;
	int j = 1; //����
	while (head->next->next) //ʣ��һ���˵�ʱ�����ѭ��
	{
		if (j == m) //���� m ���˳��в�����������
		{
			q->next = p->next;
			printf("%d ", p->num);
			j = 0;
			p = q->next;
		}
		else  //��һλ����
		{
			q = p;
			p = p->next;
		}
		if (!p) //������β֮��ص�ͷ��
		{
			p = head->next;
			q = head;
		}
		j++;
	}
	printf("%d", head->next->num); //��ӡ���һ�˵���Ϣ
	return 0;
}