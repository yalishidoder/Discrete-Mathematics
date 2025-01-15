#include <iostream>
using namespace std;

//用结构体来表示二元关系 
typedef struct
{
	char a;
	char b;
}BR;

int n, m;      //n表示集合A中的元素个数，m表示二元关系R中的元素个数 

//创建集合A并初始化 
void init_aggregation(char*& A)
{
	cout << "请输入集合A中的元素个数(正整数)，按回车键输入下一项：" << endl;
	cin >> n;
	A = new char[n];
	cout << "请依次输入集合A中的";
	cout << n;     //n是集合A中的元素个数
	cout << "个元素(形如：a b c d ......这样的格式)，按回车键输入下一项：" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> A[i];
	}
}

//创建集合A的二元关系R的集合并初始化 
void init_BinaryRelation(BR*& R)
{
	cout << "请输入二元关系R中的元素个数(正整数)，按回车键输入下一项：" << endl;
	cin >> m;
	R = new BR[m];
	cout << "请依次输入R中的";
	cout << m;   //m是R中的元素个数
	cout << "个元素，一行是一个元素\n";
	cout << "(形如：\n";
	cout << "a b\n";
	cout << "b c\n";
	cout << "c d\n";
	cout << "......\n";
	cout << "这样的格式)，按回车键输入下一项：\n";
	for (int i = 0; i < m; i++)
	{
		cin >> R[i].a;
		cin >> R[i].b;
	}
}

int fun(char ch, char*& A)
{
	for (int i = 0; i < n; i++)
	{
		if (ch == A[i])
		{
			return i;
		}
	}
	return -1;
}

//Warshall算法的核心部分 
void Warshall(char*& A, BR*& R, bool**& tR)
{
	int i, j, k;
	int x, y;

	//用关系矩阵表示二元关系R 
	for (i = 0; i < m; i++)
	{
		x = fun(R[i].a, A);
		y = fun(R[i].b, A);
		tR[x][y] = 1;
	}

	//计算传递闭包的过程 
	for (i = 0; i < n; i++)
	{ //检索列 
		for (j = 0; j < n; j++)
		{ //检索行 
			if (tR[j][i] == 1)
			{
				for (k = 0; k < n; k++)
				{
					tR[j][k] = tR[j][k] + tR[i][k];
				}
			}
		}
	}
}

//将传递闭包t(R)的关系矩阵表示转化为集合表示 
void translation_output(char*& A, bool**& tR)
{
	cout << endl;
	cout << "R的传递闭包(集合形式)为：" << endl;
	cout << "t(R) = {";
	int i, j;
	int f = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (tR[i][j] == 1)
			{
				if (f == 1)
					cout << ",";
				else
					f = 1;
				cout << "<" << A[i] << "," << A[j] << ">";
			}
		}
	}
	cout << "}" << endl;
}

//主函数
int main()
{
	char* A;
	init_aggregation(A); //初始化集合A

	BR* R;
	init_BinaryRelation(R); //初始化二元关系

	bool** tR; //传递闭包矩阵

	 //动态开辟bool类型的二维数组
	tR = new bool* [n];
	for (int i = 0; i < n; i++)
	{
		tR[i] = new bool[n];
	}

	//初始化二维数组(全部赋值为0)
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			tR[i][j] = 0;
		}
	}

	Warshall(A, R, tR);//调用Warshall算法函数

	translation_output(A, tR); //将传递闭包t(R)的关系矩阵表示转化为集合表示 

	return 0;
}