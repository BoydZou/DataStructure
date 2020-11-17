#include<iostream>
#include<fstream>
using namespace std;

#define FILEPATH "Common_Key.txt"    //�ļ�·��
#define BORROW 1     //��Կ��
#define BACK 0       //��Կ��

typedef struct teacher
{
	int num;   //Կ�ױ��
	int start;  //����Կ�׵�ʱ��
	int end;    //��Կ�׵�ʱ��
	bool borrow;  //����λ���������򣬱���Ƿ��ѽ����¼�����
	bool back;    //�����λ���������򣬱���Ƿ��ѽ����¼�����
}TCH;
typedef struct Event
{
	int type;    //���ͣ��� or ��
	int index;    //�ṹ������TCH���±�
}Event;   //�¼�����
int front = 0, rear = 0;   //�¼�����ͷβָ��

void KeyBox(Event* Eve, TCH* Key, int* Box, int N);       //����Կ�׺�״̬  
void EnQu(Event* Eve,int kind, int index);
void DeQu(Event* Eve, int& kind, int &index);
void Traverse(Event* Eve,TCH* Key)
{
	int i = front;
	for (; i < rear; i++)
	{
		if (Eve[i].type)
		{
			cout << "��" << Key[Eve[i].index].num << " ";
		}
		else
		{
			cout << "��" << Key[Eve[i].index].num << " ";
		}
	}
	cout << endl;
}

int main()
{
	fstream file;
	file.open(FILEPATH, ios::in);   //���ļ�
	if (file.fail())
	{
		cout << "�ļ���ʧ��" << endl;
		exit(0);
	}
	int K, N, i, j, time;    //time��ʱ�Ĵ�ʹ��ʱ��
	TCH* Key;
	Event * Even;
	int* Box;
	file >> N >> K;
	Key = (TCH*)malloc(K * sizeof(TCH));
	if (K < 1)
	{
		return 0;
	}
	if (!Key)
	{
		cout << "�ռ����ʧ��" << endl;
		exit(0);
	}
	Even = (Event*)malloc((2*K+1) * sizeof(Event));   //�¼�����
	if (!Even)
	{
		cout << "�ռ����ʧ��" << endl;
		exit(0);
	}
	Box = (int*)malloc(N * sizeof(int));    //����Կ�׺�
	if (N < 1)
	{
		return 0;
	}
	if (!Box)
	{
		cout << "�ռ����ʧ��" << endl;
		exit(0);
	}
	for (i = 0; i < N; i++)    //��ʼ��Կ�׺�״̬
	{
		Box[i] = i + 1;
	}
	for (i = 0; i < K; i++)
	{
		file >> Key[i].num>>Key[i].start;
		file >> time;
		Key[i].end = Key[i].start + time;
		Key[i].borrow = false;
		Key[i].back = false;
	}
	
	int Fir_borrow, Fir_back, index1 = 0, index2 = 0;   //Fir_borrow,Fir_back�ֱ��¼�����Կ��ʱ���뻹Կ��ʱ��,index1,index2�ֱ��Ӧ��ṹ�������±�
	for (i = 0; i < 2 * K; i++)
	{
		Fir_borrow = INT_MAX;
		for (j = 0; j < K; j++)
		{
			if ((Key[j].start < Fir_borrow) && !(Key[j].borrow))   //�˴ν��¼���δ�������
			{
				Fir_borrow = Key[j].start;
				index1 = j;
			}
		}

		Fir_back = INT_MAX;
		for (j = 0; j < K; j++)
		{
			if ((Key[j].end < Fir_back) && !(Key[j].back))   //�˴λ��¼���δ�������
			{
				Fir_back = Key[j].end;
				index2 = j;
			}
			else if ((Key[j].end == Fir_back) && !(Key[j].back))
			{
				if (Key[j].num < Key[index2].num)   //ѡ��Կ�ױ��С��
				{
					index2 = j;
				}
			}
		}

		if (Fir_back <= Fir_borrow)    //��ʱӦ�û�Կ��
		{
			EnQu(Even, BACK, index2);
			Key[index2].back = true;   //���
			Traverse(Even, Key);       //��ʾ�¼�����
		}
		else if (Fir_back > Fir_borrow)    //��ʱӦ�ý�Կ��
		{
			EnQu(Even, BORROW, index1);
			Key[index1].borrow = true;   //���
			Traverse(Even, Key);       //��ʾ�¼�����
		}
	}
	KeyBox(Even, Key, Box, N);
	cout << "Կ�׺�����״̬Ϊ��";
	for (i = 0; i < N; i++)
	{
		cout << Box[i] << " ";
	}
	cout << endl;
	file.close();
	free(Key);
	free(Box);
	free(Even);
	system("pause");
	return 0;
}

void EnQu(Event* Eve, int kind, int index)
{
	Eve[rear].type = kind;
	Eve[rear].index = index;
	rear++;
}
void DeQu(Event* Eve, int& kind, int& index)
{
	kind = Eve[front].type;
	index = Eve[front].index;
	front++;
}
void KeyBox(Event* Eve, TCH* Key, int* Box, int n)
{
	int type, index;
	int i;
	int num;   //�˴β�����Կ�ױ��
	while (front < rear)
	{
		DeQu(Eve, type, index);
		if (type)    //��Կ��
		{
			num = Key[index].num;
			for (i = 0; i < n; i++)
			{
				if (Box[i] == num)   //�ҵ���Կ��
				{
					Box[i] = 0;   //����ùҹ�Ϊ��
					break;
				}
			}
			//cout << "ʱ��" << Key[index].start << "Կ�׺�״̬Ϊ��";
			cout << "��ǰԿ�׺�״̬Ϊ��\n";
			for (i = 0; i < n; i++)
			{
				if (Box[i] == 0)
				{
					cout << "X ";
				}
				else
				{
					cout << Box[i] << " ";
				}
			}
			cout << endl;
		}
		else   //��Կ��
		{
			for (i = 0; i < n; i++)
			{
				if (Box[i] == 0)   //�ҵ���С�Ĺҹ�
				{
					Box[i] = Key[index].num;
					break;
				}
			}
			//cout << "ʱ��" << Key[index].end << "Կ�׺�״̬Ϊ��";
			cout << "��ǰԿ�׺�״̬Ϊ��\n";
			for (i = 0; i < n; i++)
			{
				if (Box[i] == 0)
				{
					cout << "X ";
				}
				else
				{
					cout << Box[i]<<" ";
				}
			}
			cout << endl;
		}
	}
}