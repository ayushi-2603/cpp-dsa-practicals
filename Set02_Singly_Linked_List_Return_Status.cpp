#include <cctype>
#include <iostream>
using namespace std;

struct DayStatus {
    char status;
    DayStatus* next;
    explicit DayStatus(char value) : status(value), next(nullptr) {}
};

void insertAtEnd(DayStatus*& head, char status) {
    DayStatus* node = new DayStatus(status);
    if (head == nullptr) {
        head = node;
        return;
    }
    DayStatus* current = head;
    while (current->next != nullptr) current = current->next;
    current->next = node;
}

DayStatus* getDay(DayStatus* head, int day) {
    for (int currentDay = 1; head != nullptr; ++currentDay, head = head->next)
        if (currentDay == day) return head;
    return nullptr;
}

void displayStatuses(const DayStatus* head) {
    if (head == nullptr) {
        cout << "No daily statuses recorded.\n";
        return;
    }
    int day = 1;
    while (head != nullptr) {
        cout << "Day " << day++ << ": " << head->status << '\n';
        head = head->next;
    }
}

void deleteList(DayStatus*& head) {
    while (head != nullptr) {
        DayStatus* next = head->next;
        delete head;
        head = next;
    }
}

int main() {
    DayStatus* head = nullptr;
    int choice;
    do {
        cout << "\n=== Singly Linked List: Return Status ===\n"
             << "1. Add status at end\n2. Update a day's status\n"
             << "3. Count returned books\n4. Display all statuses\n0. Exit\nChoice: ";
        if (!(cin >> choice)) break;

        if (choice == 1) {
            char status;
            cout << "Enter status (R=Returned, N=Not returned): ";
            cin >> status;
            status = static_cast<char>(toupper(static_cast<unsigned char>(status)));
            if (status != 'R' && status != 'N') {
                cout << "Status must be R or N.\n";
            } else {
                insertAtEnd(head, status);
                cout << "Status added.\n";
            }
        } else if (choice == 2) {
            int day;
            char status;
            cout << "Enter day number: ";
            cin >> day;
            cout << "Enter new status (R/N): ";
            cin >> status;
            status = static_cast<char>(toupper(static_cast<unsigned char>(status)));
            DayStatus* node = (day > 0) ? getDay(head, day) : nullptr;
            if (status != 'R' && status != 'N') cout << "Status must be R or N.\n";
            else if (node == nullptr) cout << "Day not found.\n";
            else {
                node->status = status;
                cout << "Status updated.\n";
            }
        } else if (choice == 3) {
            int returned = 0;
            for (DayStatus* node = head; node != nullptr; node = node->next)
                if (node->status == 'R') ++returned;
            cout << "Returned books: " << returned << '\n';
        } else if (choice == 4) {
            displayStatuses(head);
        } else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    deleteList(head);
    return 0;
}
