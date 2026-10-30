#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int partition(vector<double>& values, int low, int high) {
    double pivot = values[high];
    int boundary = low - 1;
    for (int current = low; current < high; ++current) {
        if (values[current] <= pivot) {
            ++boundary;
            swap(values[boundary], values[current]);
        }
    }
    swap(values[boundary + 1], values[high]);
    return boundary + 1;
}

void quickSort(vector<double>& values, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(values, low, high);
        quickSort(values, low, pivotIndex - 1);
        quickSort(values, pivotIndex + 1, high);
    }
}

int main() {
    int count;
    cout << "Enter number of student percentages: ";
    cin >> count;
    if (!cin || count < 0) {
        cout << "Invalid number of percentages.\n";
        return 1;
    }
    vector<double> percentages(static_cast<size_t>(count));
    cout << "Enter percentages:\n";
    for (double& percentage : percentages) {
        cin >> percentage;
        if (!cin || percentage < 0.0 || percentage > 100.0) {
            cout << "Percentages must be between 0 and 100.\n";
            return 1;
        }
    }

    if (!percentages.empty()) {
        int pivotIndex = partition(percentages, 0, static_cast<int>(percentages.size()) - 1);
        cout << "After partition: ";
        for (double percentage : percentages) {
            cout << percentage << ' ';
        }
        cout << "\nPivot position: " << pivotIndex + 1 << '\n';
        quickSort(percentages, 0, static_cast<int>(percentages.size()) - 1);
    }
    cout << "Sorted percentages: ";
    for (double percentage : percentages) {
        cout << percentage << ' ';
    }
    cout << '\n';
    return 0;
}
