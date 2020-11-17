#include<iostream>
#include<iomanip>
#include<algorithm>
using namespace std;
#define max 100

int* creatarr(int& n);   //��������
void copyarr(int* a, int* b, int n);   //��������
void printarr(int* a, int n);  //�������
void HeapSort(int* a, int n);  //������
void QuickSort(int* a, int low, int high);    //��������
void MSort(int* SR, int* TR1, int s, int t);  //��·�鲢����
void ShellSort(int* a, int n, int* dlta, int len); //ϣ������
void Insert(int* a, int n);   //��������
void Select(int* a, int n);   //ѡ������
void nop(int* a, int n);      //ð������

//******************************************************************
int main()
{
	int* a, *b;
	int n = 0;   //���鳤��
	int dlta[3] = { 5,3,1 };
	b = creatarr(n);
	cout << "ԭ�������£�\n";
	printarr(b, n);

	a = new int[n];
	if (!a)
	{
		cout << "�ռ����ʧ��";
		exit(0);
	}

	copyarr(a, b, n);
	Select(a, n);
	cout << "ѡ�����������£�\n";
	printarr(a, n);

	copyarr(a, b, n);
	nop(a, n);
	cout << "ð�����������£�\n";
	printarr(a, n);

	copyarr(a, b, n);
	Insert(a, n);
	cout << "�������������£�\n";
	printarr(a, n);

	copyarr(a, b, n);
	ShellSort(a, n, dlta, 3);
	cout << "ϣ�����������£�\n";
	printarr(a, n);

	copyarr(a, b, n);
	MSort(a, a, 0, n - 1);
	cout << "�鲢���������£�\n";
	printarr(a, n);

	copyarr(a, b, n);
	QuickSort(a, 0, n - 1);
	cout << "�������������£�\n";
	printarr(a, n);

	copyarr(a, b, n);
	HeapSort(a, n - 1);
	cout << "�����������£�\n";
	printarr(a, n);
	//7 6 5 4 3 2 1
	system("pause");
}
//******************************************************************
void nop(int* a, int n)   //ð������
{
	int i, j, count, sumcmp = 0, sumswap = 0;
	for (i = 0; i < n-1; i++)
	{
		count = 0; //��¼ÿ��ð�ݽ�������
		for (j = 0; j < n-i-1; j++)
		{
			sumcmp++;
			if (a[j] > a[j + 1])
			{
				sumswap++;
				swap(a[j], a[j + 1]);
				count++;
				
			}
		}
		if (count == 0)
		{
			break;
		}
	}
}
//******************************************************************
void Select(int* a, int n)  //ѡ������
{
	int i, j, min, count = 0, sum = 0;   //count����������sum�Ƚϴ���
	for (i = 0; i < n; i++)
	{
		for (min = i, j = i; j < n; j++)
		{
			sum++;
			if (a[j] < a[min])
			{
				min = j;
			}
		}
		count++;
		swap(a[i], a[min]);
	}
}
//******************************************************************
void Insert(int* a, int n)  //��������
{
	int i, j, temp, kcn = 0, rmn = 0;   //lcn�Ƚϴ�����rmn�ƶ�����
	for (i = 1; i < n; i++)
	{
		kcn++;
		if (a[i] < a[i - 1])   //û�����򣬲�����
		{
			temp = a[i];
			a[i] = a[i - 1];
			rmn += 2;
			for (j = i - 2; j > -1; j--)
			{
				kcn++;
				if (temp >= a[j])
				{
					break;
				}
				else
				{
					rmn++;
					a[j + 1] = a[j];
				}
			}
			a[j + 1] = temp;
			rmn++;
		}
	}
}
//******************************************************************
void ShellInsert(int* a, int dk, int n)
{
	int i, j, temp, kcn = 0, rmn = 0;
	for (i = dk; i < n; i++)
	{
		kcn++;
		if (a[i] < a[i - dk])    //˵����������
		{
			temp = a[i];   //�ݴ�
			a[i] = a[i - dk];
			rmn += 2;
			for (j = i - 2*dk; j >= 0; j -= dk)  //��λ��
			{
				kcn++;
				if (temp < a[j])
				{
					a[j + dk] = a[j];
				}
				else
				{
					break;
				}
			}
			rmn++;
			a[j + dk] = temp;
		}
	}
}
void ShellSort(int* a, int n, int* dlta, int len)   //dltaΪ�������飬lenΪ�䳤��
{
	int i;
	for (i = 0; i < len; i++)
	{
		ShellInsert(a, dlta[i], n);
	}
}
//******************************************************************
void Merge(int* SR, int*& TR, int i, int m, int n)   //�������SR[i...m]��SR[m+1...n]�鲢Ϊ�����TR[i...n]
{
	int j, k;
	for (j = m + 1, k = i; i <= m && j <= n; k++)    //��SR��Ԫ�أ���С������TR��
	{
		if (SR[i] <= SR[j])
		{
			TR[k] = SR[i++];
		}
		else
		{
			TR[k] = SR[j++];
		}
	}
	if (i <= m)  //SR[i...m]ʣ��
	{
		for (; k <= n; k++)
		{
			TR[k] = SR[i++];
		}
	}
	if (j <= n)   //SR[m + 1...n]ʣ��
	{
		for (; k <= n; k++)
		{
			TR[k] = SR[j++];
		}
	}
}
void MSort(int* SR, int* TR1, int s, int t)
{
	int m;
	int TR2[max];
	if (s == t)
	{
		TR1[s] = SR[s];
	}
	else
	{
		m = (s + t) / 2;
		MSort(SR, TR2, s, m);
		MSort(SR, TR2, m + 1, t);
		Merge(TR2, TR1, s, m, t);
	}
}
//******************************************************************
int Partition(int* a, int low, int high)    //�����������ӱ�r[low...high]�ļ�¼��ʹ�����¼��λ����������λ��
{
	int i = low, j = high;
	int pivot = a[low];
	while (j!=i)
	{
		while (i < j && a[j] >= pivot)
		{
			j--;
		}
		if (i < j)
		{
			a[i++] = a[j];
		}
		while (i < j && a[i] <= pivot)
		{
			i++;
		}
		if (i < j)
		{
			a[j--] = a[i];
		}
	}
	a[i] = pivot;
	return i;
}
void QuickSort(int* a, int low, int high)     //������a������a[low...high]���п�������
{
	int pivotloc;
	if (low < high)
	{
		pivotloc = Partition(a, low, high);
		QuickSort(a, low, pivotloc - 1);
		QuickSort(a, pivotloc + 1, high);
	}
}
//******************************************************************
void HeapAdjust(int* a, int s, int m)      //��֪a[s...m]�еĹؼ��ֳ�a[s]֮�������ѵĶ���
{
	int temp = a[s];
	int j;
	for (j = 2 * s; j <= m; j *= 2)
	{
		if (j < m && a[j] <a[j+1])
		{
			j++;
		}
		if (temp >= a[j])  //�Ѿ��Ǵ󶥶�
		{
			break;
		}
		a[s] = a[j];
		s = j;
	}
	a[s] = temp;
}
void HeapSort(int* a, int n)
{
	int i;
	for (i = n / 2; i >= 0; i--)   //��a[0...n]���ɴ󶥶�
	{
		HeapAdjust(a, i, n);
	}
	//printarr(a, n + 1);
	for (i = n; i > 0; i--)
	{
		swap(a[0], a[i]);
		HeapAdjust(a, 0, i - 1);
	}
}
//******************************************************************
void printarr(int* a, int n)
{
	int i;
	if (n == 0)
	{
		cout << "����Ϊ��";
	}
	for (i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}
//******************************************************************
int* creatarr( int &n)
{
	int* a;
	int i;
	cout << "����������Ԫ�ظ�����";
	cin >> n;
	a = new int[n];
	if (!a)
	{
		cout << "�ռ����ʧ��";
		exit(0);
	}
	cout << "����������Ԫ�أ�\n";
	for (i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	return a;
}
//******************************************************************
void copyarr(int* a, int* b, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		a[i] = b[i];
	}
}
//******************************************************************

