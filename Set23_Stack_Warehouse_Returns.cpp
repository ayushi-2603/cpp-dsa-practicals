#include <iostream>
#include <limits>
#include <string>
using namespace std;

const int CAPACITY = 5;

struct Parcel {
    int orderId;
    string productName;
    double price;
};

void showParcel(const Parcel& parcel) {
    cout << "Order ID: " << parcel.orderId
         << "\nProduct: " << parcel.productName
         << "\nPrice: " << parcel.price << '\n';
}

int main() {
    Parcel parcels[CAPACITY];
    int top = -1;
    int choice;

    do {
        cout << "\n=== Stack: Warehouse Returns ===\n"
             << "1. Push returned parcel\n2. Process (pop) top parcel\n"
             << "3. Peek top parcel\n4. Display all parcels\n0. Exit\nChoice: ";
        if (!(cin >> choice)) break;
        if (choice == 1) {
            if (top == CAPACITY - 1) {
                cout << "Stack Overflow\n";
                continue;
            }
            Parcel parcel;
            cout << "Enter Order ID: ";
            cin >> parcel.orderId;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter product name: ";
            getline(cin, parcel.productName);
            cout << "Enter price: ";
            cin >> parcel.price;
            parcels[++top] = parcel;
            cout << "Parcel added to the stack.\n";
        } else if (choice == 2) {
            if (top == -1) {
                cout << "Stack Underflow\n";
            } else {
                cout << "Processed parcel:\n";
                showParcel(parcels[top--]);
            }
        } else if (choice == 3) {
            if (top == -1) cout << "Stack Underflow\n";
            else showParcel(parcels[top]);
        } else if (choice == 4) {
            if (top == -1) cout << "Stack is empty.\n";
            for (int i = top; i >= 0; --i) {
                cout << "\nStack position " << i << ":\n";
                showParcel(parcels[i]);
            }
        } else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
