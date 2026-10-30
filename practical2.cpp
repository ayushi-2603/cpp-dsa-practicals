#include <cctype>
#include <iostream>
#include <limits>

using namespace std;

struct AttendanceNode {
    int day;
    char status;
    AttendanceNode* next;
};

AttendanceNode* findDay(AttendanceNode* head, int day) {
    while (head != nullptr && head->day != day) {
        head = head->next;
    }
    return head;
}

int main() {
    AttendanceNode* head = nullptr;
    AttendanceNode* tail = nullptr;
    int choice;

    do {
        cout << "\n1. Add daily attendance\n2. Update attendance for a day\n"
                "3. Count present and absent days\n4. Display attendance list\n0. Exit\nChoice: ";
        cin >> choice;
        if (!cin) {
            break;
        }
        if (choice == 1) {
            int day;
            char status;
            cout << "Enter day number: ";
            cin >> day;
            cout << "Enter status (P/A): ";
            cin >> status;
            status = static_cast<char>(toupper(static_cast<unsigned char>(status)));
            if (day < 1 || (status != 'P' && status != 'A')) {
                cout << "Invalid day or attendance status.\n";
            } else if (findDay(head, day) != nullptr) {
                cout << "Attendance for that day already exists.\n";
            } else {
                AttendanceNode* node = new AttendanceNode{day, status, nullptr};
                if (head == nullptr) {
                    head = tail = node;
                } else {
                    tail->next = node;
                    tail = node;
                }
                cout << "Attendance added.\n";
            }
        } else if (choice == 2) {
            int day;
            char status;
            cout << "Enter day number to update: ";
            cin >> day;
            cout << "Enter new status (P/A): ";
            cin >> status;
            status = static_cast<char>(toupper(static_cast<unsigned char>(status)));
            AttendanceNode* node = findDay(head, day);
            if (node == nullptr) {
                cout << "Day not found.\n";
            } else if (status != 'P' && status != 'A') {
                cout << "Invalid attendance status.\n";
            } else {
                node->status = status;
                cout << "Attendance updated.\n";
            }
        } else if (choice == 3) {
            int present = 0;
            int absent = 0;
            for (AttendanceNode* node = head; node != nullptr; node = node->next) {
                node->status == 'P' ? ++present : ++absent;
            }
            cout << "Present days: " << present << "\nAbsent days: " << absent << '\n';
        } else if (choice == 4) {
            if (head == nullptr) {
                cout << "Attendance list is empty.\n";
            }
            for (AttendanceNode* node = head; node != nullptr; node = node->next) {
                cout << "Day " << node->day << ": " << node->status << '\n';
            }
        } else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    while (head != nullptr) {
        AttendanceNode* next = head->next;
        delete head;
        head = next;
    }
    return 0;
}
