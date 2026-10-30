#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    int rollNumber;
    string name;
    double cgpa;
};

int main() {
    vector<Student> queue;
    int processed = 0;
    int choice;
    do {
        cout << "\n1. Insert student with CGPA\n2. Process highest-CGPA student\n"
                "3. Display priority queue\n4. Count students processed\n0. Exit\nChoice: ";
        cin >> choice;
        if (!cin) {
            break;
        }
        if (choice == 1) {
            Student student;
            cout << "Enter roll number, name (one word), and CGPA: ";
            cin >> student.rollNumber >> student.name >> student.cgpa;
            if (!cin || student.cgpa < 0.0 || student.cgpa > 10.0) {
                cout << "Invalid student data or CGPA.\n";
                return 1;
            }
            queue.push_back(student);
            cout << "Student added to priority queue.\n";
            cout << "Queue after operation:\n";
            for (const Student& item : queue) {
                cout << item.rollNumber << " | " << item.name << " | " << item.cgpa << '\n';
            }
        } else if (choice == 2) {
            if (queue.empty()) {
                cout << "Priority queue is empty.\n";
            } else {
                size_t highest = 0;
                for (size_t i = 1; i < queue.size(); ++i) {
                    if (queue[i].cgpa > queue[highest].cgpa) highest = i;
                }
                cout << "Processed student: " << queue[highest].rollNumber << " | "
                     << queue[highest].name << " | CGPA " << queue[highest].cgpa << '\n';
                queue.erase(queue.begin() + static_cast<vector<Student>::difference_type>(highest));
                ++processed;
            }
            cout << "Queue after operation:\n";
            if (queue.empty()) cout << "Priority queue is empty.\n";
            for (const Student& item : queue) {
                cout << item.rollNumber << " | " << item.name << " | " << item.cgpa << '\n';
            }
        } else if (choice == 3) {
            if (queue.empty()) cout << "Priority queue is empty.\n";
            for (const Student& item : queue) {
                cout << item.rollNumber << " | " << item.name << " | " << item.cgpa << '\n';
            }
        } else if (choice == 4) {
            cout << "Students processed: " << processed << '\n';
        } else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    return 0;
}
