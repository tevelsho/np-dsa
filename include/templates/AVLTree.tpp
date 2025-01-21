#include <iostream>
#include <string>
#include "../List.h"
#include "../AVLTree.h"
using namespace std;

template <class T>
struct Node {
        T item; 
        Node* next; 
};

int custom_max(const int& a, const int& b) {
    return (a > b) ? a : b;
}
template<class T> //T will either be Actor* or Movie*
struct AVLNode 
{
    int key; //year of actor birth or movie release
    List<T>* list;
    AVLNode* left;
    AVLNode* right;
    int height;

    //
    AVLNode(int key, T* item) 
        : key(key), list(new List<T*>()),
          left(nullptr), right(nullptr), height(1) {
        list->append(item);
    }
    
    // Destructor
    ~AVLNode() {
        if (list) delete list;
    }
};

template<class T>
class AVLTree
{
private:
    AVLNode* root;
    int currentYear = 2025;
public:

    AVLTree() : root(nullptr) {}
    
    ~AVLTree() {
        destroyTree(root);
    }

    void destroyTree(AVLNode* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    
    //AVL FUNCTIONS
    int height(AVLNode* node) const {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode* node) const {
        if (!node) return 0;
        return height(node->left) - height(node->right);
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        
        // Perform rotation
        x->right = y;
        y->left = T2;
        
        // Update heights
        y->height = custom_max(height(y->left), height(y->right)) + 1;
        x->height = custom_max(height(x->left), height(x->right)) + 1;
        
        // Return new root
        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        
        // Perform rotation
        y->left = x;
        x->right = T2;
        
        // Update heights
        x->height = custom_max(height(x->left), height(x->right)) + 1;
        y->height = custom_max(height(y->left), height(y->right)) + 1;
        
        // Return new root
        return y;
    }

    //Inserting an Item
    void insertItem(int key, T* item) {
        root = insertItem(root, key, item);
    }

    AVLNode* insertItem(AVLNode* node, int key, T* item) {
        if (!node)
            return new AVLNode(key, item);
        if (key < node->key)
            node->left = insertItem(node->left, key, item);
        else if (key > node->key)
            node->right = insertItem(node->right, key, item);
        else {
            // Key already exists, append actor to the list
            if (node->list)
                node->actors->append(item);
            return node;
        }
        
        node->height = 1 + custom_max(height(node->left), height(node->right));
        
        int balance = getBalance(node);
        
        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);
        
        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);
        
        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        
        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }
    
    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    // AVLNode* deleteNode(AVLNode* root, int key) {
    //     // 1. Perform standard BST delete
    //     if (!root)
    //         return root;
        
    //     if (key < root->key)
    //         root->left = deleteNode(root->left, key);
    //     else if (key > root->key)
    //         root->right = deleteNode(root->right, key);
    //     else {
    //         // Node with only one child or no child
    //         if ((root->left == nullptr) || (root->right == nullptr)) {
    //             AVLNode* temp = root->left ? root->left : root->right;
                
    //             // No child case
    //             if (temp == nullptr) {
    //                 temp = root;
    //                 root = nullptr;
    //             }
    //             else { // One child case
    //                 *root = *temp; // Copy the contents
    //             }
                
    //             delete temp;
    //         }
    //         else {
    //             // Node with two children
    //             AVLNode* temp = minValueNode(root->right);
    //             root->key = temp->key;
                
    //             if (root->list && temp->list) {
    //                 // Clear current actors list
    //                 delete root->list;
    //                 root->list = new LinkedList<T*>();
                    
    //             }
    //             root->right = deleteNode(root->right, temp->key);
    //         }
    //     }
        
    //     // If the tree had only one node
    //     if (root == nullptr)
    //         return root;
        
    //     // 2. Update height
    //     root->height = 1 + custom_max(height(root->left), height(root->right));
        
    //     // 3. Get balance factor
    //     int balance = getBalance(root);
        
    //     // 4. Balance the tree
    //     // Left Left Case
    //     if (balance > 1 && getBalance(root->left) >= 0)
    //         return rightRotate(root);
        
    //     // Left Right Case
    //     if (balance > 1 && getBalance(root->left) < 0) {
    //         root->left = leftRotate(root->left);
    //         return rightRotate(root);
    //     }
        
    //     // Right Right Case
    //     if (balance < -1 && getBalance(root->right) <= 0)
    //         return leftRotate(root);
        
    //     // Right Left Case
    //     if (balance < -1 && getBalance(root->right) > 0) {
    //         root->right = rightRotate(root->right);
    //         return leftRotate(root);
    //     }
        
    //     return root;
    // }

    // BETWEEN X AND Y
    void DisplayActors(int x, int y) {
        inOrderTraversalRangeAge(root, x, y);
        cout << endl; // For a clean newline after displaying
    }

    // PAST THREE YEARS
    void DisplayMovies(int age) {
        inOrderTraversalRange(root, currentYear-3, currentYear);
        cout << endl; // For a clean newline after displaying
    }

    // For ACTORS
    void inOrderTraversalRangeAge(AVLNode* node, int x, int y) const {
        if (node == nullptr)
            return;

        // Since it's in-order, first traverse the left subtree if needed
        if (node->key < y)
            inOrderTraversalRange(node->right, x, y);

        // If the current node is within range, display the items in the list
        if (node->key >= x && node->key <= y) {
            Node* next = list.getHead();
            while (next != nullptr){
                cout << "Age: " << currentYear - Node.item.year <<  " Name: " << Node.item.name << endl;
            }
            cout << endl;
        }

        // Then traverse the right subtree if needed
        if (node->key > x)
            inOrderTraversalRange(node->left, x, y);
    }

    // For Actors
    void inOrderTraversalRange(AVLNode* node, int x, int y) const {
        if (node == nullptr)
            return;

        // Since it's in-order, first traverse the left subtree if needed
        if (node->key > x)
            inOrderTraversalRange(node->left, x, y);

        // If the current node is within range, display the items in the list
        if (node->key >= x && node->key <= y) {
            cout << "Year: " << node->key << ", Item: ";
            Node* next = list.getHead();
            while (next != nullptr){
                cout << "Year: " << Node.item.year <<  " Name: " << Node.item.name << endl;
            }
            cout << endl;
        }

        // Then traverse the right subtree if needed
        if (node->key < y)
            inOrderTraversalRange(node->right, x, y);
    }
};