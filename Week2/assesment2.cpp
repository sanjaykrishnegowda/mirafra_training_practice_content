#include <iostream>
#include <vector>
#include <string>

// Structure to store item details (item name and quantity)
struct InventoryItem {
	std::string itemName;
	int quantity;

	InventoryItem(const std::string& name = "", int qty = 0) : itemName(name), quantity(qty) {}
};

// 3D vector to represent warehouse structure (aisle x bin x warehouse)
std::vector<std::vector<std::vector<int>>> warehouse(100, std::vector<std::vector<int>>(100, std::vector<int>(100, 0)));

// Function to add inventory at a specific location
void addInventory(const std::string& itemName, int quantity, int aisle, int bin, int warehouseIndex) {
	if (quantity > 0) {
		warehouse[aisle][bin][warehouseIndex] += quantity;
		std::cout << "Added " << quantity << " of " << itemName << " at Location (Aisle "
		          << aisle << ", Bin " << bin << ", Warehouse " << warehouseIndex << ").\n";
	} else {
		std::cout << "Error: Cannot add a non-positive quantity.\n";
	}
}

// Function to remove inventory from a specific location
void removeInventory(int quantity, int aisle, int bin, int warehouseIndex) {
	if (warehouse[aisle][bin][warehouseIndex] >= quantity) {
		warehouse[aisle][bin][warehouseIndex] -= quantity;
		std::cout << "Removed " << quantity << " from Location (Aisle "
		          << aisle << ", Bin " << bin << ", Warehouse " << warehouseIndex << ").\n";
	} else {
		std::cout << "Error: Insufficient stock to remove.\n";
	}
}

// Function to check the stock of an item at a given location
void checkStock(int aisle, int bin, int warehouseIndex) {
	int quantity = warehouse[aisle][bin][warehouseIndex];
	if (quantity > 0) {
		std::cout << "Stock at Location (Aisle " << aisle << ", Bin " << bin << ", Warehouse "
		          << warehouseIndex << "): " << quantity << " units.\n";
	} else {
		std::cout << "No stock at the specified location.\n";
	}
}

// Function to display all items with their locations and quantities
void displayInventory() {
	std::cout << "Current Inventory:\n";
	for (int aisle = 0; aisle < warehouse.size(); aisle++) {
		for (int bin = 0; bin < warehouse[aisle].size(); bin++) {
			for (int warehouseIndex = 0; warehouseIndex < warehouse[aisle][bin].size(); warehouseIndex++) {
				int quantity = warehouse[aisle][bin][warehouseIndex];
				if (quantity > 0) {
					std::cout << "Location (Aisle " << aisle << ", Bin " << bin << ", Warehouse "
					          << warehouseIndex << "): " << quantity << " units.\n";
				}
			}
		}
	}
}

// Function to transfer stock from one location to another
void transferItems(int quantity, int fromAisle, int fromBin, int fromWarehouseIndex,
                   int toAisle, int toBin, int toWarehouseIndex) {
	if (warehouse[fromAisle][fromBin][fromWarehouseIndex] >= quantity) {
		warehouse[fromAisle][fromBin][fromWarehouseIndex] -= quantity;
		warehouse[toAisle][toBin][toWarehouseIndex] += quantity;
		std::cout << "Transferred " << quantity << " from Location (Aisle " << fromAisle
		          << ", Bin " << fromBin << ", Warehouse " << fromWarehouseIndex
		          << ") to Location (Aisle " << toAisle << ", Bin " << toBin
		          << ", Warehouse " << toWarehouseIndex << ").\n";
	} else {
		std::cout << "Error: Insufficient stock to transfer.\n";
	}
}

// Function to flag low-stock items (below a threshold)
void lowStockAlert(int threshold) {
	std::cout << "Low Stock Alerts (Below threshold " << threshold << "):\n";
	for (int aisle = 0; aisle < warehouse.size(); aisle++) {
		for (int bin = 0; bin < warehouse[aisle].size(); bin++) {
			for (int warehouseIndex = 0; warehouseIndex < warehouse[aisle][bin].size(); warehouseIndex++) {
				int quantity = warehouse[aisle][bin][warehouseIndex];
				if (quantity > 0 && quantity < threshold) {
					std::cout << "Location (Aisle " << aisle << ", Bin " << bin << ", Warehouse "
					          << warehouseIndex << "): " << quantity << " units.\n";
				}
			}
		}
	}
}

int main() {
	int choice;
	while (true) {
		// Display menu options
		std::cout << "\n------ Inventory Management System ------\n";
		std::cout << "1. Add Inventory\n";
		std::cout << "2. Remove Inventory\n";
		std::cout << "3. Check Stock\n";
		std::cout << "4. Transfer Items\n";
		std::cout << "5. Display Inventory\n";
		std::cout << "6. Low Stock Alerts\n";
		std::cout << "7. Exit\n";
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		switch (choice) {
		case 1: {
			std::string itemName;
			int quantity, aisle, bin, warehouseIndex;
			std::cout << "Enter item name: ";
			std::cin.ignore();
			std::getline(std::cin, itemName);

			std::cout << "Enter quantity: ";
			std::cin >> quantity;

			std::cout << "Enter aisle number: ";
			std::cin >> aisle;

			std::cout << "Enter bin number: ";
			std::cin >> bin;

			std::cout << "Enter warehouse number: ";
			std::cin >> warehouseIndex;

			addInventory(itemName, quantity, aisle, bin, warehouseIndex);
			break;
		}
		case 2: {
			int quantity, aisle, bin, warehouseIndex;
			std::cout << "Enter quantity to remove: ";
			std::cin >> quantity;

			std::cout << "Enter aisle number: ";
			std::cin >> aisle;

			std::cout << "Enter bin number: ";
			std::cin >> bin;

			std::cout << "Enter warehouse number: ";
			std::cin >> warehouseIndex;

			removeInventory(quantity, aisle, bin, warehouseIndex);
			break;
		}
		case 3: {
			int aisle, bin, warehouseIndex;
			std::cout << "Enter aisle number: ";
			std::cin >> aisle;

			std::cout << "Enter bin number: ";
			std::cin >> bin;

			std::cout << "Enter warehouse number: ";
			std::cin >> warehouseIndex;

			checkStock(aisle, bin, warehouseIndex);
			break;
		}
		case 4: {
			int quantity, fromAisle, fromBin, fromWarehouse, toAisle, toBin, toWarehouse;
			std::cout << "Enter quantity to transfer: ";
			std::cin >> quantity;

			std::cout << "Enter source aisle: ";
			std::cin >> fromAisle;

			std::cout << "Enter source bin: ";
			std::cin >> fromBin;

			std::cout << "Enter source warehouse: ";
			std::cin >> fromWarehouse;

			std::cout << "Enter destination aisle: ";
			std::cin >> toAisle;

			std::cout << "Enter destination bin: ";
			std::cin >> toBin;

			std::cout << "Enter destination warehouse: ";
			std::cin >> toWarehouse;

			transferItems(quantity, fromAisle, fromBin, fromWarehouse, toAisle, toBin, toWarehouse);
			break;
		}
		case 5:
			displayInventory();
			break;
		case 6: {
			int threshold;
			std::cout << "Enter low stock threshold: ";
			std::cin >> threshold;
			lowStockAlert(threshold);
			break;
		}
		case 7:
			std::cout << "Exiting...\n";
			return 0;
		default:
			std::cout << "Invalid choice. Please try again.\n";
		}
	}

	return 0;
}
