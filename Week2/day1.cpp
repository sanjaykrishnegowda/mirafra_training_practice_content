#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Initializing dynamic array using vector
    vector<int> dynamicArray;

    // Adding elements to the vector (this is like dynamic allocation)
    for (int i = 0; i < 10; ++i) {
        dynamicArray.push_back(i * 10);  // Adding elements
        cout << "Added " << i * 10 << " to dynamic array." << endl;
    }

    // Displaying the contents of the vector
    cout << "Contents of the dynamic array: ";
    for (int i = 0; i < dynamicArray.size(); ++i) {
        cout << dynamicArray[i] << " ";
    }
    cout << endl;

    // Resizing the vector (increasing size)
    dynamicArray.resize(15, 100);  // Resize to 15 elements, new elements initialized to 100

    // Displaying the resized vector
    cout << "Contents after resizing: ";
    for (int i = 0; i < dynamicArray.size(); ++i) {
        cout << dynamicArray[i] << " ";
    }
    cout << endl;

    return 0;
}
