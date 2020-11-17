#include <iostream>
#include <fstream>
#include<iomanip>
using namespace std;

#define INFINITY 10000   //�������ֵ
#define MAX_V 20    //��󶥵���Ŀ
typedef char GElemType;

typedef enum
{
	UDG, DG, UDN, DN       //����ͼ������ͼ����������������
}GraphKind;
typedef struct
{
	int code;   //������
	GElemType info;  //����������Ϣ
}VertexType;
typedef struct
{
	int arcs[MAX_V][MAX_V];   //�ڽӾ���
	int vexnum, arcnum;      //ͼ�����Ķ�������ߵĸ���
	VertexType vexs[MAX_V];  //��Ŷ�����Ϣ
	GraphKind type;          //ͼ�������־����Ϊ����ͼ������ͼ����������������
}MGraph;

int LocateVex(MGraph G, GElemType v)  //Ѱ�Ҷ�����ͼ�е�λ��
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
int Closest(MGraph G, int* dist, bool* flag)
{
	int i, min = MAX_V - 1;
	for (i = 0; i < G.vexnum; i++)
	{
		if (!flag[i])
		{
			if (dist[i] <= dist[min])
			{
				min = i;
			}
		}
	}
	return min;
}
void MyGraph(MGraph& G)
{
	fstream f;
	int i, j;
	int weight;
	GElemType v1, v2;
	string filename;
	cout << "�������ļ�����";
	cin >> filename;
	f.open(filename, ios::in);
	if ( f.fail() )
	{
		cout << "�ļ���ʧ��";
		exit(0);
	}
	f >> G.vexnum;
	for (i = 0; i < G.vexnum; i++)      //��ʼ������
	{
		f >> G.vexs[i].info;
		G.vexs[i].code = i;
		for (j = 0; j < G.vexnum; j++)     //��ʼ���ڽӾ���
		{
			G.arcs[i][j] = INFINITY;
		}
	}
	G.arcnum = 0;
	while (!f.eof())
	{
		f >> v1;
		f >> v2;
		f >> weight;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		if (i < 0)
		{
			cout << "����" << v1 << "����ͼ��";
			exit(0);
		}
		if (j < 0)
		{
			cout << "����" << v2 << "����ͼ��";
			exit(0);
		}
		G.arcs[i][j] = weight;
		if (G.type == UDN)
		{
			G.arcs[j][i] = weight;
		}
		G.arcnum++;
	}
}

void showpath(MGraph G, int* path, int* dist, int s)   //sΪԴ��
{
	int i, p;
	int S[MAX_V];
	int top = -1;
	cout << "����" << G.vexs[s].info << "��������������·�����£�" << endl;
	for (i = 0; i < G.vexnum; i++)
	{
		if (i != s)
		{
			
			if (path[i] == s)
			{
				cout << G.vexs[i].info << " : ";
				cout << G.vexs[s].info << "->" << G.vexs[i].info;
				cout << endl << "����Ϊ��" << dist[i] << endl;
			}
			else if (path[i] == -1)  //��·��
			{
				cout << G.vexs[s].info << "��" << G.vexs[i].info << "��·��" << endl;
			}
			else
			{
				p = path[i];
				while (p != s)
				{
					top++;
					S[top] = p;    //ѹջ
					p = path[p];
				}

				cout << G.vexs[i].info << " : ";
				cout << G.vexs[s].info << "->";

				while (top > -1)   //���·��
				{
					p = S[top];
					top--;
					cout << G.vexs[p].info<< "->";
				}
				cout << G.vexs[i].info;
				cout << endl <<"����Ϊ��" << dist[i] << endl;
			}
		}
	}
}

void shortestpath_DIJ(MGraph G, int s)    //sΪ��ʼ����
{
	int dist[MAX_V], path[MAX_V] ;
	bool flag[MAX_V];   //����������������
	int i, j, k, mindist;
	for (i = 0; i < G.vexnum; i++)   //��ʼ����������
	{
		flag[i] = false;
		dist[i] = G.arcs[s][i];
		if (dist[i] < INFINITY)
		{
			path[i] = s;
		}
		else
		{
			path[i] = -1;
		}
	}
	flag[s] = true;   //ѡ����ʼ��
	for (i = 0; i < G.vexnum - 1; i++)   
	{//����Ѱ����������Դ������Ķ���k
		k = Closest(G, dist, flag);
		flag[k] = true;     //ѡ��
		mindist = dist[k];
		if (mindist < INFINITY)
		{//���ݴ˴�ѡ�еĶ��㣬�����������㵽Դ��ľ���
			for (j = 0; j < G.vexnum; j++)
			{
				if (flag[j] == false && dist[j] > mindist + G.arcs[k][j])
				{
					dist[j] = mindist + G.arcs[k][j];
					path[j] = k;
				}
			}
		}
	}
	showpath(G, path, dist, s);
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


int main()
{
	MGraph G;
	G.type = DN;
	MyGraph(G);
	shortestpath_DIJ(G, 0);
	//DFSTraverse(G);
	//shortestpath.txt
	return 0;
}
