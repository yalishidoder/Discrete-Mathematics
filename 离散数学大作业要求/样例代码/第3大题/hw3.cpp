#include <iostream>
using namespace std;

void output(bool s[][100]);
void zifan(bool s2[][100]);
void duichen(bool s2[][100]);
void chuandi(bool s2[][100]);
void select();
void exit();
bool s[100][100];  //s：存放关系矩阵的二维数组
int z,n,i,j;  //z：算法方式编号；n：行数（阶数）

int main() 
{
	//标语
	cout<<"*******************************************\n";  //标语
	cout<<"**                                       **\n";
	cout<<"**        欢迎进入关系的自反、对称       **\n";
	cout<<"**           和传递闭包求解程序          **\n";
	cout<<"**                                       **\n";
	cout<<"*******************************************\n\n\n";
	select();
	return 0;
}

//存储关系矩阵，选择求解的闭包
void select()
{
	//求解关系的自反、对称和传递闭包，则意味着该关系是某个非空集合上的关系，因此关系矩阵为方阵，只需知道行数（阶数）即可
	//n：关系矩阵行数（阶数）
bb:
	cout<<"请输入关系矩阵的行(或列)数(阶数)(>=2且<=100):";
	cin>>n;
	if(n < 0||n > 100)
	{
		cout<<"输入有误，请重新输入！\n"<<endl;
		goto bb;  //返回，重新输入
	}

	//输入关系矩阵
	cout<<"\n请输入关系矩阵:"<<endl;
	for(i = 0;i < n;i++)
	{
	begin:
		cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');  //清空输入缓冲区
		cout<<"请输入矩阵的第"<<i+1<<"行元素(只能输入1或0，元素以空格分隔):";
		for(j = 0;j < n;j++)
			cin >> s[i][j];  //s[100][100]：存放关系矩阵的二维数组
			if (s[i][j] != 0 && s[i][j] != 1)
			{
				cout << "输入错误，请重新输入！" << endl;
				goto begin;
			}
	}

	cout<<"\n输入对应序号选择算法\nl:自反闭包\n2:对称闭包\n3:传递闭包\n4:退出"<<endl;
	cin>>z;  //z：算法编号
	switch(z)
	{
		case 1:zifan(s); break;  //l:自反闭包
		case 2:duichen(s);break;  //3:对称闭包
		case 3:chuandi(s);break;  //2:传递闭包
		case 4:exit();break;  //4:退出
	}
}

//在一次求解结束后询问是否继续求解
void re()
{
	char x;  //存储y或n以表示继续或不继续
	cout<<"\n是否继续运行该程序？（y/n）：";
	cin>>x;
	if(x=='y')
	{
		cout<<endl;
		select();
	}
	else if(x=='n')
		exit(1);
	else
	{
		cout<<"输入错误，请重新输入。"<<endl;
		re();
	}
}

//显示算法结果
//传入的参数s[][100]为关系矩阵
void output(bool s[][100])
{
	cout<<"\n所求关系矩阵为:"<<endl;
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < n;j++) 
			cout<<s[i][j]<<" ";
		cout<<endl;;
	}
}

//求自反闭包
//传入的参数s2[][100]为关系矩阵
void zifan(bool s2[100][100])
{
	//M=M+E（+为逻辑加，因此0+1=1，1+1=1，使关系矩阵对角线元素均为1即得其自反闭包）
	for(i = 0;i < n;i++) 
		s2[i][i] = 1;
	output(s2);
	re();
}

//求对称闭包
//传入的参数s2[][100]为关系矩阵
void duichen(bool s2[][100])
{
	bool s1[100][100];  //s1：关系矩阵s2的转置矩阵
	for(i = 0;i < n;i++)
		for(j = 0;j < n;j++)
			s1[j][i] = s2[i][j];
	//M=M+M'（求关系矩阵的对称闭包，即求关系矩阵与其转置矩阵逻辑加的结果）
	for(i = 0;i < n;i++)
		for(j = 0;j < n;j++)
			s2[i][j] = s1[i][j] + s2[i][j];
	output(s2);
	re(); 
}

//求传递闭包
//传入的参数s2[][100]为关系矩阵
void chuandi(bool s2[][100])
{
	bool flag=0,t[100][100],temp[100][100],power[100][100],compare[100][100];
	int h;
	//对于各个变量初始化
	for(i = 0;i < n;i++) 
		for(j = 0;j < n;j++)
		{
			power[i][j] = 0;  //power：存放M^n结果的数组
			t[i][j] = s2[i][j];  //t：存放每次加上去的结果的数组
			compare[i][j]=s2[i][j];  //compare：存放前一次+M^n的结果，用于确认是否需要继续循环
			temp[i][j]=s2[i][j];  //temp：存储上一回power，即M^(n-1)
		}

	//进行Mt=M+M^2+M^3+…...+M^n的计算
	while(flag==0)
	{
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				power[i][j] = 0;    //每次计算M^n时把每一位初始化为0，保证之后求出来的是M^n的结果
		//计算M^n
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				for(h=0;h<n;h++)
					//power为这一轮的M^n
					//temp实际等于上一回power，即M^(n-1)；s2为M
					power[i][j]=power[i][j]+temp[i][h]*s2[h][j];  //temp实际等于上一回power，即M^(n-1)；s2为M

		//将此轮M^n存入compare，计算累加和t
		for(i = 0;i < n;i++) 
			for(j = 0;j < n;j++)
			{
				temp[i][j]=power[i][j];  //temp完全复制此轮power（即M^n）
				t[i][j]=t[i][j]+power[i][j];  //t为累加结果，Mt=M+M^2+M^3+……+M^n
			}

		flag=1;  //将flag改为1，在接下来判断中只要发现t和compare有一个元素不同则flag=0，即需要继续循环
		//判断是否需要继续循环
		for(i = 0;i < n;i++) 
			for(j = 0;j < n;j++)
				//通过t与compare是否相等的判断，判断M^n是否达到了有限种
				if(t[i][j]!=compare[i][j])  //compare为M+M^2+……+M^(n-1)
				{
					flag=0;  //flag=1表示有限项M的幂均已涵盖，不必要继续循环
					break;
				}

		//将本轮累加结果值t赋值给compare，在下一轮中可以对比
		for(i = 0;i < n;i++) 
			for(j = 0;j < n;j++)
				compare[i][j]=t[i][j];  //compare为上一轮加完后t的值
	}

	output(t);
	re();
}

void exit()
{
	exit(1);
}