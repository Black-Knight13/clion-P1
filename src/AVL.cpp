//
// Created by jackson turnbull on 2/14/25.
//
#include "AVL.h"

using namespace std;

bool AVL::insert(string name, int ID) {
    if (name.empty() or ID < 0 or (!validEntry(name))){
        cout<<"unsuccessful"<<endl;
        return false;
    }

    /* used to debug function

     cout << "Before insertion: ";
     debugRoot();  Print root before insertion
     */

    root = insert(root, name, ID);

    /* used to debug function
    cout << "After insertion: ";
     debugRoot();  Print root after insertion
    */

    cout<<"successful"<<endl;
    return true;
}

bool AVL::remove(int ID) {
    if (root == nullptr) {
        cout << "unsuccessful" << endl;
        return false;
    }

    root = remove(root, ID);

    if (root == nullptr || root->ID != ID) {  // Check if node was removed
        cout << "successful" << endl;
        return true;
    }

    cout << "unsuccessful" << endl;
    return false;

}


int AVL::getHeight(Node* n) { // if node is null returns 0 else gives height
    if (n == nullptr){
        return 0;
    }
    return n->height;
}

int AVL::getBalance(Node* n) {// if node is null returns 0 else finds balance by subtracting left and right
    if (n == nullptr) {
        return 0;
    }
     // cout << "Balance factor for " << n->name << " (" << n->ID << "): " << endl;
    return getHeight(n->left) - getHeight(n->right);
}

bool AVL::validEntry(string name) {
    for (char a : name) {
        if (!isalpha(a) && a != ' ') {
            return false;  // num found
        }
    }
    return !name.empty();  // Ensure name is not empty
}

vector<string> AVL::getInorder() {
    vector<string> result;
    inorder(root, result);
    return result;
}

vector<string> AVL::getPreorder() {
    vector<string> result;
    preorder(root, result);
    return result;
}

vector<string> AVL::getPostorder() {
    vector<string> result;
    postorder(root, result);
    return result;
}



bool AVL::isEmpty() {
    return root == nullptr;
}

vector<int> AVL::searchByName(string name) {
    vector<int> result;
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* node = q.front();
        q.pop();

        if (node->name == name) {
            result.push_back(node->ID);
        }

        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }

    return result; // Returns all matching IDs or an empty vector if none found
}

string AVL::searchByID(int ID) { // search through tree for matching name
    Node* current = root;
    while (current) {
        if (current->ID == ID) return current->name;
        else if (ID < current->ID) current = current->left;
        else current = current->right;
    }
    return "unsuccessful";
}
