#include <iostream>
#include<iomanip>
using namespace std;
#define INFINITY 20000
#define MAX_V 1001
typedef struct GNode
{
	int arcs[MAX_V][MAX_V];  //�ڽӾ���
	//int vexs[MAX_V];     //������Ϣ
	int vexnum;
	int arcnum;
}MGraph;
MGraph G;
struct
{
	int vexcode;
	int lowcost;
}closest[MAX_V + 1];

int CreatGraph()
{
	int i, j, k;
	int weight;
	cout << "���������������Ϳɽ���ˮ������";
	cin >> G.vexnum >> G.arcnum;    //�������ͱ���
	for (i = 0; i < G.vexnum; i++)   //��ʼ���ڽӾ���Ͷ�����Ϣ
	{
		//G.vexs[i] = i + 1;
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j] = INFINITY;
		}
	}
	cout << "����������ɽ���ˮ�������Ｐ���ѣ�";
	for (k = 0; k < G.arcnum; k++)
	{
		cin >> i >> j;
		cin >> weight;
		G.arcs[i-1][j-1] = weight;
		G.arcs[j-1][i-1] = weight;
	}
	return 0;
}

void MinSpanning(int v)
{
	int i, j, k;
	int min;
	long int sum = 0;
	k = v - 1;
	for (j = 0; j < G.vexnum; j++)   //��ʼ��
	{
		if (j != k)
		{
			closest[j] = { v,G.arcs[k][j] };
		}
	}
	closest[k].lowcost = 0;   //ѡ��
	for (i = 1; i < G.vexnum; i++)
	{
		min = INFINITY;
		for (j = 0; j < G.vexnum; j++)
		{
			if (closest[j].lowcost != 0 && closest[j].lowcost < min)
			{
				min = closest[j].lowcost;
				k = j;
			}
		}
		closest[k].lowcost = 0;   //ѡ��
		sum = sum + min;
		for (j = 0; j < G.vexnum; j++)
		{
			if (G.arcs[k][j] < closest[j].lowcost)
			{
				closest[j].lowcost = G.arcs[k][j];
				closest[j].vexcode = k + 1;
			}
		}
	}
	cout << "�ܵķ���Ϊ��" << sum;
}
int main()
{
	int i, j;
	CreatGraph();
	
	MinSpanning(1);
	return 0;
}