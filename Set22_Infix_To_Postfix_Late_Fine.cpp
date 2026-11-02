#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

vector<string> tokenize(const string& expression) {
    vector<string> tokens;
    for (size_t i = 0; i < expression.size();) {
        if (isspace(static_cast<unsigned char>(expression[i]))) {
            ++i;
        } else if (isalpha(static_cast<unsigned char>(expression[i]))) {
            size_t start = i++;
            while (i < expression.size() &&
                   (isalnum(static_cast<unsigned char>(expression[i])) ||
                    expression[i] == '_')) ++i;
            tokens.push_back(expression.substr(start, i - start));
        } else if (isdigit(static_cast<unsigned char>(expression[i])) ||
                   expression[i] == '.') {
            size_t start = i++;
            while (i < expression.size() &&
                   (isdigit(static_cast<unsigned char>(expression[i])) ||
                    expression[i] == '.')) ++i;
            tokens.push_back(expression.substr(start, i - start));
        } else if (string("+-*/()").find(expression[i]) != string::npos) {
            tokens.push_back(string(1, expression[i++]));
        } else {
            throw invalid_argument("Unsupported character in expression.");
        }
    }
    return tokens;
}

int precedence(const string& op) {
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

bool isOperator(const string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

vector<string> toPostfix(const vector<string>& infix) {
    vector<string> output;
    stack<string> operators;
    for (const string& token : infix) {
        if (isalpha(static_cast<unsigned char>(token[0])) ||
            isdigit(static_cast<unsigned char>(token[0])) || token[0] == '.') {
            output.push_back(token);
        } else if (token == "(") {
            operators.push(token);
        } else if (token == ")") {
            while (!operators.empty() && operators.top() != "(") {
                output.push_back(operators.top());
                operators.pop();
            }
            if (operators.empty()) throw invalid_argument("Mismatched parentheses.");
            operators.pop();
        } else if (isOperator(token)) {
            while (!operators.empty() && isOperator(operators.top()) &&
                   precedence(operators.top()) >= precedence(token)) {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.push(token);
        } else {
            throw invalid_argument("Invalid expression token.");
        }
    }
    while (!operators.empty()) {
        if (operators.top() == "(") throw invalid_argument("Mismatched parentheses.");
        output.push_back(operators.top());
        operators.pop();
    }
    return output;
}

double evaluatePostfix(const vector<string>& postfix, const map<string, double>& values) {
    stack<double> operands;
    for (const string& token : postfix) {
        if (isOperator(token)) {
            if (operands.size() < 2) throw invalid_argument("Invalid expression.");
            double right = operands.top();
            operands.pop();
            double left = operands.top();
            operands.pop();
            if (token == "+") operands.push(left + right);
            else if (token == "-") operands.push(left - right);
            else if (token == "*") operands.push(left * right);
            else {
                if (right == 0) throw invalid_argument("Division by zero.");
                operands.push(left / right);
            }
        } else {
            auto value = values.find(token);
            if (value != values.end()) operands.push(value->second);
            else {
                size_t used = 0;
                double number = stod(token, &used);
                if (used != token.size()) throw invalid_argument("Unknown variable: " + token);
                operands.push(number);
            }
        }
    }
    if (operands.size() != 1) throw invalid_argument("Invalid expression.");
    return operands.top();
}

int main() {
    const string expression = "(Days * Rate) + Fixed - Waiver";
    try {
        vector<string> postfix = toPostfix(tokenize(expression));
        cout << "=== Infix to Postfix: Late Fine ===\n"
             << "Infix: " << expression << "\nPostfix: ";
        for (size_t i = 0; i < postfix.size(); ++i)
            cout << (i == 0 ? "" : " ") << postfix[i];
        cout << '\n';

        map<string, double> values;
        cout << "Enter Days, Rate, Fixed fine, and Waiver: ";
        if (!(cin >> values["Days"] >> values["Rate"] >>
              values["Fixed"] >> values["Waiver"])) {
            cout << "Invalid numeric input.\n";
            return 1;
        }
        cout << "Late fine: " << evaluatePostfix(postfix, values) << '\n';
    } catch (const exception& error) {
        cerr << "Error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
