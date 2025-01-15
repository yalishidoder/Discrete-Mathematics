#include <iostream>

using namespace std;

bool relationship[100][100];              //��Ź�ϵ����Ķ�ά����
int n, i, j;                              //n��������������

void input(bool relationship[][100])
{
	while (1) {                           //���������
		cout << "�������ϵ�������������������<=100��:";
		cin >> n;

		if (cin.fail() || n < 0 || n>100) {
			cout << "s�������������������" << endl;
			continue;
		}
		else
			break;
	}

	cout << "�������ϵ����" << endl;

	for (i = 0; i < n; i++)
	{
		cout << "���������ĵ�" << i + 1 << "��Ԫ��(Ԫ���Կո�ָ�):";
		for (j = 0; j < n; j++)
			cin >> relationship[i][j];  //relationship[100][100]����Ź�ϵ����Ķ�ά����
	}

}

void output(bool relationship[][100])
{
	cout << "\n�����ϵ����Ϊ:" << endl;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			cout << relationship[i][j] << " ";
		cout << endl;
	}
}

void Reflexive_closures()                 //�Է��հ�
{
	for (i = 0; i < n; i++)
		relationship[i][i] = 1;           //R=R+E
}

void Symmetrical_closures()               //�ԳƱհ�
{
	bool Transpose[100][100];             //ת�þ���

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			Transpose[j][i] = relationship[i][j];

	//M=M+M'�����ϵ����ĶԳƱհ��������ϵ��������ת�þ����߼��ӵĽ����

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			relationship[i][j] = Transpose[i][j] + relationship[i][j];

}

void Pass_closures()                      //���ݱհ�
{
	//��ʹ��warshall�㷨
	bool flag = 0, t[100][100], temp[100][100], power[100][100], compare[100][100];
	int h;

	//���ڸ���������ʼ��
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			power[i][j] = 0;  //power�����M^n���������
			t[i][j] = relationship[i][j];  //t�����ÿ�μ���ȥ�Ľ��������
			compare[i][j] = relationship[i][j];  //compare�����ǰһ��+M^n�Ľ��������ȷ���Ƿ���Ҫ����ѭ��
			temp[i][j] = relationship[i][j];  //temp���洢��һ��power����M^(n-1)
		}

	//����Mt=M+M^2+M^3+���ļ���
	while (flag == 0)
	{
		//������ȷ�߼���������Ҫÿһ�ζ���power��0������0��Ӱ����
		
		//����M^n
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				for (h = 0; h < n; h++)
					//powerΪ��һ�ֵ�M^n
					//tempʵ�ʵ�����һ��power����M^(n-1)��relationshipΪM
					power[i][j] = power[i][j] + temp[i][h] * relationship[h][j];  //compareʵ�ʵ�����һ��power����M^(n-1)��relationshipΪM

		//������M^n����compare�������ۼӺ�t
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
			{
				temp[i][j] = power[i][j];  //temp��ȫ���ƴ���power����M^n��
				t[i][j] = t[i][j] + power[i][j];  //tΪ�ۼӽ����Mt=M+M^2+M^3+����+M^n
			}

		flag = 1;  //��flag��Ϊ1���ڽ������ж���ֻҪ����t��compare��һ��Ԫ�ز�ͬ��flag=0������Ҫ����ѭ��

		//�ж��Ƿ���Ҫ����ѭ��
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				//ͨ��t��compare�Ƿ���ȵ��жϣ��ж�M^n�Ƿ�ﵽ��������
				if (t[i][j] != compare[i][j])  //compareΪM+M^2+����+M^(n-1)
				{
					flag = 0;  //flag=1��ʾ������M���ݾ��Ѻ��ǣ�����Ҫ����ѭ��
					break;
				}

		//�������ۼӽ��ֵt��ֵ��compare������һ���п��ԶԱ�
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				compare[i][j] = t[i][j];  //compareΪ��һ�ּ����t��ֵ
	}

	output(t);                            //������
}

int re()
{
	char x;  //�洢y��n�Ա�ʾ�����򲻼���

	cout << endl;
	cout << "�Ƿ�������иó��򣿣�y/n����";
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
		cout << "����������������롣" << endl;
		re();
		return 0;
	}
}

void select()
{
	int option = 0, circulate = 1;

	while (option != 4 && circulate) {
		input(relationship);

		cout << "�����Ӧ���ѡ���㷨" << endl;
		cout << "1���Է��հ�" << endl;
		cout << "2���ԳƱհ�" << endl;
		cout << "3�����ݱհ�" << endl;
		cout << "4���˳�����" << endl;

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
				cout << "��ѡ����ڣ�" << endl;
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
	cout << "**        ��ӭ�����ϵ���Է����Գ�       **" << endl;
	cout << "**           �ʹ��ݱհ�������          **" << endl;
	cout << "**                                       **" << endl;
	cout << "*******************************************\n\n\n";

	select();

	return 0;
}