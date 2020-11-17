// ADT Stack ��������9������˳��洢�ṹʵ��
//����ջ����ʵ�ְ˻ʺ��������
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
using namespace std;
#define Stack_Init_Size  200
#define STACKINCREMENT   40
#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OVERFLOW 0
#define N 4
typedef int Status;
typedef int SElemType;
typedef struct
{
	SElemType* base;   // ջ��ָ��
	SElemType* top;    // ջ��ָ��
	int stacksize;    //��ǰ�ѷ���Ĵ洢�ռ䣬��SElemTypeΪ��λ
}SqStack;

Status InitStack(SqStack& S)  //����һ����ջ
{
	S.base = (SElemType*)malloc(Stack_Init_Size * sizeof(SqStack));
	if (!S.base)
	{
		printf("�洢�ռ����ʧ��");
		exit(OVERFLOW);
	}
	S.top = S.base;
	S.stacksize = Stack_Init_Size;
	printf("ջ��ʼ���ɹ�\n");
	return OK;
}
Status DestroyStack(SqStack& S)
{
	free(S.base);
	printf("ջ������");
	return OK;
}
Status ClearStack(SqStack& S)
{
	S.top = S.base;
	return OK;
}
Status StackEmpty(SqStack S)
{
	if (S.base == S.top)
		return TRUE;
	else
		return FALSE;
}
Status StackLength(SqStack S)
{
	int length;
	length = S.top - S.base;
	return length;
}
Status GetTop(SqStack S, SElemType& e)  //��ջ������e����ջ��Ԫ��
{
	if (S.base == S.top)
	{
		printf("��ջΪ��");
		return ERROR;
	}
	else
	{
		e = *(S.top - 1);
		return OK;
	}
}
Status Push(SqStack& S, SElemType e)    //����eΪ�µ�ջ��Ԫ��
{
	SElemType* newbase;
	if (S.top -S.base >= S.stacksize)
	{
		printf("�洢�ռ䲻�㣬�����ӷ���");
		newbase = (SElemType*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!newbase)
		{
			printf("�洢����ʧ��");
			exit(OVERFLOW);
		}
		S.base = newbase;
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top = e;
	S.top++;
	return OK;
}
Status Pop(SqStack& S, SElemType& e)
{
	if (S.top == S.base)
	{
		printf("��ջΪ��");
		return ERROR;
	}
	e = *(S.top-1);
	S.top--;
	return OK;
}
void visit(SElemType* p)
{
	if (p)
	{
		printf("%d ", *p);
	}
	else
	{
		printf("����ʧ��");
	}
}
Status StackTraverse(SqStack S)
{
	SElemType* p;
	for (p = S.base; p < S.top; p++)
	{
		visit(p);
	}
	printf("\n");
	return OK;
}
Status place(SqStack S)
{//�����жϻʺ�λ���Ƿ�Ϸ�
	int i, j;
	SElemType* p, * q;
	SElemType e;
	j = S.top - S.base - 1;      //ջ���ʺ���������
	GetTop(S, e);   //���ջ��Ԫ��
	for (p = S.base; p < S.top - 1; p++)
	{
		i = p - S.base;
		if (e == *p)
		{  //˵�����ڻʺ���ͬһ��
			return FALSE;
		}
		else if (((e - *p) == (j - i)) || ((e - *p) == (i - j)))
		{   //˵�����ֻʺ�λ�ڶԽ��߲��Ϸ����
			return FALSE;
		}
	}
	return TRUE;
}
void NQeens(SqStack S)
{  //���N�ʺ����⣬�ǵݹ�
	ClearStack(S);    //���ջ
	SElemType e = 1;
	SElemType a[N];
	for (int i = 0; i < N; i++)
	{
		a[i] = 1;
	}
	int  n = 0, count = 0;    //n����0-7��
	while (a[0] < N+1)
	{
		Push(S, a[n]);       // nΪ��ǰ����������
		if (place(S))
		{   // ˵���ʺ�λ�úϷ�
			n++;        // �´�ѹ����һ��
		}
		else
		{   // ˵���ʺ�λ�ò��Ϸ�
			Pop(S, a[n]);
			a[n]++;
			while(a[n] > N && n > 0)
			{    //��n�е�8��λ����ȫ���Ź��ʺ���ı���һ�лʺ�λ��
				a[n] = 1;
				n--;
				Pop(S, a[n]);
				a[n]++;
			}
		}
		if (n == N)
		{   //�˸��ʺ���ȫ���ں�
			count++;
			StackTraverse(S);
			n--;   //�ص����һ��
			Pop(S, a[n]);
			a[n]++;
			while (a[n] > N && n > 0)
			{    //��n�е�N��λ����ȫ���Ź��ʺ���ı���һ�лʺ�λ��
				a[n] = 1;
				n--;
				Pop(S, a[n]);
				a[n]++;
			}
		}
	}
	printf("%d�ʺ�����⹲�� %d ��\n", N, count);
}
Status main()
{
	SqStack S;
	int n, i;
	SElemType e,t;
	InitStack(S);
	NQeens(S);    // ����N�ʺ�������⺯��

	printf("������ջ��ʼԪ�ظ�����");
	scanf_s("%d", &n);
	printf("�������������Ԫ�أ��ո������");
	for (i = 0; i < n; i++)
	{
		scanf_s("%d", &e);
		Push(S, e);
	}
	//ClearStack(S);
	//Pop(S, e);
	StackTraverse(S);

	//printf("��������Ҫѹջ��Ԫ�أ�");
	//scanf_s("%d", &e);
	//Push(S, e);
	//StackTraverse(S);
	//Pop(S, t);
	//printf("��ջԪ��Ϊ��%d\n", t);
	//StackTraverse(S);
	//printf("%d",StackLength(S));
	//DestroyStack(S);
	return OK;
}