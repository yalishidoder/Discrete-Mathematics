#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

int main() {
	char p = '2', q = '2';//Ϊ�����������ת��ʱ�Ĵ��󣬽�int��Ϊchar�������ַ�'1'��'0'���Ƚ�
	char r;
	cout << "***************************************" << endl;  //����
	cout << "**                                   **" << endl;;
	cout << "**        ��ӭ�����߼��������       **" << endl;
	cout << "**                                   **" << endl;
	cout << "***************************************\n" << endl;
init:
	cout << "\n������p��ֵ(1��0),�Իس�����:";
	cin >> p;
	if ((p != '1') && (p != '0')) {
		cout << "p������ֵ��������������" << endl;
		goto init;
	}
	cout << "\n������q��ֵ��1��0��,�Իس�����:";
	cin >> q;
	if ((q != '1') && (q != '0')) {
		cout << "q������ֵ��������������" << endl;
		goto init;
	}
	int P = int(p) - 48, Q = int(q) - 48;//���ַ�1/0ת��Ϊ���֣��Ӷ�ֱ���ù�ʽ��P��Q�����߼�����
	cout << "��ȡ��\n\tp /\\ q = " << (P&&Q) << endl;
	cout << "��ȡ��\n\tp \\/ q = " << (P || Q) << endl;
	cout << "������\n\tp -> q = " << ((!P) || Q) << endl;
	cout << "˫������\n\tp <-> q = " << (((!P) || Q) && ((!Q) || P)) << endl;

ed:
	cout << "�������㣿[y/n]";
	cin >> r;
	if (r == 'y') {
		goto init;
	}
	else if (r == 'n') {
		exit(2);
	}
	else {
		cout << "����,������y��n��" << endl;
		goto ed;
	}

	return 0;
}
