#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void selectionSort(vector<double>& scores) {
    for (size_t i = 0; i < scores.size(); ++i) {
        size_t minimum = i;
        for (size_t j = i + 1; j < scores.size(); ++j) {
            if (scores[j] < scores[minimum]) {
                minimum = j;
            }
        }
        swap(scores[i], scores[minimum]);
    }
}

void bubbleSort(vector<double>& scores) {
    for (size_t end = scores.size(); end > 1; --end) {
        bool swapped = false;
        for (size_t i = 1; i < end; ++i) {
            if (scores[i - 1] > scores[i]) {
                swap(scores[i - 1], scores[i]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void displayTopFive(const vector<double>& ascendingScores) {
    cout << "Top scores: ";
    size_t shown = min<size_t>(5, ascendingScores.size());
    for (size_t i = 0; i < shown; ++i) {
        cout << ascendingScores[ascendingScores.size() - 1 - i] << ' ';
    }
    cout << '\n';
}

int main() {
    int count;
    cout << "Enter number of percentages: ";
    cin >> count;
    if (!cin || count < 0) {
        cout << "Invalid number of percentages.\n";
        return 1;
    }
    vector<double> selectionScores(static_cast<size_t>(count));
    cout << "Enter percentages:\n";
    for (double& score : selectionScores) {
        cin >> score;
        if (!cin || score < 0.0 || score > 100.0) {
            cout << "Percentages must be between 0 and 100.\n";
            return 1;
        }
    }
    vector<double> bubbleScores = selectionScores;
    selectionSort(selectionScores);
    cout << "Selection sort ascending: ";
    for (double score : selectionScores) {
        cout << score << ' ';
    }
    cout << '\n';
    displayTopFive(selectionScores);
    bubbleSort(bubbleScores);
    cout << "Bubble sort ascending: ";
    for (double score : bubbleScores) {
        cout << score << ' ';
    }
    cout << '\n';
    displayTopFive(bubbleScores);
    return 0;
}
