#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

// Class for Menu Items
class MenuItem {
public:
    int item_id;
    string name;
    double price;

    MenuItem(int id, string n, double p) : item_id(id), name(n), price(p) {}

    void display() const {
        cout << item_id << ": " << name << " - ₹" << price << endl;
    }
};

// Class for Menu Item Node (used in linked list for orders)
class MenuItemNode {
public:
    MenuItem item;
    MenuItemNode* next;

    MenuItemNode(const MenuItem& item) : item(item), next(nullptr) {}
};

// Class for Restaurants
class Restaurant {
public:
    int restaurant_id;
    string name;
    string location;
    vector<MenuItem> menu; //  vector for menu items

    Restaurant(int id, string n, string loc) : restaurant_id(id), name(n), location(loc) {}

    void addMenuItem(const MenuItem& item) {
        menu.push_back(item);
    }

    void displayMenu() const {
        cout << "Menu for " << name << ":\n";
        for (const auto& item : menu) {
            item.display();
        }
        if (menu.empty()) {
            cout << "No menu items available for this restaurant.\n";
        }
    }

    void displayInfo() const {
        cout << "Restaurant ID: " << restaurant_id << ", Name: " << name << ", Location: " << location << endl;
    }
};

// Class for Orders (Linked List)
class Order {
public:
    int order_id;
    Restaurant* restaurant;
    MenuItemNode* items_head; // Linked list for order items
    double total_cost;
    string status;
    Order* next; // Pointer to the next order in the queue

    Order(int id, Restaurant* res) 
        : order_id(id), restaurant(res), items_head(nullptr), total_cost(0.0), status("Pending"), next(nullptr) {}

    void addItem(const MenuItem& item) {
        MenuItemNode* newNode = new MenuItemNode(item);
        if (!items_head) {
            items_head = newNode;
        } else {
            MenuItemNode* temp = items_head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        total_cost += item.price;
    }

    double calculateTotal() const {
        return total_cost;
    }

    void updateStatus(const string& new_status) {
        status = new_status;
    }

    void displayOrder() const {
        cout << "Order ID: " << order_id << endl;
        cout << "Restaurant: " << restaurant->name << endl;
        cout << "Items:\n";
        MenuItemNode* temp = items_head;
        while (temp) {
            temp->item.display();
            temp = temp->next;
        }
        cout << "Total Cost: ₹" << total_cost << endl;
        cout << "Status: " << status << endl;
    }
};

// Class for Order Queue (Circular Linked List)
class OrderQueue {
private:
    Order* front; // Front of the queue
    Order* rear;  // Rear of the queue

public:
    OrderQueue() : front(nullptr), rear(nullptr) {}

    void enqueue(Order* order) {
        if (!front) {
            front = rear = order;
            rear->next = front;  // Circular link (rear points to front)
        } else {
            rear->next = order;  // Link the current rear to the new order
            rear = order;        // Update the rear to the new order
            rear->next = front;  // Circular link (rear points to front)
        }
    }

    Order* dequeue() {
        if (!front) {
            cout << "No orders to process!\n";
            return nullptr;
        }

        Order* nextOrder = front;
        if (front == rear) {
            front = rear = nullptr; // If there is only one order, reset the queue
        } else {
            front = front->next;    // Move front to the next order
            rear->next = front;     // Maintain circular link
        }
        nextOrder->next = nullptr;  // Break the circular link for the dequeued order
        return nextOrder;
    }

    Order* viewNext() const {
        return front;
    }
};

// Class for Delivery System
class DeliverySystem {
public:
    Order* currentOrder;

    DeliverySystem() : currentOrder(nullptr) {}

    void assignOrder(Order* order) {
        currentOrder = order;
        order->updateStatus("Out for Delivery");
        cout << "Delivering Order ID " << order->order_id << " from " << order->restaurant->name << ".\n";
    }
};

// Function Prototypes
void manageRestaurants(vector<Restaurant>& restaurants);
void placeOrder(vector<Restaurant>& restaurants, OrderQueue& orderQueue);
void processDelivery(OrderQueue& orderQueue, DeliverySystem& deliverySystem);
void viewRestaurantAndMenu(const vector<Restaurant>& restaurants);

// Main Function
int main() {
    vector<Restaurant> restaurants; // List of all restaurants
    OrderQueue orderQueue;          // Queue for managing orders
    DeliverySystem deliverySystem;  // Delivery system

    int choice;

    do {
        cout << "\nFood Ordering and Delivery System\n";
        cout << "1. Manage Restaurants\n";
        cout << "2. Place an Order\n";
        cout << "3. Process and Deliver Orders\n";
        cout << "4. View Restaurants and Menus\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manageRestaurants(restaurants);
                break;
            case 2:
                placeOrder(restaurants, orderQueue);
                break;
            case 3:
                processDelivery(orderQueue, deliverySystem);
                break;
            case 4:
                viewRestaurantAndMenu(restaurants);
                break;
            case 5:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}

// Function to Manage Restaurants
void manageRestaurants(vector<Restaurant>& restaurants) {
    int choice;
    cout << "\nManage Restaurants\n";
    cout << "1. Add a Restaurant\n";
    cout << "2. Add Menu Item to a Restaurant\n";
    cout << "3. Display Restaurants and Menus\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        int id;
        string name, location;
        cout << "Enter Restaurant ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Restaurant Name: ";
        getline(cin, name);
        cout << "Enter Restaurant Location: ";
        getline(cin, location);
        restaurants.emplace_back(id, name, location);
        cout << "Restaurant added successfully!\n";
    } else if (choice == 2) {
        int id;
        cout << "Enter Restaurant ID: ";
        cin >> id;

        for (auto& restaurant : restaurants) {
            if (restaurant.restaurant_id == id) {
                int item_id;
                string item_name;
                double item_price;
                cout << "Enter Menu Item ID: ";
                cin >> item_id;
                cin.ignore();
                cout << "Enter Menu Item Name: ";
                getline(cin, item_name);
                cout << "Enter Menu Item Price: ";
                cin >> item_price;
                restaurant.addMenuItem(MenuItem(item_id, item_name, item_price));
                cout << "Menu item added successfully!\n";
                return;
            }
        }
        cout << "Restaurant not found.\n";
    } else if (choice == 3) {
        for (const auto& restaurant : restaurants) {
            restaurant.displayInfo();
            restaurant.displayMenu();
        }
    } else {
        cout << "Invalid choice.\n";
    }
}

// Function to Place Orders
void placeOrder(vector<Restaurant>& restaurants, OrderQueue& orderQueue) {
    if (restaurants.empty()) {
        cout << "No restaurants available. Add a restaurant first.\n";
        return;
    }

    // Step 1: Show available restaurants
    cout << "\nAvailable Restaurants:\n";
    for (const auto& restaurant : restaurants) {
        restaurant.displayInfo();
    }

    int restaurant_id;
    cout << "Enter Restaurant ID to order from: ";
    cin >> restaurant_id;

    Restaurant* selectedRestaurant = nullptr;

    for (auto& restaurant : restaurants) {
        if (restaurant.restaurant_id == restaurant_id) {
            selectedRestaurant = &restaurant;
            break;
        }
    }

    if (!selectedRestaurant) {
        cout << "Restaurant not found.\n";
        return;
    }

    // Step 2: Create an order
    int order_id;
    cout << "Enter Order ID: ";
    cin >> order_id;
    Order* order = new Order(order_id, selectedRestaurant);

    char more_items;
    do {
        // Step 3: Show menu for the selected restaurant
        selectedRestaurant->displayMenu();

        int item_id;
        cout << "Enter Menu Item ID to add to order: ";
        cin >> item_id;

        bool item_found = false;
        for (const auto& item : selectedRestaurant->menu) {
            if (item.item_id == item_id) {
                order->addItem(item);
                item_found = true;
                break;
            }
        }

        if (!item_found) {
            cout << "Item not found.\n";
        }

        cout << "Add more items? (y/n): ";
        cin >> more_items;
    } while (more_items == 'y' || more_items == 'Y');

    // Step 4: Add order to the queue
    orderQueue.enqueue(order);
    cout << "Order placed successfully!\n";
}

// Function to Process and Deliver Orders
void processDelivery(OrderQueue& orderQueue, DeliverySystem& deliverySystem) {
    Order* order = orderQueue.dequeue();
    if (order) {
        order->displayOrder();
        deliverySystem.assignOrder(order);
    }
}

// Function to View Restaurants and Menus
void viewRestaurantAndMenu(const vector<Restaurant>& restaurants) {
    if (restaurants.empty()) {
        cout << "No restaurants available.\n";
        return;
    }

    cout << "\nAvailable Restaurants and Menus:\n";
    for (const auto& restaurant : restaurants) {
        restaurant.displayInfo();
        restaurant.displayMenu();
    }
}
