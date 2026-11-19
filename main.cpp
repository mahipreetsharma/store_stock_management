#include <iostream>
#include <string>
#include <vector>


using namespace std;

struct Product {
  int id;
  string name;
  double price;
  int stock;
};

struct CartItem {
  string name;
  double price;
  int quantity;
};

int findProductIndex(const vector<Product> &inventory, int id) {
  for (int i = 0; i < inventory.size(); i++) {
    if (inventory[i].id == id) {
      return i;
    }
  }
  return -1; // Not found
}

void viewInventory(const vector<Product> &inventory) {
  cout << "\n================ STORE INVENTORY ================\n";
  cout << "ID\tName\t\t\tPrice (INR)\tStock\n";
  cout << "-------------------------------------------------\n";
  for (int i = 0; i < inventory.size(); i++) {
    cout << inventory[i].id << "\t" << inventory[i].name << "\t\t"
         << inventory[i].price << "\t\t";

    if (inventory[i].stock == 0) {
      cout << "OUT OF STOCK\n";
    } else {
      cout << inventory[i].stock << "\n";
    }
  }
  cout << "=================================================\n";
}

void addProduct(vector<Product> &inventory) {
  Product p;
  cout << "\nEnter new Product ID: ";
  cin >> p.id;

  if (findProductIndex(inventory, p.id) != -1) {
    cout << "Error: Product ID already exists!\n";
    return;
  }

  cout << "Enter Product Name (use _ or short name for neat alignment): ";
  getline(cin >> ws, p.name);
  cout << "Enter Price (INR): ";
  cin >> p.price;
  cout << "Enter Initial Stock: ";
  cin >> p.stock;

  inventory.push_back(p);
  cout << "Product added successfully!\n";
}

void restockProduct(vector<Product> &inventory) {
  int id, qty;
  cout << "\nEnter Product ID to restock: ";
  cin >> id;

  int idx = findProductIndex(inventory, id);
  if (idx == -1) {
    cout << "Product not found!\n";
    return;
  }

  cout << "Current stock of " << inventory[idx].name << ": "
       << inventory[idx].stock << "\n";
  cout << "Enter quantity to add: ";
  cin >> qty;

  if (qty > 0) {
    inventory[idx].stock += qty;
    cout << "Updated stock: " << inventory[idx].stock << "\n";
  } else {
    cout << "Invalid quantity.\n";
  }
}

void generateBill(vector<Product> &inventory) {
  vector<CartItem> cart;
  int id, qty;
  char choice;

  while (true) {
    viewInventory(inventory);
    cout << "\nEnter Product ID to add to bill (or 0 to finish): ";
    cin >> id;

    if (id == 0)
      break;

    int idx = findProductIndex(inventory, id);
    if (idx == -1) {
      cout << "Invalid Product ID! Try again.\n";
      continue;
    }

    if (inventory[idx].stock == 0) {
      cout << "Sorry, " << inventory[idx].name << " is out of stock!\n";
      continue;
    }

    cout << "Enter quantity (Available: " << inventory[idx].stock << "): ";
    cin >> qty;

    if (qty <= 0 || qty > inventory[idx].stock) {
      cout << "Invalid quantity! Please enter between 1 and "
           << inventory[idx].stock << ".\n";
      continue;
    }

    inventory[idx].stock -= qty;
    cart.push_back({inventory[idx].name, inventory[idx].price, qty});
    cout << "Added " << qty << " x " << inventory[idx].name << " to bill.\n";
  }

  if (cart.empty()) {
    cout << "\nNo items purchased. Billing cancelled.\n";
    return;
  }

  double subtotal = 0;
  cout << "\n***************** FINAL RECEIPT *****************\n";
  cout << "Item\t\t\tQty\tPrice\tTotal\n";
  cout << "-------------------------------------------------\n";
  for (int i = 0; i < cart.size(); i++) {
    double lineTotal = cart[i].price * cart[i].quantity;
    subtotal += lineTotal;
    cout << cart[i].name << "\t\t" << cart[i].quantity << "\t" << cart[i].price
         << "\t" << lineTotal << "\n";
  }
  double gst = subtotal * 0.05;
  double grandTotal = subtotal + gst;

  cout << "-------------------------------------------------\n";
  cout << "Subtotal:\t\t\t\tINR " << subtotal << "\n";
  cout << "GST (5%):\t\t\t\tINR " << gst << "\n";
  cout << "GRAND TOTAL:\t\t\t\tINR " << grandTotal << "\n";
  cout << "*************************************************\n";
}

int main() {
  vector<Product> inventory = {{101, "Wireless Mouse", 599.0, 10},
                               {102, "Mech Keyboard ", 2499.0, 5},
                               {103, "USB-C Cable   ", 299.0, 15},
                               {104, "Laptop Stand  ", 899.0, 4}};

  int choice;
  while (true) {
    cout << "\n=== STORE STOCK MANAGEMENT ===\n";
    cout << "1. View Inventory\n";
    cout << "2. Add New Product\n";
    cout << "3. Restock Existing Product\n";
    cout << "4. Create Customer Bill\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
      viewInventory(inventory);
      break;
    case 2:
      addProduct(inventory);
      break;
    case 3:
      restockProduct(inventory);
      break;
    case 4:
      generateBill(inventory);
      break;
    case 5:
      cout << "Exiting system. Goodbye!\n";
      return 0;
    default:
      cout << "Invalid choice. Please try again.\n";
    }
  }
}