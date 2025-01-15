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
        cout << "**        欢迎进入逻辑运算程序       **\n";
        cout << "**                                   **\n";
        cout << "***************************************\n\n";

        // 输入P的值
        while (true) {
            cout << "\n  请输入P的值（0或1）,以回车结束: ";
            if (!(cin >> p) || (p != 0 && p != 1)) {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "\n  P的值输入有误,请重新输入!\n";
                //this_thread::sleep_for(chrono::seconds(2));
                //system("cls");
            }
            else {
                break;
            }
        }

        // 输入Q的值
        while (true) {
            cout << "\n  请输入Q的值（0或1）,以回车结束: ";
            if (!(cin >> q) || (q != 0 && q != 1)) {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "\n  Q的值输入有误,请重新输入!\n";
                //this_thread::sleep_for(chrono::seconds(2));
                //system("cls");
            }
            else {
                break;
            }
        }

        // 逻辑运算
        bool a[4];
        a[0] = p && q;    // 合取
        a[1] = p || q;    // 析取
        a[2] = !p || q;   // 蕴含
        a[3] = (!p || q) && (!q || p); // 等值

        // 输出结果
        cout << "\n\n  合取:\n       P&&Q = " << a[0] << "\n";
        cout << "  析取:\n       P||Q = " << a[1] << "\n";
        cout << "  条件:\n       P->Q = " << a[2] << "\n";
        cout << "  双条件:\n       P<->Q = " << a[3] << "\n";

        // 是否继续运算
        while (true) {
            cout << "\n是否继续运算?（y/n）";
            cin >> choice;
            if (choice == 'y' || choice == 'n') {
                if (choice == 'y') {
                    system("cls");
                    break;
                }
                else {
                    cout << "欢迎下次再次使用!\n";
                    return 0;
                }
            }
            else {
                cout << "输入错误,请重新输入!\n";
            }
        }
    }
}