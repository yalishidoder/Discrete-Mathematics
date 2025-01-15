#include <iostream>
#include <vector>

using namespace std;

// ��������
vector<vector<bool>> readMatrix(int n);
vector<vector<bool>> computeTransitiveClosure(const vector<vector<bool>>& matrix, int n);
void printMatrix(const vector<vector<bool>>& matrix, int n);

int main() {
    int n;
    cout << "������ڵ���n: ";
    cin >> n;
    if (n <= 0) {
        cout << "�ڵ����������0��" << endl;
        return 1;
    }
    vector<vector<bool>> matrix = readMatrix(n);
    vector<vector<bool>> closure = computeTransitiveClosure(matrix, n);
    cout << "���ݱհ�����:" << endl;
    printMatrix(closure, n);
    return 0;
}

// ��ȡ�ڽӾ���
vector<vector<bool>> readMatrix(int n) {
    vector<vector<bool>> matrix(n, vector<bool>(n));
    cout << "�������ڽӾ���ÿ��n��0��1���Կո�ָ���:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int input;
            cin >> input;
            if (cin.fail() || (input != 0 && input != 1)) {
                cout << "�������������0��1��" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return readMatrix(n); // �ݹ����¶�ȡ����
            }
            matrix[i][j] = bool(input);
        }
    }
    return matrix;
}

// ���㴫�ݱհ�
vector<vector<bool>> computeTransitiveClosure(const vector<vector<bool>>& matrix, int n) {
    vector<vector<bool>> closure(matrix);
    // Warshall�㷨���¿ɴ��Ծ���
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                closure[i][j] = closure[i][j] || (closure[i][k] && closure[k][j]);
            }
        }
    }
    return closure;
}

// �������
void printMatrix(const vector<vector<bool>>& matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}