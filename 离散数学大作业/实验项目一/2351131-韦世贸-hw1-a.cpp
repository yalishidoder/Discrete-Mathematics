#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

int main() 
{
    int p, q;
    char choice;

    while (true) {
        cout << "***************************************\n";
        cout << "**                                   **\n";
        cout << "**        ��ӭ�����߼��������       **\n";
        cout << "**                                   **\n";
        cout << "***************************************\n\n";

        // ����P��ֵ
        while (true) {
            cout << "\n  ������P��ֵ��0��1��,�Իس�����: ";
            if (!(cin >> p) || (p != 0 && p != 1)) {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "\n  P��ֵ��������,����������!\n";
                //this_thread::sleep_for(chrono::seconds(2));
                //system("cls");
            }
            else {
                break;
            }
        }

        // ����Q��ֵ
        while (true) {
            cout << "\n  ������Q��ֵ��0��1��,�Իس�����: ";
            if (!(cin >> q) || (q != 0 && q != 1)) {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "\n  Q��ֵ��������,����������!\n";
                //this_thread::sleep_for(chrono::seconds(2));
                //system("cls");
            }
            else {
                break;
            }
        }

        // �߼�����
        bool a[4];
        a[0] = p && q;    // ��ȡ
        a[1] = p || q;    // ��ȡ
        a[2] = !p || q;   // �̺�
        a[3] = (!p || q) && (!q || p); // ��ֵ

        // ������
        cout << "\n\n  ��ȡ:\n       P&&Q = " << a[0] << "\n";
        cout << "  ��ȡ:\n       P||Q = " << a[1] << "\n";
        cout << "  ����:\n       P->Q = " << a[2] << "\n";
        cout << "  ˫����:\n       P<->Q = " << a[3] << "\n";

        // �Ƿ��������
        while (true) {
            cout << "\n�Ƿ��������?��y/n��";
            cin >> choice;
            if (choice == 'y' || choice == 'n') {
                if (choice == 'y') {
                    system("cls");
                    break;
                }
                else {
                    cout << "��ӭ�´��ٴ�ʹ��!\n";
                    return 0;
                }
            }
            else {
                cout << "�������,����������!\n";
            }
        }
    }
}