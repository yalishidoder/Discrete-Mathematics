/*    prim�㷨ʵ��
#include <iostream>  
#include <vector>    
#include <limits.h>  // ��������ֵ���壬��INT_MAX

using namespace std;

const int N = 100;   // ����ͼ����󶥵���Ϊ100

vector<int> p(N + 1);          // p���飬��¼ÿ�������ǰ��
vector<int> key(N + 1);        // key���飬��¼ÿ������ļ�ֵ
vector<vector<int>> tb(N + 1, vector<int>(N + 1, INT_MAX)); // tb�ڽӾ��󣬳�ʼ��ΪINT_MAX��ʾ�ޱ�

void prim(int v, int n) {
    // Prim�㷨���Ӷ���v��ʼ������С��������n�Ƕ�����
    for (int i = 1; i <= n; ++i) {
        p[i] = v;          // ��ʼ�����ж����ǰ��Ϊ���v
        key[i] = tb[v][i]; // ��ʼ�����ж���ļ�ֵΪ���v���ö���ı�Ȩ
    }
    key[v] = 0;            // ���ļ�ֵ��Ϊ0

    for (int i = 2; i <= n; ++i) {
        int min = INT_MAX; // ��ʼ����С��ֵΪINT_MAX
        int u = v;         // ��ʼ����С��ֵ�Ķ���Ϊv

        // Ѱ�ҵ�ǰ��С��ֵ�Ķ���
        for (int j = 1; j <= n; ++j) {
            if (key[j] > 0 && key[j] < min) { // key[j] > 0��ʾ�ö���δ��ѡ���Ҽ�ֵС�ڵ�ǰ��Сֵ
                min = key[j]; // ������С��ֵ
                u = j;        // ������С��ֵ�Ķ���
            }
        }

        cout << "��С�ķ���:" << p[u] << "��" << u << " Ȩֵ�ǣ�" << key[u] << endl; // ���ѡ��ı�

        key[u] = 0; // ��ѡ��Ķ���ļ�ֵ��Ϊ0����ʾ��ѡ��

        // ������������ļ�ֵ
        for (int j = 1; j <= n; ++j) {
            if (tb[u][j] < key[j]) { // ���ͨ������u������j�ı�ȨС��j�ĵ�ǰ��ֵ
                p[j] = u;            // ����j��ǰ��Ϊu
                key[j] = tb[u][j];   // ����j�ļ�ֵΪ��Ȩ
            }
        }
    }
}

int main() {
    int n, m;
    cout << "����������ͼ�Ķ�����Ŀ�ͱߵ���Ŀ(�Կո�ָ�����������������0����):" << endl;
    while (cin >> n >> m) {
        if (n != 0 && m != 0) {
            // ��ʼ���ڽӾ����������бߵ�Ȩ��ΪINT_MAX
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    tb[i][j] = INT_MAX;
                }
            }

            cout << "������ߵĽڵ�����Լ����ǵ�Ȩֵ(�Կո�ָ�������):" << endl;
            // ��ȡm���ߵ���Ϣ�������ڽӾ���
            for (int j = 0; j < m; ++j) {
                int u, v, w;
                cin >> u >> v >> w;
                tb[u][v] = tb[v][u] = w; // ����ͼ��˫�����ñ�Ȩ
            }

            prim(1, n); // �Ӷ���1��ʼִ��Prim�㷨

            cout << endl;
            cout << "����������ͼ�Ķ�����Ŀ�ͱߵ���Ŀ(�Կո�ָ�����������������0����):" << endl;
        }
        else if (n == 0 && m == 0) {
            return 0; // ����0 0ʱ��������
        }
    }
    return 0;
}
*/

//kruskal�㷨ʵ��
#include <iostream>
#include <vector>
#include <algorithm> // ��������
#include <limits.h>

using namespace std;

const int N = 100;

// �ߵĽṹ�壬�������������Ȩ��
struct Edge {
    int u;
    int v;
    int w;
};

vector<Edge> edges; // ȫ�ֱ��б�

// ���鼯ʵ��
vector<int> parent(N + 1);
vector<int> Rank(N + 1);

// ��ʼ�����鼯
void initialize(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i; // ÿ���ڵ�ĸ��ڵ��ʼ��Ϊ����
        Rank[i] = 1;   // ÿ���ڵ���ȳ�ʼ��Ϊ1
    }
}

// ���Ҹ��ڵ㣨·��ѹ����
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]); // ·��ѹ��
    }
    return parent[x];
}

// �ϲ��������ϣ����Ⱥϲ���
void Union(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (Rank[rootX] > Rank[rootY]) {
            parent[rootY] = rootX;
        }
        else if (Rank[rootX] < Rank[rootY]) {
            parent[rootX] = rootY;
        }
        else {
            parent[rootY] = rootX;
            Rank[rootX]++;
        }
    }
}

// Kruskal�㷨ʵ��
void kruskal(int n) {
    // ��Ȩ�����������
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
        });

    initialize(n); // ��ʼ�����鼯
    int count = 0; // ��ѡ��ı���
    int total_cost = 0; // ��С����������Ȩ��

    // �������бߣ�ѡ���γɻ��ı�
    for (auto& edge : edges) {
        if (count == n - 1) break; // ��ѡ��n-1���ߣ�����
        if (find(edge.u) != find(edge.v)) { // ���γɻ�
            cout << "��С�ķ���:" << edge.u << "��" << edge.v << " Ȩֵ�ǣ�" << edge.w << endl;
            Union(edge.u, edge.v); // �ϲ���������
            total_cost += edge.w;  // �ۼ�Ȩ��
            count++;
        }
    }
}

int main() {
    int n, m;
    cout << "����������ͼ�Ķ�����Ŀ�ͱߵ���Ŀ(�Կո�ָ�����������������0����):\n";
    while (cin >> n >> m) {
        if (n != 0 && m != 0) {
            edges.clear(); // ��ձ��б�
            cout << "������ߵĽڵ�����Լ����ǵ�Ȩֵ(�Կո�ָ�������):\n";
            // ��ȡm���ߵ���Ϣ����ӵ����б�
            for (int j = 0; j < m; ++j) {
                int u, v, w;
                cin >> u >> v >> w;
                edges.push_back({ u, v, w }); // ��ӵ����б�
            }
            kruskal(n); // ����Kruskal�㷨
            cout << endl;
            cout << "����������ͼ�Ķ�����Ŀ�ͱߵ���Ŀ(�Կո�ָ�����������������0����):\n";
        }
        else if (n == 0 && m == 0) {
            return 0; // ����0 0ʱ��������
        }
    }
    return 0;
}