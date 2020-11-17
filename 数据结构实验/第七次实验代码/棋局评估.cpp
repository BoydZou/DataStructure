#include <iostream>
#include <algorithm>
using namespace std;

int a[3][3];

//�ж����Ƿ�ʤ�� ��atΪ�ڼ��У�idΪ��˭�����壬1ΪAlice��2ΪBob 
bool row(int at,int id)
{
    if(a[at][0] == id && a[at][1] == id && a[at][2] == id)
    {
        return true;
    }
    
    return false;
}

//�ж����Ƿ�ʤ�� ��atΪ�ڼ��У�idΪ��˭�����壬1ΪAlice��2ΪBob 
bool line(int at,int id)
{
    if(a[0][at] == id && a[1][at] == id && a[2][at] == id)
    {
        return true;
    }
    
    return false;
}

//���ʤ�����㵱ǰ���̵ĵ÷� 
int sum(int id)
{
    int s = 1;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(a[i][j] == 0)
            {
                s++;
            }
        }
    }    
    
    //Aliceʤ�����÷�Ϊ�� 
    if(id == 1)
    {
        return s;
    }
    else 
    {
        return -1 * s;
    }
} 

void show()
{
    for(int i=0;i<3;i++)
    {
        for(int j = 0;j<3;j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << endl;
}

//�ж��Ƿ��ʤ 
bool win(int id)
{
    bool yes = false;
    
    //�ȱȽϵ�ǰ������� 
    for(int i=0;i<3;i++)
    {
        if(row(i,id) == true)
        {
            yes = true;
        }
    } 
    
    //�ٱȽϵ�ǰ������� 
    for(int i=0;i<3;i++)
    {
        if(line(i,id) == true)
        {
            yes = true;
        } 
    }
    
    //�Ƚ϶Խ��� 
    if(a[0][0] == id && a[1][1] == id && a[2][2] == id)
    {
        yes = true;
    }
    
    if(a[0][2] == id && a[1][1] == id && a[2][0] == id)
    {
        yes = true;
    }
    
    //�ж��Ƿ�ʤ�� 
    if(yes)
    {
        return true;
    }
    else
    {
        return false;
    }
} 


//�Կ�������ÿ���˶�ȡ���Լ��������ĵ÷� 
int dfs(int id)
{
    //��·���ߣ����� 
    if(sum(id) == 1 || sum(id) == -1)
    {
        return 0;
    }
    
    //max��ʾ alice�ܵõ���߷� 
    int maxNum = -1000;
    //min��ʾbob�ܵõ�����߷� 
    int minNum = 1000;
    
    //����������� 
    //���жϵ�ǰ���棬�õ�ǰ���ֵ����ֻغϵ����ֵ���бȽ� 
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(a[i][j] == 0)
            {
                //��ǰ������a[i][j]���� ���ٶԴ�ʱ�ľ�������ж� 
                a[i][j] = id;
                
                if( win(id) )
                {
                    int score = sum(id);
                    a[i][j] = 0;
                    
                    //score>0����Alice��ʤ,����Alice�ĵ÷� 
                    //score<0����Bob��ʤ������Bod�ĵ÷� 
                    return score > 0 ? max(maxNum,score) : min(minNum,score);
                }
                    
                //ÿ���˶������Լ���Ӯ,���Լ�����߷ֺͶ��ֵ���һ�ν�����߷ֱ���Ƚϣ�
                //������Ӯ������������Ӯ����0 
                //����жϴ��־���Ӯ���ˣ���᷵��һ����ֵ 
                if(id == 1)
                {
                    maxNum = max(maxNum,dfs( id%2 + 1));
                }
                else
                {
                    minNum = min(minNum,dfs( id%2 + 1));
                }
            
                //���� 
                a[i][j] = 0;
            }
        }
    }
    
    return id==1 ? maxNum : minNum; 
}

int main()
{
    int n;
    cin >> n;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<3;j++)
        {
            for(int k=0;k<3;k++)
            {
                cin >> a[j][k];
             } 
        }
        
        
        if(win(1))
        {
            cout << sum(1) << endl;
            continue;
        }
        
        if(win(2))
        {
            cout << sum(2) << endl;
            continue;
        }
        
        int res = dfs(1);
        cout << res << endl;
        
    }
    return 0;
}
