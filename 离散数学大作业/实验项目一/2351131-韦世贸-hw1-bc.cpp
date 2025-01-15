#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAX_VARS = 50;
// a^b~c!b&a~c
// !a^b~(c!d~(!b&c)^!d)!a
// ����ԭ��
void assignValues(vector<int>& variable_values, int index);
string infixToPostfix(const string& infix);
int evaluatePostfix(const string& postfix, const vector<char>& variables, const vector<int>& variable_values);
int evaluateExpression(const string& expression, const vector<char>& variables, const vector<int>& variable_values);

int main() 
{
    cout << "***************************************\n";
    cout << "**                                   **\n";
    cout << "**         ��ӭ�����߼��������      **\n";
    cout << "**   (��������ֵ��,����ʽ,֧������)  **\n";
    cout << "**                                   **\n";
    cout << "**              ��!��ʾ��            **\n";
    cout << "**              ��&��ʾ��            **\n";
    cout << "**              ��|��ʾ��            **\n";
    cout << "**             ��^��ʾ�̺�           **\n";
    cout << "**             ��~��ʾ��ֵ           **\n";
    cout << "**                                   **\n";
    cout << "***************************************\n\n";
    cout << "������һ���Ϸ������⹫ʽ (����ʹ�ÿո�ָ��������Ͳ����������� \"a & !b\"):\n";

    string expression;
    getline(cin, expression);

    vector<char> variables;
    // ��ȡ������ȥ���ظ�
    for (char c : expression) {
        if (isalpha(c) && find(variables.begin(), variables.end(), c) == variables.end()) {
            variables.push_back(c);
        }
    }
    sort(variables.begin(), variables.end());

    int num_vars = variables.size();
    cout << "\n��ʽ���еı�������Ϊ:" << num_vars << "\n";
    int num_combinations = pow(2, num_vars);

    // ������ֵ��
    cout << "\n�����ֵ������:\n\n";
    // ���������ͷ
    for (char var : variables) {
        cout << " " << var << " ";
    }
    cout << "    " << expression << endl;

    vector<int> variable_values(num_vars, 0);
    vector<int> minterms;
    vector<int> maxterms;

    for (int i = 0; i < num_combinations; ++i) {
        // �������ֵ
        for (int val : variable_values) {
            cout << " " << val << " ";
        }
        // ������ʽֵ
        int result = evaluateExpression(expression, variables, variable_values);
        cout << "    " << result << endl;
        if (result) {
            minterms.push_back(i);
        }
        else {
            maxterms.push_back(i);
        }
        // ������һ���������
        assignValues(variable_values, num_vars - 1);
    }

    // �������ȡ��ʽ
    if (maxterms.empty()) {
        cout << "\n�����⹫ʽ����������ȡ��ʽ.\n";
    }
    else {
        cout << "\n�����⹫ʽ������ȡ��ʽ:\n\t";
        for (size_t i = 0; i < maxterms.size(); ++i) {
            if (i > 0) {
                cout << " \\/ ";
            }
            cout << "M(" << maxterms[i] << ")";
        }
        cout << endl;
    }

    // �������ȡ��ʽ
    if (minterms.empty()) {
        cout << "\n�����⹫ʽ����������ȡ��ʽ.\n";
    }
    else {
        cout << "\n\n�����⹫ʽ������ȡ��ʽ:\n\t";
        for (size_t i = 0; i < minterms.size(); ++i) {
            if (i > 0) {
                cout << " /\\ ";
            }
            cout << "m(" << minterms[i] << ")";
        }
        cout << endl;
    }

    cout << "\n��ӭ�´��ٴ�ʹ��!\n";
    return 0;
}

// ���ɱ����Ķ��������
void assignValues(vector<int>& variable_values, int index) {
    if (index < 0) {
        return;
    }
    if (variable_values[index] == 0) {
        variable_values[index] = 1;
    }
    else {
        variable_values[index] = 0;
        assignValues(variable_values, index - 1);
    }
}

// ��׺���ʽת��Ϊ��׺���ʽ
string infixToPostfix(const string& infix) {
    stack<char> opStack;
    string postfix;
    map<char, int> precedence = {
        {'!', 4},
        {'&', 3},
        {'|', 2},
        {'^', 1},
        {'~', 1},
    };

    for (size_t i = 0; i < infix.size(); ++i) {
        char c = infix[i];
        if (isalpha(c)) {
            postfix += c;
        }
        else if (c == '(') {
            opStack.push(c);
        }
        else if (c == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                postfix += opStack.top();
                opStack.pop();
            }
            opStack.pop(); // ���� '('
        }
        else if (c == '!') {
            opStack.push(c);
        }
        else if (precedence.find(c) != precedence.end()) {
            while (!opStack.empty() && opStack.top() != '(' && precedence[opStack.top()] >= precedence[c]) {
                postfix += opStack.top();
                opStack.pop();
            }
            opStack.push(c);
        }
    }
    while (!opStack.empty()) {
        postfix += opStack.top();
        opStack.pop();
    }
    return postfix;
}

// �����׺���ʽ��ֵ
int evaluatePostfix(const string& postfix, const vector<char>& variables, const vector<int>& variable_values) {
    stack<int> valueStack;
    for (char c : postfix) {
        if (isalpha(c)) {
            int index = find(variables.begin(), variables.end(), c) - variables.begin();
            valueStack.push(variable_values[index]);
        }
        else if (c == '!') {
            int operand = valueStack.top();
            valueStack.pop();
            valueStack.push(!operand);
        }
        else if (c == '&') {
            int operand2 = valueStack.top();
            valueStack.pop();
            int operand1 = valueStack.top();
            valueStack.pop();
            valueStack.push(operand1 && operand2);
        }
        else if (c == '|') {
            int operand2 = valueStack.top();
            valueStack.pop();
            int operand1 = valueStack.top();
            valueStack.pop();
            valueStack.push(operand1 || operand2);
        }
        else if (c == '^') {
            int operand2 = valueStack.top();
            valueStack.pop();
            int operand1 = valueStack.top();
            valueStack.pop();
            valueStack.push(!operand1 || operand2);
        }
        else if (c == '~') {
            int operand2 = valueStack.top();
            valueStack.pop();
            int operand1 = valueStack.top();
            valueStack.pop();
            valueStack.push((!operand1 || operand2) && (operand1 || !operand2));
        }
    }
    return valueStack.top();
}

// �������ʽ��ֵ
int evaluateExpression(const string& expression, const vector<char>& variables, const vector<int>& variable_values) {
    string postfix = infixToPostfix(expression);
    // �������
    // cout << "��׺���ʽ: " << postfix << endl;
    return evaluatePostfix(postfix, variables, variable_values);
}