#include <iostream>
#include <limits>
#include <string>
using namespace std;

struct Book {
    int id;
    string title;
    double price;
};

const int CAPACITY = 100;

void displayBook(const Book& book) {
    cout << "Book ID: " << book.id << "\nTitle: " << book.title
         << "\nPrice: " << book.price << "\n";
}

void displayBooks(const Book books[], int count) {
    if (count == 0) {
        cout << "No books stored.\n";
        return;
    }
    for (int i = 0; i < count; ++i) {
        cout << "\nPosition " << i + 1 << "\n";
        displayBook(books[i]);
    }
}

int main() {
    Book books[CAPACITY];
    int count = 0;
    int choice;

    do {
        cout << "\n=== Array Book Records ===\n"
             << "1. Insert book at position\n2. Delete book by ID\n"
             << "3. Search book by ID\n4. Display all books\n0. Exit\nChoice: ";
        if (!(cin >> choice)) return 0;

        if (choice == 1) {
            if (count == CAPACITY) {
                cout << "Book array is full.\n";
                continue;
            }
            int position;
            cout << "Enter position (1-" << count + 1 << "): ";
            cin >> position;
            if (position < 1 || position > count + 1) {
                cout << "Invalid position.\n";
                continue;
            }

            Book book;
            cout << "Enter Book ID: ";
            cin >> book.id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter title: ";
            getline(cin, book.title);
            cout << "Enter price: ";
            cin >> book.price;

            for (int i = count; i >= position; --i)
                books[i] = books[i - 1];
            books[position - 1] = book;
            ++count;
            cout << "Book inserted.\n";
        } else if (choice == 2) {
            int id;
            cout << "Enter Book ID to delete: ";
            cin >> id;
            int index = 0;
            while (index < count && books[index].id != id) ++index;
            if (index == count) {
                cout << "Book not found.\n";
            } else {
                for (int i = index; i < count - 1; ++i)
                    books[i] = books[i + 1];
                --count;
                cout << "Book deleted.\n";
            }
        } else if (choice == 3) {
            int id;
            cout << "Enter Book ID to search: ";
            cin >> id;
            int index = 0;
            while (index < count && books[index].id != id) ++index;
            if (index == count) cout << "Book not found.\n";
            else displayBook(books[index]);
        } else if (choice == 4) {
            displayBooks(books, count);
        } else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
