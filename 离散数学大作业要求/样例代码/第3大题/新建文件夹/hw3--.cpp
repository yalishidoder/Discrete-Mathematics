#include <iostream>
#include <cstdio>
#include <windows.h>
#include <ios>   
#include <limits>
using namespace std;

int n;
char w[5];
void output(char s[][100]) 
{    
	//��������ϵ����
	cout << "���󴫵ݱհ�Ϊ:" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << (s[i][j] - '0' + 48) << ' ';
			cout << endl;
	}
}
int main()
{
	char s[100][100];
	//����ϵ���Է����Գƺʹ��ݱհ�������ζ�Ÿù�ϵ��ĳ���ǿռ����ϵĹ�ϵ����˹�ϵ����Ϊ����ֻ��֪������������������
	//n����ϵ����������������
bb:
	cout << "�������ϵ�������(��)��(����)(ֻ����������������1<=����<=100):";
	cin >> w;
	if (atoi(w) >= 1 && atoi(w) <= 100)  //����������ڷ�Χ֮��
	{
		goto cc;
	}
	else if (atoi(w) <= 0 || atoi(w) > 100)  //���������Խ��
	{
		cout << "�����������������룡\n" << endl;
		goto bb;  //���أ���������
	}
	else if (isalpha(w[4]) != 0)   //��������ĸ
	{
		cout << "�����������������룡\n" << endl;
		goto bb;  //���أ���������
	}
	else    //�����������ַ�
	{
		cout << "�����������������룡\n" << endl;
		goto bb;  //���أ���������
	}
cc:
	n = atoi(w);
	//�����ϵ����
	cout << "�������ϵ����:" << endl;
	for (int i = 0; i < n; i++) 
	{
	begin2:
		cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');  //������뻺����
		cout << "���������ĵ�" << i + 1 << "�е�"<< n << "��Ԫ��(ֻ������1��0��Ԫ���Կո�ָ�):";
		for (int j = 0; j < n; j++) 
		{
			cin >> s[i][j];//���������Ϣ���� s ���鴢��
			if (s[i][j] != '0' && s[i][j] != '1') 
			{
				cout << "����������������룡" << endl;
				goto begin2;
			}
		}
	}
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			s[i][j] = s[i][j] - '0';
		}
	}

	for (int k = 0; k < n; k++) 
	{
	//Warshall�㷨�󴫵ݱհ�
		for (int i = 0; i < n; i++) 
		{
			for (int j = 0; j < n; j++) 
			{
				s[i][j] = s[i][j] || (s[i][k] && s[k][j]);
			}
		}
	}
	output(s);//��� s
	system("pause");
	return 0;
}