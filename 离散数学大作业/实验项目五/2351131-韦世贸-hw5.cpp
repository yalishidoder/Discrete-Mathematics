#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Tree {
    int num;          // �ڵ��Ƶ��ֵ
    Tree* left;       // ���ӽڵ�
    Tree* right;      // ���ӽڵ�
};

struct Code {
    int freq;
    vector<char> code;
    Code(const int data = -1, const vector<char>null = { 0 }) :freq(data), code(null) {}
};

// ����Ҷ�ӽڵ�
void init_node(const vector<int>& frequencies, vector<Tree*>& nodes) {
    for (int freq : frequencies) {
        Tree* node = new Tree{ freq, nullptr, nullptr };
        nodes.push_back(node);
    }
}

// ������������
Tree* buildHuffmanTree(vector<Tree*>& nodes) {
    auto comp = [](Tree* a, Tree* b) { return a->num > b->num; };
    priority_queue<Tree*, vector<Tree*>, decltype(comp)> minHeap(comp);

    // ������Ҷ�ӽڵ������С��
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

// ����ǰ׺��������������
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
    cout << "������ڵ����(������������):";
    cin >> n;
    if (n <= 0) {
        cout << "�ڵ������������������" << endl;
        return -1;
    }

    vector<int> frequencies(n);
    cout << "������ڵ�Ƶ��(�Կո�ָ�):";
    for (int i = 0; i < n; ++i) {
        cin >> frequencies[i];
    }

    // ��ʼ��Ҷ�ӽڵ�
    vector<Tree*> nodes;
    init_node(frequencies, nodes);

    // ������������
    Tree* root = buildHuffmanTree(nodes);

    if (root == nullptr) {
        cout << "�޷���������������" << endl;
        return -1;
    }

    // ����ǰ׺��
    vector<Code> codes;
    vector<char> path;
    generateCodes(root, path, codes);

    // ���ǰ׺��
    cout << "ǰ׺��:" << endl;
    for (const Code& code : codes) {
        cout << "Ƶ�� " << code.freq << ": ";
        for (char c : code.code) {
            cout << c;
        }
        cout << endl;
    }

    // �ͷ��ڴ�
    // ��Ҫ��������ɾ�����нڵ�
    // ����Ϊ�˼�����������ڳ������ʱ��ϵͳ�����ڴ�

    return 0;
}