#include <iostream>
using namespace std;

int main() {
    // Overview: Creating a 2D Array (3 rows, 3 columns)
    int matrix[3][3]; // Declaration of a 2D array

    // Initializing the multi-dimensional array with values
    cout << "Enter 9 elements for the 3x3 matrix:" << endl;
    for (int i = 0; i < 3; i++) {        
        for (int j = 0; j < 3; j++) {    
            cin >> matrix[i][j];         
        }
    }

    // Accessing and displaying the elements of the 2D array
    cout << "\nMatrix elements are:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix[i][j] << " "; // Accessing each element
        }
        cout << endl;
    }

    // Changing a specific element in the 2D array
    cout << "\nChanging matrix[1][1] to 99." << endl;
    matrix[1][1] = 99; // Updating the value at position (1, 1)

    // Traversing and printing the updated matrix
    cout << "Updated matrix is:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix[i][j] << " "; // Printing updated elements
        }
        cout << endl;
    }

    return 0;
}
