#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define List_Init_Size 100  //���Ա�洢�ռ�ĳ�ʼ������
#define List_Increment 10   //���Ա�洢�ռ�ķ�������
#define Status int
#define OK 1
#define TRUE 1
#define FALSE 0
#define OVERFLOW 0
#define ERROR 0
typedef int ElemType;   //Ԫ������
typedef struct {
	ElemType* elem;   //�洢�ռ��ַ
	int length;       //��ǰ����
	int listsize;     //��ǰ����Ĵ洢��������sizeof(ElemType)Ϊ��λ��
}SqList;

void visit(ElemType e)
{
	printf("%d ", e);
}
Status InitList_Sq(SqList &L)
{//����һ���յ����Ա�L
	L.elem = (ElemType*)malloc(List_Init_Size * sizeof(SqList));
	if (!L.elem) exit(OVERFLOW);  //�洢�ռ����ʧ��
	L.length = 0;
	L.listsize = List_Init_Size; //��ʼ��������
	return OK;
}
void DestroyList(SqList &L)
{
	free(L.elem);
}
void ClearList(SqList &L)
{
	memset(L.elem, 0, sizeof(ElemType)*L.length); 
	L.length = 0;
	
}
Status ListEmpty(SqList &L)
{
	if (L.length > 0)
		return FALSE;
	else
		return TRUE;
}
Status ListLength(SqList L)
{
	return L.length;
}
Status GetElem(SqList L,int i,ElemType &e)
{
	if (i > ListLength(L) || i < 1)
		return ERROR;
	else
	{
		e = L.elem[i-1];
		return OK;
	}
}
Status LocateElem(SqList L, ElemType e)
{
	int i, temp = FALSE;
	for (i = 1; i <= ListLength(L); i++)
	{
		if (L.elem[i - 1] == e)
		{
			temp = i;
			return temp;
		}
	}
	return FALSE;
}
Status PriorElem(SqList L, ElemType cur_e, ElemType &pre_e)
{
	int i;
	if (L.elem[0] == cur_e)
		{
			printf("��ǰԪ��Ϊ��λ����ǰ��\n");
			return ERROR;
		}
	for (i = 2; i <= ListLength(L); i++)
	{
		if (L.elem[i - 1] == cur_e)
		{
			pre_e = L.elem[i - 2];
			return OK;
		}
	}
	printf("�����ڵ�ǰԪ��\n");
	return FALSE;
}
Status NextElem(SqList L, ElemType cur_e, ElemType& next_e)
{
	int i;
	if (L.elem[ListLength(L) - 1] == cur_e)
	{
		printf("��ǰԪ��Ϊĩλ���޺��\n");
			return ERROR;
	}
	for (i = 1; i < ListLength(L); i++)
	{
		if (L.elem[i - 1] == cur_e)
		{
			next_e = L.elem[i];
			return OK;
		}
	}
	printf("�����ڵ�ǰԪ��\n");
	return ERROR;
}
Status ListInsert_Sq(SqList& L, int i, ElemType e)  
{
	ElemType* newbase, * q, * p;
	if (i<1 || i>ListLength(L)+1)
	{
		printf("iֵ���Ϸ�\n");
		return FALSE;
	}
	if (L.length > L.listsize)
	{
		printf("��ǰ����洢�ռ䲻�㣬���ӿռ�\n");
		newbase = (ElemType*)realloc(L.elem, (L.listsize + List_Increment) * sizeof(ElemType));
		if (!newbase) 
			exit(OVERFLOW); //�洢����ʧ��
		L.elem = newbase;  //�»�ַ
		L.listsize = L.listsize + List_Increment;  //���Ӵ洢����
	}
	q = &L.elem[i - 1];
	for (p = &(L.elem[L.length - 1]); p >= q; --p) * (p + 1) = *p;
	*q = e;
	++L.length;
	return OK;
}
Status ListDelete_Sq(SqList& L, int i, ElemType &e)         
{
	ElemType* p,*q;
	if ((i < 1) || (i > L.length))
	{
		printf("iֵ���Ϸ�\n");
		return FALSE;
	}
	p = &L.elem[i - 1];
	e = *p;
	for (q = p; q < &L.elem[L.length - 1]; ++q)
	{
		*q = *(q + 1);
	}
	L.length--;
	return OK;
}
Status ListTraverse(SqList L)    //ʵ��˳���Ԫ�صı���
{
	int i = 1;
	for (i; i <= L.length; i++)
	{
		visit(L.elem[i - 1]);
	}
	printf("\n");
	return OK;
}
Status ListInverse(SqList L)    //ʵ��˳���Ԫ�ؾ͵�����
{
	int i=0,n = L.length-1;
	ElemType temp;
	while (i < n)
	{
		temp = L.elem[i];
		L.elem[i] = L.elem[n];
		L.elem[n] = temp;
		++i;
		--n;
	}
	return OK;
}
Status ListInsertSort(SqList& L)   //��������  ����
{
	int n,i;
	n = ListLength(L);
	for (i = 1; i < n; i++)
	{
		if (L.elem[i] < L.elem[i - 1])  //��i��Ԫ�رȵ�i-1����Ļ����������
		{
			int j = i - 1;
			int value = L.elem[i];
			while (j > -1 && value < L.elem[j])   //��i-1��ʼ����Ѱ�Ҳ���λ��
			{
				L.elem[j + 1] = L.elem[j];
				j--;
			}
			L.elem[j + 1] = value; //�ҵ�Ҫ�����λ��֮�����
		}
	}
	return OK;
}
Status List_Intersection_Set(SqList& La, SqList& Lb, SqList& Lc)
{    //���Ľ���,���ɱ�C
	int i,t,j=0;
	ElemType e;
	for (i = 0; i < La.length; i++)
	{
		t = 0;
		while (j < Lb.length)  //t��¼��A��Ԫ���Ƿ���B��
		{
			if (La.elem[i] == Lb.elem[j])
			{
				t = 1;
				j++;
				break;
			}
			else if (La.elem[i] >= Lb.elem[j])
			{
				j++;
			}
			else
				break;
		}
		if (t == 0)  //˵����Ԫ�ز����ڱ�A��B������
		{
			ListDelete_Sq(La, i+1, e);
			i--;
		}
	}
	Lc = La;

	if (Lc.length != 0)
	{
		ListInsertSort(Lc);
		for (i = 0; i < Lc.length-1; i++)  //ɾ�������ظ���Ԫ��
		{
			if (Lc.elem[i] == Lc.elem[i + 1])
			{
				ListDelete_Sq(Lc, i + 1, e);
				i--;
			}
		}
		printf("��A��B�Ľ���CΪ��");
		ListTraverse(Lc);
		return OK;
	}
	else
	{
		printf("��A��B�Ľ���CΪ�ռ���");
		return FALSE;
	}
}
Status Listunion_Sq(SqList& La, SqList& Lb, SqList& Lc)
{  //���Ĳ�������A�Ŀռ���
	int i, j=0;
	int n = ListLength(Lb);
	ElemType e;
	for (i = 0; i < n; i++)
	{
		e = Lb.elem[i];    //�ó�b��Ԫ��
		while (j < La.length)
		{
			if (e < La.elem[j])    //˵����Ԫ�ز��ڱ�A��
			{
				ListInsert_Sq(La, j + 1, e);
				j++;
				break;
			}
			else if (e == La.elem[j])
			{
				j++;
				break;
			}
			else
			{
				j++;
			}
		}
		if (j >= La.length)    //A�ѱ���������ʣ��Ԫ��ȫ������
		{
			ListInsert_Sq(La, j + 1, e);
			j++;
		}
	}
	Lc = La;
	for (i = 0; i < Lc.length - 1; i++)  //ɾ�������ظ���Ԫ��
	{
		if (Lc.elem[i] == Lc.elem[i + 1])
		{
			ListDelete_Sq(Lc, i + 1, e);
			i--;
		}
	}
	printf("��A��B�Ĳ���CΪ��");
	ListTraverse(Lc);

	return OK;
}
int main()
{
	SqList L,La,Lb,Lc;
	int n,k,i;
	char ch;
	ElemType e;
	InitList_Sq(La);
	printf("�������A���ݸ���:");
	scanf_s("%d",&n);
	printf("����������ÿ�����ݣ��Կո����:");
	for (i = 1; i <= n; i++)
	{
		scanf_s("%d",&e);
		ListInsert_Sq(La, i, e);
	}
	InitList_Sq(Lb);
	printf("�������B���ݸ���:");
	scanf_s("%d", &k);
	printf("����������ÿ�����ݣ��Կո����:");
	for (i = 1; i <= k; i++)
	{
		scanf_s("%d", &e);
		ListInsert_Sq(Lb, i, e);
	}
	if (ListEmpty(La))
	{
		printf("��AΪ�ձ����˳�");
		return ERROR;
	}
	if (ListEmpty(Lb))
	{
		printf("��BΪ�ձ����˳�");
		return ERROR;
	}
	ListInsertSort(La);
	printf("�����ı�AΪ��");
	ListTraverse(La);
	ListInsertSort(Lb);
	printf("�����ı�BΪ��");
	ListTraverse(Lb);
	Listunion_Sq(La, Lb, Lc);
	//List_Intersection_Set(La, Lb, Lc);

	//ListInsertSort(L);   // ����������������
	//ListTraverse(L);
	
	//�������ú���
	/*ListInverse(L);
	printf("���ú�����Ա�Ϊ��");
	ListTraverse(L);*/

	/*ch = getchar(); //���߻�������\n
	printf("�Ƿ���Ҫɾ������Ԫ�أ���y ��n��");
	if (getchar() == 'y')
	{
		printf("������Ҫɾ��Ԫ�ص�λ��");
		scanf_s("%d",&i);
		ListDelete_Sq(La, i, e);
		printf("��ɾ����Ԫ��Ϊ��");
		printf("%d\n", (int)e);
		ListTraverse(La);
	}

	printf("�Ƿ���Ҫ��������Ԫ�أ���y ��n��");
	ch = getchar();
	if (getchar() == 'y')
	{
		printf("������Ҫ�����Ԫ�أ�");
		scanf_s("%d", &e);
		printf("������Ҫ����Ԫ�ص�λ��");
		scanf_s("%d", &i);
		ListInsert_Sq(L, i, e);
		ListTraverse(L);
	}*/
	return OK;
}