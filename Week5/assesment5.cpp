#include <iostream>
#include <string>
using namespace std;

// Patient class to store patient details
class Patient {
public:
    int patientId;       // Patient ID
    string name;         // Patient name
    string symptoms;     // Symptoms of the patient

    // Constructor to initialize patient details
    Patient(int id, const string& name, const string& symptoms)
        : patientId(id), name(name), symptoms(symptoms) {}
};

// BST Node for managing patient records in the department
class PatientBSTNode {
public:
    Patient* patient;        // Pointer to Patient object
    PatientBSTNode* left;    // Left child of the node
    PatientBSTNode* right;   // Right child of the node

    // Constructor to initialize the node with a patient
    PatientBSTNode(Patient* p)
        : patient(p), left(nullptr), right(nullptr) {}
};

// DepartmentNode class to store department name and patient records in a BST
class DepartmentNode {
public:
    string departmentName;     // Name of the department (e.g., Cardiology)
    DepartmentNode* left;      // Left child node (for department hierarchy)
    DepartmentNode* right;     // Right child node (for department hierarchy)
    PatientBSTNode* patientRoot; // Root of the BST for storing patients in this department

    // Constructor to initialize department with name and null pointers
    DepartmentNode(string name) : departmentName(name), left(nullptr), right(nullptr), patientRoot(nullptr) {}

    // Add patient to the department's BST
    void addPatient(Patient* patient) {
        patientRoot = addPatientToBST(patientRoot, patient);
        cout << "Patient added successfully to " << departmentName << " department.\n";
    }

    // Helper function to add patient to the BST (based on patient ID)
    PatientBSTNode* addPatientToBST(PatientBSTNode* node, Patient* patient) {
        if (node == nullptr) {  // If node is empty, create a new node with the patient
            return new PatientBSTNode(patient);
        }

        // Traverse the BST, inserting based on patient ID
        if (patient->patientId < node->patient->patientId) {
            node->left = addPatientToBST(node->left, patient);  // Insert to the left
        } else {
            node->right = addPatientToBST(node->right, patient);  // Insert to the right
        }
        return node;
    }

    // Display patients in the department's BST in-order (sorted by patient ID)
    void displayPatients() {
        if (patientRoot == nullptr) {
            cout << "No patients found in the " << departmentName << " department.\n";
        } else {
            displayPatientsInOrder(patientRoot);
        }
    }

    // Recursive function to display the patients in order (left, root, right)
    void displayPatientsInOrder(PatientBSTNode* node) {
        if (node == nullptr) return;  // Base case
        displayPatientsInOrder(node->left);  // Visit left subtree
        cout << "Patient ID: " << node->patient->patientId 
             << ", Name: " << node->patient->name 
             << ", Symptoms: " << node->patient->symptoms << endl;  // Display patient info
        displayPatientsInOrder(node->right);  // Visit right subtree
    }

    // Find patient by ID in the BST
    Patient* findPatient(int patientId) {
        return findPatientInBST(patientRoot, patientId);
    }

    // Helper function to find a patient by ID recursively
    Patient* findPatientInBST(PatientBSTNode* node, int patientId) {
        if (node == nullptr) return nullptr;  // If no such patient exists
        if (patientId == node->patient->patientId) return node->patient;  // Found the patient
        if (patientId < node->patient->patientId) return findPatientInBST(node->left, patientId);  // Search left
        return findPatientInBST(node->right, patientId);  // Search right
    }

    // Delete patient by ID from the BST
    void deletePatient(int patientId) {
        bool found = false;
        patientRoot = deletePatientFromBST(patientRoot, patientId, found);
        if (found) {
            cout << "Patient with ID " << patientId << " deleted successfully from " << departmentName << " department.\n";
        } else {
            cout << "Patient not found in " << departmentName << " department.\n";
        }
    }

    // Recursive function to delete a patient from the BST
    PatientBSTNode* deletePatientFromBST(PatientBSTNode* root, int patientId, bool& found) {
        if (root == nullptr) return root;  // If the patient is not found

        // Traverse the tree
        if (patientId < root->patient->patientId) {
            root->left = deletePatientFromBST(root->left, patientId, found);  // Search left
        } else if (patientId > root->patient->patientId) {
            root->right = deletePatientFromBST(root->right, patientId, found);  // Search right
        } else {
            found = true;
            if (root->left == nullptr) {
                PatientBSTNode* temp = root->right;
                delete root;
                return temp;  // Return the right child if no left child
            } else if (root->right == nullptr) {
                PatientBSTNode* temp = root->left;
                delete root;
                return temp;  // Return the left child if no right child
            }

            // If node has two children, replace it with the minimum value from the right subtree
            PatientBSTNode* temp = findMin(root->right);
            root->patient = temp->patient;
            root->right = deletePatientFromBST(root->right, temp->patient->patientId, found);  // Delete the minimum node
        }
        return root;
    }

    // Helper function to find the minimum value node in the BST
    PatientBSTNode* findMin(PatientBSTNode* node) {
        PatientBSTNode* current = node;
        while (current && current->left != nullptr) {
            current = current->left;  // Traverse left to find the minimum
        }
        return current;
    }
};

// Threaded Binary Tree Node for department hierarchy
class ThreadedBinaryTreeNode {
public:
    DepartmentNode* department;   // Pointer to the department
    ThreadedBinaryTreeNode* left; // Left child (department hierarchy)
    ThreadedBinaryTreeNode* right; // Right child (department hierarchy)
    bool rightThreaded;  // Boolean flag to mark if the right pointer is a thread

    // Constructor to initialize the node with department information
    ThreadedBinaryTreeNode(DepartmentNode* dept)
        : department(dept), left(nullptr), right(nullptr), rightThreaded(false) {}
};

// Threaded Binary Tree for managing department hierarchy
class ThreadedBinaryTree {
public:
    ThreadedBinaryTreeNode* root;  // Root node of the threaded binary tree

    // Constructor to initialize an empty tree
    ThreadedBinaryTree() : root(nullptr) {}

    // Add a department to the tree
    void addDepartment(DepartmentNode* department) {
        if (root == nullptr) {
            root = new ThreadedBinaryTreeNode(department);  // If tree is empty, create root
        } else {
            addDepartmentToTree(root, department);  // Otherwise, add to the correct position
        }
    }

    // Recursive function to add department to the tree
    void addDepartmentToTree(ThreadedBinaryTreeNode* node, DepartmentNode* department) {
        if (department->departmentName < node->department->departmentName) {
            if (node->left == nullptr) {
                node->left = new ThreadedBinaryTreeNode(department);  // Add to the left if possible
            } else {
                addDepartmentToTree(node->left, department);  // Otherwise, recursively go left
            }
        } else {
            if (node->right == nullptr || node->rightThreaded) {
                node->right = new ThreadedBinaryTreeNode(department);  // Add to the right
                node->rightThreaded = false;  // Mark right pointer as not threaded
            } else {
                addDepartmentToTree(node->right, department);  // Otherwise, recursively go right
            }
        }
    }

    // In-order traversal of the tree (to display departments)
    void inOrderTraversal() {
        if (root != nullptr) {
            inOrderTraversalHelper(root);  // Call the recursive helper function
        }
    }

    // Helper function to perform in-order traversal
    void inOrderTraversalHelper(ThreadedBinaryTreeNode* node) {
        if (node == nullptr) return;  // Base case
        inOrderTraversalHelper(node->left);  // Visit left subtree
        cout << "Department: " << node->department->departmentName << endl;  // Display department name
        if (!node->rightThreaded) {
            inOrderTraversalHelper(node->right);  // Visit right subtree
        }
    }
};

// Main function to interact with the user
int main() {
    ThreadedBinaryTree hospitalDepartments;  // Root of the department tree
    int choice;
    string deptName;
    int subDeptChoice, patientId;
    string patientName, symptoms;

    // Example setup for departments
    DepartmentNode* cardiology = new DepartmentNode("Cardiology");
    hospitalDepartments.addDepartment(cardiology);  // Add Cardiology department
    DepartmentNode* neurology = new DepartmentNode("Neurology");
    hospitalDepartments.addDepartment(neurology);  // Add Neurology department
    DepartmentNode* urology = new DepartmentNode("Urology");
    hospitalDepartments.addDepartment(urology);  // Add Urology department

    while (true) {
        // Display menu
        cout << "\n ---------------";
        cout << "\n|Apollo Hospital|\n";
        cout << " ---------------\n";
        cout << "1. Add Patient\n";
        cout << "2. Display Patients in Department\n";
        cout << "3. Delete Patient by ID\n";
        cout << "4. Display Departments\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // To ignore newline after entering choice

        // Process user input based on choice
        switch (choice) {
        case 1:  // Add Patient
            cout << "Enter department name (Cardiology, Neurology, Urology): ";
            getline(cin, deptName);

            cout << "Enter patient ID: ";
            cin >> patientId;
            cin.ignore();  // Clear newline

            cout << "Enter patient name: ";
            getline(cin, patientName);

            cout << "Enter symptoms: ";
            getline(cin, symptoms);

            // Add patient to the correct department
            if (deptName == "Cardiology") {
                cardiology->addPatient(new Patient(patientId, patientName, symptoms));
            } else if (deptName == "Neurology") {
                neurology->addPatient(new Patient(patientId, patientName, symptoms));
            } else if (deptName == "Urology") {
                urology->addPatient(new Patient(patientId, patientName, symptoms));
            } else {
                cout << "Invalid department name!\n";
            }
            break;

        case 2:  // Display Patients
            cout << "Enter department name (Cardiology, Neurology, Urology): ";
            getline(cin, deptName);

            // Display patients in the chosen department
            if (deptName == "Cardiology") {
                cardiology->displayPatients();
            } else if (deptName == "Neurology") {
                neurology->displayPatients();
            } else if (deptName == "Urology") {
                urology->displayPatients();
            } else {
                cout << "Invalid department name!\n";
            }
            break;

        case 3:  // Delete Patient
            cout << "Enter department name (Cardiology, Neurology, Urology): ";
            getline(cin, deptName);

            cout << "Enter patient ID to delete: ";
            cin >> patientId;
            cin.ignore();  // Clear newline

            // Delete patient from the specified department
            if (deptName == "Cardiology") {
                cardiology->deletePatient(patientId);
            } else if (deptName == "Neurology") {
                neurology->deletePatient(patientId);
            } else if (deptName == "Urology") {
                urology->deletePatient(patientId);
            } else {
                cout << "Invalid department name!\n";
            }
            break;

        case 4:  // Display Departments
            cout << "Departments:\n";
            hospitalDepartments.inOrderTraversal();  // Display all departments in sorted order
            break;

        case 5:  // Exit
            cout << "Exiting the system.\n";
            return 0;  // Exit the program

        default:  // Invalid choice
            cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
