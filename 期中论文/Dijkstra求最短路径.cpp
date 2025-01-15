#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

vector<vector<pair<int, int>>> adj; // 邻接表的定义

void dijkstra(int start, int n, vector<int>& dist, vector<int>& prev)
{
    // 优先队列，按距离升序排列
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    // 起点的距离为0
    dist[start] = 0;
    pq.push(make_pair(0, start));

    while (!pq.empty()) {
        // 取出当前距离最小的节点
        int u = pq.top().second;
        int current_dist = pq.top().first;
        pq.pop();
        // 如果当前距离大于已记录的距离，跳过
        if (current_dist > dist[u]) continue;
        // 遍历当前节点的所有邻居
        for (auto neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            // 如果通过当前节点到邻居的距离更短，更新距离和前驱节点
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
}

void printPath(int u, vector<int>& prev)
{
    // 递归打印路径，直到起点
    if (prev[u] != -1) {
        printPath(prev[u], prev);
    }
    cout << u << " ";
}

int main()
{
    int n, m;
    cout << "请输入节点数和边的数量: ";
    cin >> n >> m;
    adj.resize(n);
    cout << "按（起点-终点-权值）顺序输入边 (即u v w):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w)); // 无向图，双向添加
    }

    int start, dest;
    cout << "请输入起点和终点: ";
    cin >> start >> dest;

    if (start < 0 || start >= n || dest < 0 || dest >= n) {
        cout << "起点或终点无效。" << endl;
        return 1;
    }

    vector<int> dist(n, INT_MAX); // 初始化距离为无穷大
    vector<int> prev(n, -1);      // 初始化前驱节点为-1

    dijkstra(start, n, dist, prev);

    if (dist[dest] == INT_MAX) {
        cout << "从 " << start << " 到 " << dest << " 没有路径。" << endl;
    }
    else {
        cout << "从 " << start << " 到 " << dest << " 的最短路径: ";
        printPath(dest, prev);
        cout << endl;
        cout << "需要的花费: " << dist[dest] << endl;
    }

    return 0;
}