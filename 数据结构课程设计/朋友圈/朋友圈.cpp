#include<iostream>
#include<fstream>

using namespace std;

//#define source "pyq.txt"
//���鼯��˼�룬�����������ѵ�����һ�����ϼ���
int find(int x, int* fa);   //����x�ĸ���

int main()
{
	int stu, club, i, j, k, a, b;
	cin >> stu >> club;
	int* ST, * pyq;
	if (stu <= 0)
	{
		cout << 0;
		return 0;
	}
	ST = (int*)malloc(stu * sizeof(int));   //���첢�鼯
	if (!ST)
	{
		cout << "�ռ����ʧ��";
		exit(0);
	}
	pyq = (int*)malloc(stu * sizeof(int));   //ͳ������Ȧ�㼯�ĸ���
	if (!pyq)
	{
		cout << "�ռ����ʧ��";
		exit(0);
	}
	for (i = 0; i < stu; i++)   //��ʼ�����鼯
	{
		ST[i] = i;
		pyq[i] = 1;
	}
	for (j = 0; j < club; j++)
	{
		cin >> k;  //�þ��ֲ�����
		if (k > 0)
		{
			cin >> a;
			for (i = 1; i < k; i++)
			{
				int x, y;
				cin >> b;
				x = find(a - 1, ST);
				y = find(b - 1, ST);
				if (x != y)
				{
					if (pyq[x] > pyq[y])    //Ϊʹ����֯�Ĳ�����ͣ��������͵Ĳ��뵽�����ߵ���
					{
						ST[y] = x;
						pyq[x] += pyq[y];
					}
					else
					{
						ST[x] = y;
						pyq[y] += pyq[x];
					}
				}
			}
		}
	}
	int t = pyq[0];
	for (i = 1; i < stu; i++)
	{
		if (t < pyq[i])
		{
			t = pyq[i];
		}
	}
	cout << t;
	free(ST);
	free(pyq);
	cout << endl;
	system("pause");
	return 0;
}

int find(int x, int* fa)  //����x�ĸ���
{
	if (fa[x] != x)
	{
		fa[x] = find(fa[x], fa);
	}
	return fa[x];
}