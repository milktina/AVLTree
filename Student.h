#pragma once
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Student {
private:
    struct Node {
        string studentName;
        string gatorID;
        int height;
        int count;
        Node* left;
        Node* right;
        Node(string studentName, string gatorID) : studentName(studentName), gatorID(gatorID), height(1), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;

    int max(int a, int b);
    int height(Node* node);
    int getHeight(Node* root);
    int getBalance(Node* node);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    Node* insert(Node* root, string studentName, string gatorID);
    Node* minValueNode(Node* node);
    Node* deleteNode(Node* root, string gatorID);
    Node* removeNthInorder(Node* root, int n);
    void helperSearchName(Node* root, string studentName, vector<string>& matchingGatorIDs);
    void helperSearchID(Node* root, string gatorID);

    void inorder(Node* root, bool& first);
    void preorder(Node* root, bool& first);
    void postorder(Node* root, bool& first);

public:
    void insert(string studentName, string gatorID);
    void deleteStudent(string gatorID);
    void removeNthInorder(int n);
    void searchName(string studentName);
    void searchID(string gatorID);
    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevels();
};

int Student::max(int a, int b) {
    return (a > b) ? a : b;
}

int Student::height(Node* node) {
    if (node == nullptr) {
        return 0;
    }

    return node->height;
}

int Student::getHeight(Node* root) {
    if (root == nullptr) {
        return 0;
    }

    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    // Return the greater height of the left and right subtrees, plus 1 for the current level
    return 1 + max(leftHeight, rightHeight);
}

void Student::printLevels() {
    int levels = getHeight(root);
    cout << levels << endl;
}

int Student::getBalance(Node* node) {
    if (node == nullptr) {
        return 0;
    }

    return height(node->left) - height(node->right);
}

Student::Node* Student::rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

Student::Node* Student::leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

Student::Node* Student::insert(Node* root, string studentName, string gatorID) {
    if (root == nullptr) {
        return new Node(studentName, gatorID);
    }

    if (gatorID < root->gatorID) {
        root->left = insert(root->left, studentName, gatorID);
    } else if (gatorID > root->gatorID) {
        root->right = insert(root->right, studentName, gatorID);
    } else {
        return root; // Duplicate gatorID is not allowed
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && gatorID < root->left->gatorID) {
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && gatorID > root->right->gatorID) {
        return leftRotate(root);
    }

    // Left Right Case
    if (balance > 1 && gatorID > root->left->gatorID) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && gatorID < root->right->gatorID) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void Student::insert(string studentName, string gatorID) {
    this->root = insert(root, studentName, gatorID);
    if (root != nullptr) {
        cout << "successful" << endl;
    }
    else {
        cout << "unsuccessful" << endl;
    }
}

Student::Node* Student::minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

Student::Node* Student::deleteNode(Node* root, string gatorID) {
    if (root == nullptr) {
        return root;
    }

    if (gatorID < root->gatorID) {
        root->left = deleteNode(root->left, gatorID);
    } else if (gatorID > root->gatorID) {
        root->right = deleteNode(root->right, gatorID);
    } else {
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->gatorID = temp->gatorID;
            root->studentName = temp->studentName;
            root->right = deleteNode(root->right, temp->gatorID);
        }
    }

    if (root == nullptr) {
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    root->count = 1 + (root->left != nullptr ? root->left->count : 0) + (root->right != nullptr ? root->right->count : 0);

    return root;
}

void Student::deleteStudent(string gatorID) {
    bool success = deleteNode(root, gatorID);
    if (success) {
        cout << "successful" << endl;
    }
    else {
        cout << "unsuccessful" << endl;
    }
}

void Student::removeNthInorder(int n) {
    bool success = removeNthInorder(root, n);
    if (success) {
        cout << "successful" << endl;
    }
    else {
        cout << "unsuccessful" << endl;
    }
}

// Helper function to remove the Nth GatorID
Student::Node* Student::removeNthInorder(Node* root, int n) {
    if (root == nullptr) {
        return nullptr;
    }

    int leftCount = 0; // Number of nodes in the left subtree

    if (root->left != nullptr) {
        leftCount = root->left->count;
    }

    if (n < leftCount) {
        // The Nth node is in the left subtree
        root->left = removeNthInorder(root->left, n);
    } else if (n > leftCount) {
        // The Nth node is in the right subtree
        root->right = removeNthInorder(root->right, n - leftCount - 1); // Subtract leftCount and 1 for the current node
    } else {
        // This is the Nth node to be removed
        return deleteNode(root, root->gatorID);
    }

    // Update the count of nodes in this subtree
    root->count = 1 + (root->left != nullptr ? root->left->count : 0) + (root->right != nullptr ? root->right->count : 0);

    return root;
}

void Student::searchName(string studentName) {
    vector<string> matchingGatorIDs;
    helperSearchName(root, studentName, matchingGatorIDs);

    if (matchingGatorIDs.empty()) {
        cout << "unsuccessful" << endl;
    }
    else {
        for (int i = 0; i < matchingGatorIDs.size(); i++) {
            cout << matchingGatorIDs[i] << endl;
        }
    }
}

void Student::helperSearchName(Node* root, string studentName, vector<string>& matchingGatorIDs) {
    if (root == nullptr) {
        return;
    }

    if (root->studentName.find(studentName) != string::npos) {
        // Name found, add the GatorID to the vector
        matchingGatorIDs.push_back(root->gatorID);
    }

    // Continue searching in both left and right subtrees
    helperSearchName(root->left, studentName, matchingGatorIDs);
    helperSearchName(root->right, studentName, matchingGatorIDs);
}

void Student::searchID(string gatorID) {
    helperSearchID(root, gatorID);
}

void Student::helperSearchID(Node* root, string gatorID) {
    if (root == nullptr) {
        cout << "unsuccessful" << endl;
        return;
    }

    if (gatorID < root->gatorID) {
        helperSearchID(root->left, gatorID);
    }
    else if (gatorID > root->gatorID) {
        helperSearchID(root->right, gatorID);
    }
    else {
        cout << root->studentName << endl;
    }
}

void Student::inorder(Node* root, bool& first) {
    if (root == nullptr) {
        return;
    }

    inorder(root->left, first);
    if (!first) {
        cout << ", ";
    } else {
        first = false;
    }
    cout << root->studentName;
    inorder(root->right, first);
}

void Student::printInorder() {
    bool first = true;
    inorder(root, first);
    cout << endl;
}

void Student::preorder(Node* root, bool& first) {
    if (root == nullptr) {
        return;
    }

    if (!first) {
        cout << ", ";
    }

    cout << root->studentName;
    first = false;

    preorder(root->left, first);
    preorder(root->right, first);
}

void Student::printPreorder() {
    bool first = true;
    preorder(root, first);
    cout << endl;
}

void Student::postorder(Node* root, bool& first) {
    if (root == nullptr) {
        return;
    }

    postorder(root->left, first);
    postorder(root->right, first);

    if (!first) {
        cout << ", ";
    }

    cout << root->studentName;
    first = false;
}

void Student::printPostorder() {
    bool first = true;
    postorder(root, first);
    cout << endl;
}

