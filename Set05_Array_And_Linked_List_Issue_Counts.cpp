#include <iostream>
using namespace std;

const int CAPACITY = 100;

struct Node {
    int count;
    Node* next;
    explicit Node(int value) : count(value), next(nullptr) {}
};

void appendNode(Node*& head, int value) {
    Node* node = new Node(value);
    if (head == nullptr) {
        head = node;
        return;
    }
    Node* current = head;
    while (current->next != nullptr) current = current->next;
    current->next = node;
}

void display(const int values[], int size, const Node* head) {
    cout << "\nArray memory representation (index -> count):\n";
    for (int i = 0; i < size; ++i)
        cout << "[" << i << "] -> " << values[i] << '\n';

    cout << "\nLinked-list nodes (node address -> count):\n";
    int index = 0;
    while (head != nullptr) {
        cout << "Node " << index++ << " at " << static_cast<const void*>(head)
             << " -> " << head->count << '\n';
        head = head->next;
    }
}

void deleteList(Node*& head) {
    while (head != nullptr) {
        Node* next = head->next;
        delete head;
        head = next;
    }
}

int main() {
    int values[CAPACITY];
    int size;
    Node* head = nullptr;

    cout << "=== Array and Linked List: Books Issued per Member ===\n";
    cout << "Enter number of members (0-" << CAPACITY << "): ";
    if (!(cin >> size) || size < 0 || size > CAPACITY) {
        cout << "Invalid number of members.\n";
        return 1;
    }

    for (int i = 0; i < size; ++i) {
        cout << "Books issued by member " << i + 1 << ": ";
        if (!(cin >> values[i]) || values[i] < 0) {
            cout << "Enter a non-negative count.\n";
            deleteList(head);
            return 1;
        }
        appendNode(head, values[i]);
    }

    display(values, size, head);
    int moreThanFive = 0;
    for (int i = 0; i < size; ++i)
        if (values[i] > 5) ++moreThanFive;
    cout << "\nMembers who issued more than 5 books: " << moreThanFive << '\n';

    deleteList(head);
    return 0;
}
