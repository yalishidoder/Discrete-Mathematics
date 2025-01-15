#include <iostream>
#include <vector>

using namespace std;

// 函数声明
vector<vector<bool>> readMatrix(int n);
vector<vector<bool>> computeTransitiveClosure(const vector<vector<bool>>& matrix, int n);
void printMatrix(const vector<vector<bool>>& matrix, int n);

int main() {
    int n;
    cout << "请输入节点数n: ";
    cin >> n;
    if (n <= 0) {
        cout << "节点数必须大于0。" << endl;
        return 1;
    }
    vector<vector<bool>> matrix = readMatrix(n);
    vector<vector<bool>> closure = computeTransitiveClosure(matrix, n);
    cout << "传递闭包矩阵:" << endl;
    printMatrix(closure, n);
    return 0;
}

// 读取邻接矩阵
vector<vector<bool>> readMatrix(int n) {
    vector<vector<bool>> matrix(n, vector<bool>(n));
    cout << "请输入邻接矩阵（每行n个0或1，以空格分隔）:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int input;
            cin >> input;
            if (cin.fail() || (input != 0 && input != 1)) {
                cout << "输入错误，请输入0或1。" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return readMatrix(n); // 递归重新读取矩阵
            }
            matrix[i][j] = bool(input);
        }
    }
    return matrix;
}

// 计算传递闭包
vector<vector<bool>> computeTransitiveClosure(const vector<vector<bool>>& matrix, int n) {
    vector<vector<bool>> closure(matrix);
    // Warshall算法更新可达性矩阵
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                closure[i][j] = closure[i][j] || (closure[i][k] && closure[k][j]);
            }
        }
    }
    return closure;
}

// 输出矩阵
void printMatrix(const vector<vector<bool>>& matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}