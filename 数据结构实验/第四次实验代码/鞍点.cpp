#include<iostream>
#include<iomanip>
using namespace std;
int main() 
{
	int m, n,flag = 0;
	cout<<"���������������������";
	cin >> m >> n;
	int T[10][10];
	int F[10][10] = { 0 };
	int i, j, k, min, max;
	cout<<"����������Ԫ�أ�"<<endl;
	for (i = 0; i < m; i++) 
	{
		for (k = 0; k < n; k++) 
		{
			cin >> T[i][k];
		}
	}
	for (i = 0; i < m; i++)
	{
		for (k = 0; k < n; k++)
		{
			cout<<setw(5)<<left<< T[i][k];
		}
		cout << endl;
	}

	/*
	�жϾ���İ���,���������׼ȷ�Ķ��壬����
	1 1 1
	1 1 1
	1 1 1
	���ǰ�����Ԫ�ض��ǰ��������
	*/
	for (i = 0; i < m; i++)   //������Сֵ�����
	{
		min = T[i][0];
		for (j = 0; j < n; j++)
		{
			if (min > T[i][j])
			{
				min = T[i][j];
			}
		}
		for (j = 0; j < n; j++)
		{
			if (min == T[i][j])
			{
				F[i][j] = 1;
			}
		}
	}
	for (i = 0; i < n; i++)    ////�������ֵ������շ������ֵ�ı��
	{
		max = T[0][i];
		for (j = 0; j < m; j++)
		{
			if (max < T[j][i])
			{
				max = T[j][i];
			}
		}
		for (j = 0; j < m; j++)
		{
			if (max != T[j][i])
			{
				F[j][i] = 0;
			}
		}
	}
	for (i = 0; i < m; i++)
	{
		for (k = 0; k < n; k++)
		{
			cout << setw(5) << left << F[i][k];
		}
		cout << endl;
	}
	for (i = 0; i < m; i++) 
	{
		for (k = 0; k < n; k++)
		{
			if (F[i][k] == 1)
			{
				flag = 1;
				cout << "��" << i + 1 << "�е�" << k + 1 << "���ǰ��㣬ֵΪ��" << T[i][k] << endl;
			}
		}
	}
	if (flag == 0)
	{
		cout << "�þ���û�а���";
	}
	return 0;
}