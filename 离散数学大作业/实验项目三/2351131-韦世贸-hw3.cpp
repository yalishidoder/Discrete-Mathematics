#include <iostream>

using namespace std;

bool relationship[100][100];              //存放关系矩阵的二维数组
int n, i, j;                              //n：行数（阶数）

void input(bool relationship[][100])
{
	while (1) {                           //输入错误处理
		cout << "请输入关系矩阵的行数（阶数）（<=100）:";
		cin >> n;

		if (cin.fail() || n < 0 || n>100) {
			cout << "s输入有误，请重新输出！" << endl;
			continue;
		}
		else
			break;
	}

	cout << "请输入关系矩阵：" << endl;

	for (i = 0; i < n; i++)
	{
		cout << "请输入矩阵的第" << i + 1 << "行元素(元素以空格分隔):";
		for (j = 0; j < n; j++)
			cin >> relationship[i][j];  //relationship[100][100]：存放关系矩阵的二维数组
	}

}

void output(bool relationship[][100])
{
	cout << "\n所求关系矩阵为:" << endl;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			cout << relationship[i][j] << " ";
		cout << endl;
	}
}

void Reflexive_closures()                 //自反闭包
{
	for (i = 0; i < n; i++)
		relationship[i][i] = 1;           //R=R+E
}

void Symmetrical_closures()               //对称闭包
{
	bool Transpose[100][100];             //转置矩阵

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			Transpose[j][i] = relationship[i][j];

	//M=M+M'（求关系矩阵的对称闭包，即求关系矩阵与其转置矩阵逻辑加的结果）

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			relationship[i][j] = Transpose[i][j] + relationship[i][j];

}

void Pass_closures()                      //传递闭包
{
	//不使用warshall算法
	bool flag = 0, t[100][100], temp[100][100], power[100][100], compare[100][100];
	int h;

	//对于各个变量初始化
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			power[i][j] = 0;  //power：存放M^n结果的数组
			t[i][j] = relationship[i][j];  //t：存放每次加上去的结果的数组
			compare[i][j] = relationship[i][j];  //compare：存放前一次+M^n的结果，用于确认是否需要继续循环
			temp[i][j] = relationship[i][j];  //temp：存储上一回power，即M^(n-1)
		}

	//进行Mt=M+M^2+M^3+…的计算
	while (flag == 0)
	{
		//按照正确逻辑，这里需要每一次都将power置0，不置0不影响结果
		
		//计算M^n
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				for (h = 0; h < n; h++)
					//power为这一轮的M^n
					//temp实际等于上一回power，即M^(n-1)；relationship为M
					power[i][j] = power[i][j] + temp[i][h] * relationship[h][j];  //compare实际等于上一回power，即M^(n-1)；relationship为M

		//将此轮M^n存入compare，计算累加和t
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
			{
				temp[i][j] = power[i][j];  //temp完全复制此轮power（即M^n）
				t[i][j] = t[i][j] + power[i][j];  //t为累加结果，Mt=M+M^2+M^3+……+M^n
			}

		flag = 1;  //将flag改为1，在接下来判断中只要发现t和compare有一个元素不同则flag=0，即需要继续循环

		//判断是否需要继续循环
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				//通过t与compare是否相等的判断，判断M^n是否达到了有限种
				if (t[i][j] != compare[i][j])  //compare为M+M^2+……+M^(n-1)
				{
					flag = 0;  //flag=1表示有限项M的幂均已涵盖，不必要继续循环
					break;
				}

		//将本轮累加结果值t赋值给compare，在下一轮中可以对比
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				compare[i][j] = t[i][j];  //compare为上一轮加完后t的值
	}

	output(t);                            //输出结果
}

int re()
{
	char x;  //存储y或n以表示继续或不继续

	cout << endl;
	cout << "是否继续运行该程序？（y/n）：";
	cin >> x;

	if (x == 'y')
	{
		cout << endl;
		return 1;
	}
	else if (x == 'n')
		return 0;
	else
	{
		cout << "输入错误，请重新输入。" << endl;
		re();
		return 0;
	}
}

void select()
{
	int option = 0, circulate = 1;

	while (option != 4 && circulate) {
		input(relationship);

		cout << "输入对应序号选择算法" << endl;
		cout << "1：自反闭包" << endl;
		cout << "2：对称闭包" << endl;
		cout << "3：传递闭包" << endl;
		cout << "4：退出程序" << endl;

		cin >> option;

		switch (option)
		{
			case 1:
				Reflexive_closures();
				break;
			case 2:
				Symmetrical_closures();
				break;
			case 3:
				Pass_closures();
				break;
			default:
				cout << "该选项不存在！" << endl;
				break;
		}

		if (option <= 2)
			output(relationship);

		circulate = re();
	}

	return;
}

int main()
{
	cout << "*******************************************" << endl;
	cout << "**                                       **" << endl;
	cout << "**        欢迎进入关系的自反、对称       **" << endl;
	cout << "**           和传递闭包求解程序          **" << endl;
	cout << "**                                       **" << endl;
	cout << "*******************************************\n\n\n";

	select();

	return 0;
}