#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> history;
    int choice;
    do {
        cout << "\n1. Visit a new page\n2. Go back\n3. Display current page\n"
                "4. Display browsing history stack\n0. Exit\nChoice: ";
        cin >> choice;
        if (!cin) {
            break;
        }
        if (choice == 1) {
            string url;
            cout << "Enter URL: ";
            cin >> url;
            history.push_back(url);
            cout << "Page visited: " << url << '\n';
        } else if (choice == 2) {
            if (history.size() <= 1) {
                cout << "No previous page is available.\n";
            } else {
                history.pop_back();
                cout << "Returned to: " << history.back() << '\n';
            }
        } else if (choice == 3) {
            if (history.empty()) {
                cout << "No page is currently open.\n";
            } else {
                cout << "Current page: " << history.back() << '\n';
            }
        } else if (choice == 4) {
            if (history.empty()) {
                cout << "Browsing history is empty.\n";
            } else {
                cout << "Browsing history stack (bottom to top):\n";
                for (const string& url : history) {
                    cout << url << '\n';
                }
            }
        } else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    return 0;
}
