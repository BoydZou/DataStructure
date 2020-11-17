#pragma warning (disable : 4996)
#include<iostream>
#include<fstream>
#include<iomanip>

using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#define source "MinimumSpanningTree.txt"   //Դ�ļ���ַ
#define MAX_NAME 20    //�������ֵ���󳤶�Ϊ20
#define maxx INT_MAX

typedef struct MyGraph
{
	int type;            //0����ʾ��������1��ʾ������
	int arcnum;          //�ߵĸ���
	int vexnum;          //�������
	char** vexname;      //��Ŷ������Ķ�ά����
	float** Arcs;           //�ڽӾ���A[i][j]��ʾi�Ŷ�����j�Ŷ���֮��ߵ�Ȩֵ����i,j֮��û�бߣ���A[i][j]ȡֵ�����
}GH;

typedef struct help
{
	int index;       //�±�
	float weight;    //Ȩ��
}HELP;               //��������

float SUM = 0;
int findvex(char* s, GH* G);//ȷ������s��Ӧ����ţ���������������s��ͼG
void creatgraph(GH* G);//���ڽӾ������ʽ����ͼ��������ͼG
void showgraph(GH* G);//���ڽӱ����ʽ��ʾͼ,������ͼG
void initi(GH* T, GH* G);//��ʼ����С������,������ͼT ͼG
void add(int a, int b, GH* T, GH* G);//����a,b�������߼��뵽ͼT��ȥ�������������±�a��b��ͼT ͼG
void prim(GH* G);//����ķ�㷨��������ͼG

int main()
{
	GH G;
	char vex[20];
	creatgraph(&G);//����ͼ
	showgraph(&G);//��ʾͼ
	prim(&G);//����ķ�㷨
	cout << "��С������Ȩֵ֮��Ϊ��" << SUM << endl;
	return 0;
}

//**********************************************************
void creatgraph(GH *G)
{
	fstream fin;
	fin.open(source, ios::in);
	if (fin.fail())
	{
		cout << "�ļ���ʧ��";
		exit(0);
	}
	int i, j, M;
	int len;
	float weight;
	char s1[20], s2[20];
	fin >> M;  //�������
	G->vexnum = M;
	G->vexname = (char**)malloc(M * sizeof(char*));    //����M���洢�������ֵ�����ָ��
	if (!G->vexname)
	{
		cout << "�ռ����ʧ��";
		exit(0);
	}
	G->Arcs = (float**)malloc(M * sizeof(float*));      //����M���洢�ڽӾ��������ָ��
	if (!G->Arcs)
	{
		cout << "�ռ����ʧ��";
		exit(0);
	}
	G->type = 0;
	G->arcnum = 0;

	for (i = 0; i < M; i++)   //��ʼ��������Ϣ�ͱ�
	{
		fin >> s1;
		G->vexname[i] = (char*)malloc(strlen(s1) * sizeof(char));
		if (!G->vexname[i])
		{
			cout << "�ռ����ʧ��";
			exit(0);
		}
		len = strlen(s1);
		strcpy(G->vexname[i],s1);
		G->Arcs[i] = (float*)malloc(M * sizeof(float));
		if (!G->Arcs[i])
		{
			cout << "�ռ����ʧ��";
			exit(0);
		}
		for (j = 0; j < M; j++)   //��ʼ����
		{
			G->Arcs[i][j] = maxx;
		}   
	}
	while (!fin.eof())
	{
		fin >> s1 >> s2 >> weight;
		if (fin.eof())
		{
			break;
		}
		i = findvex(s1, G);
		j = findvex(s2, G);
		G->Arcs[i][j] = weight;
		if (G->type == 0)  //������
		{
			G->Arcs[j][i] = weight;
		}
		G->arcnum++;
	}

}
//**********************************************************
int findvex(char* s, GH* G)  //ȷ������s��Ӧ����ţ���������������s��ͼG
{
	int i;
	for (i = 0; i < G->vexnum; i++)
	{
		if (strcmp(s, G->vexname[i]) == 0)
		{
			return i;
		}
	}
	return -1;
}
//**********************************************************
void showgraph(GH* G)//���ڽӱ����ʽ��ʾͼ,������ͼG
{
	int i, j;
	SUM = 0;
	for (i = 0; i < G->vexnum; i++)
	{
		cout << endl << G->vexname[i];
		for (j = 0; j < G->vexnum; j++)
		{
			if (G->Arcs[i][j] < maxx)
			{
				SUM += G->Arcs[i][j];
				cout << "---" << G->vexname[j] <<"("<< G->Arcs[i][j]<<")";
			}
		}
	}
	SUM = SUM / 2;
	cout << endl;
}
//**********************************************************
void prim(GH* G)//����ķ�㷨����С������
{
	HELP* H;
	int i;
	int M;
	int n = 0;
	int temp, i1 = 0;//Ѱ�Ҹ���������Ȩֵ��С��
	GH T;

	initi(&T, G);

	M = G->vexnum;

	H = (HELP*)malloc(M * sizeof(HELP));
	if (!H)
	{
		cout << "�ռ����ʧ��";
		exit(0);
	}

	for (i = 0; i < M; i++)
	{
		H[i].index = 0;
		H[i].weight = G->Arcs[H[i].index][i];
	}        //��ʼ��ѡ0�����
	H[0].weight = 0;
	n++;

	while (n <= M)
	{

		for (i = 0; i < M; i++)
		{
			if (H[i].weight != 0) //ѡ��ĳһ����0��weight��i
			{
				i1 = i;
				temp = H[i].weight;
				break;
			}
		}

		for (i = 0; i < M; i++)
		{
			if (H[i].weight < temp && H[i].weight != 0) //����Сֵ
			{
				temp = H[i].weight;
				i1 = i;
			}
		}
		add(H[i1].index, i1, &T, G);//�������Сֵ�����������Ӧ�ı߷���T

		H[i1].weight = 0;//���������Сֵ��weightΪ0����ʾ�Ѿ�ѡ��

		for (i = 0; i < M; i++)
		{
			if (H[i].weight > G->Arcs[i1][i])
			{
				H[i].index = i1;
				H[i].weight = G->Arcs[i1][i];
			}
		}
		n++;
	}

	cout << "��prim�㷨�õ���С������Ϊ��\n";
	showgraph(&T);     //���ڽӱ����ʽ��ʾ��С������
	//cout << "��С��������ȨֵΪ��" << SUM << endl;
}
//**********************************************************
void initi(GH* T, GH* G)
{
	int i, j, M;
	char s1[20];
	M = G->vexnum;
	T->arcnum = 0;
	T->type = G->type;
	T->vexnum = M;
	T->vexname = (char**)malloc(M * sizeof(char*));
	if (!T->vexname)
	{
		cout << "�ռ����ʧ��";
		exit(0);
	}
	T->Arcs = (float**)malloc(M * sizeof(float*));
	if (!T->Arcs)
	{
		cout << "�ռ����ʧ��";
		exit(0);
	}

	for (i = 0; i < M; i++)
	{
		strcpy(s1 ,G->vexname[i]);
		T->vexname[i] = (char*)malloc(strlen(s1) * sizeof(char));
		if (!T->vexname[i])
		{
			cout << "�ռ����ʧ��";
			exit(0);
		}
		strcpy(T->vexname[i],s1);
		T->Arcs[i] = (float*)malloc(M * sizeof(float));
		if (!T->Arcs[i])
		{
			cout << "�ռ����ʧ��";
			exit(0);
		}
		for (j = 0; j < M; j++)//��ʼ��
		{
			T->Arcs[i][j] = maxx;
		}

	}
}
//**********************************************************
void add(int a, int b, GH* T, GH* G)
{
	T->Arcs[a][b] = G->Arcs[a][b];      //����ͼ�����������ݸ���
	T->Arcs[b][a] = G->Arcs[b][a];
	T->arcnum++;
}