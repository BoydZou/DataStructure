#include<iostream>
#include<fstream>
#include<iomanip>

using namespace std;

#define source "xingcheluxian.txt"
#define MAX 100000000   //��·��󳤶�
typedef struct
{
	int length;  //·������
	int type;    //·������
}road;

typedef struct
{
	int vexnum;    //������Ŀ
	int arcnum;    //�ߵ���Ŀ
	road** arcs;    //�ڽӾ���
}Graph, * GH;

void CreatGraph(GH G);   //����ͼ
void Dijkstra(GH G, int s);     //Ѱ�����·��
int MIN(GH G, bool* flag, int* fatigue);     //Ѱ�ҵ�ĳ�����ƣ�Ͷ���С���Ҹý��δ��ѡ��
void showpath(int* path, int* fatigue, GH G, int s);  //���·��

int main()
{
	GH G;
	G = (GH)malloc(sizeof(Graph));
	if (!G)
	{
		cout << "�ռ����ʧ��";
		exit(0);
	}
	CreatGraph(G);
	Dijkstra(G, 1);
	for (int i = 0; i < G->vexnum; i++)
	{
		free(G->arcs[i]);
	}
	free(G->arcs);
	free(G);
	system("pause");
	return 0;
}
//**************************************************************
void CreatGraph(GH G)
{
	fstream file;
	file.open(source, ios::in);
	if (file.fail())
	{
		cout << "�ļ���ʧ��";
		exit(0);
	}
	file >> G->vexnum;
	file >> G->arcnum;   //��ʼ���������ͱ���
	if (G->vexnum <= 0)
	{
		cout << 0;
		return;
	}
	G->arcs = (road**)malloc(G->vexnum * sizeof(road*));
	if (!G->arcs)
	{
		cout << "�ռ����ʧ��";
		exit(0);
	}
	int i, j;
	for (i = 0; i < G->vexnum; i++)
	{
		G->arcs[i] = (road*)malloc(G->vexnum * sizeof(road));
		if (!G->arcs[i])
		{
			cout << "�ռ����ʧ��";
			exit(0);
		}
	}
	for (i = 0; i < G->vexnum; i++)   //��ʼ���ڽӾ���
	{
		for (j = 0; j < G->vexnum; j++)
		{
			G->arcs[i][j].length = MAX;
			G->arcs[i][j].type = 0;
		}
	}
	int k, t, len;
	for (k = 0; k < G->arcnum; k++)
	{
		file >> t >> i >> j >> len;   //��������
		G->arcs[i - 1][j - 1].length = len;
		G->arcs[j - 1][i - 1].length = len;
		G->arcs[i - 1][j - 1].type = t;
		G->arcs[j - 1][i - 1].type = t;
	}
	/*for (i = 0; i < G->vexnum; i++)
	{
		for (j = 0; j < G->vexnum; j++)
		{
			cout <<setw(10) <<G->arcs[i][j].length << "-" << G->arcs[i][j].type << "   ";
		}
		cout << endl;
	}*/
	file.close();
}
//**************************************************************
void Dijkstra(GH G, int s)
{
	int* path, * dist, * fatigue, * pre;
	bool *flag;   //���帨������
	if (G->vexnum <= 0)
	{
		return;
	}
	if (s <= 0 || s > G->vexnum)
	{
		cout << "��ʼ����Ϣ���Ϸ�";
		return;
	}
	path = (int*)malloc(G->vexnum * sizeof(int));
	dist = (int*)malloc(G->vexnum * sizeof(int));
	fatigue = (int*)malloc(G->vexnum * sizeof(int));
	pre = (int*)malloc(G->vexnum * sizeof(int));  //��¼�ߵ�����·�ǲ���С��
	flag = (bool*)malloc(G->vexnum * sizeof(bool));
	if (!path || !dist || !flag || !fatigue || !pre)
	{
		cout << "�ռ����ʧ��";
		exit(0);
	}
	int i, j;
	for (i = 0; i < G->vexnum; i++)    //��ʼ����������
	{
		flag[i] = false;   //����õ�δ�������·���㼯
		dist[i] = G->arcs[s - 1][i].length;
		if (dist[i] < MAX)     //��·
		{
			if (G->arcs[s - 1][i].type == 1)   //С·
			{
				fatigue[i] = G->arcs[s - 1][i].length * G->arcs[s - 1][i].length;
				pre[i] = 1;
			}
			else
			{
				fatigue[i] = G->arcs[s - 1][i].length;
				pre[i] = 0;
			}
			path[i] = s - 1;
		}
		else
		{
			pre[i] = -1;
			path[i] = -1;
			fatigue[i] = MAX;
		}
	}
	/*for (i = 0; i < G->vexnum; i++)
	{
		cout << setw(3) << dist[i] << "*" << fatigue[i] << "*" << path[i] << "*" << pre[i] << endl;
	}*/

	flag[s - 1] = true;   //��ʼ����Ϊ��ѡ��״̬
	int sum = 0;    //��¼��ƣ�Ͷ�
	int count = 0;  //��¼�������˶���С��
	   
	int k, minfati, temp;
	for (i = 0; i < G->vexnum; i++)
	{
		k = MIN(G, flag, fatigue);   ////Ѱ�ҵ�ĳ�����ƣ�Ͷ���С
		flag[k] = true;  //ѡ��
		minfati = fatigue[k];
		sum += minfati;    //��¼ƣ�Ͷ�
		for (j = 0; j < G->vexnum; j++)   //����fatigue����
		{
			if (flag[j] == false)
			{
				if (pre[k] == 1)   //�ߵ�С·����k
				{
					count += dist[k];   //�Ѿ������ߵ�С·����
					if (G->arcs[k][j].type == 1)   //��k��jΪС·
					{
						temp = (count + G->arcs[k][j].length) * (count + G->arcs[k][j].length) - count * count;   //��ѡ������·��ƣ�Ͷȵ�������
						if (fatigue[j] > minfati + temp)    //j����k��Դ���ԭ������
						{
							fatigue[j] = minfati + temp;
							path[j] = k;
							pre[j] = 1;
						}
					}
					else if (G->arcs[k][j].type == 0)  //��·
					{
						if (fatigue[j] > minfati + G->arcs[k][j].length)  //j����k��Դ���ԭ������ 
						{
							fatigue[j] = minfati + G->arcs[k][j].length;
							path[j] = k;
							pre[j] = 0;
						}
					}
				}
				else if(pre[k] == 0)  //�ߴ�·����k
				{
					count = 0;  //����С��������
					if (G->arcs[k][j].type == 1)   //��k��jΪС·
					{
						temp = (G->arcs[k][j].length) * (G->arcs[k][j].length);   //��ѡ������·��ƣ�Ͷȵ�������
						if (fatigue[j] > minfati + temp)    //j����k��Դ���ԭ������
						{
							fatigue[j] = minfati + temp;
							path[j] = k;
							pre[j] = 1;
						}
					}
					else if (G->arcs[k][j].type == 0)   //��k��jΪ��·
					{
						if (fatigue[j] > minfati + G->arcs[k][j].length)  //j����k��Դ���ԭ������ 
						{
							fatigue[j] = minfati + G->arcs[k][j].length;
							path[j] = k;
							pre[j] = 0;
						}
					}
				}
			}
		}
	}
	showpath(path, fatigue, G, s);
	free(dist);
	free(flag);
	free(path);
	free(fatigue);
	free(pre);
}
//**************************************************************
int MIN(GH G, bool* flag, int* fatigue)    //Ѱ�ҵ�ĳ�����ƣ�Ͷ���С���Ҹý��δ��ѡ��
{
	int mindex = 0, min = MAX;
	int i;
	
	for (i = 0; i < G->vexnum; i++)
	{
		if (fatigue[i] <= min && flag[i] == false)
		{
			min = fatigue[i];
			mindex = i;
		}
	}
	return mindex;
}
//**************************************************************
void showpath(int* path, int *fatigue, GH G, int s)
{
	int* Stack;
	int n = G->vexnum;
	if (n <= 0)
	{
		return;
	}
	Stack = (int*)malloc((n+1) * sizeof(int));
	if (!Stack)
	{
		cout << "�ռ����ʧ��";
		exit(0);
	}
	int top, i, p;
	top = -1;
	for (i = n-1; i >= 0; i--)
	{
		if (i != s - 1)
		{
			if (path[i] == s - 1)
			{
				cout << s << "��·�ڵ�" << i + 1 << "��·�ڵ�����·�ߣ�\n";
				cout << s << "->" << i + 1 << "\n";
				cout << "ƣ��ֵΪ��" << fatigue[i] << endl;;
			}
			else if (path[i] == -1)
			{
				cout << s << "��·�ڵ�" << i + 1 << "��·����·��" << endl;
			}
			else
			{
				p = path[i];
				while (p != s - 1)
				{
					Stack[++top] = p;   //·��p��ջ
					p = path[p];
				}
				cout << s << "��·�ڵ�" << i + 1 << "��·�ڵ�����·�ߣ�\n";
				cout << s << "->";
				while (top > -1)
				{
					p = Stack[top--];   //·����ջ
					cout << p + 1 << "->";
				}
				cout << i + 1 << "\n";
				cout << "ƣ��ֵΪ��" << fatigue[i] << endl;
			}
		}
	}
}
//**************************************************************