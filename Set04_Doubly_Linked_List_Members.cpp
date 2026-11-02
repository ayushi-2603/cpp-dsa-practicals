#include <iostream>
#include <string>
using namespace std;

struct Member {
    int id;
    string name;
    Member* previous;
    Member* next;
    Member(int memberId, const string& memberName)
        : id(memberId), name(memberName), previous(nullptr), next(nullptr) {}
};

void insertSorted(Member*& head, int id, const string& name) {
    Member* current = head;
    while (current != nullptr && current->id < id) current = current->next;
    if (current != nullptr && current->id == id) {
        cout << "A member with that ID already exists.\n";
        return;
    }

    Member* node = new Member(id, name);
    if (current == head) {
        node->next = head;
        if (head != nullptr) head->previous = node;
        head = node;
    } else if (current == nullptr) {
        Member* tail = head;
        while (tail->next != nullptr) tail = tail->next;
        tail->next = node;
        node->previous = tail;
    } else {
        node->next = current;
        node->previous = current->previous;
        current->previous->next = node;
        current->previous = node;
    }
    cout << "Member inserted in ID order.\n";
}

void deleteMember(Member*& head, int id) {
    Member* node = head;
    while (node != nullptr && node->id != id) node = node->next;
    if (node == nullptr) {
        cout << "Member not found.\n";
        return;
    }
    if (node->previous != nullptr) node->previous->next = node->next;
    else head = node->next;
    if (node->next != nullptr) node->next->previous = node->previous;
    delete node;
    cout << "Member deleted.\n";
}

void forward(const Member* head) {
    if (head == nullptr) cout << "Member list is empty.\n";
    for (; head != nullptr; head = head->next)
        cout << "ID: " << head->id << ", Name: " << head->name << '\n';
}

void backward(const Member* head) {
    if (head == nullptr) {
        cout << "Member list is empty.\n";
        return;
    }
    while (head->next != nullptr) head = head->next;
    for (; head != nullptr; head = head->previous)
        cout << "ID: " << head->id << ", Name: " << head->name << '\n';
}

void deleteList(Member*& head) {
    while (head != nullptr) {
        Member* next = head->next;
        delete head;
        head = next;
    }
}

int main() {
    Member* head = nullptr;
    int choice;
    do {
        cout << "\n=== Doubly Linked List: Library Members ===\n"
             << "1. Insert member\n2. Delete member by ID\n"
             << "3. Traverse forward\n4. Traverse backward\n0. Exit\nChoice: ";
        if (!(cin >> choice)) break;
        if (choice == 1) {
            int id;
            string name;
            cout << "Enter Member ID: ";
            cin >> id;
            cout << "Enter name: ";
            cin >> ws;
            getline(cin, name);
            insertSorted(head, id, name);
        } else if (choice == 2) {
            int id;
            cout << "Enter Member ID to delete: ";
            cin >> id;
            deleteMember(head, id);
        } else if (choice == 3) {
            forward(head);
        } else if (choice == 4) {
            backward(head);
        } else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    deleteList(head);
    return 0;
}
