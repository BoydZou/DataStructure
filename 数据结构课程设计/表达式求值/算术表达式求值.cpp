#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

#define MAX 1000
#define Stack_Init_Size  100
#define STACKINCREMENT   40

typedef struct
{
	char* base;//ջ��ָ��
	char* top;//ջ��
	int size;//ջ�Ĵ�С
}TR,*OPTR;//�����ջ

typedef struct
{
	float* base;//ջ��ָ��
	float* top;//ջ��
	int size;//ջ�Ĵ�С

}ND, *OPND;//����ջ


int Init(TR& S);                          //��ʼ�������ջ�������������ջ
int Push(TR& S, char e);                  //�������ջ�������������ջS�������e
int Pop(TR& S, char& e);                  //�������ջ�������������ջS���ַ�e
int Gettop(TR S, char& e);                //ȡ�����ջջ��Ԫ�أ������������ջS���ַ�e
int Init_Data(ND& S);                     //��ʼ������ջ������������ջ
int Push_Data(ND& S, float e);            //������ջ����������ջS������e
int Pop_Data(ND& S, float& e);            //���ֵ�ջ������������ջS������e
int Gettop_Data(ND S, float& e);          //ȡ����ջջ��Ԫ�أ�����������ջ������e
char Judge(char a, char b);               //�ж���������ȼ������������������a��b
int IsOptr(char c);                       //�ж��Ƿ�Ϊ��������������ַ�c
float cal_ans(float a, char k, float b);  //����akb�Ľ����kΪ�������a��bΪ���֣�����������a�������k������b
int Get_Answer(char* input, float& ans);       //��������ʽa����ans
int TraveraseOptr(TR S);                  //��������ջ
int TraveraseOpnd(ND S);                  //����������ջ
int BracketMatch(char* a);                    //���������Ƿ�ƥ��

int main()
{
	char a[MAX];   //�������
	char c[MAX] = {'\0'};   //���ڴ�����ţ���������ƥ��
	int i, j = 0;   //���ڱ���
	int flag = 0;   //��ʾ��ǰ��ʽ���޵Ⱥ�
	float ans;    //�洢���ս��
	int left = 0, right = 0;//ͳ��������������
	cout << "������Ҫ����ı��ʽ��" << endl;
	cin.getline(a, MAX);
	if (a[0] != '#')
	{
		cout << "[����] ���ʽ�Ŀ�ͷӦΪ'#'" << endl;
		system("pause");
		return -1;
	}//��ʱa[0] == '#'
	flag = 0;
	for (i = 1; i < strlen(a); i++)  //�����жϱ��ʽ�Ƿ�Ϸ�
	{
		if (a[i] == '(')
		{
			c[j] = '(';
			j++;
			c[j] = '\0';   //��֤�����βΪ\0
			left++;
		}
		else if (a[i] == ')')
		{
			c[j] = ')';
			j++;
			c[j] = '\0';
			right++;
		}
		else if (a[i] == '/' && a[i + 1] == '0')
		{
			cout << "[����]��������Ϊ0";
			system("pause");
			return -1;
		}
		else if (!(a[i] == '.' || IsOptr(a[i]) || isdigit(a[i])))
		{
			cout << "�в��Ϸ��ַ�����" << endl;
			system("pause");
			return -1;
		}
	}
	if (left != right)
	{
		cout << "�������Ų�ƥ��";
		system("pause");
		return -1;
	}
	else
	{
		if (!BracketMatch(c))//���ü������ƥ�亯��
		{
			system("pause");
			return 0;
		}
		else if (Get_Answer(a, ans))
		{
			cout << "���ʽ�Ľ��Ϊ��" << ans << endl;
			system("pause");
			return 0;
		}
	}
}
//********************************************************************
int Init(TR &S)//��ʼ�������ջ�������������ջ����
{
	S.base = (char*)malloc(Stack_Init_Size * sizeof(char));
	if (S.base == NULL)
	{
		cout << "�洢�ռ����ʧ��";
		exit(0);
	}
	S.size = Stack_Init_Size;
	S.top = S.base;
	return 1;
}
//********************************************************************
int Push(TR& S, char e)//�������ջ�������������ջs���ã������e
{
	char* newbase;
	if (S.top - S.base >= S.size)
	{
		printf("�洢�ռ䲻�㣬�����ӷ���");
		newbase = (char*)realloc(S.base, (S.size + STACKINCREMENT) * sizeof(char));
		if (!newbase)
		{
			printf("�洢����ʧ��");
			exit(OVERFLOW);
		}
		S.base = newbase;
		S.top = S.base + S.size;
		S.size += STACKINCREMENT;
	}
	*S.top = e;
	S.top++;
	return 1;
}
//********************************************************************
int Pop(TR& S, char& e)
{
	if (S.top == S.base)
	{
		return -1;
	}
	S.top--;
	e = *(S.top);
	return 1;
}
//********************************************************************
int Gettop(TR S, char& e)//ȡ�����ջջ��Ԫ�أ������������ջs���ַ�e
{
	if (S.top == S.base)
	{
		exit(-1);
	}
	e = *(S.top-1);
	return 1;
}
//********************************************************************
int Init_Data(ND& S)//��ʼ������ջ������������ջ����
{
	S.base = (float*)malloc(Stack_Init_Size * sizeof(float));
	if (S.base == NULL)
	{
		cout << "�洢�ռ����ʧ��";
		exit(0);
	}
	S.size = Stack_Init_Size;
	S.top = S.base;
	return 1;
}
//********************************************************************
int Push_Data(ND& S, float e)//�������ջ�������������ջs���ã������e
{
	float* newbase;
	if (S.top - S.base >= S.size)
	{
		printf("�洢�ռ䲻�㣬�����ӷ���");
		newbase = (float*)realloc(S.base, (S.size + STACKINCREMENT) * sizeof(float));
		if (!newbase)
		{
			printf("�洢����ʧ��");
			exit(0);
		}
		S.base = newbase;
		S.top = S.base + S.size;
		S.size += STACKINCREMENT;
	}
	*S.top = e;
	S.top++;
	return 1;
}
//********************************************************************
int Pop_Data(ND& S, float& e)
{
	if (S.top == S.base)
	{
		return -1;
	}
	S.top--;
	e = *(S.top);
	return 1;
}
//********************************************************************
int Gettop_Data(ND S, float& e)//ȡ����ջջ��Ԫ�أ�����������ջ������e
{
	if (S.top == S.base)
	{
		exit(-1);
	}
	e = *(S.top - 1);
	return 1;
}
//********************************************************************
char Judge(char a, char b)//�ж����ȼ�
{
	switch (a)
	{
	case '+':
		if (b == '+' || b == '-' || b == ')' || b == '#')
		{
			return '>';
		}
		else
		{
			return '<';
		}
	case '-':
		if (b == '+' || b == '-' || b == ')' || b == '#')
		{
			return '>';
		}
		else
		{
			return '<';
		}
	case '*':
		if (b == '(')
		{
			return '<';
		}
		else
		{
			return '>';
		}
	case '/':
		if (b == '(')
		{
			return '<';
		}
		else
		{
			return '>';
		}
	case '#':
		if (b == '#')
		{
			return '=';
		}
		else if (b == ')')
		{
			return '0';
		}
		else
		{
			return '<';
		}
	case '(':
		if (b == ')')
		{
			return '=';
		}
		else if (b == '#')
		{
			return '0';
		}
		else
		{
			return '<';
		}
	case ')':
		if (b == '(')
		{
			return ' ';
		}
		else
		{
			return '>';
		}

	default:
		return '0';
	}
}
//********************************************************************
int IsOptr(char c)//�ж��Ƿ�Ϊ��������������ַ�c
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '#')
	{
		return 1;
	}
	return 0;
}
//********************************************************************
float cal_ans(float a, char k, float b)//����akb�Ľ����kΪ�������a��bΪ���֣�����������a�������k������b
{
	switch (k)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	default:
		return 0.0;
	}
}
//********************************************************************
int Get_Answer(char* input, float& ans)//��������ʽa����ans
{
	TR optr;
	ND opnd;     //��������ջ
	int i = 0;   //���ڱ���
	float data;
	char t[20] = {0};
	char help[2] = { '#', '\0' };
	//char* c;
	char e;
	char x;
	float a, b;
	int flag = 0;//��¼���޴���

	Init(optr);   //��ʼ������ջ
	Init_Data(opnd);  //��ʼ������ջ
	Push(optr, input[i]);   //����#��
	i++;
	TraveraseOptr(optr);
	Gettop(optr, e);
	cout << "�������У�" << &input[i] << endl << endl;
	while (input[i] != '#' || e != '#')
	{
		if (!IsOptr(input[i]))
		{
			help[0] = input[i];
			strcat_s(t, 20, help);
			i++;
			if (IsOptr(input[i]) || input[i] == '#')
			{
				data = atof(t);
				Push_Data(opnd, data);
				TraveraseOpnd(opnd);
				strcpy_s(t, 20, "\0");
				//printf("%.2f, ", data);
			}
		}
		else
		{
			switch (Judge(e, input[i]))
			{
			case '<':
				Push(optr, input[i]);    //�����ѹջ
				TraveraseOptr(optr);
				i++;
				break;
			case '=':
				Pop(optr, e);    //���������
				TraveraseOptr(optr);
				i++;
				break;
			case '>':
				Pop(optr, e);
				TraveraseOptr(optr);
				//
				if (opnd.top - opnd.base < 2)
				{
					cout << "���ʽ���������������������ƥ�䣬��ʽ����" << endl;
					system("pause");
					//flag = 1;
					return 0;
				}
				else
				{
					Pop_Data(opnd, b);
					Pop_Data(opnd, a);   //��������������,a��������b����
					TraveraseOpnd(opnd);
					if (e == '/' && b == 0)
					{
						cout << "[����]��������Ϊ0" << endl;
						system("pause");
						return 0;
					}
					else   //��������ջ
					{
						Push_Data(opnd, cal_ans(a, e, b));
						TraveraseOpnd(opnd);
					}
				}
				break;
			}
			cout << "�������У�" << &input[i] << endl << endl;
		}
		Gettop(optr, e);
	}
	cout << endl;
	Gettop_Data(opnd, ans);   //ȡ��ջ����
	free(opnd.base);
	free(optr.base);
	return 1;
}
//********************************************************************
int TraveraseOptr(TR S)
{
	char* p;
	cout << "�����ջ��";
	for (p = S.base; p < S.top; p++)
	{
		cout << *p << " ";
	}
	cout << endl;
	return 1;
}
//********************************************************************
int TraveraseOpnd(ND S)
{
	float* p;
	cout << "������ջ��";
	for (p = S.base; p < S.top; p++)
	{
		cout << *p << " ";
	}
	cout << endl;
	return 1;
}
//********************************************************************
int BracketMatch(char* a)
{
	int i = 0, n = strlen(a);
	char e;
	TR bracket;   //����ջ
	Init(bracket);
	for (i = 0; i < n; i++)
	{
		switch (a[i])
		{
		case '(':   //��������ѹջ
			Push(bracket, a[i]);   
			break;
		case ')':
			if (bracket.base == bracket.top)   //��ջ�գ��������Ŷ���
			{
				cout << "[����]�������Ŷ���" << endl;
				return 0;
			}
			Pop(bracket, e);   //����ջ��Ԫ��
			if (e != '(')  //˵����ƥ��
			{
				cout << "[����]�������Ų�ƥ��" << endl;
				return 0;
			}
			break;
		default:
			break;
		}
	}
	if (bracket.base != bracket.top)   //ջ����,�ж����������
	{
		cout << "[����]�ж����������" << endl;
		return 0;
	}
	free(bracket.base);
	return 1;
}
//********************************************************************