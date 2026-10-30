#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    int rollNumber;
    string name;
    string division;
};

int main() {
    int count;
    cout << "Enter number of students: ";
    cin >> count;
    if (!cin || count < 0) {
        cout << "Invalid number of students.\n";
        return 1;
    }
    vector<Student> students(static_cast<size_t>(count));
    for (Student& student : students) {
        cout << "Enter roll number, name (one word), and division: ";
        cin >> student.rollNumber >> student.name >> student.division;
    }
    if (!cin) {
        cout << "Invalid student data.\n";
        return 1;
    }

    string name;
    cout << "Enter name for linear search: ";
    cin >> name;
    int linearComparisons = 0;
    bool nameFound = false;
    for (const Student& student : students) {
        ++linearComparisons;
        if (student.name == name) {
            cout << "Found: " << student.rollNumber << " | " << student.name
                 << " | " << student.division << '\n';
            nameFound = true;
            break;
        }
    }
    if (!nameFound) {
        cout << "Student name not found.\n";
    }
    cout << "Linear search comparisons: " << linearComparisons << '\n';

    sort(students.begin(), students.end(), [](const Student& left, const Student& right) {
        return left.rollNumber < right.rollNumber;
    });
    int rollNumber;
    cout << "Enter roll number for binary search: ";
    cin >> rollNumber;
    int low = 0;
    int high = static_cast<int>(students.size()) - 1;
    int binaryComparisons = 0;
    bool rollFound = false;
    while (low <= high) {
        int middle = low + (high - low) / 2;
        ++binaryComparisons;
        if (students[middle].rollNumber == rollNumber) {
            cout << "Found: " << students[middle].rollNumber << " | "
                 << students[middle].name << " | " << students[middle].division << '\n';
            rollFound = true;
            break;
        }
        if (students[middle].rollNumber < rollNumber) {
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }
    if (!rollFound) {
        cout << "Student roll number not found.\n";
    }
    cout << "Binary search comparisons: " << binaryComparisons << '\n';
    return 0;
}
