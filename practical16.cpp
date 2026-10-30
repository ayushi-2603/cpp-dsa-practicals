#include <deque>
#include <iostream>
#include <string>

using namespace std;

struct ServiceRequest {
    int requestId;
    string name;
    string category;
};

void display(const deque<ServiceRequest>& requests) {
    if (requests.empty()) {
        cout << "Service deque is empty.\n";
        return;
    }
    cout << "Service deque from front to rear:\n";
    for (const ServiceRequest& request : requests) {
        cout << request.requestId << " | " << request.name << " | "
             << request.category << '\n';
    }
}

int main() {
    deque<ServiceRequest> requests;
    int nextId = 1;
    int choice;
    do {
        cout << "\n1. Add emergency request at front\n2. Add normal request at rear\n"
                "3. Serve request from front\n4. Display service deque\n0. Exit\nChoice: ";
        cin >> choice;
        if (!cin) {
            break;
        }
        if (choice == 1 || choice == 2) {
            string name;
            cout << "Enter student name (one word): ";
            cin >> name;
            ServiceRequest request{nextId++, name, choice == 1 ? "Emergency" : "Normal"};
            if (choice == 1) {
                requests.push_front(request);
                cout << "Emergency request added at front.\n";
            } else {
                requests.push_back(request);
                cout << "Normal request added at rear.\n";
            }
            display(requests);
        } else if (choice == 3) {
            if (requests.empty()) {
                cout << "No service requests are waiting.\n";
            } else {
                const ServiceRequest request = requests.front();
                requests.pop_front();
                cout << "Served request " << request.requestId << " for "
                     << request.name << " (" << request.category << ").\n";
            }
            display(requests);
        } else if (choice == 4) {
            display(requests);
        } else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    return 0;
}
