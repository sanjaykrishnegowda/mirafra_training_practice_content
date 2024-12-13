#include <iostream>
using namespace std;

int main() {
    // Declare an array of pointers
    int* arr[3];

    // Dynamically allocate memory for each pointer
    arr[0] = new int(10); 
    arr[1] = new int(20); 
    arr[2] = new int(30); 

    // Display the values stored in the array of pointers
    cout << "Values in the array of pointers:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "arr[" << i << "] = " << *arr[i] << endl;
    }

    // Modify the values using the pointers
    *arr[1] = 50; // Changing the value at pointer 1

    cout << "\nValues after modification:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "arr[" << i << "] = " << *arr[i] << endl;
    }

    // Deallocate the memory to avoid memory leaks
    for (int i = 0; i < 3; i++) {
        delete arr[i];
    }

    cout << "\nMemory is free." << endl;

    return 0;
}
