//ħ���Ż�ȯ
#include<iostream>
#include<algorithm>
using namespace std;


int Partition(int* a, int low, int high)
{
	a[0] = a[low];
	int pivotkey = a[low];
	while (low < high)
	{
		while (low < high && a[high] >= pivotkey)
			--high;
		a[low] = a[high];
		while (low < high && a[low] <= pivotkey)
			++low;
		a[high] = a[low];
	}
	a[low] = a[0];
	return low;
}
void QuickSort(int* a, int low, int high)      //�������� 
{
	//ͨ��һ�����򽫴��ż�¼��Ϊ�����������֣�
	//����һ���ּ�¼�Ĺؼ��־�����һ���ֵļ�¼�Ĺؼ���С
	//��ɷֱ�������ּ�¼������������,�ݹ�
	if (low < high)
	{
		int pivotloc = Partition(a, low, high);
		QuickSort(a, low, pivotloc - 1);
		QuickSort(a, pivotloc + 1, high);
	}
}

int main()
{
	int N, M;
	
	int t = 0, t1 = 0;
	int m;
	cin >> N;
	
	int* a;	   //�Ż�ȯ 
	a = new int[N];
	int* a1;
	a1 = new int[N];
	if (!a || !a1)
	{
		cout << "�ռ����ʧ��";
		exit(0);
	}
	if (N < 0)
	{
		return 0;
	}
	for (int i = 0; i < N; i++)
	{
		cin >> m;
		if (m > 0)
		{
			t++;
			a[t] = m;
		}
		else if (m < 0)
		{
			t1++;
			a1[t1] = m;
		}
	}
	int k = 0, k1 = 0;
	cin >> M;
	int* b;	    //��Ʒ
	b = new int[M];
	int* b1;
	b1 = new int[M];    
	if (!b || !b1)   
	{
		cout << "�ռ����ʧ��";
		exit(0);
	}
	if (M < 0)
	{
		return 0;
	}
	for (int i = 0; i < M; i++)
	{
		cin >> m;
		if (m > 0)
		{
			k++;
			b[k] = m;
		}
		else if (m < 0)
		{
			k1++;
			b1[k1] = m;
		}
	}
	QuickSort(a, 1, t);
	QuickSort(a1, 1, t1);
	QuickSort(b, 1, k);
	QuickSort(b1, 1, k1);
	int money = 0;
	int q = min(t, k);
	for (int i = 0; i < q; i++)
	{
		money += a[t] * b[k];
		t--;
		k--;
	}
	q = min(t1, k1);
	int j = 1;
	for (int i = 0; i < q; i++)
	{
		money += a1[t1] * b1[j];
		t1--;
		j++;
	}
	cout << money << endl;
	system("pause");
	return 0;
}
