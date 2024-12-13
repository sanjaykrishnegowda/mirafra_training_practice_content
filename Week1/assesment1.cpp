#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// Base Class
class Product {
protected:
    int id;
    string name;
    double price;

public:
    Product(int id, string name, double price) : id(id), name(name), price(price) {}
    virtual void displayInfo() const = 0;
    virtual ~Product() {}
    int getId() const { return id; }
    double getPrice() const { return price; }
    string getName() const { return name; }
};

// Electronics Class
class Electronics : public Product {
    string brand;

public:
    Electronics(int id, string name, double price, string brand) 
        : Product(id, name, price), brand(brand) {}
    void displayInfo() const override {
        cout << "Electronics: " << name << " (Brand: " << brand << "), Price: ₹" << price << endl;
    }
};

// Clothing Class
class Clothing : public Product {
    string size;

public:
    Clothing(int id, string name, double price, string size)
        : Product(id, name, price), size(size) {}
    void displayInfo() const override {
        cout << "Clothing: " << name << " (Size: " << size << "), Price:  ₹" << price << endl;
    }
};

// Food Class
class Food : public Product {
    string expirationDate;

public:
    Food(int id, string name, double price, string expirationDate)
        : Product(id, name, price), expirationDate(expirationDate) {}
    void displayInfo() const override {
        cout << "Food: " << name << " (Exp: " << expirationDate << "), Price:  ₹" << price << endl;
    }
};

// Customer Class
class Customer {
    int id;
    string name;
    string email;
    string address;

public:
    Customer(int id, string name, string email, string address)
        : id(id), name(name), email(email), address(address) {}

    void displayCustomerInfo() const {
        cout << "Customer: " << name << ", Email: " << email << ", Address: " << address << endl;
    }
    string getName() const { return name; } // Added getName method
};

// ShoppingCart Class
class ShoppingCart {
    vector<Product*> products;

public:
    void addProduct(Product* product) {
        products.push_back(product);
    }

    double calculateTotal() const {
        double total = 0;
        for (const auto& product : products) {
            total += product->getPrice();
        }
        return total;
    }

    void displayCart() const {
        cout << "Shopping Cart:" << endl;
        for (const auto& product : products) {
            product->displayInfo();
        }
        cout << "Total:  ₹" << calculateTotal() << endl;
    }

    const vector<Product*>& getProducts() const { return products; }
};

// Payment Base Class
class Payment {
public:
    virtual void processPayment(double amount) = 0;
    virtual ~Payment() {}
};

// Credit Payment Class
class CreditPayment : public Payment {
public:
    void processPayment(double amount) override {
        cout << "Processing credit payment of ₹" << amount << endl;
    }
};

// Debit Payment Class
class DebitPayment : public Payment {
public:
    void processPayment(double amount) override {
        cout << "Processing debit payment of ₹" << amount << endl;
    }
};

// Cash Payment Class
class CashPayment : public Payment {
public:
    void processPayment(double amount) override {
        cout << "Processing cash payment of ₹" << amount << endl;
    }
};

// Inventory Class
class Inventory {
    map<int, pair<Product*, int>> stock;

public:
    void addProduct(Product* product, int quantity) {
        stock[product->getId()] = make_pair(product, quantity);
    }

    bool isAvailable(int productId, int quantity) {
        return stock.count(productId) && stock[productId].second >= quantity;
    }

    void reduceStock(int productId, int quantity) {
        if (isAvailable(productId, quantity)) {
            stock[productId].second -= quantity;
        }
    }

    void displayInventory() const {
        cout << "Inventory:" << endl;
        for (const auto& stockItem : stock) {  
            stockItem.second.first->displayInfo();
            cout << "Stock: " << stockItem.second.second << endl;
        }
    }

    Product* getProductById(int id) {
        return stock.count(id) ? stock[id].first : nullptr;
    }
};

     //Order Class with File Handling
class Order {
    Customer customer;
    ShoppingCart cart;

public:
    Order(const Customer& customer, const ShoppingCart& cart) : customer(customer), cart(cart) {}

    void saveOrderDetails() {
        ofstream outFile("order_history.txt", ios::app);
        if (outFile.is_open()) {
            outFile << "Order Details for Customer: " << endl;
            outFile << "Name: " << customer.getName() << endl;
            for (const auto& product : cart.getProducts()) {  
                outFile << product->getName() << " - ₹" << product->getPrice() << endl;
            }
            outFile << "Total: ₹" << cart.calculateTotal() << endl;
            outFile << "------------------------" << endl;
            outFile.close();
            cout << "Order saved to file." << endl;
        }
    }
};

// Main Function
int main() {
    Inventory inventory;
    ShoppingCart cart;
    Customer customer(1, "Sanjay S K", "sanjaykrishnegowda@mirafra.com", "Mandya_Namooru");

    // products
    inventory.addProduct(new Electronics(1, "Laptop (ID is 1)", 65289, "DellInspiron"), 10);
    inventory.addProduct(new Clothing(2, "Shirt (ID is 2)", 499.20, "M"), 20);
    inventory.addProduct(new Food(3, "Apple (ID is 3)", 50, "2024-12-31"), 50);

    int choice;
    bool running = true;

    while (running) {
        cout << "\nE-Commerce Management System\n";
        cout << "1. Display Inventory\n";
        cout << "2. Add Product to Cart\n";
        cout << "3. View Cart\n";
        cout << "4. Checkout\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                inventory.displayInventory();
                break;

            case 2: {
                int productId, quantity;
                cout << "Enter Product ID to add to cart: ";
                cin >> productId;
                cout << "Enter quantity: ";
                cin >> quantity;

                Product* product = inventory.getProductById(productId);
                if (product && inventory.isAvailable(productId, quantity)) {
                    cart.addProduct(product);
                    inventory.reduceStock(productId, quantity);
                    cout << "Added " << quantity << " of " << product->getName() << " to cart.\n";
                } else {
                    cout << "Product not available or insufficient stock.\n";
                }
                break;
            }

            case 3:
                cart.displayCart();
                break;

            case 4: {
                int paymentOption;
                cout << "Choose payment method:\n";
                cout << "1. Credit\n";
                cout << "2. Debit\n";
                cout << "3. Cash\n";
                cout << "Option: ";
                cin >> paymentOption;

                Payment* payment;
                switch (paymentOption) {
                    case 1:
                        payment = new CreditPayment();
                        break;
                    case 2:
                        payment = new DebitPayment();
                        break;
                    case 3:
                        payment = new CashPayment();
                        break;
                    default:
                        cout << "Invalid payment option.\n";
                        continue;
                }

                payment->processPayment(cart.calculateTotal());
                Order order(customer, cart);
                order.saveOrderDetails();

                delete payment;  // Cleanup payment object
                cout << "Checkout complete!\n";
                running = false;  // Exit after checkout
                break;
            }

            case 5:
                running = false;
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid option. Try again.\n";
                break;
        }
    }

    return 0;
}
