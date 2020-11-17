#include<iostream>
#include<fstream>
#include<string>

using namespace std;
#define INPUT_FILEPATH "source.txt"  //�����ļ���ַ
#define HUFFMAN "Huffman.txt"    //������ַ
#define HCODE "Hcode.txt"    //���ַ������ļ���ַ
#define Code "code.dat"       //��λ������ļ�
#define recode "recode.txt"   //�������ļ�

#define Stack_Init_Size  200
#define STACKINCREMENT   100

typedef struct
{
	char ch;    //�����ַ���Ϣ
	int weight;
	int parent, lchild, rchild;
}HTNode, * HufTree;

int sum = 0;   //��0/1�ַ���������ַ���
int freq[256] = {0};

typedef char** HuffmanCode;

typedef struct
{
	char* base;   // ջ��ָ��
	char* top;    // ջ��ָ��
	int stacksize;    //��ǰ�ѷ���Ĵ洢�ռ䣬��SElemTypeΪ��λ
}SqStack, *Stack;

void Select(HufTree HT, int i, int& s1, int& s2);
void HufCode(int n, int* w, HufTree& HT, HuffmanCode& HC);
void readfile();   //�������ļ�ͳ�Ƹ����ַ���Ƶ��
int GetNum();    //ͳ��Ҷ�ڵ�����
void GetHCode(HuffmanCode HC,HufTree HT, int n);    //�õ����³��������ļ�
void storebit(HuffmanCode HC);   //ת��Ϊ������bit;
void Recode(HuffmanCode HC, HufTree HT, int n);   //�Ա������ļ�����
void InitStack(Stack S); //����һ����ջ
void Push(Stack S, char e);//ѹջ
void ClearStack(Stack S);  //���ջ

int main()
{
	int n;
	int w[100];
	HuffmanCode HC;
	HufTree HT;
	//cout << sizeof(bool);
	readfile();
	n = GetNum();
	HufCode(n, w, HT, HC);
	GetHCode(HC, HT, n);
	storebit(HC);
	Recode(HC, HT, n);
	free(HT);
	free(HC);
	system("pause");

	return 0;
}
//********************************************************************
void Select(HufTree HT, int i, int& s1, int& s2)
{//��1~i-1��Ԫ�У�ѡ��parentΪ0��weight��С���������
	int j;
	int mindex1 = 0, mindex2 = 0;
	HT[0].weight = INT_MAX;
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
//********************************************************************
void HufCode(int n, int* w, HufTree& HT, HuffmanCode& HC)
{
	//n��ʾҶ�������
	//w���������Ҷ���Ȩֵ��һά������
	//HT������ʾ�洢����������һά������
	//HC�������洢��������������
	fstream file;
	int m, i, j;
	int s1, s2, start, c, f;
	char* cd;
	file.open(HUFFMAN, ios::out);
	if (file.fail())
	{
		cout << "�ļ���ʧ��";
		exit(0);
	}
	if (n == 0)
	{//�޽ڵ㣬ֱ�ӷ���
		
		return;
	}
	m = 2 * n - 1;
	HT = (HufTree)malloc((m + 1) * sizeof(HTNode));   //0�ŵ�Ԫδ��
	if (HT == NULL)
	{
		cout << "�ռ����ʧ��";
		exit(0);
	}
	for (i = 0, j = 1; i < 256; i++)
	{
		if (freq[i] != 0)
		{
			HT[j].weight = freq[i];   //��ʼ��Ȩ��
			HT[j].ch = i;             //��ʼ��������Ϣ
			HT[j].lchild = 0;
			HT[j].rchild = 0;
			HT[j].parent = 0;
			j++;
		}
	}
	
	file << "�ַ�\t" << "Ƶ��\t" <<"����" << endl;
	if (n == 1)
	{
		file << HT[1].ch << "\t" << freq[(int)HT[1].ch] << "\t0" << endl;
		return ;
	}
	for (j = n + 1; j <= m; j++)
	{
		HT[j] = { 0,0,0,0,0 };
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
	cd = (char *)malloc(n * sizeof(char));  //�����Ĺ����ռ�
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
		HC[i] = (char *)malloc((n - start) * sizeof(char));
		if (HC[i] == NULL)
		{
			printf("�ռ����ʧ��");
			exit(0);
		}
		strcpy_s(HC[i], n - start, &cd[start]);
	}
	
	for (i = 1; i <= n; i++)
	{
		file << HT[i].ch << "\t" << HT[i].weight<<"\t" <<HC[i] << endl;
	}


	free(cd);
}
//********************************************************************
void readfile()
{
	fstream file;
	char ch = 0;
	file.open(INPUT_FILEPATH, ios::in);
	if (file.fail())
	{
		cout << "�ļ���ʧ��";
		exit(0);
	}
	file.unsetf(ios::skipws);   //����Ĭ�ϵĲ����հ��ַ�
	while (1)   //�����ļ�����
	{
		file>>ch;
		if (file.eof())
		{
			break;
		}
		freq[(int)ch]++;
	}
	file.close();
}
//********************************************************************
int GetNum()
{
	int n = 0;
	for (int i = 0; i < 256; i++)
	{
		if (freq[i] != 0)   //˵�����ַ�����
		{
			n++;
		}
	}
	return n;
}
//********************************************************************
void GetHCode(HuffmanCode HC,HufTree HT, int n)
{
	fstream filein,fileout;
	char ch;
	int i;
	filein.open(INPUT_FILEPATH, ios::in);
	if (filein.fail())
	{
		cout << "�ļ���ʧ��";
		exit(0);
	}
	fileout.open(HCODE, ios::out);
	if (fileout.fail())
	{
		cout << "�ļ���ʧ��";
		exit(0);
	}
	filein.unsetf(ios::skipws);   //����Ĭ�ϵĲ����ո���
	while (1)    //���ļ�
	{
		filein >> ch;
		if (filein.eof())  //���һ���Ƕ���ģ���Ӧ�ô���
		{
			break;
		}
		for (i = 1; i <= n; i++)
		{
			if (ch == HT[i].ch)
			{
				sum += strlen(HC[i]);
				fileout << HC[i];
				break;
			}
		}
	}
	filein.close();
	fileout.close();
}
//********************************************************************
void storebit(HuffmanCode HC)
{
	fstream fin, fout;
	fin.open(HCODE, ios::in);
	if (fin.fail())
	{
		cout << "�ļ���ʧ��";
		exit(0);
	}
	fout.open(Code, ios::out|ios::binary);   //�����Ʒ�ʽд�ļ�
	if (fout.fail())
	{
		cout << "�ļ���ʧ��";
		exit(0);
	}
	char c = '\0';
	//char d = ' ';
	char ch;
	int count = 0;
	while (1)
	{
		fin >> ch;  //��һ���ַ�
		if (fin.eof())   
		{
			break;
		}
		count++;
		if (ch == '1')
		{
			c = (c << 1) | 1;
		}
		else
		{
			c = c << 1;
		}
		if (count == 8)   //��8���ַ�0/1дһ���ֽ�
		{
			count = 0;
			fout.write(&c, sizeof(char));
			c = '\0';
		}
	}
	if (count > 0)   //˵����ʣ�µ��ַ�0/1�����⴦��
	{
		fout.write(&c, sizeof(char));
	}
	fin.close();
	fout.close();
}
//********************************************************************
void Recode(HuffmanCode HC, HufTree HT, int n)
{
	fstream fout,fin;
	fout.open(recode, ios::out);
	if (fout.fail())
	{
		cout << "�ļ���ʧ��";
		exit(0);
	}
	fin.open(Code, ios::in | ios::binary);   //�����ļ�Ϊ�������ļ�
	if (fin.fail())
	{
		cout << "�ļ���ʧ��";
		exit(0);
	}
	char c, d;
	char a;
	int i;
	int tag;   //���ֶ����Ʊ����ļ��������ֽڻ���ż���ֽ�
	int r = sum & 7;    //��r = sum % 8������ʣ���һ���ֽ���Ч��λΪ��rλ
	int count = 8;
	Stack S;
	S = (Stack)malloc(sizeof(SqStack));
	if (!S)
	{
		cout << "�ļ���ʧ��";
		exit(0);
	}
	InitStack(S);
	fin.read(&c, sizeof(char));   //�ȶ�һ���ֽ�

	//���һ���ֽڵ�8λ�ĵ�λ�����зǱ����0����Ϊ���ַ�0/1����õ����ַ�������һ����8�ı���
	//���һ���ֽڵ�������
	while (!fin.eof())   //�������ļ�����
	{

		fin.read(&d, sizeof(char));   //һ�ζ�һ���ֽ�
		if (fin.eof())   
		{
			break;
		}
		while (count)
		{
			count--;
			a = c >> count;
			a = a & 0x01;    //ֻ�������λ
			a = a | 0x30;     //���0/1��Ӧ���ַ�

			Push(S, a);
			for (i = 1; i <= n; i++)
			{
				if (!strcmp(S->base, HC[i]))    //�ж��Ƿ��ҵ��˸ñ���
				{
					fout << HT[i].ch;
					ClearStack(S);
					break;
				}
			}
		}
		count = 8;
		c = d;
	}

	//��ʱ��ʣһ���ֽ�,Ҫ����tagλ�ж�ʣ�����c��ֵ����d��ֵ
	//cout << S->base;
	
	while (r)
	{
		r--;
		a = c >> r;
		a = a & 0x01;    //ֻ�������λ
		a = a | 0x30;     //���0/1��Ӧ���ַ�
		Push(S, a);
		for (i = 1; i <= n; i++)
		{
			if (!strcmp(S->base, HC[i]))    //�ж��Ƿ��ҵ��˸ñ���
			{
				fout << HT[i].ch;
				ClearStack(S);
				break;
			}
		}
	}
	fin.close();
	fout.close();
	free(S->base);
	free(S);
}
//********************************************************************
void InitStack(Stack S) //����һ����ջ
{
	S->base = (char*)malloc(Stack_Init_Size * sizeof(SqStack));
	if (!S->base)
	{
		printf("�洢�ռ����ʧ��");
		exit(OVERFLOW);
	}
	S->top = S->base;
	S->stacksize = Stack_Init_Size;
}
//********************************************************************
void Push(Stack S, char e)
{
	char* newbase;
	if (S->top - S->base >= S->stacksize)
	{
		printf("�洢�ռ䲻�㣬�����ӷ���");
		newbase = (char*)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(char));
		if (!newbase)
		{
			printf("�洢����ʧ��");
			exit(OVERFLOW);
		}
		S->base = newbase;
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}
	*(S->top) = e;
	(S->top)++;
	*(S->top) = '\0';
}
//********************************************************************
void Pop(Stack S, char& e)
{
	if (S->top == S->base)
		exit(0);
	(S->top)--;
	e = *(S->top);
	*(S->top) = '\0';
}
//********************************************************************
void ClearStack(Stack S)
{
	S->top = S->base;
}
//********************************************************************