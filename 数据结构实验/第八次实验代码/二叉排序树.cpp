#include<iostream>
#include<iomanip>

using namespace std;

typedef int TElemType;

typedef struct node
{
	TElemType data;    //�������ֵ
	struct  node* lchild, * rchild;   //���Һ���ָ��
}BSTNode, * BSTree;
BSTree BSTSearch(BSTree root, TElemType x, BSTree& father);    //����rootΪ�������в���Ԫ��x��fatherָ����˫�ף�����ָ��Ԫ��x��ָ��
bool BSTInsert(BSTree& root, TElemType x);   //����rootΪ�������в���Ԫ��x
bool BSTRemove(BSTree& root, TElemType x);     // ����rootΪ��������ɾ��Ԫ��x
void ShowTree(BSTree ptr);    //�����ŵ���ʽ��ʾ������
BSTree CreatBSTree();   //����BS��

//****************************************************************
int main()
{
	BSTree T;
	T = CreatBSTree();
	cout << "�����������£�" << endl;
	ShowTree(T);
	int c;
	cout<< endl << "������Ҫɾ�������ݣ�" << endl;
	cin >> c;
	BSTRemove(T, c);
	cout << "ɾ����Ԫ�غ���Ϊ��" << endl;
	ShowTree(T);
	cout << endl;
	system("pause");
	return 0;
}
//****************************************************************
BSTree CreatBSTree()
{
	int n, i, num;
	BSTree root;
	root = NULL;
	cout << "�������ʼBS��Ԫ�ظ�����\n";
	cin >> n;
	cout << "�������������Ԫ�أ�\n";
	for (i = 0; i < n; i++)
	{
		cin >> num;
		BSTInsert(root, num);
	}
	return root;
}
//****************************************************************
BSTree BSTSearch(BSTree root, TElemType x, BSTree& father)
{
	BSTree p = root;
	father = NULL;
	while (p)
	{
		if (x == p->data)
		{
			break;
		}
		else if (x > p->data)
		{
			father = p;
			p = p->rchild;
		}
		else
		{
			father = p;
			p = p->lchild;
		}
	}
	return p;
}
//****************************************************************
bool BSTInsert(BSTree& root, TElemType x)
{
	BSTree p, fa;
	if (BSTSearch(root, x, fa))  //�ж�Ԫ���Ƿ�������
	{
		cout << "Ԫ��" << x << "��������" << endl;
		return NULL;
	}
	p = new BSTNode;
	if (!p)
	{
		cout << "�ռ����ʧ��";
		exit(0);
	}
	p->data = x;
	p->lchild = NULL;
	p->rchild = NULL;
	if (fa == NULL)   //����
	{
		root = p;
	}
	else
	{
		if (x < fa->data)
		{
			fa->lchild = p;
		}
		else
		{
			fa->rchild = p;
		}
	}
	return true;
}
//****************************************************************
bool BSTRemove(BSTree& root, TElemType x)
{
	BSTree s, p, fa;
	p = BSTSearch(root, x, fa);
	if (p == NULL)
	{
		cout << "���в�����Ԫ��" << x << endl;
		exit(0);
	}
	if (p->lchild != NULL && p->rchild != NULL)  //��������Ů����*p������ǰ��*s,Ҳ������������*s
	{
		s = p->lchild;
		while (s->rchild != NULL)
		{
			fa = s;
			s = s->rchild;
		}
		//��ʱ*sΪ������ǰ��,*faΪ��˫��
		p->data = s->data;  //�����滻,��ɾs
		p = s;
	}

	if (p->rchild == NULL)   //����Ҫ��ɾ���Ľ�����������
	{
		s = p->lchild;
	}
	else  //�������������
	{
		s = p->rchild;    //����Ҳ��
	}

	if (p == root)
	{
		root = s;
	}
	else if(fa->lchild == p)
	{
		fa->lchild = s;
	}
	else
	{
		fa->rchild = s;
	}
	delete p;
	return true;
}
//****************************************************************
void ShowTree(BSTree ptr)    //�����ŵ���ʽ��ʾ������
{
	BSTree p;
	if (ptr)
	{
		cout << ptr->data;   //��ӡ���ڵ�
		if (ptr->lchild || ptr->rchild)
		{
			cout << "(";
			if (ptr->lchild)
			{
				ShowTree(ptr->lchild);
			}
			cout << ",";
			if (ptr->rchild)
			{
				ShowTree(ptr->rchild);
			}
			cout << ")";
		}
	}
}