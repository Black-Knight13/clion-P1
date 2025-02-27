//
// Created by jackson turnbull on 2/14/25.
//

#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class AVL {
    struct Node { // create Node struct
        int ID;
        int height;
        string name;

        Node *left;
        Node *right;

        // Node default constructor
        Node(string Name, int id) {
            name = Name;
            ID = id;
            left = nullptr;
            right = nullptr;
            height = 1;
        }
    };

    Node *LeftRotation(Node *n1) { // Rotate left
        Node *temp = n1->right;
        Node *temp2 = temp->left;

        temp->left = n1;
        n1->right = temp2;

        n1->height = max(getHeight(n1->left), getHeight(n1->right)) + 1;
        temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
        return temp;
    }


    Node *RightRotation(Node *n2) { // Rotate right
        Node *temp = n2->left;
        Node *temp2 = temp->right;

        temp->right = n2;
        n2->left = temp2;

        n2->height = max(getHeight(n2->left), getHeight(n2->right)) + 1;
        temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
        return temp;
    }

    // Insertion function for nodes of AVL Tree
    Node *insert(Node *n, string name, int id) {
        if (n == nullptr) {
            return new Node(name, id);
        }
        if (id < n->ID) {
            n->left = insert(n->left, name, id);
        }
        else if (id > n->ID) {
            n->right = insert(n->right, name, id);
        }
        if (id == n->ID) {  // Ensure strict equality check
            cout << "Duplicate ID found: " << id << endl;
            return n;
        }
        // update height
        n->height = max(getHeight(n->left), getHeight(n->right)) + 1;

        int balanceFactor = getBalance(n);

        // Case # 1
        if (balanceFactor > 1 && id < n->left->ID) {
            return RightRotation(n);
        }

        // Case # 2
        else if (balanceFactor < -1 && id > n->right->ID) {
            return LeftRotation(n);

        }
        // Case # 3
        else if (balanceFactor > 1 && id > n->left->ID) {
            n->left = LeftRotation(n->left);
            return RightRotation(n);
        }
        // Case # 4
        else if (balanceFactor < -1 && id < n->right->ID) {
            n->right = RightRotation(n->right);
            return LeftRotation(n);
        }

        return n;
    }

    /* used to debug function ensuring correct insertion
     void debugRoot() {
        if (root)
            cout << "Root: " << root->name << " (" << root->ID << "), Height: " << root->height << endl;
        else
            cout << "Root is null" << endl;
    }
*/

    Node *remove(Node *root, int id) {
        if (root == nullptr) {
            cout << "Root = nullptr" << endl;
            return nullptr;
        }

        if (id < root->ID) { // Base Case #1 if id < root
            root->left = remove(root->left, id);
        }

        else if (id > root->ID) { // Base Case #2 if id > root
            root->right = remove(root->right, id);
        }

        else {
            if (root->left == nullptr && root->right == nullptr) { // if there's no children
                delete root;
                return nullptr;
            }

            else if (root->left != nullptr && root->right == nullptr) { // if there's one child on the left
                Node *temp = root->left;
                delete root;
                return temp;

            }

            else if (root->left == nullptr && root->right != nullptr) { // if there's one child on the right
                Node *temp = root->right;
                delete root;
                return temp;
            }

            else { // if there's 2 children
                Node *successor = findSuccessor(root->right);
                root->ID = successor->ID;
                root->name = successor->name;
                root->right = remove(root->right, successor->ID);
            }

        }
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        // Balance the tree
        int balance = getBalance(root);

        // Left Heavy (Right Rotation)
        if (balance > 1 && getBalance(root->left) >= 0) {
            return RightRotation(root);
        }

        // Left Heavy (Left-Right Rotation)
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = LeftRotation(root->left);
            return RightRotation(root);
        }

        // Right Heavy (Left Rotation)
        if (balance < -1 && getBalance(root->right) <= 0) {
            return LeftRotation(root);
        }

        // Right Heavy (Right-Left Rotation)
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = RightRotation(root->right);
            return LeftRotation(root);
        }

        return root;
    }

    Node *findSuccessor(Node *n) { // find leftmost node
        while (n->left != nullptr) {
            n = n->left;
        }
        return n;
    };

    public:

    bool validEntry(string name);

    bool insert(string name, int ID);

    bool remove(int ID);

    // Getter functions
    int getHeight(Node *n);
    int getBalance(Node *n);


    // Tree ordering
    void inorder(Node* node) {
        if (node) {
            inorder(node->left);
            cout << node->name << ", ";
            inorder(node->right);
        }
    }

    void preorder(Node* node) {
        if (node) {
            cout << node->name << ", ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(Node* node) {
        if (node) {
            postorder(node->left);
            postorder(node->right);
            cout << node->name << ", ";
        }
    }

    // Print trees

    Node *root = nullptr;

    void printInorder() {
        inorder(root);
        cout << endl;
    }

    void printPreorder() {
        preorder(root);
        cout << endl;
    }

    void printPostorder() {
        postorder(root);
        cout << endl;
    }

    void printLevelCount() {
        cout << getHeight(root) << endl;
    }


    // For Testing purposes

    vector<string> getInorder();
    vector<string> getPreorder();

    bool isEmpty();

    vector<int> searchByName(string name);

    string searchByID(int ID);
    vector<string> getPostorder();

    void inorder(Node* node, vector<string>& result) { // inorder traversal storing storing nodes in vector
        if (node == nullptr) return;
        inorder(node->left, result);
        result.push_back(node->name);
        inorder(node->right, result);
    }

    void preorder(Node* node, vector<string>& result) { // preorder traversal storing storing nodes in vector
        if (node == nullptr) return;
        result.push_back(node->name);
        preorder(node->left, result);
        preorder(node->right, result);
    }

    void postorder(Node* n, vector<string>& result) { // postorder traversal storing storing nodes in vector
        if (n == nullptr) return;
        postorder(n->left, result);
        postorder(n->right, result);
        result.push_back(n->name);
    }

    void removeInorder(int n) { // store nodes in vector and search through to remove target
        vector<Node*> nodes;
        storeInorderNodes(root, nodes);

        if (n < 0 || n >= nodes.size()) {
            cout << "unsuccessful" << endl;
            return;
        }

        int IDtoRemove = nodes[n]->ID;
        root = remove(root, IDtoRemove);
        cout << "successful" << endl;
    }


    void storeInorderNodes(Node* n, vector<Node*>& nodes) { //recursive callback function to store nodes in vector
        if (n == nullptr) return;
        storeInorderNodes(n->left, nodes);
        nodes.push_back(n);
        storeInorderNodes(n->right, nodes);
    }


};



#endif //AVL_H