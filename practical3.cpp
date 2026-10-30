#include <iostream>
#include <limits>
#include <string>

using namespace std;

struct StudentNode {
    int rollNumber;
    string name;
    StudentNode* previous;
    StudentNode* next;
};

void insertStudent(StudentNode*& head, int rollNumber, const string& name) {
    StudentNode* current = head;
    while (current != nullptr && current->rollNumber < rollNumber) {
        current = current->next;
    }
    if (current != nullptr && current->rollNumber == rollNumber) {
        cout << "A student with that roll number already exists.\n";
        return;
    }

    StudentNode* node = new StudentNode{rollNumber, name, nullptr, current};
    if (current == nullptr) {
        if (head == nullptr) {
            head = node;
        } else {
            StudentNode* tail = head;
            while (tail->next != nullptr) {
                tail = tail->next;
            }
            tail->next = node;
            node->previous = tail;
        }
    } else {
        node->previous = current->previous;
        if (current->previous != nullptr) {
            current->previous->next = node;
        } else {
            head = node;
        }
        current->previous = node;
    }
    cout << "Student inserted in sorted order.\n";
}

int main() {
    StudentNode* head = nullptr;
    int choice;
    do {
        cout << "\n1. Insert student\n2. Delete student by roll number\n"
                "3. Display students forward\n4. Display students backward\n0. Exit\nChoice: ";
        cin >> choice;
        if (!cin) {
            break;
        }
        if (choice == 1) {
            int rollNumber;
            string name;
            cout << "Enter roll number: ";
            cin >> rollNumber;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter name: ";
            getline(cin, name);
            insertStudent(head, rollNumber, name);
        } else if (choice == 2) {
            int rollNumber;
            cout << "Enter roll number to delete: ";
            cin >> rollNumber;
            StudentNode* node = head;
            while (node != nullptr && node->rollNumber != rollNumber) {
                node = node->next;
            }
            if (node == nullptr) {
                cout << "Student not found.\n";
            } else {
                if (node->previous != nullptr) {
                    node->previous->next = node->next;
                } else {
                    head = node->next;
                }
                if (node->next != nullptr) {
                    node->next->previous = node->previous;
                }
                delete node;
                cout << "Student deleted.\n";
            }
        } else if (choice == 3) {
            if (head == nullptr) {
                cout << "Student list is empty.\n";
            }
            for (StudentNode* node = head; node != nullptr; node = node->next) {
                cout << node->rollNumber << " - " << node->name << '\n';
            }
        } else if (choice == 4) {
            if (head == nullptr) {
                cout << "Student list is empty.\n";
            } else {
                StudentNode* tail = head;
                while (tail->next != nullptr) {
                    tail = tail->next;
                }
                for (StudentNode* node = tail; node != nullptr; node = node->previous) {
                    cout << node->rollNumber << " - " << node->name << '\n';
                }
            }
        } else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    while (head != nullptr) {
        StudentNode* next = head->next;
        delete head;
        head = next;
    }
    return 0;
}
