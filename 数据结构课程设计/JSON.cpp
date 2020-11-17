//JSON
#include<iostream>
#include<map>
#include<string>
#include<fstream>
using namespace std;
//��ֵ������ 
map<string, string> mp;

void format(string& s)
{
	//���ַ���s�е�ת���ַ�\ɾ��������������һ���ַ�
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '\\')
		{
			s.erase(s.begin() + i);
		}
	}
}

//����������ֵ
void deal(string& json, string& add)
{
	int count, i, j;
	string key, value;
	for (i = 0; i < json.size(); i++)
	{
		if (json[i] == '"')   //˫���ſ�ʼ
		{
			j = json.find(':', i + 1);   //��i+1λ�ÿ�ʼ�� ':'
			//�ҵ�:  ��������������value
			key = json.substr(i + 1, j - i - 2);  //��ȡ""������Ӵ� 
			if (add == "")    //��һ��û�в�ѯ��С�������ʽ
			{
				key = add + key;
			}
			else		   //��һ���� 
			{
				key = add + '.' + key;
			}
			if (json[j + 1] == '"')    //˵�����治�Ƕ������ַ���
			{
				if (json.find(',', j + 1) != -1)   //���ҵ�',' ˵��
				{
					i = json.find(',', j + 1);
				}
				else                         //û�ҵ���˵��������
				{
					i = json.size() - 1;
				}
				value = json.substr(j + 2, i - j - 3);
				format(key);   //ȥת���ַ�
				format(value);
			}
			else
			{   //ð�ź�����������{,���Ժ����Ƕ���
				count = 1;
				i = j + 2; 					//{ ֮��һ���ַ���ʼ
				while (count != 0)         //�ҵ���Ӧ�����} 
				{
					if (json[i] == '{')
					{
						++count;
					}
					if (json[i] == '}')
					{
						--count;
					}
					i++;
				}
				value = json.substr(j + 1, i - j - 1);  //��ʱ��value��һ������
				//�ݹ�ʵ��
				deal(value, key);
			}
			mp[key] = value;
		}
	}
}
int main()
{
	//���ļ�
	fstream file;
	file.open("JSON.txt", ios::in);
	if (file.fail())
	{
		cout << "���ļ�ʧ��" << endl;
		exit(0);
	}
	//����ȥ���հ׷��ŵ�
	string s, json;
	//json�����������ȥ���ո��֮����ַ���
	string::iterator it;
	int n, m;
	file >> n >> m; //�õ�����Ͳ�ѯ�ĸ��� 
	getline(file, s);   //��һ�����������Ǹ� 
	for (int i = 0; i < n; i++)
	{
		getline(file, s);
		//�Ѹ��еĿո���Ĩȥ
		for (it = s.begin(); it != s.end();)
		{
			//��s����ÿһ���ַ�������һ��
			if (isspace(*it)) //�ж��ַ�Ϊ�ո��з��Ʊ���򷵻ط�0ֵ�����򷵻�0 
			{
				s.erase(it);  //ɾ��������λ�õ�һ���ַ�
			}
			else
			{
				++it;         //�����һ�� 
			}
		}
		//Ĩȥ�ո�֮��,���ӵ�json����
		json += s;
	}
	string add;
	add = "";
	deal(json, add);
	//��ʼ��ѯ 
	for (int i = 0; i < m; i++)
	{
		getline(file, s);
		if (mp.find(s) != mp.end())   //�ҵ���
		{
			if (mp[s][0] == '{')
			{
				cout << "OBJECT" << endl;
			}
			else
			{
				cout << "STRING " << mp[s] << endl;
			}
		}
		else
		{
			cout << "NOTEXISTENCE" << endl;
		}
	}
	file.close();
	cout << endl;
	system("pause");
	return 0;
}