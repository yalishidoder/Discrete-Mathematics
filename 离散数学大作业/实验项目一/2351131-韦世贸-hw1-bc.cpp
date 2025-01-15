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
// 函数原型
void assignValues(vector<int>& variable_values, int index);
string infixToPostfix(const string& infix);
int evaluatePostfix(const string& postfix, const vector<char>& variables, const vector<int>& variable_values);
int evaluateExpression(const string& expression, const vector<char>& variables, const vector<int>& variable_values);

int main() 
{
    cout << "***************************************\n";
    cout << "**                                   **\n";
    cout << "**         欢迎进入逻辑运算软件      **\n";
    cout << "**   (可运算真值表,主范式,支持括号)  **\n";
    cout << "**                                   **\n";
    cout << "**              用!表示非            **\n";
    cout << "**              用&表示与            **\n";
    cout << "**              用|表示或            **\n";
    cout << "**             用^表示蕴含           **\n";
    cout << "**             用~表示等值           **\n";
    cout << "**                                   **\n";
    cout << "***************************************\n\n";
    cout << "请输入一个合法的命题公式 (建议使用空格分隔操作符和操作数，例如 \"a & !b\"):\n";

    string expression;
    getline(cin, expression);

    vector<char> variables;
    // 提取变量并去除重复
    for (char c : expression) {
        if (isalpha(c) && find(variables.begin(), variables.end(), c) == variables.end()) {
            variables.push_back(c);
        }
    }
    sort(variables.begin(), variables.end());

    int num_vars = variables.size();
    cout << "\n该式子中的变量个数为:" << num_vars << "\n";
    int num_combinations = pow(2, num_vars);

    // 生成真值表
    cout << "\n输出真值表如下:\n\n";
    // 输出变量列头
    for (char var : variables) {
        cout << " " << var << " ";
    }
    cout << "    " << expression << endl;

    vector<int> variable_values(num_vars, 0);
    vector<int> minterms;
    vector<int> maxterms;

    for (int i = 0; i < num_combinations; ++i) {
        // 输出变量值
        for (int val : variable_values) {
            cout << " " << val << " ";
        }
        // 计算表达式值
        int result = evaluateExpression(expression, variables, variable_values);
        cout << "    " << result << endl;
        if (result) {
            minterms.push_back(i);
        }
        else {
            maxterms.push_back(i);
        }
        // 生成下一个变量组合
        assignValues(variable_values, num_vars - 1);
    }

    // 输出主合取范式
    if (maxterms.empty()) {
        cout << "\n该命题公式不存在主合取范式.\n";
    }
    else {
        cout << "\n该命题公式的主合取范式:\n\t";
        for (size_t i = 0; i < maxterms.size(); ++i) {
            if (i > 0) {
                cout << " \\/ ";
            }
            cout << "M(" << maxterms[i] << ")";
        }
        cout << endl;
    }

    // 输出主析取范式
    if (minterms.empty()) {
        cout << "\n该命题公式不存在主析取范式.\n";
    }
    else {
        cout << "\n\n该命题公式的主析取范式:\n\t";
        for (size_t i = 0; i < minterms.size(); ++i) {
            if (i > 0) {
                cout << " /\\ ";
            }
            cout << "m(" << minterms[i] << ")";
        }
        cout << endl;
    }

    cout << "\n欢迎下次再次使用!\n";
    return 0;
}

// 生成变量的二进制组合
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

// 中缀表达式转换为后缀表达式
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
            opStack.pop(); // 弹出 '('
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

// 计算后缀表达式的值
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

// 评估表达式的值
int evaluateExpression(const string& expression, const vector<char>& variables, const vector<int>& variable_values) {
    string postfix = infixToPostfix(expression);
    // 调试语句
    // cout << "后缀表达式: " << postfix << endl;
    return evaluatePostfix(postfix, variables, variable_values);
}