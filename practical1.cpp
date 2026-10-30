#include <iostream>
#include <limits>
#include <string>

using namespace std;

struct Student {
    int rollNumber;
    string name;
    double cgpa;
};

const int CAPACITY = 1000;

void displayStudent(const Student& student) {
    cout << "Roll No: " << student.rollNumber << ", Name: " << student.name
         << ", CGPA: " << student.cgpa << '\n';
}

int findStudent(const Student students[], int count, int rollNumber) {
    for (int i = 0; i < count; ++i) {
        if (students[i].rollNumber == rollNumber) {
            return i;
        }
    }
    return -1;
}

int main() {
    Student students[CAPACITY];
    int count;
    cout << "Enter number of students: ";
    cin >> count;
    if (!cin || count < 0 || count > CAPACITY) {
        cout << "Invalid number of students.\n";
        return 1;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 0; i < count; ++i) {
        cout << "Enter roll number, name, and CGPA for student " << i + 1 << ":\n";
        cin >> students[i].rollNumber;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, students[i].name);
        cin >> students[i].cgpa;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int choice;
    do {
        cout << "\n1. Insert student\n2. Delete student by roll number\n"
                "3. Search student by roll number\n4. Display all students\n0. Exit\nChoice: ";
        cin >> choice;
        if (!cin) {
            return 1;
        }

        if (choice == 1) {
            if (count == CAPACITY) {
                cout << "Student array is full.\n";
                continue;
            }
            int position;
            Student student;
            cout << "Enter position (1-" << count + 1 << "): ";
            cin >> position;
            if (position < 1 || position > count + 1) {
                cout << "Invalid position.\n";
                continue;
            }
            cout << "Enter roll number, name, and CGPA:\n";
            cin >> student.rollNumber;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, student.name);
            cin >> student.cgpa;
            if (findStudent(students, count, student.rollNumber) != -1) {
                cout << "A student with that roll number already exists.\n";
                continue;
            }
            for (int i = count; i >= position; --i) {
                students[i] = students[i - 1];
            }
            students[position - 1] = student;
            ++count;
            cout << "Student inserted.\n";
        } else if (choice == 2 || choice == 3) {
            int rollNumber;
            cout << "Enter roll number: ";
            cin >> rollNumber;
            int index = findStudent(students, count, rollNumber);
            if (index == -1) {
                cout << "Student not found.\n";
            } else if (choice == 2) {
                for (int i = index; i < count - 1; ++i) {
                    students[i] = students[i + 1];
                }
                --count;
                cout << "Student deleted.\n";
            } else {
                displayStudent(students[index]);
            }
        } else if (choice == 4) {
            if (count == 0) {
                cout << "No students to display.\n";
            }
            for (int i = 0; i < count; ++i) {
                displayStudent(students[i]);
            }
        } else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    return 0;
}
