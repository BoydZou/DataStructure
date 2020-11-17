#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<iomanip>

using namespace std;

#define Source "BUS.txt"
typedef struct BusStop
{
	int busNum;    //վ��������·
	int pre;       //�����·�ϵ���һ��վ��ͨ��վ����
	int next;      //�����·����һ��վ��ͨ��վ����
}BusStop;

typedef struct station
{
	int ID;               //վ����
	char name[50];        //վ����
	bool flag;            //���ڱ�Ǹ�վ�ڹ������ʱ�Ƿ�ʹ��
	vector<BusStop> Total_Next_Stations; //��վ���ڵ�������·������ͨվ
}Station;
typedef struct road
{
	int parent;         //���ڴ���·��
	int Num;            //����վ���
}Path;

vector<int> BusLine[1000];    //������

vector<Station> Graph;       //������·ͼ

int IsExist(char* name);   //���������ļ�ʱ�ж�վ���Ƿ��Ѵ���
void BFS_Station(char* start, char* finish);   //������վ���ٵ�·��   ����������վ����
void Min_BusLine(char* start, char* finish);   //�������ٵ�·�ߣ�����������վ����

int main()
{
	fstream file;
	file.open(Source, ios::in);
	if (file.fail())
	{
		cout << "�ļ���ʧ��";
		return 0;
	}
	Station temp;   //��ʱ�洢վ����
	int pre = 0, next, BusNum, Sta_Num, i = 0, j;
	char help[2] = { '\0','\0' };
	char Input[1000];
	temp.Total_Next_Stations.clear();
	temp.ID = 0;
	temp.flag = true;
	Graph.push_back(temp);    //��Ϊ0Ԫ�ش洢
	BusStop Adj_Station;
	char BusName[10], busname[10] = { '\0' };
	char sta_name[40] = {'\0'};
	while (!file.eof())
	{
		pre = 0;
		file >> BusName;  //�����ո�ͣ
		file >> Input;    //��ȡ������·��Ϣ
		if (file.eof())
		{
			break;
		}
		i = 0;
		while (BusName[i] >= '0' && BusName[i] <= '9')
		{
			help[0] = BusName[i];
			strcat_s(busname, 10, help);
			i++;
		}
		BusNum = atoi(busname);    //�õ����
		i = 0;
		while (i < strlen(Input))
		{
			while (Input[i] != ',' && Input[i] != '\n' && i < strlen(Input))
			{
				help[0] = Input[i];
				strcat_s(sta_name, 40, help);
				i++;
			}
			if (Input[i] != '\0')
			{
				i++;
			}
			Sta_Num = IsExist(sta_name);
			if (Sta_Num > 0)   //����վ����Ϣ
			{
				Adj_Station.pre = pre;
				Adj_Station.busNum = BusNum;
				Adj_Station.next = 0;
				Graph[Sta_Num].Total_Next_Stations.push_back(Adj_Station);
				//�޸���һ����վ�ڸ�·���ϵ���һ����վ��Ϣ
				if (pre != 0)   //��һ����վ�ı�Ų�Ϊ 0
				{
					//������һ����վ���޸�
					for (j = 0; j < Graph[pre].Total_Next_Stations.size(); j++)
					{
						if (Graph[pre].Total_Next_Stations[j].busNum == BusNum)
						{
							Graph[pre].Total_Next_Stations[j].next = Sta_Num;
							break;
						}
					}
				}
				pre = Sta_Num;    //�޸���һ����վ����һ����վΪ����վ
			}
			else     //վ����Ϣ������
			{
				Sta_Num = Graph.size();   //����վ������+1��Ҳ���������վ��ı��
				temp.flag = false;
				strcpy_s(temp.name, 40, sta_name);
				temp.ID = Sta_Num;
				temp.Total_Next_Stations.clear();
				Graph.push_back(temp);
				Adj_Station.busNum = BusNum;
				Adj_Station.next = 0;
				Adj_Station.pre = pre;
				Graph[Sta_Num].Total_Next_Stations.push_back(Adj_Station);    //������·�ϵĸ�վ����Ϣ�洢
				if (pre != 0)  //�޸ı���·�ϵ���һ����վ����Ϣ
				{
					for (j = 0; j < Graph[pre].Total_Next_Stations.size(); j++)
					{
						if (Graph[pre].Total_Next_Stations[j].busNum == BusNum)
						{
							Graph[pre].Total_Next_Stations[j].next = Sta_Num;
							break;
						}
					}
				}
				pre = Sta_Num;
			}
			BusLine[BusNum].push_back(Sta_Num);
			memset(sta_name, 0, 40);
			
		}
		memset(busname, 0, 10);
	}
	char start_station[40], finish_station[40];
	cout << "������Ҫ��ѯ·�ߵ�����վ��" << endl;
	cout << "��ʼվ��";
	cin >> finish_station;
	cout << "�յ�վ��";
	cin >> start_station;
	if (IsExist(start_station) == 0)
	{
		cout << "��ʼվ������" << endl;
	}
	else if(IsExist(finish_station) == 0)
	{
		cout << "�յ�վ������" << endl;
	}
	else
	{
		cout << "����վ�����ٵ�·�����£�" << endl;
		BFS_Station(start_station, finish_station);
		cout << endl;
		cout << "ת�����ٵ�·�����£�" << endl;
		Min_BusLine(start_station, finish_station);
	}
	cout << endl;
	system("pause");
	return 0;
}
//******************************************************************
void BFS_Station(char* start, char* finish)
{
	int start_ID, finish_ID;
	int size, j, i = 0, now;
	bool find = false;
	start_ID = IsExist(start);
	finish_ID = IsExist(finish);
	if (start_ID == finish_ID)
	{
		cout << "���վ���յ�վ��ͬ" << endl;
		return;
	}
	vector<Path> path;
	Path temp, Next;   //����ʱ��ʱʹ�õĽ��
	temp.parent = 0;
	temp.Num = 0;
	path.push_back(temp);
	temp.Num = start_ID;
	path.push_back(temp);   //������ʼվ
	Graph[start_ID].flag = true;  //ѡ����ʼ��
	i = 1;
	while (i < path.size())
	{
		temp = path[i];
		i++;
		if (temp.Num != finish_ID)  
		{
			for (j = 0; j < Graph[temp.Num].Total_Next_Stations.size(); j++)
			{   //��������վ�����·��
				Next.parent = i - 1;//��ǵ�ǰ���
				Next.Num = Graph[temp.Num].Total_Next_Stations[j].next;
				if (!Graph[Next.Num].flag)
				{
					path.push_back(Next);
					Graph[Next.Num].flag = true;
				}
				Next.Num = Graph[temp.Num].Total_Next_Stations[j].pre;
				if (!Graph[Next.Num].flag)
				{
					path.push_back(Next);
					Graph[Next.Num].flag = true;
				}
			}
		}
		else     //˵���ҵ����յ㣬��ʼ���·��
		{
			cout << Graph[temp.Num].name;
			now = temp.Num;
			temp = path[temp.parent];
			while (temp.parent != 0)
			{
				cout << "->";
				for (int j = 0; j < Graph[now].Total_Next_Stations.size(); j++)
				{
					for (int k = 0; k < Graph[temp.Num].Total_Next_Stations.size(); k++)
					{
						if (Graph[now].Total_Next_Stations[j].busNum == Graph[temp.Num].Total_Next_Stations[k].busNum)
						{
							cout << Graph[now].Total_Next_Stations[j].busNum << "· ";
						}
					}
				}
				cout << "->" << Graph[temp.Num].name;
				now = temp.Num;
				temp = path[temp.parent];
			}
			cout << "->";
			for (int j = 0; j < Graph[now].Total_Next_Stations.size(); j++)
			{
				for (int k = 0; k < Graph[path[1].Num].Total_Next_Stations.size(); k++)
				{
					if (Graph[now].Total_Next_Stations[j].busNum == Graph[path[1].Num].Total_Next_Stations[k].busNum)
					{
						cout << Graph[now].Total_Next_Stations[j].busNum << "· ";
					}
				}
			}
			cout << "->" << Graph[path[1].Num].name;
			for (j = 1; j < Graph.size(); j++)
			{
				Graph[j].flag = false;
			}
			find = true;
			break;
		}
	}
	if (!find)
	{
		cout << "��վ��֮��û��·�߿��Ե���" << endl;
		for (j = 1; j < Graph.size(); j++)   //��ձ�־λ��Ϊ�´β�ѯ��׼��
		{
			Graph[j].flag = false;
		}
	}
}
//******************************************************************
void Min_BusLine(char* start, char* finish)
{
	int start_ID, finish_ID, i, j, k;
	start_ID = IsExist(start);
	finish_ID = IsExist(finish);
	int line;
	/*struct line
	{
		int BusNum;
		int parent;
		int now;
	};
	
	queue<int>Q;
	queue<line>P;
	if (start_ID == finish_ID)
	{findBus
		cout << "���վ���յ�վ��ͬ" << endl;
		return;
	}
	int i, j;
	int now;
	//line temp;
	Q.push(start_ID);
	while (!Q.empty())
	{
		now = Q.front();
		Q.pop();
		for (i = 0; i < Graph[now].Total_Next_Stations.size(); i++)
		{
			for (j = 0; j < Graph[finish_ID].Total_Next_Stations.size(); j++)
			{
				if (Graph[now].Total_Next_Stations[i].busNum == Graph[finish_ID].Total_Next_Stations[j].busNum)
				{//�ж϶����Ƿ���һ����������
					find = true;
				}
			}
		}
	}*/

	bool find[1000];//���ڱ��·���Ƿ��Ѿ����
	for (i = 0; i < 1000; i++)
	{
		find[i] = true;
	}
	vector<Path> path;
	Path temp;
	temp.parent = 0;
	temp.Num = 0;
	path.push_back(temp);
	temp.Num = start_ID;  //��ʼ��
	path.push_back(temp);
	int nowstation;   //��ǰվ��
	int busNum;
	Path Next_Sta;
	i = 1;
	Graph[start_ID].flag= true;
	while (i < path.size())
	{
		temp = path[i];
		i++;
		//�ӵ�һ��վ�㿪ʼ�Ų飬�Ƿ����ͨ��ĳ��������ֱ�ӵ��յ�վ
		for (j = 0; j < Graph[temp.Num].Total_Next_Stations.size(); j++)
		{
			//����û������������·
			int line = Graph[temp.Num].Total_Next_Stations[j].busNum;
			if (find[line])
			{
				//��ʼ��������·
				find[line] = false;
				int k = 0;
				while (k < BusLine[line].size())
				{
					if (BusLine[line][k] != finish_ID)
					{
						//��վ�����յ�վ
						if (!Graph[BusLine[line][k]].flag)
						{
							Next_Sta.parent = i - 1;
							Next_Sta.Num = BusLine[line][k];
							path.push_back(Next_Sta);
							Graph[BusLine[line][k]].flag = true;
						}
					}
					else
					{
						//�õ����յ�վ
						//���·��
						if (temp.Num != finish_ID)
						{
							cout << Graph[finish_ID].name;
							cout << "->";
							for (j = 0; j < Graph[finish_ID].Total_Next_Stations.size(); j++)
							{
								for (k = 0; k < Graph[temp.Num].Total_Next_Stations.size(); k++)
								{
									if (Graph[finish_ID].Total_Next_Stations[j].busNum == Graph[temp.Num].Total_Next_Stations[k].busNum)
									{
										cout << Graph[finish_ID].Total_Next_Stations[j].busNum << "· ";
									}
								}
							}
							cout << "->";
						}
						cout << Graph[temp.Num].name;
						nowstation = temp.Num;
						temp = path[temp.parent];
						while (temp.parent != 0)
						{
							cout << "->";
							for (j = 0; j < Graph[nowstation].Total_Next_Stations.size(); j++)
							{
								for (k = 0; k < Graph[temp.Num].Total_Next_Stations.size(); k++)
								{
									if (Graph[nowstation].Total_Next_Stations[j].busNum == Graph[temp.Num].Total_Next_Stations[k].busNum)
									{
										cout << Graph[nowstation].Total_Next_Stations[j].busNum << "· ";
									}
								}
							}
							cout << "->" << Graph[temp.Num].name;
							nowstation = temp.Num;
							temp = path[temp.parent];
						}
						if (nowstation != path[1].Num)
						{
							cout << "->";
							for (int j = 0; j < Graph[nowstation].Total_Next_Stations.size(); j++)
							{
								for (int k = 0; k < Graph[path[1].Num].Total_Next_Stations.size(); k++)
								{
									if (Graph[nowstation].Total_Next_Stations[j].busNum == Graph[path[1].Num].Total_Next_Stations[k].busNum)
									{
										cout << Graph[nowstation].Total_Next_Stations[j].busNum << "· ";
									}
								}
							}
							cout << "->" << Graph[path[1].Num].name;
						}
						for (int j = 1; j < Graph.size(); j++)
						{
							Graph[j].flag = false;
						}
						return;
					}
					k++;
				}
			}
		}
	}
	for (int j = 1; j < Graph.size(); j++)
	{
		Graph[j].flag = false;
	}
	cout << "��վ֮��û��·��" << endl;
}
//******************************************************************
int IsExist(char* name)
{
	int i;
	for (i = 0; i < Graph.size(); i++)
	{
		if (!strcmp(Graph[i].name, name))
		{
			return i;
		}
	}
	return 0;
}
//******************************************************************