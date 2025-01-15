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
	//输出所求关系矩阵
	cout << "所求传递闭包为:" << endl;
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
	//求解关系的自反、对称和传递闭包，则意味着该关系是某个非空集合上的关系，因此关系矩阵为方阵，只需知道行数（阶数）即可
	//n：关系矩阵行数（阶数）
bb:
	cout << "请输入关系矩阵的行(列)数(阶数)(只能输入正整数，且1<=阶数<=100):";
	cin >> w;
	if (atoi(w) >= 1 && atoi(w) <= 100)  //输入的数字在范围之内
	{
		goto cc;
	}
	else if (atoi(w) <= 0 || atoi(w) > 100)  //输入的数字越界
	{
		cout << "输入有误，请重新输入！\n" << endl;
		goto bb;  //返回，重新输入
	}
	else if (isalpha(w[4]) != 0)   //输入了字母
	{
		cout << "输入有误，请重新输入！\n" << endl;
		goto bb;  //返回，重新输入
	}
	else    //输入了其他字符
	{
		cout << "输入有误，请重新输入！\n" << endl;
		goto bb;  //返回，重新输入
	}
cc:
	n = atoi(w);
	//输入关系矩阵
	cout << "请输入关系矩阵:" << endl;
	for (int i = 0; i < n; i++) 
	{
	begin2:
		cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');  //清空输入缓冲区
		cout << "请输入矩阵的第" << i + 1 << "行的"<< n << "个元素(只能输入1或0，元素以空格分隔):";
		for (int j = 0; j < n; j++) 
		{
			cin >> s[i][j];//输入矩阵信息，用 s 数组储存
			if (s[i][j] != '0' && s[i][j] != '1') 
			{
				cout << "输入错误，请重新输入！" << endl;
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
	//Warshall算法求传递闭包
		for (int i = 0; i < n; i++) 
		{
			for (int j = 0; j < n; j++) 
			{
				s[i][j] = s[i][j] || (s[i][k] && s[k][j]);
			}
		}
	}
	output(s);//输出 s
	system("pause");
	return 0;
}