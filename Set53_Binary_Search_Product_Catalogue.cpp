#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

struct Product {
    int id;
    string name;
    double price;
};

int binarySearch(const vector<Product>& products, int key, int& comparisons) {
    int low = 0;
    int high = static_cast<int>(products.size()) - 1;
    comparisons = 0;
    while (low <= high) {
        int middle = low + (high - low) / 2;
        ++comparisons;
        if (products[middle].id == key) return middle;
        if (key < products[middle].id) high = middle - 1;
        else low = middle + 1;
    }
    return -1;
}

int main() {
    vector<Product> products;
    int count;
    cout << "=== Binary Search: Product Catalogue ===\n";
    cout << "Enter number of products: ";
    if (!(cin >> count) || count < 0) {
        cout << "Invalid number of products.\n";
        return 1;
    }
    products.resize(static_cast<size_t>(count));

    for (int i = 0; i < count; ++i) {
        cout << "\nProduct " << i + 1 << '\n';
        cout << "Product ID: ";
        cin >> products[i].id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Name: ";
        getline(cin, products[i].name);
        cout << "Price: ";
        cin >> products[i].price;
    }

    sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
        return a.id < b.id;
    });

    int key;
    cout << "\nEnter Product ID to search: ";
    cin >> key;
    int comparisons = 0;
    int index = binarySearch(products, key, comparisons);
    if (index == -1) {
        cout << "Product not found.\n";
    } else {
        const Product& product = products[index];
        cout << "Product found:\nProduct ID: " << product.id
             << "\nName: " << product.name
             << "\nPrice: " << product.price << '\n';
    }
    cout << "Comparisons made: " << comparisons << '\n';
    return 0;
}
