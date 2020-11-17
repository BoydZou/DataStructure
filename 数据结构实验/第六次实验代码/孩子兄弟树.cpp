#include<iostream>
using namespace std;

#define MAX 20
typedef char TElemType;
typedef struct CSNode
{
	TElemType value;
	struct CSNode* firstchild, * nextsibling;
}CSNode,*CSTree;
int CreatCSTree(CSTree& T)
{
	char ch;
	ch = getchar();
	if (ch == '\0' || ch == '\n') 
	{
		return 0;   //���� 
	}
	if (ch == ' ')
	{
		T = NULL;
		return 0;
	}
	else
	{
		T = (CSTree)malloc(sizeof(CSNode));
		if (!T)
		{
			cout << "�ռ����ʧ��";
			exit(0);
		}
		T->value = ch;
		CreatCSTree(T->firstchild);
		CreatCSTree(T->nextsibling);
		return 0;
	}
}
int Depth(CSTree T)
{
	if (!T)
	{
		return 0;
	}
	else
	{
		return (Depth(T->firstchild) + 1) > (Depth(T->nextsibling)) ? (Depth(T->firstchild) + 1) : (Depth(T->nextsibling));
	}
}
int print_x_level(CSTree T,int i)
{
	if (i > Depth(T) || i < 1)
	{
		cout << "����Ĳ������Ϸ�" << endl;
		return -1;
	}
	if (T == NULL)
	{
		cout << "����Ϊ��" << endl;
		return -1;
	}
	CSTree Qu[MAX];   //�������
	int rear, front, level, len;
	CSTree q, p = T;
	rear = 0;
	front = 0;
	level = 0;
	Qu[rear++] = p;    //���ڵ����
	len = (rear + MAX - front) % MAX;   //����Ԫ�ظ���
	cout << "��" << i << "��Ľ��Ϊ��";
	while ((rear != front))
	{
		level++;    //����
		len = (rear + MAX - front) % MAX;   //����Ԫ�ظ���
		while (len--)
		{
			p = Qu[front];
			front = (front + 1) % MAX;    //����
			if (i == level)   //��i��
			{
				cout << p->value << "   ";
			}
			if (p->firstchild)
			{
				Qu[rear] = p->firstchild;   //�������
				rear = (rear + 1) % MAX;
				q = p->firstchild;
				while (q->nextsibling)
				{
					Qu[rear] = q->nextsibling;   
					rear = (rear + 1) % MAX;     //�ֵ����
					q = q->nextsibling;
				}
			}
		}
	}
	return 0;
}
int main()
{
	CSTree T;
	CreatCSTree(T);
	//int depth = Depth(T);
	//cout << depth;
	print_x_level(T, 3);
	//ABF G H  CD  E   
	//AB CD  E   
	return 0;
}