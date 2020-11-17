#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <stddef.h>
using namespace std;

#define Status int
#define OK 1
#define TRUE 1
#define ERROR 0
#define FALSE 0
#define OVERFLOW -1
typedef int ElemType;

typedef struct LNode
{
	ElemType data;
	struct LNode* next;
}LNode,*linklist;

Status InitList(linklist& L)
{
	L = (linklist)malloc(sizeof(LNode));
	if (!L)
		printf("�ռ����ʧ��");
	else
	{
		L->next = NULL;
		L->data = 0;
		printf("�������ɹ�\n");
	}
	return OK;
}
Status DestoryList(linklist& L)
{
	linklist p,tmp;
	if (!L)
	{
		printf("�ñ�����");
		return ERROR;
	}
	p = L->next;
	while (p)
	{
		tmp = p->next;
		free(p);
		p = tmp;
	}
	free(L);
	printf("���Ա�������\n");
	return OK;
}
Status ClearList(linklist& L)
{
	linklist p,q;
	if (!L)  
	{
		printf("�ñ�����");
		return ERROR;
	}
	p = L->next;
	q = p->next;
	L->next = NULL;
	while (p)
	{
		free(p);
		p = q;
		q = q->next;
	}
	free(p);
	printf("���Ա�������Ϊ�ձ�");
	return OK;
}
Status ListEmpty(linklist L)
{
	if (!L)
	{
		printf("�ñ�����");
		return ERROR;
	}
	if (NULL == L->next)
	{
		printf("���Ա��ǿձ�\n");
		return TRUE;
	}
	else
	{
		printf("���Ա��ǿձ�\n");
		return FALSE;
	}
}
Status ListLength(linklist L)
{
	if (!L)
	{
		printf("�ñ�����");
		return ERROR;
	}
	int length=0;
	linklist p;
	p = L->next;
	while (p)
	{
		length++;
		p = p->next;
	}
	return length;
}
Status GetElem(linklist L, int i, ElemType& e)
{
	if (!L)
	{
		printf("�ñ�����");
		return ERROR;
	}
	linklist p;
	p = L;
	if (i > ListLength(L) || i < 1)
	{
		printf("���벻�Ϸ�\n");
		return ERROR;
	}
	while (i != 0)
	{
		p = p->next;
		i--;
	}
	e = p->data;
	return OK;
}
Status LocateElem(linklist L, ElemType e)
{
	if (!L)
	{
		printf("�ñ�����");
		return ERROR;
	}
	linklist p;
	int i=0;
	p = L->next;
	while (p)
	{
		i++;
		if (p->data == e)
		{
			return i;
		}
		p = p->next;
	}
	return FALSE;
}
Status PriorElem(linklist L, ElemType cur_e, ElemType& pre_e)
{
	if (!L)
	{
		printf("�ñ�����");
		return ERROR;
	}
	linklist p,q;
	p = L->next;
	q = L;
	if (p->data == cur_e)
	{
		printf("��ǰԪ��Ϊ��λ����ǰ��\n");
		return FALSE;
	}
	else
	{
		while (p!=NULL)
		{
			if (p->data == cur_e)
			{
				pre_e = q->data;
				printf("��ǰ��Ϊ��%d\n", pre_e);
				return OK;
			}
			q = p;
			p = p->next;
		}
	}
	printf("��ǰԪ�ز���������\n");
	return FALSE;
}
Status NextElem(linklist L, ElemType cur_e, ElemType& next_e)
{
	if (!L)
	{
		printf("�ñ�����");
		return ERROR;
	}
	linklist p;
	p = L->next;
	while (p->next != NULL)
		p = p->next;  //�������һ��Ԫ��
	if (p->data == cur_e)
	{
		printf("��ǰԪ��Ϊĩλ���޺��\n");
		return FALSE;
	}
	p = L->next;
	while (p != NULL)
	{
		if (p->data == cur_e)
		{
			next_e = p->next->data;
			printf("����Ϊ��%d\n", next_e);
			return OK;
		}
		p = p->next;
	}
	printf("��ǰԪ�ز���������\n");
	return FALSE;
}
Status ListInsert(linklist& L, int i, ElemType e)
{
	if (!L)
	{
		printf("�ñ�����");
		return ERROR;
	}
	int j=0;
	linklist q,s;
	s = (linklist)malloc(sizeof(LNode));
	if (s == NULL) 
	{
		printf("�ռ����ʧ��\n");
		return ERROR;
	}
	s->data = e;    //�����µĽ��
	if (i<1 || i>ListLength(L) + 1)
	{
		printf("����Ԫ��λ��Խ�磬iֵ���Ϸ�\n");
		return ERROR;
	}
	else
	{
		q = L;
		j++;
		while (j != i)   //�ҵ�����λ��
		{
			q = q->next;
			j++;
		}
		s->next = q->next;
		q->next = s;
		return OK;
	}
}
Status ListDelete(linklist& L, int i, ElemType& e)
{
	if (!L)
	{
		printf("�ñ�����");
		return ERROR;
	}
	linklist p,q;
	int j = 1;
	if (i<1 || i>ListLength(L))
	{
		printf("ɾ��Ԫ��λ��Խ�磬iֵ���Ϸ�\n");
		return ERROR;
	}
	p = L;
	q = L->next;
	while (j != i) //Ѱ��ɾ��λ��
	{
		q = q->next;
		p = p->next;
		j++;
	}
	e = q->data;
	//printf("��ɾ��Ԫ��Ϊ��%d\n", e);
	p->next = q->next;
	free(q);
	return OK;
}
void visit(linklist L)
{
	if (!L)
	{
		printf("�ñ�����");
	}
	else
	{
		printf("%d ", L->data);  
	}
}
Status ListTraverse(linklist L)
{
	if (!L)
	{
		printf("�ñ�����");
		return ERROR;
	}
	linklist p;
	p = L->next;
	while (p)
	{
		visit(p);
		p = p->next;
	}
	printf("\n");
	return OK;
}
Status ListInverse(linklist &L)  //��������
{
	if (!L)
	{
		printf("�ñ�����");
		return ERROR;
	}
	linklist p,q,r;
	p = L->next;
	q = p->next;
	while (q)
	{
		r = L->next;
		
		p->next = q->next;
		q->next = r;L->next = q;
		q = p->next;
	}
	return OK;
}
Status ListInsertSort(linklist& L)  //������������
{
	if (!L)
	{
		printf("�ñ�����");
		return ERROR;
	}
	int n = ListLength(L);
	int i;
	linklist p, q, r;
	if (n > 1) 
	{
		p = L->next; // pһֱָ�����������еĲ��ֵ����һ��Ԫ��
		q = p->next; // q��ǰ������Ԫ��
		for (i = 1; i < n; i++)  // ����һ��Ԫ�ص�������ģ��ӵڶ�����ʼ
		{
			r = L;
			if (q->data < p->data)  // ��Ȳ���������֤������ȶ���
			{
				while (r != p)   // ���������򲿷ֵ�β������
				{
					if (q->data < r->next->data)// ��Ȳ���������֤������ȶ���
					{
						p->next = q->next;
						q->next = r->next;
						r->next = q;
						q = p->next;
						break;    // ����ȷ�������˳�ѭ��
					}
					r = r->next;
				}
			}
			else
			{
				p = q;
				q = q->next;
			}
		}
	}
	return OK;
}
Status List_Insection_Set(linklist& La, linklist& Lb, linklist& Lc)
{    //������Ľ���Ԫ��
	if (!La || !Lb || !Lc)
	{
		printf("������\n");
		return ERROR;
	}
	int i=0, t;
	ElemType e;
	linklist q = Lb->next;
	linklist p = La->next;
	linklist r = La;
	linklist temp;
	if (!p || !q)
	{
		printf("����Ϊ�ռ�\n");
		return ERROR;
	}
	while(p != NULL)  //�ӱ�A�б�������Ԫ�أ����ǽ���Ԫ�������ɾ��
	{
		i++;
		t = 0;
		while (q) //��ѯ��B��Ԫ��
		{
			if (p->data == q->data)   //�˴β�����Ԫ���ǽ���Ԫ��
			{
				t = 1;
				break;
			}
			else if (p->data > q->data)
			{
				q = q->next;
			}
			else
			{
				break;
			}
		}
		if (!t)
		{
			ListDelete(La, i, e); //���ǽ���Ԫ�أ�ɾ��
			i--;  //�´β�����Ԫ��λ�򲻱�
			p = r->next;
		}
		else
		{
			r = p;
			p = p->next;
		}
	}
	Lc = La;
	ListInsertSort(Lc);
	p = Lc->next;
	if(p)   //�ռ������ж��Ƿ�����ͬԪ��
	{ 
		q = p->next;
		while (q)
		{
			if (p->data == q->data)  //ɾ����ͬԪ��
			{
				p->next = q->next;
				temp = q;
				q = p->next;
				free(temp);
			}
			else
			{
				p = q;
				q = q->next;
			}
		}
	}
	if (ListLength(Lc) == 0)
	{
		printf("��A���B����Ϊ��\n");
	}
	else
	{
		printf("��A���B�Ľ���Ϊ��");
		ListTraverse(Lc);
	}
	return OK;
}
Status Listunion(linklist& La, linklist& Lb, linklist& Lc)
{
	int i, j;
	ElemType e;
	linklist temp;
	linklist p = La->next;
	linklist q = Lb->next; 
	linklist r = La;
	while (q)      //��b��Ԫ�ر���һ��
	{
		e = q->data;  //b��Ҫ�Ƚϵ�Ԫ��
		while (p)
		{
			if (e < p->data)   //e���ڱ�a��,��Ҫ����
			{
				temp = (linklist)malloc(sizeof(LNode));
				if (!temp)
				{
					printf("�洢�ռ����ʧ��");
						return ERROR;
				}
				temp->data = e;   //����B,�½����
				r->next = temp;
				temp->next = p;
				r = r->next;
				q = q->next;   //���ʱ�B����һ��Ԫ��
				break;
			}
			else if (e == p->data)    //��Ԫ����A��
			{
				q = q->next;
				break;
			}
			else
			{
				r = p;
				p = p->next;
			}
		}
		if (!p)  //Az��Ԫ���ѱ���������B��ʣ��Ԫ��ȫ������
		{
			temp = (linklist)malloc(sizeof(LNode));
			if (!temp)
			{
				printf("�洢�ռ����ʧ��");
				return ERROR;
			}
			temp->data = e;
			r->next = temp;
			temp->next = p;
			r = r->next;
			q = q->next;   //������һ��Ԫ��
		}
	}
	Lc = La;
	p = Lc->next;
	if (p)   //�ռ������ж��Ƿ�����ͬԪ��
	{
		q = p->next;
		while (q)
		{
			if (p->data == q->data)  //ɾ����ͬԪ��
			{
				p->next = q->next;
				temp = q;
				free(temp);
				q = p->next;
			}
			else
			{
				p = q;
				q = q->next;
			}
		}
	}
	if (ListLength(Lc) == 0)
	{
		printf("��A���B����Ϊ��\n");
	}
	else
	{
		printf("��A���B�Ĳ���Ϊ��");
		ListTraverse(Lc);
	}
	return OK;
}
int main()
{
	linklist L,La,Lb,Lc;
	ElemType e,cur_e,pre_e,next_e;
	int i,n;
	char ch;
	InitList(La);
	printf("�������AԪ�ظ�����");
	scanf_s("%d", &n);
	printf("��������������Ԫ�أ�");
	for (i = 1; i <= n; i++)
	{
		scanf_s("%d",&e);
		ListInsert(La, i, e);
	}
	InitList(Lb);
	printf("�������BԪ�ظ�����");
	scanf_s("%d", &n);
	printf("��������������Ԫ�أ�");
	for (i = 1; i <= n; i++)
	{
		scanf_s("%d", &e);
		ListInsert(Lb, i, e);
	}
	if (ListEmpty(La))
	{
		printf("��AΪ��\n");
	}
	if (ListEmpty(Lb))
	{
		printf("��BΪ��\n");
	}
	ListInsertSort(La);
	printf("�����ı�A����Ϊ��");
	ListTraverse(La);
	
	ListInsertSort(Lb);
	printf("�����ı�B����Ϊ��");
	ListTraverse(Lb);
	Listunion(La, Lb, Lc);
	//List_Insection_Set(La, Lb, Lc);
	/*ch = getchar();
	printf("�Ƿ���Ҫ�������Ա���y ��n��");
	if (getchar() == 'y')
	{
		ListInverse(L);
		printf("���ú�����Ա�Ϊ��");
		ListTraverse(L);
	}
	type = GetElem(L, i, e);

	printf("��������Ҫ��ѯ��ǰ��������Ԫ�أ�");
	scanf_s("%d", &cur_e);
	PriorElem(L, cur_e, pre_e);

	printf("��������Ҫ��ѯ���̵�����Ԫ�أ�");
	scanf_s("%d", &cur_e);
	NextElem(L, cur_e, next_e);
	
	ch = getchar(); //���߻�������\n
	printf("�Ƿ���Ҫɾ������Ԫ�أ���y ��n��");
	if (getchar() == 'y')
	{
		printf("������Ҫɾ��Ԫ�ص�λ��");
		scanf_s("%d", &i);
		ListDelete(L, i, e);
		printf("��ɾ����Ԫ��Ϊ��");
		printf("%d\n", (int)e);
		printf("ɾ��������Ա�Ϊ��");
		ListTraverse(L);
	}

	ch = getchar(); //���߻�������\n
	printf("�Ƿ���Ҫ��������Ԫ�أ���y ��n��");
	if (getchar() == 'y')
	{
		printf("������Ҫ�����Ԫ�أ�");
		scanf_s("%d", &e);
		printf("������Ҫ����Ԫ�ص�λ��");
		scanf_s("%d", &i);
		ListInsert(L, i, e);
		printf("���������Ա�Ϊ��");
		ListTraverse(L);
		DestoryList(L);
	}*/
	DestoryList(La);
	DestoryList(Lb);
	return OK;
}