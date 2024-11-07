#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Product structure to store product details
struct Product {
    int id;
    string name;
    double price;
    int stock;

    Product(int id, string name, double price, int stock)
        : id(id), name(name), price(price), stock(stock) {}
};

// OrderItem structure to store items in an order
struct OrderItem {
    Product product;
    int quantity;

    OrderItem(Product product, int quantity)
        : product(product), quantity(quantity) {}
};

// Order class to manage an individual order
class Order {
private:
    vector<OrderItem> items;

public:
    void addItem(Product product, int quantity) {
        if (product.stock >= quantity) {
            items.push_back(OrderItem(product, quantity));
            cout << quantity << " " << product.name << "(s) added to your order." << endl;
        } else {
            cout << "Insufficient stock for " << product.name << endl;
        }
    }

    void displayOrderSummary() {
        double total = 0;
        cout << "\n--- Order Summary ---" << endl;
        for (const auto& item : items) {
            double cost = item.product.price * item.quantity;
            total += cost;
            cout << item.product.name << " x " << item.quantity
                 << " = $" << fixed << setprecision(2) << cost << endl;
        }
        cout << "Total: $" << fixed << setprecision(2) << total << endl;
    }
};

// Inventory class to manage available products
class Inventory {
private:
    vector<Product> products;

public:
    void addProduct(int id, string name, double price, int stock) {
        products.push_back(Product(id, name, price, stock));
    }

    Product* findProduct(int id) {
        for (auto& product : products) {
            if (product.id == id) {
                return &product;
            }
        }
        return nullptr;
    }

    void displayProducts() {
        cout << "\n--- Available Products ---" << endl;
        for (const auto& product : products) {
            cout << "ID: " << product.id << " | " << product.name
                 << " | Price: $" << product.price
                 << " | Stock: " << product.stock << endl;
        }
    }
};

int main() {
    Inventory inventory;
    inventory.addProduct(1, "Lipstick", 12.99, 50);
    inventory.addProduct(2, "Foundation", 25.50, 30);
    inventory.addProduct(3, "Eyeliner", 8.75, 40);
    inventory.addProduct(4, "Mascara", 15.20, 25);

    Order order;
    int choice, productId, quantity;

    do {
        inventory.displayProducts();
        cout << "\nEnter Product ID to add to order (0 to checkout): ";
        cin >> productId;

        if (productId == 0) break;

        Product* product = inventory.findProduct(productId);
        if (product != nullptr) {
            cout << "Enter quantity: ";
            cin >> quantity;
            order.addItem(*product, quantity);
        } else {
            cout << "Invalid Product ID!" << endl;
        }

    } while (true);

    order.displayOrderSummary();
    cout << "Thank you for your order!" << endl;

    return 0;
}