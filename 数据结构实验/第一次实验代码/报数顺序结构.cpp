#include<stdio.h>
#include<stdlib.h>

int main()
{
	int* p;
	int n, m,i,length=0,temp=0;
	scanf_s("%d %d", &n, &m);
	if (m >= n || m <= 0 || n <= 0)  // �ж������Ƿ�Ϸ�
	{
		printf("���벻�Ϸ�");
		return -1;
	}
	p = (int*)malloc(n * sizeof(int));  // ��������ռ�
	if (!p)
	{
		printf("�ռ����ʧ��");
		return -1;
	}
	for (i = 0; i < n; i++)  // ��ʼ��������Ϣ
	{
		p[i] = i + 1;
	}
	length = n;  // length ����ʣ������
	i = 0;
	while (length > 0)  // �����˾�����ʱ����ѭ��
	{
		if (p[i] != 0)   // p[i]Ϊ������i���ѳ��У����ٲ��뱨��
		{
			temp++;
		}
		if (temp == m)
		{
			printf("%d ", p[i]);
			p[i] = 0;    // ��Ҫ���е�������Ϊ 0
			length--;
			temp = 0;
		}
		i++;
		if (i >= n)  // ���������һ����֮�󣬻ص���һ�˼�������
		{
			i = 0;
		}
	}
	/*for (i = 0; i < n; i++)  //��ӡ���һ�˵���Ϣ
	{
		if (p[i] != 0)
		{
			printf("%d", p[i]);
			break;
		}
	}*/
	return 0;
}