#include <iostream>
#include <vector>

using namespace std;

struct MarksNode {
    int marks;
    MarksNode* next;
};

int main() {
    int capacity;
    cout << "Enter maximum number of students: ";
    cin >> capacity;
    if (!cin || capacity < 1) {
        cout << "Invalid capacity.\n";
        return 1;
    }

    vector<int> marks;
    marks.reserve(static_cast<size_t>(capacity));
    MarksNode* head = nullptr;
    MarksNode* tail = nullptr;
    int choice;
    do {
        cout << "\n1. Insert marks\n2. Display array and linked-list representation\n"
                "3. Count marks greater than 80\n0. Exit\nChoice: ";
        cin >> choice;
        if (!cin) {
            break;
        }
        if (choice == 1) {
            if (static_cast<int>(marks.size()) == capacity) {
                cout << "Maximum student capacity reached.\n";
                continue;
            }
            int score;
            cout << "Enter marks (0-100): ";
            cin >> score;
            if (score < 0 || score > 100) {
                cout << "Marks must be between 0 and 100.\n";
                continue;
            }
            marks.push_back(score);
            MarksNode* node = new MarksNode{score, nullptr};
            if (head == nullptr) {
                head = tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
            cout << "Marks inserted in both structures.\n";
        } else if (choice == 2) {
            cout << "Array representation:\n";
            for (size_t i = 0; i < marks.size(); ++i) {
                cout << "Index " << i << ", address " << static_cast<const void*>(&marks[i])
                     << ", marks " << marks[i] << '\n';
            }
            cout << "Linked-list nodes:\n";
            int index = 0;
            for (MarksNode* node = head; node != nullptr; node = node->next, ++index) {
                cout << "Node " << index << ", address " << static_cast<const void*>(node)
                     << ", marks " << node->marks << ", next "
                     << static_cast<const void*>(node->next) << '\n';
            }
        } else if (choice == 3) {
            int count = 0;
            for (int score : marks) {
                if (score > 80) {
                    ++count;
                }
            }
            cout << "Students scoring more than 80: " << count << '\n';
        } else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    while (head != nullptr) {
        MarksNode* next = head->next;
        delete head;
        head = next;
    }
    return 0;
}
