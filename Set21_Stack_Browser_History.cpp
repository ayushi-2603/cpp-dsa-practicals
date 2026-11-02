#include <iostream>
#include <string>
using namespace std;

const int CAPACITY = 100;

void showHistory(const string history[], int size) {
    if (size == 0) {
        cout << "Browsing history is empty.\n";
        return;
    }
    cout << "Browsing history (current page first):\n";
    for (int i = size - 1; i >= 0; --i)
        cout << history[i] << (i == size - 1 ? " <- current\n" : "\n");
}

int main() {
    string history[CAPACITY];
    int size = 0;
    int choice;

    do {
        cout << "\n=== Stack: Library Catalogue Browser ===\n"
             << "1. Visit a page\n2. Go back\n3. Display current page\n"
             << "4. Display browsing history\n0. Exit\nChoice: ";
        if (!(cin >> choice)) break;

        if (choice == 1) {
            if (size == CAPACITY) {
                cout << "History stack is full.\n";
                continue;
            }
            cout << "Enter page URL: ";
            cin >> ws;
            getline(cin, history[size]);
            ++size;
        } else if (choice == 2) {
            if (size <= 1) {
                cout << "No previous page to go back to.\n";
            } else {
                --size;
                cout << "Returned to: " << history[size - 1] << '\n';
            }
        } else if (choice == 3) {
            if (size == 0) cout << "No page is currently open.\n";
            else cout << "Current page: " << history[size - 1] << '\n';
        } else if (choice == 4) {
            showHistory(history, size);
        } else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
