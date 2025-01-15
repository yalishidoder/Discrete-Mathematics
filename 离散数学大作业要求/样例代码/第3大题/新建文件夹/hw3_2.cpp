#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

void output(int s[][100]);
void zifan(int s2[][100]);
void duichen(int s2[][100]);
void chuandi(int s2[][100]);
void select();
void exit();
int s[100][100], z;
int n, i, j;

int main()
{
	select();
	return 0;
}

void select()
{
	cout<<"�����������л�����:";
	cin>>n;
	cout<<"�������ϵ����:\n";
	for (i = 0; i < n; i++)
	{
		cout<<endl;
		cout<<"���������ĵ�"<<i+1<<"��Ԫ��(Ԫ���Կո�ָ�) :";
		for (j = 0; j < n; j++)
			cin>>s[i][j];
	}
	cout<<"�����Ӧ���ѡ���㷨\nl:�Է��հ�\n2:���ݱհ�\n3:�ԳƱհ�\n4:�˳�\n";
	cin>>z;
	switch (z)
	{
	case 1:zifan(s); break;
	case 2:chuandi(s); break;
	case 3:duichen(s); break;
	case 4:exit(); break;
	}
}

void output(int s[][100])
{
	cout<<"�����ϵ����Ϊ:\n";
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			cout<<s[i][j]<<" ";
		cout<<endl;
	}
}

void zifan(int s2[][100])
{
	for (i = 0; i < n; i++)
		s2[i][i] = 1;    //�Խ���ȡ1
	output(s2);
	select();
}

void duichen(int s2[][100])
{
	int s1[100][100];
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			s1[j][i] = s2[i][j];  //����ת�þ���
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			s2[i][j] = s2[i][j] + s1[i][j];    //������ת�þ�����ӣ�����1�Ľ��ת��Ϊ1
			if (s2[i][j] > 1)
				s2[i][j] = 1;
		}
	output(s2);
	select();
}

void chuandi(int s2[][100])
{
	int m[100][100], a[100][100], k;
	bool flag = true;
	int t[100][100];
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			a[i][j] = 0;   //�м����
			t[i][j] = s2[i][j];   //�洢����ľ���
			m[i][j] = s2[i][j];  //�洢�߽�M2,M3��
		}
	while (flag) {
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (m[i][j] == 1)
				{
					for (k = 0; k < n; k++)
						if (s2[j][k] == 1)  //�������˷�
							a[i][k] = 1;
				}
		//�Ƚ���ӽ��
		flag = false;
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (a[i][j]&&(!t[i][j]))
					flag = true;
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
			{
				m[i][j] = a[i][j];    //�洢����ṹ
				t[i][j] += a[i][j];   //����ӷ�
				a[i][j] = 0;          //��0
				if (t[i][j] > 1)
					t[i][j] = 1;
			}

	}
	output(t);
	select();
}

void exit()
{
	exit(1);
}