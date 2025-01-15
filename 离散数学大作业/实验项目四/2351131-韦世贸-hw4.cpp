/*    prim算法实现
#include <iostream>  
#include <vector>    
#include <limits.h>  // 包含极限值定义，如INT_MAX

using namespace std;

const int N = 100;   // 定义图的最大顶点数为100

vector<int> p(N + 1);          // p数组，记录每个顶点的前驱
vector<int> key(N + 1);        // key数组，记录每个顶点的键值
vector<vector<int>> tb(N + 1, vector<int>(N + 1, INT_MAX)); // tb邻接矩阵，初始化为INT_MAX表示无边

void prim(int v, int n) {
    // Prim算法，从顶点v开始构造最小生成树，n是顶点数
    for (int i = 1; i <= n; ++i) {
        p[i] = v;          // 初始化所有顶点的前驱为起点v
        key[i] = tb[v][i]; // 初始化所有顶点的键值为起点v到该顶点的边权
    }
    key[v] = 0;            // 起点的键值设为0

    for (int i = 2; i <= n; ++i) {
        int min = INT_MAX; // 初始化最小键值为INT_MAX
        int u = v;         // 初始化最小键值的顶点为v

        // 寻找当前最小键值的顶点
        for (int j = 1; j <= n; ++j) {
            if (key[j] > 0 && key[j] < min) { // key[j] > 0表示该顶点未被选择，且键值小于当前最小值
                min = key[j]; // 更新最小键值
                u = j;        // 更新最小键值的顶点
            }
        }

        cout << "最小耗费是:" << p[u] << "和" << u << " 权值是：" << key[u] << endl; // 输出选择的边

        key[u] = 0; // 将选择的顶点的键值设为0，表示已选择

        // 更新其他顶点的键值
        for (int j = 1; j <= n; ++j) {
            if (tb[u][j] < key[j]) { // 如果通过顶点u到顶点j的边权小于j的当前键值
                p[j] = u;            // 更新j的前驱为u
                key[j] = tb[u][j];   // 更新j的键值为边权
            }
        }
    }
}

int main() {
    int n, m;
    cout << "请输入所求图的顶点数目和边的数目(以空格分隔各个数，输入两个0结束):" << endl;
    while (cin >> n >> m) {
        if (n != 0 && m != 0) {
            // 初始化邻接矩阵，设置所有边的权重为INT_MAX
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    tb[i][j] = INT_MAX;
                }
            }

            cout << "请输入边的节点序号以及它们的权值(以空格分隔各个数):" << endl;
            // 读取m条边的信息，更新邻接矩阵
            for (int j = 0; j < m; ++j) {
                int u, v, w;
                cin >> u >> v >> w;
                tb[u][v] = tb[v][u] = w; // 无向图，双向设置边权
            }

            prim(1, n); // 从顶点1开始执行Prim算法

            cout << endl;
            cout << "请输入所求图的顶点数目和边的数目(以空格分隔各个数，输入两个0结束):" << endl;
        }
        else if (n == 0 && m == 0) {
            return 0; // 输入0 0时结束程序
        }
    }
    return 0;
}
*/

//kruskal算法实现
#include <iostream>
#include <vector>
#include <algorithm> // 用于排序
#include <limits.h>

using namespace std;

const int N = 100;

// 边的结构体，包含两个顶点和权重
struct Edge {
    int u;
    int v;
    int w;
};

vector<Edge> edges; // 全局边列表

// 并查集实现
vector<int> parent(N + 1);
vector<int> Rank(N + 1);

// 初始化并查集
void initialize(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i; // 每个节点的父节点初始化为自身
        Rank[i] = 1;   // 每个节点的秩初始化为1
    }
}

// 查找根节点（路径压缩）
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]); // 路径压缩
    }
    return parent[x];
}

// 合并两个集合（按秩合并）
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

// Kruskal算法实现
void kruskal(int n) {
    // 按权重升序排序边
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
        });

    initialize(n); // 初始化并查集
    int count = 0; // 已选择的边数
    int total_cost = 0; // 最小生成树的总权重

    // 遍历所有边，选择不形成环的边
    for (auto& edge : edges) {
        if (count == n - 1) break; // 已选择n-1条边，结束
        if (find(edge.u) != find(edge.v)) { // 不形成环
            cout << "最小耗费是:" << edge.u << "和" << edge.v << " 权值是：" << edge.w << endl;
            Union(edge.u, edge.v); // 合并两个集合
            total_cost += edge.w;  // 累加权重
            count++;
        }
    }
}

int main() {
    int n, m;
    cout << "请输入所求图的顶点数目和边的数目(以空格分隔各个数，输入两个0结束):\n";
    while (cin >> n >> m) {
        if (n != 0 && m != 0) {
            edges.clear(); // 清空边列表
            cout << "请输入边的节点序号以及它们的权值(以空格分隔各个数):\n";
            // 读取m条边的信息，添加到边列表
            for (int j = 0; j < m; ++j) {
                int u, v, w;
                cin >> u >> v >> w;
                edges.push_back({ u, v, w }); // 添加到边列表
            }
            kruskal(n); // 调用Kruskal算法
            cout << endl;
            cout << "请输入所求图的顶点数目和边的数目(以空格分隔各个数，输入两个0结束):\n";
        }
        else if (n == 0 && m == 0) {
            return 0; // 输入0 0时结束程序
        }
    }
    return 0;
}