#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<Windows.h>
#include<TlHelp32.h>
#include<psapi.h>
#include<time.h>
#include<iomanip>
#pragma comment(lib,"Psapi.lib") 
using namespace std;
typedef struct Node 
{
	double t;
	int pId;
	char start_time[40];
	char IDName[100];
	SIZE_T Mem_Size;
	char end_time[40];
	double Work_Time;		//����ʱ��
	struct Node * pre;     //ָ��ǰ��
	struct Node * next;    //ָ����
}proNode, * pro;

void Get_Pro_Info(pro p);      //��ȡ����
SIZE_T Get_Pro_Mem(DWORD pId);//���ؽ���ռ�õ��ڴ��С
void Sort_Mem(pro p);      //���ڴ�����
void Sort_Time(pro Closed_head);   //������ʱ������
void Show_Process(pro p);      //��ʾ�����Ľ�����Ϣ
void Show_Close(pro p);     //��ʾ�ѽ����Ľ�����Ϣ
void Refresh(pro p, pro pCur, pro pEnd);	//���ݵ�ǰ������pCur����p����pEnd
void DestroyList(pro head);


int main()
{
	char ch = 'y';
	pro pCur, head, Closed_head;
	head = new proNode;		//��Ծ����
	Closed_head = new proNode;	//�����Ľ���
	if (!head || !Closed_head)
	{
		cout << "�ռ����ʧ��";
		return 0;
	}
	Closed_head->next = NULL;
	head->next = NULL;
	Get_Pro_Info(head);
	Sort_Mem(head);
	/*
	time_t rawtime;
	struct tm* info;
	info = new tm;

	time(&rawtime);

	localtime_s(info, &rawtime);
	asctime_s(buffer, info);
	cout<<"��ǰ�ı���ʱ������ڣ�"<<buffer;*/

	while (ch == 'y')
	{
		pCur = new proNode;		//��һ��Ľ���
		if (!pCur)
		{
			cout << "�ռ����ʧ��";
			return 0;
		}
		Get_Pro_Info(pCur);						//��ȡ�µĽ����б�
		Refresh(head, pCur, Closed_head);						//������������
		Sort_Mem(head);								//���ڴ�����
		Sort_Time(Closed_head);								//��ʱ������
		cout << "��ǰ����̣�" << endl;
		Show_Process(head);
		cout << endl << "�ѽ������̣�" << endl;
		Show_Close(Closed_head);
		DestroyList(pCur);
		cout << "�Ƿ������ʾ��(y or n):";
		cin >> ch;
		//Sleep(5*1000);
		system("cls");
	}
	DestroyList(head);
	DestroyList(Closed_head);

	system("pause");
	return 0;
}
//**************************************************************
void Get_Pro_Info(pro p)      //��ȡ����
{
	time_t rawtime;
	struct tm* info;
	info = new tm;
	int i = 1;
	pro cur, last;
	STARTUPINFO st_Info;
	PROCESS_INFORMATION Pro_Info;
	PROCESSENTRY32 ps;
	HANDLE HP;
	memset(&st_Info, 0, sizeof(STARTUPINFO));
	memset(&Pro_Info, 0, sizeof(PROCESS_INFORMATION));
	st_Info.cb = sizeof(STARTUPINFO);
	memset(&ps, 0, sizeof(PROCESSENTRY32));
	ps.dwSize = sizeof(PROCESSENTRY32);
	HP = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);	//��ȡ���̿���
	BOOL bMore = Process32First(HP, &ps);
	cur = p;
	p->pre = NULL;
	p->next = NULL;
	while (bMore) 
	{
		if (Get_Pro_Mem(ps.th32ProcessID) != -1) 
		{				//��ȡռ���ڴ��С
			last = new proNode;
			if (!last)
			{
				cout << "�ռ����ʧ��";
				exit(0);
			}
			last->t = clock();
			last->next = NULL;
			last->pId = ps.th32ProcessID;
			char* m_char;
			int len = WideCharToMultiByte(CP_ACP, 0, ps.szExeFile, wcslen(ps.szExeFile), NULL, 0, NULL, NULL);
			m_char = new char[len + 1];
			WideCharToMultiByte(CP_ACP, 0, ps.szExeFile, wcslen(ps.szExeFile), m_char, len, NULL, NULL);
			m_char[len] = '\0';

			strcpy_s(last->IDName, strlen(m_char) + 1, m_char);				//��ȡ������

			last->Mem_Size = Get_Pro_Mem(ps.th32ProcessID) / 1024;
			last->Work_Time = 0;
			time(&rawtime);
			localtime_s(info, &rawtime);
			asctime_s(last->start_time, info);
			last->pre = cur;
			cur->next = last;
			cur = cur->next;
		}
		bMore = Process32Next(HP, &ps);		//��ȡ��һ��������Ϣ
	}
	CloseHandle(HP);
}
//**************************************************************
SIZE_T Get_Pro_Mem(DWORD pId)//���ؽ���ռ�õ��ڴ��С
{
	HANDLE HP;
	PROCESS_MEMORY_COUNTERS pc;
	HP = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE, pId);
	if (HP)
	{
		if (GetProcessMemoryInfo(HP, &pc, sizeof(pc)))
		{
			return pc.WorkingSetSize;         //���ص�ǰ�ڴ�ʹ��
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
	//CloseHandle(HP);
}
//**************************************************************
void Sort_Mem(pro head)     //���ڴ�����
{
	pro p, q, temp, min, pre;
	if (head->next == NULL)
	{
		return;
	}
	q = head->next;
	
	p = new proNode;    //�����õ�ͷ���
	p->next = NULL;
	while (head->next)
	{
		pre = head;
		min = head->next;
		temp = min->next;
		while (temp)
		{
			if (temp->Mem_Size < min->Mem_Size)
			{
				min = temp;
			}
			temp = temp->next;
		}
		pre = min->pre;
		pre->next = min->next;
		if (min->next)
		{
			min->next->pre = pre;
		}

		min->next = p->next;
		p->next = min;
		if (min->next)
		{
			min->next->pre = min;
		}
		min->pre = p;
	}
	head->next = p->next;   //�������
	if (p->next)
	{
		p->next->pre = head;
	}
	delete p;  
}
//**************************************************************
void Sort_Time(pro Closed_head)   //������ʱ������
{
	pro temp_head, temp, pre, max;
	if (Closed_head->next == NULL)
	{
		return;
	}
	temp_head = new proNode;
	if (!temp_head)
	{
		cout << "�ռ����ʧ��";
		return;
	}
	temp_head->next = NULL;
	while (Closed_head->next)
	{
		pre = Closed_head;
		max = Closed_head->next;
		temp = max->next;
		while (temp)
		{
			if (temp->Work_Time > max->Work_Time)
			{
				max = temp;
				while (pre->next != max)
				{
					pre = pre->next;
				}
			}
			temp = temp->next;
		}
		pre->next = max->next;
		max->next = temp_head->next;
		temp_head->next = max;
	}
	Closed_head->next = temp_head->next;
	delete temp_head;
}
//**************************************************************
void Show_Process(pro head)      //��ʾ�����Ľ�����Ϣ
{
	pro temp;
	int num = 1;
	temp = head->next;
	//***********************
	using std::wcout;
	using std::cout;
	cout.setf(std::ios::left);
	cout.width(8);
	cout << "����ID��";
	cout.width(70);
	cout << "                                     ��������" ;
	cout.width(20);
	cout << "     �����ڴ棺";
	cout.width(10);
	cout << "       ����ʱ�䣺" ;
	cout << "   ��ʼʱ�䣺"<< endl;
	
	while (temp)
	{
		cout<< setw(8)<< right << temp->pId;
		cout << setw(70) << temp->IDName;
		cout << setw(10) << right << temp->Mem_Size << " KB     ";
		cout << setw(15) << right << temp->Work_Time<<" S     ";
		cout << temp->start_time;
		
		temp = temp->next;
	}
}
//**************************************************************
void Show_Close(pro head)     //��ʾ�ѽ����Ľ�����Ϣ
{
	pro temp;
	int num = 1;
	temp = head->next;
	using std::cout;
	cout.setf(std::ios::left);
	cout.width(8);
	cout << "  ����ID��";
	cout.width(70);
	cout << "                                     ��������";
	cout.width(20);
	cout << "       ����ʱ�䣺";
	cout.width(20);
	cout << "����ʱ�䣺" << endl;
	
	while (temp) 
	{
		cout << setw(8) << right << temp->pId;
		cout << setw(70)<< temp->IDName;
		cout << setw(10)<< right << temp->Work_Time<<" S     ";
		cout << temp->end_time;
		
		temp = temp->next;
	}
}
//**************************************************************
void Refresh(pro head, pro head_now, pro head_Closed)
{
	clock_t Now_Time;
	time_t rawtime;
	struct tm* info;
	info = new tm;

	/*time(&rawtime);

	localtime_s(info, &rawtime);
	asctime_s(buffer, info);*/
	pro temp_now, temp_end, temp_open, pre, temp, temp_close;   //temp_end����β���
	bool flag;
	temp_end = head_Closed;
	while (temp_end->next) //�ҵ��ѽ���������������һ�����
	{	
		temp_end = temp_end->next;
	}
	temp_open = head->next;
	while (temp_open) //�����򿪵Ľ���������ÿһ�����̣����ڵ�ǰ�����б�δ�ҵ��������ѱ��رգ�������ӵ��ѽ�����������
	{
		flag = false;   //����δ�ҵ�
		temp_now = head_now->next;
		while (temp_now != NULL) 
		{
			if (!strcmp(temp_open->IDName, temp_now->IDName) && temp_open->pId == temp_now->pId)	//˵������Ŀǰ�Ա���
			{
				flag = true;
				break;
			}
			temp_now = temp_now->next;
		}

		temp = temp_open;     //Ҫ�Ƴ��Ľ��
		temp_open = temp_open->next;    //�������������һ��
		if (!flag)    //˵��temp_open���ر�
		{
			//����ӹ����н���������ȡ������ӵ��ѹر�������
			pre = temp->pre;
			pre->next = temp->next;
			if (pre->next)
			{
				pre->next->pre = temp->pre;
			}
			//ժ��temp���
			Now_Time = clock();
			temp->Work_Time = (double)(Now_Time - temp->t) / CLOCKS_PER_SEC;
			
			time(&rawtime);
			localtime_s(info, &rawtime);
			asctime_s(temp->end_time, info);

			temp->next = temp_end->next;
			temp_end->next = temp;				//�ӵ�pEnd
			temp_end = temp_end->next;
		}
		else
		{
			Now_Time = clock();
			temp->Work_Time = (double)(Now_Time - temp->t) / CLOCKS_PER_SEC;
		}
	}

	temp_end = head;
	while (temp_end->next)
	{
		temp_end = temp_end->next;
	}

	temp_now = head_now->next;
	while (temp_now) 
	{		//������ǰ����������ÿһ�����̣�������Ѵ򿪽����б���δ�ҵ�����˵�����´򿪵Ľ��̣�Ȼ����ӵ��Ѵ򿪽��̵�β��
		flag = false;
		temp_open = head->next;
		while (temp_open) 
		{
			if (!strcmp(temp_open->IDName, temp_now->IDName) && temp_open->pId == temp_now->pId)	//�������ԭ���Ľ��̣����Թ�
			{
				flag = true;
				break;
			}
			temp_open = temp_open->next;
		}
		temp = temp_now;   //Ҫ���Ƴ��Ľ��
		temp_now = temp_now->next;    //���������ָ����һ��
		if (!flag)
		{	//˵�����´򿪵Ľ���
			pre = temp->pre;   
			pre->next = temp->next;
			if (pre->next)
			{
				pre->next->pre = temp->pre;
			}
			time(&rawtime);
			localtime_s(info, &rawtime);
			asctime_s(temp->start_time, info);
			temp->next = temp_end->next;
			temp_end->next = temp;
			temp_end = temp_end->next;
		}
	}

	temp_close = head_Closed->next; 
	while (temp_close)   //�ж��ѹرս����Ƿ����´�
	{
		flag = false;
		temp_now = head_now->next;
		while (temp_now)
		{
			if (!strcmp(temp_close->IDName, temp_now->IDName) && temp_close->pId == temp_now->pId)
			{//˵���ֱ���
				flag = true;
				break;
			}
			temp_now = temp_now->next;
		}
		temp = temp_close;                //��ǰ���
		temp_close = temp_close->next;    //ָ����һ��
		if (flag)
		{
			pre = head_Closed;
			while (pre->next != temp)
			{
				pre = pre->next;
			}
			pre->next = temp->next;
			delete temp;
		}
	}
}
//**************************************************************
void DestroyList(pro head)
{
	pro temp;
	temp = head->next;
	while (temp)
	{
		head->next = temp->next;
		delete temp;
		temp = head->next;
	}
	delete head;
}