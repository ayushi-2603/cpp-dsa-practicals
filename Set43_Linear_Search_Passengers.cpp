#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

struct Passenger {
    int ticketNumber;
    string name;
    string seatNumber;
};

int main() {
    vector<Passenger> passengers;
    int count;
    cout << "=== Linear Search: Flight Passengers ===\n";
    cout << "Enter number of passengers: ";
    if (!(cin >> count) || count < 0) {
        cout << "Invalid number of passengers.\n";
        return 1;
    }
    passengers.resize(static_cast<size_t>(count));

    for (int i = 0; i < count; ++i) {
        cout << "\nPassenger " << i + 1 << '\n';
        cout << "Ticket number: ";
        cin >> passengers[i].ticketNumber;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Name: ";
        getline(cin, passengers[i].name);
        cout << "Seat number: ";
        getline(cin, passengers[i].seatNumber);
    }

    string searchName;
    cout << "\nEnter passenger name to search: ";
    getline(cin >> ws, searchName);
    int comparisons = 0;
    int foundIndex = -1;
    for (int i = 0; i < count; ++i) {
        ++comparisons;
        if (passengers[i].name == searchName) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        cout << "Passenger not found.\n";
    } else {
        const Passenger& passenger = passengers[foundIndex];
        cout << "Passenger found:\nTicket No: " << passenger.ticketNumber
             << "\nName: " << passenger.name
             << "\nSeat No: " << passenger.seatNumber << '\n';
    }
    cout << "Comparisons made: " << comparisons << '\n';
    return 0;
}
