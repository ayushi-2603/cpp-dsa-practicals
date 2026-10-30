#include <cctype>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

vector<string> tokenize(const string& expression) {
    vector<string> tokens;
    for (size_t i = 0; i < expression.size();) {
        if (isspace(static_cast<unsigned char>(expression[i]))) {
            ++i;
        } else if (isdigit(static_cast<unsigned char>(expression[i])) || expression[i] == '.') {
            size_t start = i;
            bool hasDigit = false;
            while (i < expression.size() &&
                   (isdigit(static_cast<unsigned char>(expression[i])) || expression[i] == '.')) {
                hasDigit = hasDigit || isdigit(static_cast<unsigned char>(expression[i]));
                ++i;
            }
            if (!hasDigit) {
                throw runtime_error("Invalid number.");
            }
            string number = expression.substr(start, i - start);
            size_t parsedLength = 0;
            stod(number, &parsedLength);
            if (parsedLength != number.size()) {
                throw runtime_error("Invalid number.");
            }
            tokens.push_back(number);
        } else if (string("+-*/^()").find(expression[i]) != string::npos) {
            tokens.emplace_back(1, expression[i]);
            ++i;
        } else {
            throw runtime_error("Expression contains an unsupported character.");
        }
    }
    return tokens;
}

int precedence(const string& operation) {
    if (operation == "^") return 3;
    if (operation == "*" || operation == "/") return 2;
    if (operation == "+" || operation == "-") return 1;
    return 0;
}

vector<string> toPostfix(const vector<string>& tokens) {
    vector<string> output;
    vector<string> operators;
    bool expectsOperand = true;
    for (const string& token : tokens) {
        if (isdigit(static_cast<unsigned char>(token[0])) || token[0] == '.') {
            if (!expectsOperand) throw runtime_error("Missing operator in expression.");
            output.push_back(token);
            expectsOperand = false;
        } else if (token == "(") {
            if (!expectsOperand) throw runtime_error("Missing operator before parenthesis.");
            operators.push_back(token);
        } else if (token == ")") {
            if (expectsOperand) throw runtime_error("Missing operand before closing parenthesis.");
            while (!operators.empty() && operators.back() != "(") {
                output.push_back(operators.back());
                operators.pop_back();
            }
            if (operators.empty()) throw runtime_error("Mismatched parentheses.");
            operators.pop_back();
            expectsOperand = false;
        } else {
            if (expectsOperand) throw runtime_error("An operator is missing its left operand.");
            while (!operators.empty() && operators.back() != "(" &&
                   (precedence(operators.back()) > precedence(token) ||
                    (precedence(operators.back()) == precedence(token) && token != "^"))) {
                output.push_back(operators.back());
                operators.pop_back();
            }
            operators.push_back(token);
            expectsOperand = true;
        }
    }
    if (tokens.empty() || expectsOperand) throw runtime_error("Expression is incomplete.");
    while (!operators.empty()) {
        if (operators.back() == "(") throw runtime_error("Mismatched parentheses.");
        output.push_back(operators.back());
        operators.pop_back();
    }
    return output;
}

double evaluate(const vector<string>& postfix) {
    vector<double> values;
    for (const string& token : postfix) {
        if (isdigit(static_cast<unsigned char>(token[0])) || token[0] == '.') {
            values.push_back(stod(token));
        } else {
            if (values.size() < 2) throw runtime_error("Invalid postfix expression.");
            double right = values.back();
            values.pop_back();
            double left = values.back();
            values.pop_back();
            if (token == "+") values.push_back(left + right);
            else if (token == "-") values.push_back(left - right);
            else if (token == "*") values.push_back(left * right);
            else if (token == "/") {
                if (right == 0.0) throw runtime_error("Division by zero.");
                values.push_back(left / right);
            } else values.push_back(pow(left, right));
        }
    }
    if (values.size() != 1) throw runtime_error("Invalid postfix expression.");
    return values.back();
}

int main() {
    cout << "Enter an infix arithmetic expression: ";
    string expression;
    getline(cin, expression);
    try {
        vector<string> postfix = toPostfix(tokenize(expression));
        cout << "Postfix expression: ";
        for (const string& token : postfix) cout << token << ' ';
        cout << "\nResult: " << evaluate(postfix) << '\n';
    } catch (const exception& error) {
        cout << "Error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
