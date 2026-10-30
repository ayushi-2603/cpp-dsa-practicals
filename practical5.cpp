#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    int rollNumber;
    string name;
    double cgpa;
};

void display(const vector<Student>& students) {
    for (const Student& student : students) {
        cout << student.rollNumber << " | " << student.name << " | "
             << student.cgpa << '\n';
    }
}

int main() {
    int count;
    cout << "Enter number of students: ";
    cin >> count;
    if (!cin || count < 0) {
        cout << "Invalid number of students.\n";
        return 1;
    }
    vector<Student> original(static_cast<size_t>(count));
    for (Student& student : original) {
        cout << "Enter roll number, name (one word), and CGPA: ";
        cin >> student.rollNumber >> student.name >> student.cgpa;
        if (!cin || student.cgpa < 0.0 || student.cgpa > 10.0) {
            cout << "Invalid student data.\n";
            return 1;
        }
    }

    vector<Student> selection = original;
    for (size_t i = 0; i < selection.size(); ++i) {
        size_t highest = i;
        for (size_t j = i + 1; j < selection.size(); ++j) {
            if (selection[j].cgpa > selection[highest].cgpa) {
                highest = j;
            }
        }
        if (highest != i) {
            swap(selection[i], selection[highest]);
        }
    }
    cout << "\nSelection sort (descending CGPA):\n";
    display(selection);

    vector<Student> insertion = original;
    int shifts = 0;
    for (size_t i = 1; i < insertion.size(); ++i) {
        Student current = insertion[i];
        size_t j = i;
        while (j > 0 && insertion[j - 1].cgpa < current.cgpa) {
            insertion[j] = insertion[j - 1];
            --j;
            ++shifts;
        }
        insertion[j] = current;
    }
    cout << "\nInsertion sort (descending CGPA):\n";
    display(insertion);
    cout << "Number of shifts: " << shifts << "\nTop students:\n";
    for (size_t i = 0; i < insertion.size() && i < 5; ++i) {
        cout << insertion[i].rollNumber << " | " << insertion[i].name << " | "
             << insertion[i].cgpa << '\n';
    }
    return 0;
}
