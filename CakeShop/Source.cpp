#include <iostream>
#include <string>
#include <limits>

using namespace std;

const int MAX_CAKES = 100;

struct Cake {
    int id;
    string flavor;
    string frosting;
    string topping;
    int weight;
};

void displayCake(const Cake& cake);
void displayCakes(const Cake shop[], int size);
void addCake(Cake shop[], int& size, const Cake& newCake);
void removeCake(Cake shop[], int& size, int targetId);
int binarySearchCake(const Cake shop[], int size, int targetId);
void insertionSortById(Cake arr[], int n);

int main() {
    Cake shop[MAX_CAKES];
    int shopSize = 0;

    addCake(shop, shopSize, { 101, "Chocolate", "Vanilla", "Sprinkles", 500 });
    addCake(shop, shopSize, { 102, "Red Velvet", "Cream Cheese", "Strawberries", 700 });
    addCake(shop, shopSize, { 103, "Lemon", "Lemon Buttercream", "Blueberries", 600 });
    insertionSortById(shop, shopSize);

    int choice;
    do {
        cout << "\nOptions:\n";
        cout << "1. Display available cakes\n";
        cout << "2. Add a cake\n";
        cout << "3. Remove a cake\n";
        cout << "4. Search for a cake by ID\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number between 1 and 5.\n";
            continue;
        }

        switch (choice) {
        case 1:
            displayCakes(shop, shopSize);
            break;
        case 2: {
            Cake newCake;
            cout << "Enter cake ID: ";
            while (!(cin >> newCake.id) || newCake.id <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid ID. Please enter a positive integer: ";
            }
            cin.ignore();
            cout << "Enter cake flavor: ";
            getline(cin, newCake.flavor);
            cout << "Enter cake frosting: ";
            getline(cin, newCake.frosting);
            cout << "Enter cake topping: ";
            getline(cin, newCake.topping);
            cout << "Enter cake weight (grams): ";
            while (!(cin >> newCake.weight) || newCake.weight <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid weight. Please enter a positive integer: ";
            }
            addCake(shop, shopSize, newCake);
            insertionSortById(shop, shopSize);
            break;
        }
        case 3: {
            int targetId;
            cout << "Enter the ID of the cake to remove: ";
            while (!(cin >> targetId) || targetId <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid ID. Please enter a positive integer: ";
            }
            removeCake(shop, shopSize, targetId);
            break;
        }
        case 4: {
            int targetId;
            cout << "Enter the ID of the cake to search: ";
            while (!(cin >> targetId) || targetId <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid ID. Please enter a positive integer: ";
            }
            int index = binarySearchCake(shop, shopSize, targetId);

            if (index != -1) {
                cout << "Cake found:\n";
                displayCake(shop[index]);
            }
            else {
                cout << "Cake not found.\n";
            }
            break;
        }
        case 5:
            cout << "Exiting program.\n";
            break;
        default:
            break;
        }
    } while (choice != 5);

    return 0;
}

void displayCake(const Cake& cake) {
    cout << "ID: " << cake.id << endl;
    cout << "Flavor: " << cake.flavor << endl;
    cout << "Frosting: " << cake.frosting << endl;
    cout << "Topping: " << cake.topping << endl;
    cout << "Weight: " << cake.weight << " grams" << endl;
}

void displayCakes(const Cake shop[], int size) {
    cout << "\nCake Shop:\n";
    for (int i = 0; i < size; i++) {
        cout << "Cake " << i + 1 << ":\n";
        displayCake(shop[i]);
        cout << endl;
    }
}

void addCake(Cake shop[], int& size, const Cake& newCake) {
    if (size >= MAX_CAKES) {
        cout << "Cake shop is full. Cannot add more cakes.\n";
        return;
    }
    shop[size++] = newCake;
    cout << "Cake added successfully to the shop.\n";
}

void removeCake(Cake shop[], int& size, int targetId) {
    int index = binarySearchCake(shop, size, targetId);
    if (index == -1) {
        cout << "Cake with ID " << targetId << " not found.\n";
        return;
    }
    for (int i = index; i < size - 1; i++) {
        shop[i] = shop[i + 1];
    }
    size--;
    cout << "Cake with ID " << targetId << " removed successfully from the shop.\n";
}

int binarySearchCake(const Cake shop[], int size, int targetId) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (shop[mid].id == targetId) {
            return mid;
        }
        else if (shop[mid].id < targetId) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

void insertionSortById(Cake arr[], int n) {
    for (int i = 1; i < n; ++i) {
        Cake key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].id > key.id) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
