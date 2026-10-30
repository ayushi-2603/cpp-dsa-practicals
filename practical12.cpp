#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

bool isOperator(const string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "^";
}

vector<string> tokenize(const string& expression) {
    vector<string> tokens;
    for (size_t i = 0; i < expression.size();) {
        unsigned char character = static_cast<unsigned char>(expression[i]);
        if (isspace(character)) {
            ++i;
        } else if (isdigit(character) || expression[i] == '.') {
            size_t start = i;
            bool hasDigit = false;
            while (i < expression.size() &&
                   (isdigit(static_cast<unsigned char>(expression[i])) || expression[i] == '.')) {
                hasDigit = hasDigit || isdigit(static_cast<unsigned char>(expression[i]));
                ++i;
            }
            if (!hasDigit) throw runtime_error("Invalid number.");
            string number = expression.substr(start, i - start);
            size_t parsedLength = 0;
            stod(number, &parsedLength);
            if (parsedLength != number.size()) throw runtime_error("Invalid number.");
            tokens.push_back(number);
        } else if (isalpha(character) || expression[i] == '_') {
            size_t start = i++;
            while (i < expression.size() &&
                   (isalnum(static_cast<unsigned char>(expression[i])) || expression[i] == '_')) {
                ++i;
            }
            tokens.push_back(expression.substr(start, i - start));
        } else if (string("+-*/^()").find(expression[i]) != string::npos) {
            tokens.emplace_back(1, expression[i++]);
        } else {
            throw runtime_error("Formula contains an unsupported character.");
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

void printStack(const vector<string>& values) {
    cout << '[';
    for (size_t i = 0; i < values.size(); ++i) {
        if (i != 0) cout << ", ";
        cout << values[i];
    }
    cout << ']';
}

vector<string> toPostfix(const vector<string>& tokens) {
    vector<string> output;
    vector<string> operators;
    bool expectsOperand = true;
    cout << "\nPostfix conversion steps:\n";
    for (const string& token : tokens) {
        if (!token.empty() &&
            (isdigit(static_cast<unsigned char>(token[0])) || token[0] == '.' ||
             isalpha(static_cast<unsigned char>(token[0])) || token[0] == '_')) {
            if (!expectsOperand) throw runtime_error("Missing operator in formula.");
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
        } else if (isOperator(token)) {
            if (expectsOperand) throw runtime_error("An operator is missing its left operand.");
            while (!operators.empty() && operators.back() != "(" &&
                   (precedence(operators.back()) > precedence(token) ||
                    (precedence(operators.back()) == precedence(token) && token != "^"))) {
                output.push_back(operators.back());
                operators.pop_back();
            }
            operators.push_back(token);
            expectsOperand = true;
        } else {
            throw runtime_error("Invalid formula token.");
        }
        cout << "Token " << token << " | operators: ";
        printStack(operators);
        cout << " | output: ";
        printStack(output);
        cout << '\n';
    }
    if (tokens.empty() || expectsOperand) throw runtime_error("Formula is incomplete.");
    while (!operators.empty()) {
        if (operators.back() == "(") throw runtime_error("Mismatched parentheses.");
        output.push_back(operators.back());
        operators.pop_back();
        cout << "Pop operator | operators: ";
        printStack(operators);
        cout << " | output: ";
        printStack(output);
        cout << '\n';
    }
    return output;
}

double evaluate(const vector<string>& postfix, const map<string, double>& variables) {
    vector<double> values;
    cout << "\nPostfix evaluation steps:\n";
    for (const string& token : postfix) {
        if (isOperator(token)) {
            if (values.size() < 2) throw runtime_error("Invalid postfix formula.");
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
        } else if (isdigit(static_cast<unsigned char>(token[0])) || token[0] == '.') {
            values.push_back(stod(token));
        } else {
            auto variable = variables.find(token);
            if (variable == variables.end()) throw runtime_error("No value supplied for " + token + ".");
            values.push_back(variable->second);
        }
        cout << "Token " << token << " | stack: [";
        for (size_t i = 0; i < values.size(); ++i) {
            if (i != 0) cout << ", ";
            cout << values[i];
        }
        cout << "]\n";
    }
    if (values.size() != 1) throw runtime_error("Invalid postfix formula.");
    return values.back();
}

int main() {
    cout << "Enter fee formula in infix form (use Tuition, Hostel, ExamFee, Scholarship): ";
    string expression;
    getline(cin, expression);
    try {
        vector<string> tokens = tokenize(expression);
        map<string, double> variables;
        const vector<string> requiredVariables = {
            "Tuition", "Hostel", "ExamFee", "Scholarship"
        };
        for (const string& variable : requiredVariables) {
            cout << "Enter value for " << variable << ": ";
            double value;
            cin >> value;
            if (!cin) throw runtime_error("Invalid fee amount.");
            variables[variable] = value;
        }
        for (const string& token : tokens) {
            if (!token.empty() &&
                (isalpha(static_cast<unsigned char>(token[0])) || token[0] == '_') &&
                variables.find(token) == variables.end()) {
                cout << "Enter value for " << token << ": ";
                double value;
                cin >> value;
                if (!cin) throw runtime_error("Invalid fee amount.");
                variables[token] = value;
            }
        }

        vector<string> postfix = toPostfix(tokens);
        cout << "\nPostfix expression: ";
        for (const string& token : postfix) cout << token << ' ';
        cout << '\n';
        double payable = evaluate(postfix, variables);
        cout << fixed << setprecision(2) << "\nFinal payable fee: " << payable << '\n';
    } catch (const exception& error) {
        cout << "Error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
