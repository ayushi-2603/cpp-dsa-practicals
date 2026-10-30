#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string expression;
    cout << "Enter an expression: ";
    getline(cin, expression);
    vector<char> brackets;
    bool balanced = true;

    for (char character : expression) {
        if (character == '(' || character == '[' || character == '{') {
            brackets.push_back(character);
        } else if (character == ')' || character == ']' || character == '}') {
            if (brackets.empty()) {
                balanced = false;
                break;
            }
            char opening = brackets.back();
            brackets.pop_back();
            if ((character == ')' && opening != '(') ||
                (character == ']' && opening != '[') ||
                (character == '}' && opening != '{')) {
                balanced = false;
                break;
            }
        }
    }
    if (!brackets.empty()) {
        balanced = false;
    }
    cout << (balanced ? "Parentheses are balanced.\n" : "Parentheses are not balanced.\n");
    return 0;
}
