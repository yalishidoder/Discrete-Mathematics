#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

vector<vector<pair<int, int>>> adj; // �ڽӱ�Ķ���

void dijkstra(int start, int n, vector<int>& dist, vector<int>& prev)
{
    // ���ȶ��У���������������
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    // ���ľ���Ϊ0
    dist[start] = 0;
    pq.push(make_pair(0, start));

    while (!pq.empty()) {
        // ȡ����ǰ������С�Ľڵ�
        int u = pq.top().second;
        int current_dist = pq.top().first;
        pq.pop();
        // �����ǰ��������Ѽ�¼�ľ��룬����
        if (current_dist > dist[u]) continue;
        // ������ǰ�ڵ�������ھ�
        for (auto neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            // ���ͨ����ǰ�ڵ㵽�ھӵľ�����̣����¾����ǰ���ڵ�
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
    // �ݹ��ӡ·����ֱ�����
    if (prev[u] != -1) {
        printPath(prev[u], prev);
    }
    cout << u << " ";
}

int main()
{
    int n, m;
    cout << "������ڵ����ͱߵ�����: ";
    cin >> n >> m;
    adj.resize(n);
    cout << "�������-�յ�-Ȩֵ��˳������� (��u v w):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w)); // ����ͼ��˫�����
    }

    int start, dest;
    cout << "�����������յ�: ";
    cin >> start >> dest;

    if (start < 0 || start >= n || dest < 0 || dest >= n) {
        cout << "�����յ���Ч��" << endl;
        return 1;
    }

    vector<int> dist(n, INT_MAX); // ��ʼ������Ϊ�����
    vector<int> prev(n, -1);      // ��ʼ��ǰ���ڵ�Ϊ-1

    dijkstra(start, n, dist, prev);

    if (dist[dest] == INT_MAX) {
        cout << "�� " << start << " �� " << dest << " û��·����" << endl;
    }
    else {
        cout << "�� " << start << " �� " << dest << " �����·��: ";
        printPath(dest, prev);
        cout << endl;
        cout << "��Ҫ�Ļ���: " << dist[dest] << endl;
    }

    return 0;
}