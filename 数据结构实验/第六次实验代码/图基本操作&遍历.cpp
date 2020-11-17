#include<iostream>
#include<stdio.h>
using namespace std;

#define INFINITY INT_MAX   //�������ֵ
#define MAX_V 20    //��󶥵���Ŀ
#define Stack_Init_Size  200
#define STACKINCREMENT   40


#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
typedef char GElemType;
typedef int QElemType;
typedef int Status;
typedef struct
{
	int code;   //������
	GElemType info;  //����������Ϣ
}VertexType;
typedef enum 
{
	 UDG, DG, UDN, DN       //����ͼ������ͼ����������������
}GraphKind;
typedef struct
{
	int arcs[MAX_V][MAX_V];   //�ڽӾ���
	int vexnum, arcnum;      //ͼ�����Ķ�������ߵĸ���
	VertexType vexs[MAX_V];  //��Ŷ�����Ϣ
	GraphKind type;          //ͼ�������־����Ϊ����ͼ������ͼ����������������
}MGraph;


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
Status DestoryQueue(LinkQueue& Q)
{
	while (Q.front)
	{
		Q.rear = Q.front;
		Q.front = Q.front->next;
		free(Q.rear);
	}
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

Status LocateVex(MGraph G, GElemType v)  //Ѱ�Ҷ�����ͼ�е�λ��
{
	int i;
	for (i = 0; i < G.vexnum; i++)
	{
		if (G.vexs[i].info == v)
		{
			return i;
		}
	}
	return -1;
}
Status CreateUDN(MGraph& G)    //������
{
	G.type = UDN;
	int i, j, k;
	char ch;
	GElemType v1, v2;
	int weight;    //Ȩֵ
	cout << "������ͼ����Ϣ������������������";
	cin >> G.vexnum >> G.arcnum;
	ch = getchar();
	cout << "�����붥����Ϣ��";
	for (i = 0; i < G.vexnum; i++)    //��ʼ��������Ϣ
	{
		cin >> G.vexs[i].info;
		G.vexs[i].code = i;
	}
	for (i = 0; i < G.vexnum; i++)     //��ʼ���ڽӾ���
	{
		for (j = 0; j < G.vexnum; j++)    //��ʼ���ߵ���Ϣ���ֵ
		{
			G.arcs[i][j] = INFINITY;
		}
	}
	cout << "��������Լ������Ķ��㼰Ȩֵ��";
	for (k = 0; k < G.arcnum; k++)     //�����ڽӾ���
	{
		cin >> v1 >> v2 >> weight;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		if (i < 0)
		{
			cout << "����1����ͼ�У�����������" << endl;
			k--;
		}
		else if (j < 0)
		{
			cout << "����2����ͼ�У�����������" << endl;
			k--;
		}
		else
		{
			G.arcs[i][j] = weight;
			G.arcs[j][i] = G.arcs[i][j];//���������Գ�
		}
	}
	return OK;
}
Status CreateUDG(MGraph& G)     //����ͼ
{
	G.type = UDG;
	int i, j, k;
	char ch;
	GElemType v1, v2;
	cout << "�����붥������Լ��ߵ�������";
	cin >> G.vexnum >> G.arcnum;
	ch = getchar();
	cout << "�����붥�����Ϣ��";
	for (i = 0; i < G.vexnum; i++)    //��ʼ��������Ϣ
	{
		cin >> G.vexs[i].info;    //������Ϣ
		G.vexs[i].code = i;    //������
	}
	for (i = 0; i < G.vexnum; i++)   //��ʼ���ڽӾ���
	{
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j] = 0;
		}
	}
	cout << "����������������Ķ��㣺";
	for (k = 0; k < G.arcnum; k++)
	{
		cin >> v1 >> v2;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		if (i < 0)
		{
			cout << "����1����ͼ�У�����������" << endl;
			k--;
		}
		else if (j < 0)
		{
			cout << "����2����ͼ�У�����������" << endl;
			k--;
		}
		else
		{
			G.arcs[i][j] = 1;
			G.arcs[j][i] = 1;    //����ͼ���Գ�
		} 
	}
	return OK;
}
Status CreateDN(MGraph& G)    //������
{
	G.type = DN;
	int i, j, k;
	char ch;
	int weight;
	GElemType v1, v2;
	cout << "�����붥������Լ��ߵ�������";
	cin >> G.vexnum >> G.arcnum;
	ch = getchar();
	cout << "�����붥����Ϣ��";
	for (i = 0; i < G.vexnum; i++)   //��ʼ��������Ϣ
	{
		cin >> G.vexs[i].info;
		G.vexs[i].code = i;
	}
	for (i = 0; i < G.vexnum; i++)    //��ʼ���ڽӾ���
	{
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j] = INFINITY;
		}
	}
	cout << "������������������������㼰Ȩֵ��v1->v2����";
	for (k = 0; k < G.arcnum; k++)
	{
		cin >> v1 >> v2 >> weight;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		if (i < 0)
		{
			cout << "����1����ͼ�У�����������" << endl;
			k--;
		}
		else if (j < 0)
		{
			cout << "����2����ͼ�У�����������" << endl;
			k--;
		}
		else
		{
			G.arcs[i][j] = weight;
		}
	}
	return OK;
}
Status CreateDG(MGraph& G)    //����ͼ
{
	G.type = DG;
	int i, j, k;
	char ch;
	GElemType v1, v2;
	cout << "�����붥������Լ��ߵ�������";
	cin >> G.vexnum >> G.arcnum;
	ch = getchar();
	cout << "�����붥����Ϣ��";
	for (i = 0; i < G.vexnum; i++)   //��ʼ��������Ϣ
	{
		cin >> G.vexs[i].info;
		G.vexs[i].code = i;
	}
	for (i = 0; i < G.vexnum; i++)    //��ʼ���ڽӾ���
	{
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j] = 0;
		}
	}
	cout << "������������������������㣨v1->v2����";
	for (k = 0; k < G.arcnum; k++)
	{
		cin >> v1 >> v2;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		if (i < 0)
		{
			cout << "����1����ͼ�У�����������" << endl;
			k--;
		}
		else if (j < 0)
		{
			cout << "����2����ͼ�У�����������" << endl;
			k--;
		}
		else
		{
			G.arcs[i][j] = 1;
		}
	}
	return OK;
}
Status CreateGraph(MGraph& G)         //ѡ����Ҫ������ͼ�����ͣ�����ͼ1��������2������ͼ3��������4��
{
	cout<<"ѡ����Ҫ������ͼ�����ͣ�����ͼ1��������2������ͼ3��������4����";
	int a;
	cin >> a;
	switch (a) 
	{
	case 1:return CreateDG(G);
	case 2:return CreateDN(G);
	case 3:return CreateUDG(G);
	case 4:return CreateUDN(G);
	default:return CreateGraph(G);
	}
}
Status DestroyGraph(MGraph& G)
{
		free(G.arcs);
		free(G.vexs);
		return OK;
}
char GetVex(MGraph G, int i)     //���ض���ֵ
{
	if (i > G.vexnum || i < 1)
	{
		cout << "ͼ���޸ö���" << endl;
		return NULL;
	}
	else
	{
		cout << "�ö����ֵΪ��" << G.vexs[i - 1].info << endl;
		return G.vexs[i - 1].info;
	}
}
Status PutVex(MGraph& G, int i, GElemType value)      //������ֵ��Ϊvalue
{
	if (i > G.vexnum || i < 1)
	{
		cout << "ͼ�в����ڸý��" << endl;
		return ERROR;
	}
	else
	{
		G.vexs[i - 1].info = value;
		return OK;
	}
}
Status FirstAdjVex_text(MGraph G, GElemType v)    //����v�ĵ�һ���ڽӶ���
{
	int i, j;
	if (G.type == UDG || G.type == DG)   //����ͼ������ͼ
	{
		i = LocateVex(G, v);
		if (i == -1)
		{
			cout << "�ö��㲻��ͼ��" << endl;
			return -1;
		}
		else
		{
			for (j = 0; j < G.vexnum; j++)
			{
				if (G.arcs[i][j] == 1)
				{
					cout << "��һ���ڽӵ�Ϊ��" << G.vexs[j].info<<"���Ϊ��"<< j+1 << endl;
					return j;
				}
			}
			cout << "����" << v << "û���ڽӵ�" << endl;
			return -1;
		}
	}
	else if (G.type == UDN || G.type == DN)     //��������������
	{
		i = LocateVex(G, v);
		if (i == -1)
		{
			cout << "�ö��㲻��ͼ��" << endl;
			return -1;
		}
		for (j = 0; j < G.vexnum; j++)
		{
			if (G.arcs[i][j] != INFINITY)
			{
				cout << "��һ���ڽӵ�Ϊ��" << G.vexs[j].info << "���Ϊ��" << j + 1 << endl;
				return j;
			}
		}
		cout << "����" << v << "û���ڽӵ�" << endl;
		return -1;
	}
}
int NextAdiVex_text(MGraph G, GElemType v, GElemType w)
{
	int i, j, k;
	i = LocateVex(G, v);
	k = LocateVex(G, w);
	if (i == -1)
	{
		cout << "����" << v << "����ͼ��" << endl;
		return -1;
	}
	if (k == -1)
	{
		cout << "����" << w << "����ͼ��" << endl;
		return -1;
	}
	if (G.type == DN || G.type == UDN)
	{
		for (j = k + 1; j < G.vexnum; j++)
		{
			if (G.arcs[i][j] != INFINITY)
			{
				cout << "����" << v << "����ڶ���" << w << "����һ���ڽӵ�Ϊ��" << G.vexs[j].info << endl;
				return j;
			}
		}
		cout << w << "��" << v << "�����һ���ڽӵ�" << endl;
		return -1;
	}
	else
	{
		for (j = k + 1; j < G.vexnum; j++)
		{
			if (G.arcs[i][j] == 1)
			{
				cout << "����" << v << "����ڶ���" << w << "����һ���ڽӵ�Ϊ��" << G.vexs[j].info << endl;
				return j;
			}
		}
		cout << w << "��" << v << "�����һ���ڽӵ�" << endl;
		return -1;
	}
}

int InsertVex(MGraph& G, GElemType v)
{
	int i, j;
	i = LocateVex(G, v);
	if (i != -1) 
	{
		cout<<"�Ѵ��ڸö���\n";
		return -1;
	}
	j = G.vexnum;
	G.vexs[j].info = v;
	G.vexs[j].code = j;
	if (G.type == UDG || G.type == DG)  //����ͼ������ͼ
	{
		for (i = 0; i <= j; i++)
		{
			G.arcs[j][i] = 0;
			G.arcs[i][j] = 0;
		}
	}
	else
	{
		for (i = 0; i <= j; i++)
		{
			G.arcs[j][i] = INFINITY;
			G.arcs[i][j] = INFINITY;
		}
	}
	cout << "����" << v << "�����"<<endl;
	G.vexnum++;   //��������һ
	return OK;
}
int DeleteVex(MGraph& G, GElemType v)
{
	int i, j, k;
	i = LocateVex(G, v);
	if (i == -1)
	{
		cout << "����" << v << "����ͼ��" << endl;
		return -1;
	}
	for (j = i; j < G.vexnum - 1; j++)
	{
		G.vexs[j] = G.vexs[j + 1];
	}
	if (G.type == DG)     //����ͼ
	{
		for (k = 0; k < G.vexnum; k++)
		{
			if (G.arcs[i][k] != 0)
			{
				G.arcnum--;
			}
			if (G.arcs[k][i] != 0)
			{
				G.arcnum--;
			}
		}
	}
	else if (G.type == UDG)   //����ͼ
	{
		for (k = 0; k < G.vexnum; k++)
		{
			if (G.arcs[i][k] != 0)
			{
				G.arcnum--;
			}
		}
	}
	else if (G.type == DN)   //������
	{
		for (k = 0; k < G.vexnum; k++)
		{
			if (G.arcs[i][k] != INFINITY)
			{
				G.arcnum--;
			}
			if (G.arcs[k][i] != INFINITY)
			{
				G.arcnum--;
			}
		}
	}
	else             //������
	{
		for (k = 0; k < G.vexnum; k++)
		{
			if (G.arcs[i][k] != INFINITY)
			{
				G.arcnum--;
			}
		}
	}
	for (j = i; j < G.vexnum - 1; j++)
	{
		for (k = 0; k < G.vexnum; k++)
		{
			G.arcs[j][k] = G.arcs[j + 1][k];
			G.arcs[k][j] = G.arcs[k][j + 1];
		}
	}
	cout << "����" << v << "��ɾ��"<<endl;
	G.vexnum--;
	return OK;
}
int InsertArc(MGraph& G, GElemType v, GElemType w)
{
	int i, j;
	int weight;
	i = LocateVex(G, v);
	j = LocateVex(G, w);
	if (i == -1)
	{
		cout << "����" << v << "����ͼ��" << endl;
		return -1;
	}
	if (j == -1)
	{
		cout << "����" << v << "����ͼ��" << endl;
		return -1;
	}
	if (G.type == DG)  //����ͼ
	{
		G.arcs[i][j] = 1;
	}
	else if (G.type == UDG)  //����ͼ
	{
		G.arcs[i][j] = 1;
		G.arcs[j][i] = 1;
	}
	else if (G.type == DN)   //������
	{
		cout << "����������ߵ�Ȩֵ��";
		cin >> weight;
		G.arcs[i][j] = weight;
	}
	else if (G.type == UDN)   //������
	{
		cout << "����������ߵ�Ȩֵ��";
		cin >> weight;
		G.arcs[i][j] = weight;
		G.arcs[j][i] = weight;
	}
	cout << "��ӱ����"<<endl;
	return OK;
}
int DeleteArc(MGraph& G, GElemType v, GElemType w)
{
	int i, j;
	i = LocateVex(G, v);
	j = LocateVex(G, w);
	if (i == -1)
	{
		cout << "����" << v << "����ͼ��" << endl;
		return -1;
	}
	if (j == -1)
	{
		cout << "����" << v << "����ͼ��" << endl;
		return -1;
	}
	if (G.type == DG)  //����ͼ
	{
		G.arcs[i][j] = 0;
	}
	else if (G.type == UDG)  //����ͼ
	{
		G.arcs[i][j] = 0;
		G.arcs[j][i] = 0;
	}
	else if (G.type == DN)   //������
	{
		G.arcs[i][j] = INFINITY;
	}
	else if (G.type == UDN)   //������
	{
		G.arcs[i][j] = INFINITY;
		G.arcs[j][i] = INFINITY;
	}
	cout << "ɾ�������" << endl;
	return OK;
}
int NextAdiVex(MGraph G, GElemType v, GElemType w)
{
	int i, j, k;
	i = LocateVex(G, v);
	k = LocateVex(G, w);
	if (G.type == DN || G.type == UDN)
	{
		for (j = k + 1; j < G.vexnum; j++)
		{
			if (G.arcs[i][j] != INFINITY)
			{
				return j;
			}
		}
		return -1;
	}
	else
	{
		for (j = k + 1; j < G.vexnum; j++)
		{
			if (G.arcs[i][j] == 1)
			{
				return j;
			}
		}
		return -1;
	}
}
int FirstAdjVex(MGraph G, GElemType v)    //����v�ĵ�һ���ڽӶ���
{
	int i, j;
	if (G.type == UDG || G.type == DG)   //����ͼ������ͼ
	{
		i = LocateVex(G, v);
		for (j = 0; j < G.vexnum; j++)
		{
			if (G.arcs[i][j] == 1)
			{
				return j;
			}
		}
		return -1;
		
	}
	else if (G.type == UDN || G.type == DN)     //��������������
	{
		i = LocateVex(G, v);
		for (j = 0; j < G.vexnum; j++)
		{
			if (G.arcs[i][j] != INFINITY)
			{
				return j;
			}
		}
		return -1;
	}
}

void DFS(MGraph G, int v, bool* visited)
{
	visited[v] = true;
	int w;
	cout << G.vexs[v].info << "  ";
	w = FirstAdjVex(G, G.vexs[v].info);
	while (w >= 0)
	{
		if (!visited[w])
		{
			DFS(G, w, visited);
		}
		w = NextAdiVex(G, G.vexs[v].info, G.vexs[w].info);
	}
}

void DFSTraverse(MGraph G)  //������ȱ���
{
	int i;
	bool visited[MAX_V];     //���ʱ������
	for (i = 0; i < G.vexnum; i++)  //��ʼ��
	{
		visited[i] = false;
	}
	cout << "������ȱ������Ϊ��";
	for (i = 0; i < G.vexnum; i++)
	{
		if (!visited[i])
		{
			DFS(G, i, visited);
		}
	}
	cout << endl;
}

int BFSTraverse(MGraph G)   //������ȱ���
{
	int v, u, w;
	LinkQueue Q;
	bool visited[MAX_V];
	for (v = 0; v < G.vexnum; v++)
	{
		visited[v] = false;
	}
	InitQueue(Q);   //��ʼ������
	cout << "������ȱ������Ϊ��";
	for (v = 0; v < G.vexnum; v++)
	{
		if (!visited[v])
		{
			visited[v] = true;
			cout << G.vexs[v].info << "   ";
			EnQueue(Q, v);   //���
			while (!QueueEmpty(Q))
			{
				DeQueue(Q, u);
				for (w = FirstAdjVex(G, G.vexs[u].info);w>=0;w = NextAdiVex(G, G.vexs[u].info, G.vexs[w].info))
				{
					if (!visited[w])   //��δ������
					{
						visited[w] = true;
						cout << G.vexs[w].info << "   ";
						EnQueue(Q, w);
					}
				}
			}
		}
	}
	cout << endl;
}
int main()
{
	MGraph G;
	CreateGraph(G);
	DFSTraverse(G);
	BFSTraverse(G);
	DeleteVex(G, 'C');
	DFSTraverse(G);
	BFSTraverse(G);
	/*
	A B
	A D
	B C
	C D
	C E
	*/
	return 0;
}