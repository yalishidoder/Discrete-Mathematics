#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

int main() {
	char p = '2', q = '2';//为避免出现类型转换时的错误，将int改为char类型与字符'1'和'0'作比较
	char r;
	cout << "***************************************" << endl;  //标语
	cout << "**                                   **" << endl;;
	cout << "**        欢迎进入逻辑运算程序       **" << endl;
	cout << "**                                   **" << endl;
	cout << "***************************************\n" << endl;
init:
	cout << "\n请输入p的值(1或0),以回车结束:";
	cin >> p;
	if ((p != '1') && (p != '0')) {
		cout << "p的输入值有误，请重新输入" << endl;
		goto init;
	}
	cout << "\n请输入q的值（1或0）,以回车结束:";
	cin >> q;
	if ((q != '1') && (q != '0')) {
		cout << "q的输入值有误，请重新输入" << endl;
		goto init;
	}
	int P = int(p) - 48, Q = int(q) - 48;//将字符1/0转化为数字，从而直接用公式对P、Q进行逻辑运算
	cout << "合取：\n\tp /\\ q = " << (P&&Q) << endl;
	cout << "析取：\n\tp \\/ q = " << (P || Q) << endl;
	cout << "条件：\n\tp -> q = " << ((!P) || Q) << endl;
	cout << "双条件：\n\tp <-> q = " << (((!P) || Q) && ((!Q) || P)) << endl;

ed:
	cout << "继续运算？[y/n]";
	cin >> r;
	if (r == 'y') {
		goto init;
	}
	else if (r == 'n') {
		exit(2);
	}
	else {
		cout << "错误,请输入y或n：" << endl;
		goto ed;
	}

	return 0;
}
