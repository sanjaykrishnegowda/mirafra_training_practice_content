#include <iostream>
#include <queue>
#include <ctime>
#include <map>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

class Vehicle {
public:
    int type;  // 1 for Normal Car, 2 for Normal Bike, 3 for Emergency Vehicle
    string plateNumber;
    time_t entryTime;
    time_t exitTime;

    Vehicle(int type, string plateNumber) {
        this->type = type;
        this->plateNumber = plateNumber;
        this->entryTime = time(0);  // Record current time when vehicle enters
    }

    double calculateFee() {
        if (type == 3) {
            return 0;  // No fee for emergency vehicles
        }
        double hours = difftime(exitTime, entryTime) / 3600.0;
        double fee = 0;
        if (type == 1) {
            fee = hours * 20.0;  // $20 per hour for 4-wheel vehicles
        } else if (type == 2) {
            fee = hours * 10.0;  // $10 per hour for bikes
        }
        return fee;
    }
};

class ParkingLot {
private:
    int fourWheelCapacity = 3;
    int twoWheelCapacity = 3;

    queue<Vehicle*> normalCarQueue;
    queue<Vehicle*> normalBikeQueue;
    queue<Vehicle*> emergencyQueue;

    Vehicle* fourWheelParking[3];
    Vehicle* twoWheelParking[3];

    double totalRevenue = 0;
    map<string, Vehicle*> vehicleMap;  // For fast lookup of vehicles by plate number

public:
    ParkingLot() {
        for (int i = 0; i < fourWheelCapacity; i++) {
            fourWheelParking[i] = nullptr;
        }
        for (int i = 0; i < twoWheelCapacity; i++) {
            twoWheelParking[i] = nullptr;
        }
    }

    void parkVehicle(Vehicle* vehicle) {
        if (vehicle->type == 1 || vehicle->type == 3) 
        {  // 4-wheel vehicles
            for (int i = 0; i < fourWheelCapacity; i++) {
                if (fourWheelParking[i] == nullptr) {
                    fourWheelParking[i] = vehicle;
                    vehicleMap[vehicle->plateNumber] = vehicle;
                    cout << (vehicle->type == 3 ? "Emergency" : "Normal") << " vehicle " 
                         << vehicle->plateNumber << " parked in 4-wheel lot.\n";
                    return;
                }
            }
            if (vehicle->type == 3) {
                emergencyQueue.push(vehicle);
                cout << "4-wheel lot full. Emergency vehicle " << vehicle->plateNumber << " waiting in queue.\n";
            } else {
                normalCarQueue.push(vehicle);
                cout << "4-wheel lot full. Vehicle " << vehicle->plateNumber << " waiting in queue.\n";
            }
        } else if (vehicle->type == 2) {  // 2-wheel vehicles
            for (int i = 0; i < twoWheelCapacity; i++) {
                if (twoWheelParking[i] == nullptr) {
                    twoWheelParking[i] = vehicle;
                    vehicleMap[vehicle->plateNumber] = vehicle;
                    cout << "Normal bike " << vehicle->plateNumber << " parked in 2-wheel lot.\n";
                    return;
                }
            }
            normalBikeQueue.push(vehicle);
            cout << "2-wheel lot full. Bike " << vehicle->plateNumber << " waiting in queue.\n";
        }
    }

    void vehicleExit(const string& plateNumber) {
        if (vehicleMap.find(plateNumber) != vehicleMap.end())
        {
            Vehicle* vehicle = vehicleMap[plateNumber];
            vehicle->exitTime = time(0);
            double fee = vehicle->calculateFee();
            if (vehicle->type != 3) {
                totalRevenue += fee;  // Only add fee if it's not an emergency vehicle
            }
            cout << "Vehicle " << vehicle->plateNumber << " exited. Fee: $" << fee << endl;

            if (vehicle->type == 1 || vehicle->type == 3) {
                for (int i = 0; i < fourWheelCapacity; i++) {
                    if (fourWheelParking[i] == vehicle) {
                        fourWheelParking[i] = nullptr;
                        break;
                    }
                }
            } else if (vehicle->type == 2) {
                for (int i = 0; i < twoWheelCapacity; i++) {
                    if (twoWheelParking[i] == vehicle) {
                        twoWheelParking[i] = nullptr;
                        break;
                    }
                }
            }

            vehicleMap.erase(plateNumber);
            parkFromQueue();
        } else {
            cout << "Vehicle with plate number " << plateNumber << " not found in the parking lot.\n";
        }
    }

    void parkFromQueue() {
        // Always prioritize Emergency Vehicles, even if Normal Cars arrived first
        if (!emergencyQueue.empty()) {
            Vehicle* emergencyVehicle = emergencyQueue.front();
            emergencyQueue.pop();
            parkVehicle(emergencyVehicle);
            return;  // Once an emergency vehicle is parked, return immediately
        }

        // If no Emergency Vehicles, check for Normal Cars
        if (!normalCarQueue.empty()) {
            Vehicle* normalCar = normalCarQueue.front();
            normalCarQueue.pop();
            parkVehicle(normalCar);
            return;
        }

        // If no Normal Cars, check for Bikes
        if (!normalBikeQueue.empty()) {
            Vehicle* normalBike = normalBikeQueue.front();
            normalBikeQueue.pop();
            parkVehicle(normalBike);
        }
    }

    void showSystemReport() {
        cout << "\nTotal Revenue: $" << totalRevenue << endl;
        cout << "\nParking Status:\n";
        cout << "4-wheel Lot:\n";
        for (int i = 0; i < fourWheelCapacity; i++) {
            if (fourWheelParking[i] != nullptr) cout << "Spot " << i + 1 << ": " << fourWheelParking[i]->plateNumber << endl;
        }
        cout << "2-wheel Lot:\n";
        for (int i = 0; i < twoWheelCapacity; i++) {
            if (twoWheelParking[i] != nullptr) cout << "Spot " << i + 1 << ": " << twoWheelParking[i]->plateNumber << endl;
        }
        cout << "Waiting Areas:\n";
        cout << "Emergency Queue: " << emergencyQueue.size() << " vehicles\n";
        cout << "Normal Car Queue: " << normalCarQueue.size() << " vehicles\n";
        cout << "Normal Bike Queue: " << normalBikeQueue.size() << " vehicles\n";
    }
};

int main() {
    ParkingLot system;

    // Adding initial vehicles
    system.parkVehicle(new Vehicle(1, "tata"));  // Normal Car
    system.parkVehicle(new Vehicle(1, "mahindra"));  // Normal Car
    system.parkVehicle(new Vehicle(1, "swift"));  // Normal Car
    this_thread::sleep_for(chrono::seconds(5));

    // Queueing vehicles after parking lot fills
    system.parkVehicle(new Vehicle(1, "rolls"));  // Normal Car (Queued)
    system.parkVehicle(new Vehicle(3, "ambulance"));  // Emergency Vehicle (Queued)
    this_thread::sleep_for(chrono::seconds(5));

    // Exit a vehicle
    system.vehicleExit("swift");  // Normal Car exits

    // Show final report
    system.showSystemReport();

    return 0;
}
