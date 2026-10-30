#include <iostream>
#include <vector>

using namespace std;

class CircularQueue {
    vector<int> values;
    size_t frontIndex = 0;
    size_t count = 0;

public:
    explicit CircularQueue(size_t capacity) : values(capacity) {}

    bool empty() const {
        return count == 0;
    }

    bool full() const {
        return count == values.size();
    }

    bool enqueue(int studentId) {
        if (full()) return false;
        size_t rearIndex = (frontIndex + count) % values.size();
        values[rearIndex] = studentId;
        ++count;
        return true;
    }

    bool dequeue(int& studentId) {
        if (empty()) return false;
        studentId = values[frontIndex];
        frontIndex = (frontIndex + 1) % values.size();
        --count;
        return true;
    }

    void display() const {
        if (empty()) {
            cout << "Circular queue is empty.\n";
            return;
        }
        cout << "Circular queue from front to rear: ";
        for (size_t i = 0; i < count; ++i) {
            cout << values[(frontIndex + i) % values.size()] << ' ';
        }
        cout << '\n';
    }
};

int main() {
    size_t capacity;
    cout << "Enter circular queue capacity: ";
    cin >> capacity;
    if (!cin || capacity == 0) {
        cout << "Capacity must be greater than zero.\n";
        return 1;
    }
    CircularQueue queue(capacity);
    int choice;
    do {
        cout << "\n1. Insert student ID\n2. Issue bus pass and remove student\n"
                "3. Check queue full/empty\n4. Display circular queue\n0. Exit\nChoice: ";
        cin >> choice;
        if (!cin) {
            break;
        }
        if (choice == 1) {
            int studentId;
            cout << "Enter student ID: ";
            cin >> studentId;
            if (queue.enqueue(studentId)) cout << "Student added to circular queue.\n";
            else cout << "Queue is full; student cannot be added.\n";
        } else if (choice == 2) {
            int studentId;
            if (queue.dequeue(studentId)) cout << "Bus pass issued to student " << studentId << ".\n";
            else cout << "Queue is empty; no pass can be issued.\n";
        } else if (choice == 3) {
            cout << "Queue is " << (queue.full() ? "full" : "not full")
                 << " and " << (queue.empty() ? "empty" : "not empty") << ".\n";
        } else if (choice == 4) {
            queue.display();
        } else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    return 0;
}
