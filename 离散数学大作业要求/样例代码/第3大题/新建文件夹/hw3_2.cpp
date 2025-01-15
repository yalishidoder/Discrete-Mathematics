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
	cout<<"请输入矩阵的行或列数:";
	cin>>n;
	cout<<"请输入关系矩阵:\n";
	for (i = 0; i < n; i++)
	{
		cout<<endl;
		cout<<"请输入矩阵的第"<<i+1<<"行元素(元素以空格分隔) :";
		for (j = 0; j < n; j++)
			cin>>s[i][j];
	}
	cout<<"输入对应序号选择算法\nl:自反闭包\n2:传递闭包\n3:对称闭包\n4:退出\n";
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
	cout<<"所求关系矩阵为:\n";
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
		s2[i][i] = 1;    //对角线取1
	output(s2);
	select();
}

void duichen(int s2[][100])
{
	int s1[100][100];
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			s1[j][i] = s2[i][j];  //计算转置矩阵
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			s2[i][j] = s2[i][j] + s1[i][j];    //矩阵与转置矩阵相加，大于1的结果转换为1
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
			a[i][j] = 0;   //中间矩阵
			t[i][j] = s2[i][j];   //存储结果的矩阵
			m[i][j] = s2[i][j];  //存储高阶M2,M3等
		}
	while (flag) {
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (m[i][j] == 1)
				{
					for (k = 0; k < n; k++)
						if (s2[j][k] == 1)  //计算矩阵乘法
							a[i][k] = 1;
				}
		//比较相加结果
		flag = false;
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (a[i][j]&&(!t[i][j]))
					flag = true;
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
			{
				m[i][j] = a[i][j];    //存储计算结构
				t[i][j] += a[i][j];   //矩阵加法
				a[i][j] = 0;          //归0
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