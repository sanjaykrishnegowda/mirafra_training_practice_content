#include <iostream>
#include <vector>
using namespace std;

int main() {
    cout << "=== Using Vector ===" << endl;
    vector<int> dynamicArray;
    for (int i = 0; i < 10; ++i) {
        dynamicArray.push_back(i * 10);  // Adding elements
        cout << "Added " << i * 10 << " to dynamic array." << endl;
    }

    // Display the vector contents
    cout << "Contents of dynamic array (Vector): ";
    for (int i = 0; i < dynamicArray.size(); ++i) {
        cout << dynamicArray[i] << " ";
    }
    cout << endl;

    // Resizing the vector (increasing size)
    dynamicArray.resize(15, 100);  // Resize to 15 elements, initialize new ones with 100
    cout << "Contents after resizing (Vector): ";
    for (int i = 0; i < dynamicArray.size(); ++i) {
        cout << dynamicArray[i] << " ";
    }
    cout << endl;

    cout << "\n=== Using Dynamic Array (Manual Memory Management) ===" << endl;

    int* arr = new int[5];  // Allocating an array of 5 integers

    // Initializing the array with values
    for (int i = 0; i < 5; ++i) {
        arr[i] = i * 10;
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }

    // Dynamically resizing the array (simulated by allocating a new larger array)
    int* newArr = new int[10];  // New array of size 10
    for (int i = 0; i < 5; ++i) {
        newArr[i] = arr[i];  // Copying old values to new array
    }

    // Initializing the new elements in the resized array
    for (int i = 5; i < 10; ++i) {
        newArr[i] = i * 20;
    }

    // Display the resized array
    cout << "\nNew Array after resizing: ";
    for (int i = 0; i < 10; ++i) {
        cout << newArr[i] << " ";
    }
    cout << endl;

    // Deleting the old dynamically allocated array
    delete[] arr;
    arr = nullptr;

    // Deleting the resized dynamically allocated array
    delete[] newArr;
    newArr = nullptr;

    cout << "\nMemory is freed after deleting arrays." << endl;

    return 0;
}
