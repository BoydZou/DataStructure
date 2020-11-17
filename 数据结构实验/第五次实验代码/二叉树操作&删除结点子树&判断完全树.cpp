#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OVERFLOW 0
#define Stack_Init_Size  200
#define STACKINCREMENT   40
typedef int Status;
typedef char BiElemType;
typedef struct BNode
{
	BiElemType value;
	struct BNode* lchild, * rchild;    //���Һ���ָ��
}BiTNode, * BiTree;
typedef BiTree SElemType;
typedef BiTree QElemType;
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
	return OK;
}
Status DestroyStack(SqStack& S)
{
	free(S.base);
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
	if (S.top - S.base >= S.stacksize)
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
	e = *(S.top - 1);
	S.top--;
	return OK;
}
void Svisit(SElemType* p)
{
	if (p)
	{
		printf("%c ", (*p)->value);
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
		Svisit(p);
	}
	printf("\n");
	return OK;
}
typedef struct QNode
{
	QElemType data;
	struct QNode* next;
}QNode, * QueuePtr;
typedef struct
{
	QueuePtr front;   //��ͷָ��
	QueuePtr rear;    //��βָ��
}LinkQueue;

Status Qvisit(QueuePtr p)
{
	if (p)
	{
		printf("%c ", (p->data)->value);
	}
	return OK;
}
Status InitQueue(LinkQueue& Q)
{ // ����һ���ն���Q
	Q.front = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front)
	{
		printf("�ռ����ʧ��");
		exit(OVERFLOW);
	}
	Q.rear = Q.front;
	Q.front->next = NULL;
	return OK;
}
Status DestroyQueue(LinkQueue& Q)
{
	while (Q.front)
	{
		Q.rear = Q.front;
		Q.front = Q.front->next;
		free(Q.rear);
	}
	return OK;
}
Status ClearQueue(LinkQueue& Q)
{
	QueuePtr temp;
	Q.rear = Q.front->next;
	Q.front->next = NULL;
	while (Q.rear)
	{
		temp = Q.rear;
		Q.rear = Q.rear->next;
		free(temp);
	}
	Q.rear = Q.front;
	return OK;
}
Status QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)  //����Ϊ��
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
int QueueLength(LinkQueue Q)
{
	int i = 0;
	QueuePtr p = Q.front;
	while (p != Q.rear)
	{
		i++;
		p = p->next;
	}
	return i;
}
Status GetHead(LinkQueue Q, QElemType& e)
{ //��e����Q�Ķ�ͷԪ��
	if (Q.front == Q.rear)
	{
		printf("�ö���Ϊ��");
		return ERROR;
	}
	else
	{
		e = Q.front->data;
		return OK;
	}
}
Status EnQueue(LinkQueue& Q, QElemType e)
{ //����Ԫ��eΪQ���¶�βԪ��
	QueuePtr s;
	s = (QueuePtr)malloc(sizeof(QNode));
	if (!s)  //�ռ����ʧ��
	{
		printf("�ռ����ʧ��");
		exit(OVERFLOW);
	}
	s->next = NULL;
	s->data = e;
	Q.rear->next = s;
	Q.rear = s;
	return OK;
}
Status DeQueue(LinkQueue& Q, QElemType& e)
{
	QueuePtr p;
	if (Q.front == Q.rear)
	{
		printf("�ö���Ϊ��");
		return ERROR;
	}
	p = Q.front;
	Q.front = Q.front->next;
	e = Q.front->data;
	free(p);
	return OK;
}
Status QueueTraverse(LinkQueue Q)
{
	if (!Q.front || !Q.rear)
	{
		printf("�ö��в�����");
		return ERROR;
	}
	QueuePtr p;
	if (Q.front == Q.rear)
	{
		printf("�ö���Ϊ��");
		return ERROR;
	}
	else
	{
		p = Q.front->next;
		while (p)
		{
			Qvisit(p);
			p = p->next;
		}
		printf("\n");
		return OK;
	}
}

Status Bivisit(BiTree T)
{
	if (T)
	{
		printf("%c ", T->value);
	}
	return OK;
}
Status InitTree(BiTree& T)
{   //�������
	T = NULL;
	return OK;
}
Status DestroyBiTree(BiTree& T)
{
	if (T)
	{
		DestroyBiTree(T->lchild);
		DestroyBiTree(T->rchild);
		free(T);
	}
	return OK;
}
Status CreatBiTree(BiTree& T)
{    //�����������������
	BiElemType ch;
	//BiTree head;        //head����init���������ɵ�ͷ�ڵ�
	BiTree s;
	ch = getchar();
	if (ch == '\0')
	{     //����
		return OK;
	}
	if (ch == ' ')
	{  //����
		T = NULL;
		return OK;
	}
	else
	{
		T = (BiTree)malloc(sizeof(BiTNode));
		if (!T)
		{
			printf("�洢�ռ����ʧ�ܣ�");
			exit(OVERFLOW);
		}
		else
		{
			T->value = ch;                   //���ɸ��ڵ�
			CreatBiTree(T->lchild);         //����������
			CreatBiTree(T->rchild);         //����������
		}
		return OK;
	}
}
Status BiTreeEmpty(BiTree T)
{
	if (!T)
	{
		printf("����Ϊ��");
		return TRUE;
	}
	else
	{
		printf("�����ǿ�");
		return FALSE;
	}
}
Status PreOrderTraverse(BiTree T)
{  //�ǵݹ��������
	SqStack S;
	InitStack(S);
	BiTree p;
	if (T == NULL)
	{
		printf("����Ϊ��");
		return ERROR;
	}
	p = T;
	printf("��������Ľ��Ϊ��");
	while (p || !StackEmpty(S))
	{
		if (p)
		{
			Push(S, p);
			Bivisit(p);
			p = p->lchild;
		}
		else
		{
			Pop(S, p);
			p = p->rchild;
		}
	}
	printf("\n");
	DestroyStack(S);
	return OK;
}
Status InOrderTraverse(BiTree T)
{ //�ǵݹ��������
	SqStack S;
	InitStack(S);
	BiTree p;
	if (T == NULL)
	{
		printf("����Ϊ��");
		return ERROR;
	}
	p = T;
	printf("��������Ľ��Ϊ��");
	while (p != NULL || !StackEmpty(S))
	{
		if (p)
		{   //����������
			Push(S, p);
			p = p->lchild;
		}
		else
		{
			Pop(S, p);
			Bivisit(p);
			p = p->rchild;
		}
	}
	DestroyStack(S);
	printf("\n");
	return OK;
}
Status PostOrderTraverse(BiTree T)
{  //�ǵݹ�������
	//����1�����üӱ��
	SqStack S,D;
	InitStack(S); 
	InitStack(D);
	BiTree p;
	if (T == NULL)
	{
		printf("����Ϊ��");
		return ERROR;
	}
	p = T;
	printf("��������Ľ��Ϊ��");
	while (p || !StackEmpty(S))
	{
		if (p)
		{
			Push(S, p);
			Push(D, p);
			p = p->rchild;
		}
		else
		{
			Pop(S, p);
			p = p->lchild;
		}
	}
	while (!StackEmpty(D))
	{
		Pop(D, p);
		printf("%c ", p->value);
	}
	printf("\n");
	return OK;
}
Status LevelOrderTraverse(BiTree T)
{//�ǵݹ�������
	LinkQueue Q;
	BiTree p;
	InitQueue(Q);
	if (T == NULL)
	{
		printf("����Ϊ��");
		return ERROR;
	}
	p = T;
	printf("��������Ľ��Ϊ��");
	EnQueue(Q, p);   //���ڵ����
	while (!QueueEmpty(Q))
	{    
		DeQueue(Q, p);
		printf("%c ", p->value);
		if (p->lchild)
		{
			EnQueue(Q, p->lchild);        //����Ӳ�Ϊ�գ�����ӽ���
		}
		if (p->rchild)
		{
			EnQueue(Q, p->rchild);          //�Ҷ��Ӳ�Ϊ�գ��Ҷ��ӽ���
		}
	}
	printf("\n");
	return OK;
}
Status BiTreeDepth(BiTree T)
{//�ǵݹ����������,���ò������
	
	if (T == NULL)
	{
		return 0;
	}
	BiTree p;
	int depth = 0;
	int len = 0;          //������¼ÿ��ڵ���
	LinkQueue Q;
	InitQueue(Q);
	p = T;
	EnQueue(Q, p);
	while (!QueueEmpty(Q))
	{
		depth++;
		len = QueueLength(Q);
		while (len--)
		{
			DeQueue(Q, p);
			if (p->lchild)
			{
				EnQueue(Q, p->lchild);
			}
			if (p->rchild)
			{
				EnQueue(Q, p->rchild);
			}
		}
	}
	return depth;
}
Status ClearBiTree(BiTree& T)
{
	if (T == NULL)
	{
		return OK;
	}
	ClearBiTree(T->lchild);
	ClearBiTree(T->rchild);
	free(T);
	return OK;
}
Status Root(BiTree T)
{
	if (T)
	{
		printf("�������ĸ�Ϊ��%c\n",T->value);
		return T->value;
	}
	else
	{
		printf("����Ϊ������");
		return OK;
	}
}
Status Value(BiTree T, BiTree e)
{
	printf("����ֵΪ��%d\n", e->value);
	return e->value;
}
Status Assign(BiTree& T, BiTree& e, BiElemType value)
{
	e->value = value;
	return OK;
}
BiTree Parent(BiTree T, BiElemType e)
{
	if (e == T->value)
	{
		printf("�ý��Ϊ��������˫��\n");
		return NULL;
	}
	else
	{
		BiTree p;
		p = T;
		SqStack S;
		InitStack(S);
		while (!StackEmpty(S) || p)
		{
			if (p)
			{
				if ((p->lchild != NULL) && (p->lchild->value == e))
				{
					printf("����˫�׽��Ϊ��%c\n", p->value);
					return p;
				}
				else if ((p->rchild != NULL) && (p->rchild->value == e))
				{
					printf("����˫�׽��Ϊ��%c\n", p->value);
					return p;
				}
				Push(S, p);
				p = p->lchild;
			}
			else
			{
				Pop(S, p);
				p = p->rchild;
			}
		}
	}
	printf("�ý�㲻�����н��\n");
	return NULL;
}
BiTree LeftChild(BiTree T, BiElemType e)
{
	SqStack S;
	BiTree p;
	if (T == NULL)
	{
		printf("��Ϊ��\n");
		return NULL;
	}
	else
	{
		InitStack(S);
		p = T;
		while (!StackEmpty(S) || p)
		{
			if (p)
			{
				if (p->value == e)
				{//�����ҵ��ý��
					if (p->lchild)
					{
						printf("���%c������Ϊ%c\n", e, p->lchild->value);
						return p->lchild;
					}
					else
					{
						printf("���%c������", e);
						return NULL;
					}
				}
				Push(S, p);
				p = p->lchild;
			}
			else
			{
				Pop(S, p);
				p->rchild;
			}
		}
	}
	printf("���%c��������\n", e);
}
BiTree RightChild(BiTree T, BiElemType e)
{
	SqStack S;
	BiTree p;
	if (T == NULL)
	{
		printf("��Ϊ��\n");
		return NULL;
	}
	else
	{
		InitStack(S);
		p = T;
		while (!StackEmpty(S) || p)
		{
			if (p)
			{
				if (p->value == e)
				{//�����ҵ��ý��
					if (p->rchild)
					{
						printf("���%c���Һ���Ϊ%c\n", e, p->rchild->value);
						return p->rchild;
					}
					else
					{
						printf("���%c���Һ���", e);
						return NULL;
					}
				}
				Push(S, p);
				p = p->lchild;
			}
			else
			{
				Pop(S, p);
				p->rchild;
			}
		}
	}
	printf("���%c��������\n", e);
}
BiTree LeftSibling(BiTree T, BiElemType e)
{
	SqStack S;
	BiTree p;
	p = T;
	if (T == NULL)
	{
		printf("����Ϊ�������ý�������ֵ�\n");
		return NULL;
	}
	else if(T->value == e)
	{
		printf("�ý��Ϊ���������ֵ�\n");
		return NULL;
	}
	InitStack(S);
	while (p || !StackEmpty(S))
	{
		if (p)
		{
			if ((p->rchild != NULL) && (e == p->rchild->value))
			{//���eΪ��T�Һ��ӣ��ж����Ƿ������ֵ�
				if (p->lchild)
				{
					printf("�ý������ֵ�Ϊ��%c\n", p->lchild->value);
					DestroyStack(S);
					return p->lchild;
				}
				else
				{
					printf("�ý�������ֵ�\n");
					DestroyStack(S);
					return NULL;
				}
			}
			if ((p->lchild != NULL) && e == p->lchild->value)
			{//���Ϊ��T����
				printf("�ý��Ϊ��T�����ӣ������ֵ�\n");
				DestroyStack(S);
				return NULL;
			}
			Push(S, p);
			p = p->lchild;
		}
		else
		{
			Pop(S, p);
			p = p->rchild;
		}
	}
	printf("���%c��������\n", e);
	DestroyStack(S);
	return NULL;
}
BiTree RightSibling(BiTree T, BiElemType e)
{
	SqStack S;
	InitStack(S);
	if (T == NULL)
	{
		printf("����Ϊ��,�����ֵ�\n");
		return NULL;
	}
	else if (T->value == e)
	{
		printf("�ý��Ϊ�����������ֵ�\n");
		return NULL;
	}
	BiTree p;
	p = T;
	while (p || !StackEmpty(S))
	{
		if (p)
		{
			if ((p->lchild !=NULL) && (p->lchild->value == e))
			{//eΪT������,���ж����Ƿ������ֵ�
				if (p->rchild)
				{
					printf("�ý������ֵ�Ϊ��%c\n", p->rchild->value);
					return p->rchild;
				}
				else
				{
					printf("�ý�������ֵ�\n");
					return NULL;
				}
			}
			else if ((p->rchild != NULL) && (p->rchild->value == e))
			{
				printf("�ý��Ϊ��T���Һ��ӣ������ֵ�\n");
				return NULL;
			}
			Push(S, p);
			p = p->lchild;
		}
		else
		{
			Pop(S, p);
			p = p->rchild;
		}
	}
	printf("���%c��������\n", e);
	return NULL;
}
Status InsertChild(BiTree &T, BiTree e, int LR, BiTree c)
{
	if (LR != 0 && LR != 1)
	{
		printf("LR��ʽ����ֻ�ܲ���Ϊ��������������������\n");
		return ERROR;
	}
	BiTree temp;
	if (T == NULL)
	{
		printf("��TΪ�������޷�����\n");
		return FALSE;
	}
	if (c == NULL)
	{
		printf("���������Ϊ�գ��������\n");
		return FALSE;
	}
	if (LR == 1)
	{//����������
		temp = e->rchild;
		e->rchild = c;
		c->rchild = temp;
		printf("�����������ɹ�\n");
		return OK;
	}
	else if(LR == 0)
	{//����������
		temp = e->lchild;
		e->lchild = c;
		c->rchild = temp;
		printf("�����������ɹ�\n");
		return OK;
	}
}
Status DeleteChild(BiTree& T, BiTree e, int LR)
{
	if (LR != 0 && LR != 1)
	{
		printf("LR��ʽ����ֻ��ɾ����������������������\n");
		return ERROR;
	}
	if (T == NULL)
	{
		printf("��TΪ�������޷�ɾ��\n");
		return FALSE;
	}
	
	if (LR == 1)
	{//ɾ��������
		DestroyBiTree(e->rchild);
		e->rchild = NULL;   //����Ұָ��
		printf("ɾ���������ɹ�\n");
		return OK;
	}
	else if (LR == 0)
	{//ɾ��������
		DestroyBiTree(e->lchild);
		e->lchild = NULL;
		printf("ɾ���������ɹ�\n");
		return OK;
	}
}
Status Delete_x_Child(BiTree& T, BiElemType e)
{
	SqStack S;
	BiTree p;
	if (T == NULL)
	{
		printf("����Ϊ�������޷�ɾ������\n");
		return FALSE;
	}
	InitStack(S);
	p = T;
	while (p || !StackEmpty(S))
	{
		if (p)
		{
			if (p->value == e)
			{  //�ҵ����eɾ��������
				DestroyBiTree(p->lchild);
				DestroyBiTree(p->rchild);
				p->rchild = NULL;
				p->lchild = NULL;
				printf("���%c��������ɾ��\n",p->value);
				DestroyStack(S);
				return OK;
			}
			Push(S, p);
			p = p->lchild;
		}
		else
		{
			Pop(S, p);
			p = p->rchild;
		}
	}
	printf("���%c���ڸ�����\n", e);
	return OK;
}
//*************************************
//�����ݹ�ʵ��
Status Recur_PreOrderTraverse(BiTree T)
{//�������
	if (T)
	{
		printf("%c ", T->value);
		Recur_PreOrderTraverse(T->lchild);
		Recur_PreOrderTraverse(T->rchild);
	}
	return OK;
}
Status Recur_InOrderTraverse(BiTree T)
{
	if (T)
	{
		Recur_InOrderTraverse(T->lchild);
		printf("%c ", T->value);
		Recur_InOrderTraverse(T->rchild);
	}
	return OK;
}
Status Recur_PostOrderTraverse(BiTree T)
{
	if (T)
	{
		Recur_PostOrderTraverse(T->lchild);
		Recur_PostOrderTraverse(T->rchild);
		printf("%c ", T->value);
	}
	return OK;
}
//*************************************
Status CompleteBiTree(BiTree T)
{
	int d;   //���������-���������
	if (T)
	{
		d = BiTreeDepth(T->lchild);
		if (d < 0 || d > 1)
		{
			return ERROR;
		}
		else
		{
			if (CompleteBiTree(T->lchild) && CompleteBiTree(T->rchild))
			{
				return OK;
			}
			else
			{
				return ERROR;
			}
		}
	}
	return FALSE;
}

int main()
{
	BiTree T,C;
	char ch;
	int Depth;
	InitTree(T);
	InitTree(C);
	printf("��������T�����򴴽���:");
	CreatBiTree(T);
	ch = getchar();    //���߻�������\n
	//ABC  DE G  F  H  
	   
	PreOrderTraverse(T);
	InOrderTraverse(T);
	PostOrderTraverse(T);
	LevelOrderTraverse(T);
	/*Depth = BiTreeDepth(T);
	printf("�������Ϊ��%d\n", Depth);
	if (CompleteBiTree(T))
	{
		printf("��������ȫ������\n");
	}
	else
	{
		printf("����������ȫ������\n");
	}
	printf("����Ҫ��˫�׵Ľ��ֵ��");
	scanf_s("%c", &ch,1);
	Parent(T, ch);
	ch = getchar();   //��������\n
	printf("����Ҫ�����ֵܵĽ��ֵ��");
	scanf_s("%c", &ch, 1);
	RightSibling(T,ch);
	ch = getchar();   //��������\n
	printf("�������������C:");
	CreatBiTree(C);
	ch = getchar();   //��������\n
	//ST   
	InsertChild(T, T->lchild, 1,C);
	printf("��������Ľ��Ϊ��");
	Recur_PreOrderTraverse(T);
	printf("\n��������Ľ��Ϊ��");
	Recur_InOrderTraverse(T);
	printf("\n��������Ľ��Ϊ��");
	Recur_PostOrderTraverse(T);
	printf("\n");
	LevelOrderTraverse(T);
	DeleteChild(T, T->lchild, 1);
	LevelOrderTraverse(T);*/
	printf("������Ҫɾ���������Ľ�㣺");
	scanf_s("%c", &ch, 1);
	Delete_x_Child(T, ch);
	ch = getchar();   //��������\n
	PreOrderTraverse(T);
	InOrderTraverse(T);
	PostOrderTraverse(T);
	LevelOrderTraverse(T);
	return 0;
}