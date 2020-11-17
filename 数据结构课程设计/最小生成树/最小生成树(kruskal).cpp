#pragma warning (disable:4996)
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


#define maxx INT_MAX
#define source "MinimumSpanningTree.txt"
typedef struct arcnode
{
	int index;//�ڽӵ����
	float weight;//Ȩֵ
	struct arcnode* next;
}AR;

typedef struct MyGraph
{
	int type;//0����ʾ����ͼ��1��ʾ����ͼ
	int arcnum, vexnum;//ͼ�бߵĸ����Լ��������
	char** vexname;//��Ŷ������Ķ�ά����
	AR* N;//����ڽӱ�ͷ��������
}GH;


int findvex(char* s, GH* G);//ȷ������s��Ӧ�����,����������s��ͼG
void creatgraph(GH* G);//���ڽӱ����ʽ����ͼ,������ͼG
void showgraph(GH* G);//���ڽӱ����ʽ��ʾͼ,������ͼG
void initi(int* help, int M);//��ʼ�����飬��������������help,���鳤��M
void kruskal(int* help, GH* G);//��³˹�����㷨����������������help,ͼG
void ini(GH* T, GH* G);//��ʼ����С��������ͼ����������С��������ͼT��ͼG
void add(int x, int y, GH* T, float t);//����С��������ͼ�мӱߣ���������������x��y����С��������ͼT���Լ�Ȩֵt

int main()
{
	GH G;
	int* help;
	creatgraph(&G);//����ͼ
	showgraph(&G);//��ʾͼ
	help = (int*)malloc(G.vexnum * sizeof(int));//Ϊ�������鿪�ٿռ�
	initi(help, G.vexnum);//��ʼ����������
	kruskal(help, &G);//��³˹�����㷨����������������help,ͼG
	return 0;
}
int findvex(char* s, GH* G)//ȷ������s��Ӧ�����,����������s��ͼG
{
	int i;
	for (i = 0; i < G->vexnum; i++)
	{
		if (strcmp(s, G->vexname[i]) == 0)
			return i;
	}
	printf("read file error\n");
	exit(-1);
}

void creatgraph(GH* G)//���ڽӱ����ʽ����ͼ,������ͼG
{
	char filename[30];
	AR* p;
	int i, j, M;
	float weight;
	FILE* fp;
	char s1[20], s2[20];
	if ((fp = fopen(source, "rb")) == NULL)
	{
		printf("open error\n");
		exit(0);
	}
	fscanf(fp, "%d", &(G->vexnum));
	M = G->vexnum;
	G->type = 0;
	G->arcnum = 0;
	G->N = (AR*)malloc(M * sizeof(AR));
	G->vexname = (char**)malloc(M * sizeof(char*));

	for (i = 0; i < M; i++)
	{
		G->N[i].next = NULL;
		fscanf(fp, "%s", s1);
		G->vexname[i] = (char*)malloc(strlen(s1) * sizeof(char));
		strcpy(G->vexname[i], s1);

	}

	while (fscanf(fp, "%s%s%f", s1, s2, &weight) != EOF)
	{
		i = findvex(s1, G);
		j = findvex(s2, G);
		p = (AR*)malloc(sizeof(AR));
		p->index = j;
		p->weight = weight;
		p->next = G->N[i].next;
		G->N[i].next = p;

		if (!G->type)
		{
			p = (AR*)malloc(sizeof(AR));
			p->index = i;
			p->weight = weight;
			p->next = G->N[j].next;
			G->N[j].next = p;
		}
		(G->arcnum)++;
	}
}
void showgraph(GH* G)//���ڽӱ����ʽ��ʾͼ,������ͼG
{
	int i;
	AR* p;
	for (i = 0; i < G->vexnum; i++)
	{
		printf("\n%s ", G->vexname[i]);
		p = G->N[i].next;
		while (p)
		{
			printf("--%s(%4.2f) ", G->vexname[p->index], p->weight);
			p = p->next;
		}
	}
	printf("\n");
}
void initi(int* help, int M)//��ʼ�����飬��������������help,���鳤��M
{
	int i;
	for (i = 0; i < M; i++)
	{
		help[i] = i;
	}
}
void kruskal(int* help, GH* G)//��³˹�����㷨����������������help,ͼG
{
	int i, j, m = -1, n = -1, M, k;
	int count = 0;
	int* visit;
	float temp;
	GH T;
	AR* p;
	M = G->vexnum;
	ini(&T, G);

	visit = (int*)malloc(M * sizeof(int));
	for (i = 0; i < M; i++)//��ʼ��visit
	{
		visit[i] = 0;
	}

	temp = maxx;
	while (count < G->arcnum)
	{

		temp = maxx;//����temp

		for (i = 0; i < G->vexnum; i++)//�������еıߣ�����СȨֵ
		{
			p = G->N[i].next;
			while (p)
			{
				if (p->weight < temp)
				{
					if (visit[i] == 0 || visit[p->index] == 0)
					{
						temp = p->weight;
						m = i;
						n = p->index;
					}
				}
				p = p->next;
			}
		}

		visit[m] = 1;
		visit[n] = 1;//��������������Ϊ�ѷ���

		if (help[m] != help[n])//�����ɻ�·
		{
			add(m, n, &T, temp);
			k = help[m];
			for (i = 0; i < G->vexnum; i++)
			{
				if (help[i] == k)
					help[i] = help[n];
			}
		}

		count++;
	}
	printf("\n��С����������³˹�����㷨����\n");
	showgraph(&T);

}
void ini(GH* T, GH* G)//��ʼ����С��������ͼ����������С��������ͼT��ͼG
{
	char s1[20];
	int i, M;
	T->arcnum = 0;
	M = G->vexnum;
	T->vexnum = G->vexnum;
	T->type = G->type;
	T->vexname = (char**)malloc(sizeof(char*) * M);
	T->N = (AR*)malloc(M * sizeof(AR));//����ͷ�ڵ�Ŀռ�

	for (i = 0; i < G->vexnum; i++)
	{
		T->N[i].next = NULL;
		strcpy(s1, G->vexname[i]);
		T->vexname[i] = (char*)malloc(strlen(s1) * sizeof(char));
		strcpy(T->vexname[i], s1);
	}
}
void add(int x, int y, GH* T, float temp)
{
	AR* p;

	p = (AR*)malloc(sizeof(AR));

	p->index = y;
	p->weight = temp;
	p->next = T->N[x].next;
	T->N[x].next = p;
	if (!T->type)
	{
		p = (AR*)malloc(sizeof(AR));
		p->index = x;
		p->weight = temp;
		p->next = T->N[y].next;
		T->N[y].next = p;
	}
	(T->arcnum)++;
	//printf("T�б���Ϊ��%d\n",T->arcnum);
}
