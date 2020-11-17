#include<iostream>
using namespace std;

typedef struct
{
	 int weight;
	 int parent, lchild, rchild;
}HTNode,*HufTree;
typedef char** HuffmanCode;

void Select(HufTree HT, int i, int &s1, int &s2)
{//��1~i-1��Ԫ�У�ѡ��parentΪ0��weight��С���������
	int j;
	int mindex1 = 0, mindex2 = 0;
	HT[0].weight = 999;
	for (j = 1; j <= i - 1; j++)
	{
		if (HT[j].parent == 0)
		{
			if (HT[mindex1].weight > HT[j].weight)
			{
				mindex1 = j;
			}
		}
	}
	for (j = 1; j <= i - 1; j++)
	{
		if (HT[j].parent == 0)
		{
			if ((HT[mindex2].weight > HT[j].weight) && (j != mindex1))
			{
				mindex2 = j;
			}
		}
	}
	s1 = mindex1;
	s2 = mindex2;
}
void HufCode(int n, int* w, HufTree &HT, HuffmanCode &HC)
{
	//n��ʾҶ�������
	//w���������Ҷ���Ȩֵ��һά������
	//HT������ʾ�洢����������һά������
	//HC�������洢��������������
	int m,i;
	int s1, s2, start, c, f;
	char* cd;
	HufTree p;
	if (n <= 1)
	{//ֻ��һ���ڵ㣬ֱ�ӷ���
		return;
	}
	m = 2 * n - 1;
	HT = (HufTree)malloc((m+1) * sizeof(HTNode));   //0�ŵ�Ԫδ��
	if (HT == NULL)
	{
		cout << "�ռ����ʧ��";
		exit(0);
	}
	for (i = 1; i <= n; i++)
	{
		HT[i].weight = w[i-1];
		HT[i].lchild = 0;
		HT[i].rchild = 0;
		HT[i].parent = 0;
	}
	for (; i <= m; i++)
	{
		HT[i] = { 0,0,0,0 };
	}
	
	for (i = n + 1; i <= m; i++)   //����������
	{
		Select(HT, i, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//��Ҷ�ӵ���������ÿ���ַ��ı���
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));   //����n���ַ������ͷ����
	if (HC == NULL)
	{
		cout << "�ռ����ʧ��";
		exit(0);
	}
	cd = (char*)malloc(n * sizeof(char));  //�����Ĺ����ռ�
	if (cd == NULL)
	{
		cout << "�ռ����ʧ��";
		exit(0);
	}
	cd[n - 1] = '\0';
	for (i = 1; i <= n; i++)
	{
		start = n - 1;   //���������λ��
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
		{
			if (HT[f].lchild == c)
			{
				start--;
				cd[start] = '0';
			}
			else
			{
				start--;
				cd[start] = '1';
			}
			
		}	
		HC[i] = (char*)malloc((n - start) * sizeof(char));
		if (HC[i] == NULL)
		{
			printf("�ռ����ʧ��");
			exit(0);
		}
		strcpy_s(HC[i], n-start, &cd[start]);
	}
	free(cd);
}
int main()
{
	int n, i;
	int w[100];
	HuffmanCode HC;
	HufTree HT;
	cout << "������Ҷ�ӽڵ�����";
	cin >> n;
	
	cout << "����������������Ȩֵ���ո��������";
	for (i = 0; i < n; i++)
	{
		cin >> w[i];
	}
	if (n == 1)
	{
		cout << "ֻ��һ����㣬�����Ϊ��0" << endl;
		return 0;
	}
	else if (n > 1)
	{
		HufCode(n, w, HT, HC);
		for (i = 1; i <= n; i++)
		{
			cout << "��" << i << "��������������Ϊ��" << HC[i] << endl;
		}
		return 0;
	}
}