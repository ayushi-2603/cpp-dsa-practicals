#include <deque>
#include <iostream>

using namespace std;

int main() {
    deque<int> tokens;
    int choice;
    do {
        cout << "\n1. Enqueue student token\n2. Dequeue and process student\n"
                "3. Display front and rear tokens\n4. Display complete queue\n0. Exit\nChoice: ";
        cin >> choice;
        if (!cin) {
            break;
        }
        if (choice == 1) {
            int token;
            cout << "Enter student token number: ";
            cin >> token;
            tokens.push_back(token);
            cout << "Token enqueued.\n";
        } else if (choice == 2) {
            if (tokens.empty()) {
                cout << "Queue is empty; no student can be processed.\n";
            } else {
                cout << "Processed student token: " << tokens.front() << '\n';
                tokens.pop_front();
            }
        } else if (choice == 3) {
            if (tokens.empty()) {
                cout << "Queue is empty.\n";
            } else {
                cout << "Front token: " << tokens.front()
                     << "\nRear token: " << tokens.back() << '\n';
            }
        } else if (choice == 4) {
            if (tokens.empty()) {
                cout << "Queue is empty.\n";
            } else {
                cout << "Queue from front to rear: ";
                for (int token : tokens) cout << token << ' ';
                cout << '\n';
            }
        } else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    return 0;
}
