#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

struct Flight {
    int number;
    string destination;
    string departureTime;
};

int binarySearch(const vector<Flight>& flights, int key, int& comparisons) {
    int low = 0;
    int high = static_cast<int>(flights.size()) - 1;
    comparisons = 0;
    while (low <= high) {
        int middle = low + (high - low) / 2;
        ++comparisons;
        if (flights[middle].number == key) return middle;
        if (key < flights[middle].number) high = middle - 1;
        else low = middle + 1;
    }
    return -1;
}

int main() {
    vector<Flight> flights;
    int count;
    cout << "=== Binary Search: Flight Lookup ===\n";
    cout << "Enter number of flights: ";
    if (!(cin >> count) || count < 0) {
        cout << "Invalid number of flights.\n";
        return 1;
    }
    flights.resize(static_cast<size_t>(count));

    for (int i = 0; i < count; ++i) {
        cout << "\nFlight " << i + 1 << '\n';
        cout << "Flight number: ";
        cin >> flights[i].number;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Destination: ";
        getline(cin, flights[i].destination);
        cout << "Departure time: ";
        getline(cin, flights[i].departureTime);
    }

    sort(flights.begin(), flights.end(), [](const Flight& a, const Flight& b) {
        return a.number < b.number;
    });

    int key;
    cout << "\nEnter Flight Number to search: ";
    cin >> key;
    int comparisons = 0;
    int index = binarySearch(flights, key, comparisons);
    if (index == -1) {
        cout << "Flight not found.\n";
    } else {
        const Flight& flight = flights[index];
        cout << "Flight found:\nFlight Number: " << flight.number
             << "\nDestination: " << flight.destination
             << "\nDeparture Time: " << flight.departureTime << '\n';
    }
    cout << "Comparisons made: " << comparisons << '\n';
    return 0;
}
