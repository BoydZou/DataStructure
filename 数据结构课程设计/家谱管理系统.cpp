#include<iostream>
#include<queue>
#include<stack>
#include<fstream>

using namespace std;

#define Source "FamilyTree_Input.txt"
#define OutFile "Family_Tree_Result.txt"
typedef struct person
{
	int ID;          //���
	int parentID;    //���׵ı�ţ������Ҹ���
	char name[20];   //����
	bool IsMarry;    //1���ѻ�  0��δ��
	bool IsLive;     //�Ƿ�����
	char address[40];  //��ַ
	char Birth[20];    //����ʱ��
	char Dead_Time[20];  //����ʱ�䣬����������
	int x;              //���ʱ��x����
	int y;              //���ʱ��y����
	struct person* nextSibling;
	struct person* firstChild;

}Person, *Member;
int num = 0;                //��¼��Ա����
Member familyTree();                        //��������
Member findPerson_ID(int ID, Member T);     //���ݱ���ҳ�Ա
void Write_File(Member T);                  //������ļ�
void deletTree(Member p, Member T);         //ɾ������
void Print_Tree(Member T);                  //��ʾ����
void Show_Gen(int n, Member T);             //��ʾ��n����������Ϣ
void Show_Member(Member p);                 //��ʾ��Ա������Ϣ
Member findPerson_Birth(char* birth, Member T);//��������ʾ��Ա
void Search_ship(person*, person*);         //��ѯ���˹�ϵ
bool IsElder(Member p, Member q, Member T); //��ѯ�Ƿ��ǳ���
void AddChild(Member p);                    //���Ӻ���
Member findPerson_name(char* name, Member T);//�����������ҳ�Ա
void Delete(Member& p);                     //ɾ����pΪ������
int Depth(Member T);                       //����������
void Locate(Member T);                      //�Լ����еĽ�㶨λ

int main()
{
	Member T, ptr, temp;
	T = familyTree();
	char ch = 'y';
	int choice, n;
	char name[20], birthday[20], address[40];
	while (ch == 'y')
	{
		cout << "**************���׹���ϵͳ��ӭ��*************" << endl;
		cout << "1����ʾ����" << endl;
		cout << "2����ʾ��n����������Ϣ" << endl;
		cout << "3��ͨ��������ѯ��Ա��Ϣ" << endl;
		cout << "4��ͨ�����ղ�ѯ��Ա��Ϣ" << endl;
		cout << "5�������Ա��Ϊ����Ӻ���" << endl;
		cout << "6����ѯ���˹�ϵ" << endl;
		cout << "7��ɾ��ĳ��Ա������" << endl;
		cout << "8���޸ĳ�Ա��Ϣ" << endl;
		cout << "9������Ϣ������ļ�" << endl;
		cout << "��ѡ��Ҫ������Ŀ��";
		cin >> choice;
		switch (choice)
		{
		case 1:
			Print_Tree(T);
			break;
		case 2:
			cout << "������Ҫ��ѯ�ڼ�����";
			cin >> n;
			Show_Gen(n,T);
			break;
		case 3:
			cout << "������Ҫ��ѯ��������";
			cin >> name;
			ptr = findPerson_name(name, T);
			if (ptr == NULL)
			{
				cout << "�ó�Ա���ڼ�����" << endl;
			}
			else
			{
				cout << "������Ϣ���£�" << endl;
				Show_Member(ptr);
				temp = findPerson_ID(ptr->parentID, T);
				if (temp == NULL)
				{
					cout << "���Ǹü��������" << endl;
				}
				else
				{
					cout << "������Ϣ����: " << endl;
					Show_Member(temp);
				}
				if (ptr->firstChild)
				{
					cout << "������Ϣ���£�" << endl;
					temp = ptr->firstChild;
					Show_Member(temp);
					temp = temp->nextSibling;
					while (temp)
					{
						Show_Member(temp);
						temp = temp->nextSibling;
					}
				}
				else
				{
					cout << "��û�к���" << endl;
				}
			}
			break;
		case 4:
			cout << "������Ҫ��ѯ�ĳ�Ա�����գ�";
			cin >> birthday;
			ptr = findPerson_Birth(birthday, T);
			if (ptr == NULL)
			{
				cout << "�������޸ó�Ա" << endl;
			}
			else
			{
				cout << "�ó�Ա��Ϣ���£�" << endl;
				Show_Member(ptr);
			}
			break;
		case 5:
			cout << "������Ҫ��Ӻ��ӵĳ�Ա��: ";
			cin >> name;
			ptr = findPerson_name(name, T);
			if (ptr == NULL)
			{
				cout << "�ó�Ա���ڼ�����,�޷���Ӻ���" << endl;
			}
			else
			{
				AddChild(ptr);
				num++;
			}
			break;
		case 6:
			char name2[20];
			cout << "����������Ҫ��ѯ��ϵ��������Ա��" << endl;
			cout << "��Ա1��";
			cin >> name;
			ptr = findPerson_name(name, T);
			if (ptr == NULL)
			{
				cout << "��Ա1���ڼ�����" << endl;
				break;
			}
			cout << "��Ա2��";
			cin >> name2;
			temp = findPerson_name(name2, T);
			if (temp == NULL)
			{
				cout << "��Ա2���ڼ�����" << endl;
				break;
			}
			if (IsElder(ptr, temp, T))
			{
				cout << name << "��" << name2 << "�ĳ���" << endl;
			}
			else if(IsElder(temp,ptr,T))
			{
				cout << name2 << "��" << name << "�ĳ���" << endl;
			}
			else
			{
				cout << "����Ա�޹�ϵ" << endl;
			}
			break;
		case 7:
			cout << "������Ҫɾ����Ա��������������";
			cin >> name;
			ptr = findPerson_name(name, T);
			if (ptr == NULL)
			{
				cout << "�ó�Ա���ڼ�����" << endl;
			}
			else
			{
				deletTree(ptr, T);
			}
			break;
		case 8:
			cout << "������Ҫ�޸���Ϣ�ĳ�Ա����";
			cin >> name;
			ptr = findPerson_name(name, T);
			if (ptr == NULL)
			{
				cout << "�ó�Ա���ڼ�����" << endl;
			}
			else
			{
				char ch;
				cout << "1������" << endl;
				cout << "2������" << endl;
				cout << "3����ַ" << endl;
				cout << "4���Ƿ���" << endl;
				cout << "5���Ƿ�����" << endl;
				cout << "������Ҫ�޸ĵ���Ŀ��ţ�" << endl;
				cin >> choice;
				switch (choice)
				{
				case 1:
					cout << "������Ҫ�޸ĵ�������";
					cin >> name;
					cout << "ȷ�Ͻ������޸�Ϊ��" << name << "��?(y or n)";
					cin >> ch;
					if (ch == 'y')
					{
						strcpy_s(ptr->name, 20, name);
						cout << "�����޸ĳɹ�";
					}
					else
					{
						cout << "ȡ���޸�" << endl;
					}
					break;
				case 2:
					cout << "������Ҫ�޸����գ�";
					cin >> birthday;
					cout << "ȷ�Ͻ������޸�Ϊ��" << birthday << "��?(y or n)";
					cin >> ch;
					if (ch == 'y')
					{
						strcpy_s(ptr->Birth, 20, birthday);
						cout << "�����޸ĳɹ�";
					}
					else
					{
						cout << "ȡ���޸�" << endl;
					}
					break;
				case 3:
					cout << "������Ҫ�޸ĵĵ�ַ��";
					cin >> address;
					cout << "ȷ�Ͻ���ַ�޸�Ϊ��" << address << "��?(y or n)";
					cin >> ch;
					if (ch == 'y')
					{
						strcpy_s(ptr->address, 20, address);
						cout << "��ַ�޸ĳɹ�";
					}
					else
					{
						cout << "ȡ���޸�" << endl;
					}
					break;
				case 4:
					cout << "�������Ƿ��ѻ飨1���ѻ� 0��δ�飩��";
					cin >> ch;
					if (ch == '1')
					{
						cout << "ȷ�Ͻ��޸�Ϊ�ѻ���?(y or n)";
						cin >> ch;
						if (ch == 'y')
						{
							ptr->IsMarry = true;
							cout << "�޸ĳɹ�";
						}
						else
						{
							cout << "ȡ���޸�" << endl;
						}
					}
					else
					{
						cout << "ȷ�Ͻ��޸�Ϊδ����?(y or n)";
						cin >> ch;
						if (ch == 'y')
						{
							ptr->IsMarry = false;
							cout << "�޸ĳɹ�";
						}
						else
						{
							cout << "ȡ���޸�" << endl;
						}
					}
					break;
				case 5:
					cout << "�������Ƿ�������1������ 0��ȥ������";
					cin >> ch;
					if (ch == '1')
					{
						cout << "ȷ�Ͻ��޸�Ϊ������?(y or n)";
						cin >> ch;
						if (ch == 'y')
						{
							ptr->IsLive = true;
							cout << "�޸ĳɹ�";
						}
						else
						{
							cout << "ȡ���޸�" << endl;
						}
					}
					else
					{
						cout << "ȷ�Ͻ��޸�Ϊδ����?(y or n)";
						cin >> ch;
						if (ch == 'y')
						{
							ptr->IsLive = false;
							cout << "�޸ĳɹ�";
						}
						else
						{
							cout << "ȡ���޸�" << endl;
						}
					}
					break;
				default:
					break;
				}
			}
			break;
		case 9:
			Write_File(T);
			break;

		default:
			break;
		}
		cout << endl << "�Ƿ����ʹ��ϵͳ��y or n��:";
		cin >> ch;
		//system("cls");
	}
	system("pause");
	return 0;
}
//*************************************************************************
Member familyTree()
{
	fstream file;
	file.open(Source, ios::in);
	Member T, temp, parent;
	if (file.fail())
	{
		cout << "�ļ���ʧ��";
		exit(0);
	}
	T = new Person;
	if (!T)
	{
		cout << "�ռ����ʧ��";
		exit(0);
	}
	T->parentID = 0;
	T->firstChild = NULL;
	T->nextSibling = NULL;
	int i, j;
	char ID[5] = { '\0'};
	char parentID[5] = { '\0' };
	char help[2] = { '\0','\0' };
	char name[20] = { '\0' };
	char Birth[20] = { '\0' };    //����ʱ��
	char Dead_Time[20] = {'\0'};  //����ʱ�䣬����������
	char address[40] = { '\0' };
	char inputLine[128] = { '\0' };
	while (!file.eof())
	{
		file.getline(inputLine, 128);
		if (file.eof())
		{
			break;
		}
		if (num == 0)
		{
			temp = T;
			num++;
		}
		else
		{
			temp = new person;
			num++;
		}
		i = 0;

		//��ȡID
		while (inputLine[i] == '\t' || inputLine[i] == '\n' || inputLine[i] == ' ')
		{ 
			i++;
		}
		while (inputLine[i] != '\t' && inputLine[i] != '\n' && inputLine[i] != ' ')
		{
			help[0] = inputLine[i];
			strcat_s(ID, 5,help);
			i++;
		}
		temp->ID = atoi(ID);
		
		while (inputLine[i] == '\t' || inputLine[i] == '\n' || inputLine[i] == ' ')
		{
			i++; 
		}
		while (inputLine[i] != '\t' && inputLine[i] != '\n' && inputLine[i] != ' ')
		{
			help[0] = inputLine[i];
			strcat_s(name, 20, help);
			i++;
		}
		strcpy_s(temp->name, 20, name);

		while (inputLine[i] == '\t' || inputLine[i] == '\n' || inputLine[i] == ' ')
		{
			i++;
		}
		while (inputLine[i] != '\t' && inputLine[i] != '\n' && inputLine[i] != ' ')
		{
			help[0] = inputLine[i];
			strcat_s(parentID, 5, help);
			i++;
		}
		temp->parentID = atoi(parentID);
		while (inputLine[i] == '\t' || inputLine[i] == '\n' || inputLine[i] == ' ')
		{
			i++;
		}
		while (inputLine[i] != '\t' && inputLine[i] != '\n' && inputLine[i] != ' ')
		{
			help[0] = inputLine[i];
			strcat_s(Birth, 20, help);
			i++;
		}
		strcpy_s(temp->Birth, 20, Birth);

		while (inputLine[i] == '\t' || inputLine[i] == '\n' || inputLine[i] == ' ')
		{
			i++;
		}
		if (inputLine[i] == '1')
		{
			temp->IsMarry = true;    //˵���ѽ��
		}
		else if (inputLine[i] == '0')
		{
			temp->IsMarry = false;
		}
		else
		{
			cout << "�������ݴ���" << endl;
			exit(0);
		}
		i++;

		while (inputLine[i] == '\t' || inputLine[i] == '\n' || inputLine[i] == ' ')
		{
			i++;
		}
		while (inputLine[i] != '\t' && inputLine[i] != '\n' && inputLine[i] != ' ')
		{
			help[0] = inputLine[i];
			strcat_s(address, 40, help);
			i++;
		}
		strcpy_s(temp->address, 40, address);

		//�Ƿ�����
		while (inputLine[i] == '\t' || inputLine[i] == '\n' || inputLine[i] == ' ')
		{
			i++;
		}
		if (inputLine[i] == '1')
		{
			temp->IsLive = true;
		}
		else if (inputLine[i] == '0')
		{   //��������¼����ʱ��
			temp->IsLive = false;
			i++;
			while (inputLine[i] == '\t' || inputLine[i] == '\n' || inputLine[i] == ' ')
			{
				i++;
			}
			while (inputLine[i] != '\t' && inputLine[i] != '\n' && inputLine[i] != ' ' && inputLine[i] != '\r' && inputLine[i] != '\0')
			{
				help[0] = inputLine[i];
				strcat_s(Dead_Time, 20, help);
				i++;
			}
			strcpy_s(temp->Dead_Time, 20, Dead_Time);
		}
		else
		{
			cout << "�������ݴ���" << endl;
			exit(0);
		}
		temp->firstChild = NULL;
		temp->nextSibling = NULL;
		//�������뵽������ȷλ����
		parent = findPerson_ID(temp->parentID,T);
		if (parent != NULL)
		{
			if (parent->firstChild == nullptr)
			{
				parent->firstChild = temp;
			}
			else
			{
				parent = parent->firstChild;
				while (parent->nextSibling != nullptr)
				{
					parent = parent->nextSibling;
				}
				parent->nextSibling = temp;
			}
		}
		memset(inputLine, 0, 128);
		memset(name, 0, 20);
		memset(ID, 0, 5);
		memset(address, 0, 40);
		memset(Birth, 0, 20);
		memset(Dead_Time, 0, 20);
		memset(parentID, 0, 5);
	}
	file.close();
	return T;
}
//*************************************************************************
Member findPerson_ID(int ID, Member T)
{
	Member p = T;
	stack<Member> S;
	while (!S.empty() || p)
	{
		if (p)
		{
			if (p->ID == ID)
			{
				return p;
			}
			S.push(p);
			p = p->firstChild;
		}
		else
		{
			p = S.top();
			S.pop();
			p = p->nextSibling;
		}
	}
	return NULL;
}
//*************************************************************************
Member findPerson_name(char* name, Member T)
{
	Member p = T;
	stack<Member> S;
	while (!S.empty() || p)
	{
		if (p)
		{
			if (!strcmp(name,p->name))
			{
				return p;
			}
			S.push(p);
			p = p->firstChild;
		}
		else
		{
			p = S.top();
			S.pop();
			p = p->nextSibling;
		}
	}
	return NULL;
}
//*************************************************************************
Member findPerson_Birth(char* birth, Member T)
{
	Member p = T;
	stack<Member> S;
	while (!S.empty() || p)
	{
		if (p)
		{
			if (!strcmp(birth, p->Birth))
			{
				//Show_Member(p);
				return p;
			}
			S.push(p);
			p = p->firstChild;
		}
		else
		{
			p = S.top();
			S.pop();
			p = p->nextSibling;
		}
	}
	return NULL;
}
//*************************************************************************
void deletTree(Member p, Member T)
{
	Member parent;
	Member del;
	if (p == T)
	{
		delete(T);
		return;
	}
	parent = findPerson_ID(p->parentID,T);
	if (parent->firstChild == p)   //p����˫�׵ĵ�һ������
	{
		del = p;
		parent->firstChild = p->nextSibling;   //˫�׵�һ������ָ��ָ������һ�����Ӽ���
		Delete(p);
	}
	else
	{
		parent = parent->firstChild;
		while (parent->nextSibling != NULL && parent->nextSibling != p)   //һֱ�ҵ�Ҫɾ���������ĸ����p
		{
			parent = parent->nextSibling;
		}
		del = p;
		parent->nextSibling = p->nextSibling;
		Delete(p);
	}
	cout << "ɾ���ɹ�" << endl;
}
//*************************************************************************
void Delete(Member& p)//ɾ����pΪ��������
{
	if (p)
	{
		Delete(p->firstChild);
		Delete(p->nextSibling);
		delete p;
	}
}
//*************************************************************************
void Show_Gen(int n, Member T)
{
	queue<Member> Q;   //�������
	Member p, q;
	int level = 0;
	int Dep, len;
	Dep = Depth(T);
	if (n > Dep)
	{
		cout << "��ѯ�Ĵ������ڼ��׵Ĵ���" << endl;
		return;
	}
	if (T == NULL)
	{
		cout << "����Ϊ��" << endl;
		return;
	}
	Q.push(T);
	while (!Q.empty())
	{
		len = Q.size();
		level++;   //����
		while (len--)
		{
			p = Q.front();
			Q.pop();
			if (level == n)
			{
				Show_Member(p);
			}
			if (p->firstChild)
			{
				q = p->firstChild;
				Q.push(q);
				while (q->nextSibling)   //���к������
				{
					q = q->nextSibling;
					Q.push(q);
				}
			}
		}
	}
}
//*************************************************************************
int Depth(Member T)
{
	if (T == NULL)
	{
		return 0;
	}
	else
	{
		return ((Depth(T->firstChild) + 1) > Depth(T->nextSibling)) ? (Depth(T->firstChild) + 1) : Depth(T->nextSibling);
	}
}
//*************************************************************************
void Show_Member(Member p)
{
	if (p == NULL)
	{
		cout << "�ó�Ա������" << endl;
	}
	cout << "�ó�Ա������Ϣ����" << endl;
	cout << "���:		" << p->ID << endl;
	cout << "����:		" << p->name << endl;
	cout << "��������:	" << p->Birth << endl;
	if (p->IsMarry) 
	{ 
		cout << "�ѻ�"; 
	}
	else
	{
		cout << "δ��";
	}
	cout << endl;
	cout << "��ͥ��ַ:	" << p->address << endl;
	if (p->IsLive)
	{
		cout << "����" << endl;
	}
	else
	{
		cout << "��ȥ��" << endl;
		cout << "ȥ��ʱ��Ϊ: " << p->Dead_Time << endl;
	}
}
//*************************************************************************
void Relationship(Member p, Member q, Member T)
{
	if (IsElder(p, q, T))
	{
		cout << " " << p->name << " �� " << q->name << "�ĳ���" << endl;
	}
	else
	{
		if (IsElder(q, p, T))
		{
			cout << " " << q->name << " �� " << p->name << "�ĳ���" << endl;
		}
	}
}
//*************************************************************************
bool IsElder(Member p, Member q, Member T)
{
	//�ж�p�Ƿ���q�ĳ���
	Member temp;
	temp = q;
	if (p == NULL || q == NULL)
	{
		cout << "��ѯ��ϵ����";
		return false;
	}
	while (temp->parentID != 0)
	{
		temp = findPerson_ID(temp->parentID, T);
		if (temp->ID == p->ID)
		{
			return true;
		}
	}
	return false;
}
//*************************************************************************
void AddChild(Member p)
{
	if (p == NULL)
	{
		return;
	}
	Member temp, index;
	int IsMerry, IsDead;
	temp = new person;
	//temp = p->firstChild;
	if (p->firstChild == NULL)  //�ó�Աû�к���
	{
		p->firstChild = temp;
	}
	else
	{
		index = p->firstChild;
		while (index->nextSibling)
		{
			index = index->nextSibling;
		}
		//��ʱindex����һ���ֵ�Ϊtemp
		index->nextSibling = temp;
	}
	temp->firstChild = NULL;
	temp->nextSibling = NULL;
	//cout << "�������ţ�";
	//cin >> temp->ID;
	temp->ID = num + 1;
	cout << "����������";
	cin >> temp->name;
	temp->parentID = p->ID;
	cout << "����������ڣ�";
	cin >> temp->Birth;
	cout << "�Ƿ��飨1/0����";
	cin >> IsMerry;
	temp->IsMarry = (IsMerry == 1) ? true : false;
	cout << "�����ַ��";
	cin >> temp->address;
	cout << "�Ƿ�������1/0����";
	cin >> IsDead;
	if (IsDead == 1)
	{
		temp->IsLive = false;
		cout << "�����������ڣ�";
		cin >> temp->Dead_Time;
	}
	else
	{
		temp->IsLive = 1;
	}
	cout << "��ӳɹ�!" << endl;
}
//*************************************************************************
void Locate(Member T)   //��λ���
{
	stack<Member> S;
	queue<Member> Q;
	Member p, temp;
	int x = 1, y = 1;
	int len;
	int level = 0;
	p = T;
	while (p || !S.empty())
	{
		if (p)
		{
			S.push(p);
			p = p->firstChild;
		}
		else
		{
			p = S.top();
			S.pop();
			p->x = x++;
			p = p->nextSibling;
		}
	}//��λx
	/*
	while (!S.empty() || p)
	{
		if (p)
		{
			if (!strcmp(name,p->name))
			{
				return p;
			}
			S.push(p);
			p = p->firstChild;
		}
		else
		{
			p = S.top();
			S.pop();
			p = p->nextSibling;
		}
	}
	*/
	p = T;
	Q.push(p);
	while (!Q.empty())
	{
		len = Q.size();
		level++;
		while (len--)
		{
			p = Q.front();
			Q.pop();
			p->y = level;
			if (p->firstChild)
			{
				temp = p->firstChild;
				Q.push(temp);
				temp = temp->nextSibling;
				while (temp)
				{
					Q.push(temp);
					temp = temp->nextSibling;
				}
			}
		}
	}
}
//*************************************************************************
void Print_Tree(Member T)  //����
{
	cout << endl;
	Locate(T);
	Member p, temp, draw;// , pre;
	queue<Member>Q;
	int count = 0, num = 0, len, pre = -1;
	p = T;
	Q.push(p);
	queue<Member> W;
	while (!Q.empty())
	{
		count = 0;
		//line = 0;
		len = Q.size();
		while (len--)
		{
			p = Q.front();
			Q.pop();
			W.push(p);
			//W.push(p->firstChild);
			count = (p->x - count);
			num = count * 1;
			while (num--)
			{
				if (pre == p->parentID)
				{
					cout << "-";
				}
				else
				{
					cout << " ";
				}
			}
			cout << p->name;
			if (p->firstChild)
			{
				temp = p->firstChild;
				Q.push(temp);
				temp = temp->nextSibling;
				while (temp)
				{
					Q.push(temp);
					temp = temp->nextSibling;
				}
			}
			pre = p->parentID;
			
		}
		count = 0;
		cout << endl;
		while (!W.empty())
		{
			draw = W.front();
			W.pop();
			count = (draw->x - count);
			num = count * 1;
			while (num--)
			{
				cout << " ";
			}
			if (draw->firstChild)
			{
				cout << " |   ";
			}
			else
			{
				cout << "       ";
			}
		}
		cout << endl << endl;
	}
}
//*************************************************************************
void Write_File(Member T)
{
	fstream file;
	file.open(OutFile, ios::out);
	if (file.fail())
	{
		cout << "�ļ���ʧ��";
		return;
	}
	if (T == NULL)
	{
		return;
	}
	queue<Member>Q;
	Member p, q;
	p = T;
	Q.push(p);
	while (!Q.empty())
	{
		p = Q.front();
		Q.pop();
		file << p->ID << "\t" << p->name << "\t\t" << p->parentID << "\t" << p->Birth << "\t\t";
		if (p->IsMarry)
		{
			file << "1";
		}
		else
		{
			file << "0";
		}
		file << "\t" << p->address << "\t\t";
		if (p->IsLive)
		{
			file << "1" << endl;
		}
		else
		{
			file << "0\t" << p->Dead_Time << endl;
		}
		if (p->firstChild != NULL)
		{
			Q.push(p->firstChild);
			q = p->firstChild->nextSibling;
			while (q)
			{
				Q.push(q);
				q = q->nextSibling;
			}
		}
	}
	file.close();
}
//*************************************************************************