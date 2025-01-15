#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Tree {
    int num;          // 节点的频率值
    Tree* left;       // 左子节点
    Tree* right;      // 右子节点
};

struct Code {
    int freq;
    vector<char> code;
    Code(const int data = -1, const vector<char>null = { 0 }) :freq(data), code(null) {}
};

// 生成叶子节点
void init_node(const vector<int>& frequencies, vector<Tree*>& nodes) {
    for (int freq : frequencies) {
        Tree* node = new Tree{ freq, nullptr, nullptr };
        nodes.push_back(node);
    }
}

// 构建哈夫曼树
Tree* buildHuffmanTree(vector<Tree*>& nodes) {
    auto comp = [](Tree* a, Tree* b) { return a->num > b->num; };
    priority_queue<Tree*, vector<Tree*>, decltype(comp)> minHeap(comp);

    // 将所有叶子节点放入最小堆
    for (Tree* node : nodes) {
        minHeap.push(node);
    }

    while (minHeap.size() > 1) {
        Tree* left = minHeap.top();
        minHeap.pop();
        Tree* right = minHeap.top();
        minHeap.pop();

        Tree* internal = new Tree{ left->num + right->num, left, right };
        minHeap.push(internal);
    }

    return minHeap.empty() ? nullptr : minHeap.top();
}

// 生成前缀码的先序遍历函数
void generateCodes(Tree* root, vector<char>& path, vector<Code>& codes) {
    if (root == nullptr) {
        return;
    }
    if (root->left == nullptr && root->right == nullptr) {
        Code code;
        code.freq = root->num;
        code.code = path;
        codes.push_back(code);
    }
    path.push_back('0');
    generateCodes(root->left, path, codes);
    path.pop_back();

    path.push_back('1');
    generateCodes(root->right, path, codes);
    path.pop_back();
}

int main() {
    int n;
    cout << "请输入节点个数(必须是正整数):";
    cin >> n;
    if (n <= 0) {
        cout << "节点个数必须是正整数。" << endl;
        return -1;
    }

    vector<int> frequencies(n);
    cout << "请输入节点频率(以空格分隔):";
    for (int i = 0; i < n; ++i) {
        cin >> frequencies[i];
    }

    // 初始化叶子节点
    vector<Tree*> nodes;
    init_node(frequencies, nodes);

    // 构建哈夫曼树
    Tree* root = buildHuffmanTree(nodes);

    if (root == nullptr) {
        cout << "无法构建哈夫曼树。" << endl;
        return -1;
    }

    // 生成前缀码
    vector<Code> codes;
    vector<char> path;
    generateCodes(root, path, codes);

    // 输出前缀码
    cout << "前缀码:" << endl;
    for (const Code& code : codes) {
        cout << "频率 " << code.freq << ": ";
        for (char c : code.code) {
            cout << c;
        }
        cout << endl;
    }

    // 释放内存
    // 需要遍历树并删除所有节点
    // 这里为了简单起见，假设在程序结束时由系统回收内存

    return 0;
}