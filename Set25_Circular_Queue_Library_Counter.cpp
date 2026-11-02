#include <iostream>
using namespace std;

const int CAPACITY = 5;

int main() {
    int queue[CAPACITY];
    int front = 0;
    int size = 0;
    int choice;

    do {
        cout << "\n=== Circular Queue: Library Issue Counter ===\n"
             << "1. Enqueue member token\n2. Dequeue next member\n"
             << "3. Display front and rear\n4. Display complete queue\n0. Exit\nChoice: ";
        if (!(cin >> choice)) break;

        if (choice == 1) {
            if (size == CAPACITY) {
                cout << "Queue is full.\n";
            } else {
                int token;
                cout << "Enter member token number: ";
                cin >> token;
                queue[(front + size) % CAPACITY] = token;
                ++size;
                cout << "Token added to queue.\n";
            }
        } else if (choice == 2) {
            if (size == 0) {
                cout << "Queue is empty.\n";
            } else {
                cout << "Now serving token: " << queue[front] << '\n';
                front = (front + 1) % CAPACITY;
                --size;
            }
        } else if (choice == 3) {
            if (size == 0) cout << "Queue is empty.\n";
            else {
                int rear = (front + size - 1) % CAPACITY;
                cout << "Front token: " << queue[front]
                     << "\nRear token: " << queue[rear] << '\n';
            }
        } else if (choice == 4) {
            if (size == 0) {
                cout << "Queue is empty.\n";
            } else {
                cout << "Queue (front to rear): ";
                for (int i = 0; i < size; ++i)
                    cout << queue[(front + i) % CAPACITY] << ' ';
                cout << '\n';
            }
        } else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
