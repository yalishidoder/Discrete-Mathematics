#include <iostream>
using namespace std;

void output(bool s[][100]);
void zifan(bool s2[][100]);
void duichen(bool s2[][100]);
void chuandi(bool s2[][100]);
void select();
void exit();
bool s[100][100];  //s����Ź�ϵ����Ķ�ά����
int z,n,i,j;  //z���㷨��ʽ��ţ�n��������������

int main() 
{
	//����
	cout<<"*******************************************\n";  //����
	cout<<"**                                       **\n";
	cout<<"**        ��ӭ�����ϵ���Է����Գ�       **\n";
	cout<<"**           �ʹ��ݱհ�������          **\n";
	cout<<"**                                       **\n";
	cout<<"*******************************************\n\n\n";
	select();
	return 0;
}

//�洢��ϵ����ѡ�����ıհ�
void select()
{
	//����ϵ���Է����Գƺʹ��ݱհ�������ζ�Ÿù�ϵ��ĳ���ǿռ����ϵĹ�ϵ����˹�ϵ����Ϊ����ֻ��֪������������������
	//n����ϵ����������������
bb:
	cout<<"�������ϵ�������(����)��(����)(>=2��<=100):";
	cin>>n;
	if(n < 0||n > 100)
	{
		cout<<"�����������������룡\n"<<endl;
		goto bb;  //���أ���������
	}

	//�����ϵ����
	cout<<"\n�������ϵ����:"<<endl;
	for(i = 0;i < n;i++)
	{
	begin:
		cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');  //������뻺����
		cout<<"���������ĵ�"<<i+1<<"��Ԫ��(ֻ������1��0��Ԫ���Կո�ָ�):";
		for(j = 0;j < n;j++)
			cin >> s[i][j];  //s[100][100]����Ź�ϵ����Ķ�ά����
			if (s[i][j] != 0 && s[i][j] != 1)
			{
				cout << "����������������룡" << endl;
				goto begin;
			}
	}

	cout<<"\n�����Ӧ���ѡ���㷨\nl:�Է��հ�\n2:�ԳƱհ�\n3:���ݱհ�\n4:�˳�"<<endl;
	cin>>z;  //z���㷨���
	switch(z)
	{
		case 1:zifan(s); break;  //l:�Է��հ�
		case 2:duichen(s);break;  //3:�ԳƱհ�
		case 3:chuandi(s);break;  //2:���ݱհ�
		case 4:exit();break;  //4:�˳�
	}
}

//��һ����������ѯ���Ƿ�������
void re()
{
	char x;  //�洢y��n�Ա�ʾ�����򲻼���
	cout<<"\n�Ƿ�������иó��򣿣�y/n����";
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
		cout<<"����������������롣"<<endl;
		re();
	}
}

//��ʾ�㷨���
//����Ĳ���s[][100]Ϊ��ϵ����
void output(bool s[][100])
{
	cout<<"\n�����ϵ����Ϊ:"<<endl;
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < n;j++) 
			cout<<s[i][j]<<" ";
		cout<<endl;;
	}
}

//���Է��հ�
//����Ĳ���s2[][100]Ϊ��ϵ����
void zifan(bool s2[100][100])
{
	//M=M+E��+Ϊ�߼��ӣ����0+1=1��1+1=1��ʹ��ϵ����Խ���Ԫ�ؾ�Ϊ1�������Է��հ���
	for(i = 0;i < n;i++) 
		s2[i][i] = 1;
	output(s2);
	re();
}

//��ԳƱհ�
//����Ĳ���s2[][100]Ϊ��ϵ����
void duichen(bool s2[][100])
{
	bool s1[100][100];  //s1����ϵ����s2��ת�þ���
	for(i = 0;i < n;i++)
		for(j = 0;j < n;j++)
			s1[j][i] = s2[i][j];
	//M=M+M'�����ϵ����ĶԳƱհ��������ϵ��������ת�þ����߼��ӵĽ����
	for(i = 0;i < n;i++)
		for(j = 0;j < n;j++)
			s2[i][j] = s1[i][j] + s2[i][j];
	output(s2);
	re(); 
}

//�󴫵ݱհ�
//����Ĳ���s2[][100]Ϊ��ϵ����
void chuandi(bool s2[][100])
{
	bool flag=0,t[100][100],temp[100][100],power[100][100],compare[100][100];
	int h;
	//���ڸ���������ʼ��
	for(i = 0;i < n;i++) 
		for(j = 0;j < n;j++)
		{
			power[i][j] = 0;  //power�����M^n���������
			t[i][j] = s2[i][j];  //t�����ÿ�μ���ȥ�Ľ��������
			compare[i][j]=s2[i][j];  //compare�����ǰһ��+M^n�Ľ��������ȷ���Ƿ���Ҫ����ѭ��
			temp[i][j]=s2[i][j];  //temp���洢��һ��power����M^(n-1)
		}

	//����Mt=M+M^2+M^3+��...+M^n�ļ���
	while(flag==0)
	{
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				power[i][j] = 0;    //ÿ�μ���M^nʱ��ÿһλ��ʼ��Ϊ0����֤֮�����������M^n�Ľ��
		//����M^n
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				for(h=0;h<n;h++)
					//powerΪ��һ�ֵ�M^n
					//tempʵ�ʵ�����һ��power����M^(n-1)��s2ΪM
					power[i][j]=power[i][j]+temp[i][h]*s2[h][j];  //tempʵ�ʵ�����һ��power����M^(n-1)��s2ΪM

		//������M^n����compare�������ۼӺ�t
		for(i = 0;i < n;i++) 
			for(j = 0;j < n;j++)
			{
				temp[i][j]=power[i][j];  //temp��ȫ���ƴ���power����M^n��
				t[i][j]=t[i][j]+power[i][j];  //tΪ�ۼӽ����Mt=M+M^2+M^3+����+M^n
			}

		flag=1;  //��flag��Ϊ1���ڽ������ж���ֻҪ����t��compare��һ��Ԫ�ز�ͬ��flag=0������Ҫ����ѭ��
		//�ж��Ƿ���Ҫ����ѭ��
		for(i = 0;i < n;i++) 
			for(j = 0;j < n;j++)
				//ͨ��t��compare�Ƿ���ȵ��жϣ��ж�M^n�Ƿ�ﵽ��������
				if(t[i][j]!=compare[i][j])  //compareΪM+M^2+����+M^(n-1)
				{
					flag=0;  //flag=1��ʾ������M���ݾ��Ѻ��ǣ�����Ҫ����ѭ��
					break;
				}

		//�������ۼӽ��ֵt��ֵ��compare������һ���п��ԶԱ�
		for(i = 0;i < n;i++) 
			for(j = 0;j < n;j++)
				compare[i][j]=t[i][j];  //compareΪ��һ�ּ����t��ֵ
	}

	output(t);
	re();
}

void exit()
{
	exit(1);
}