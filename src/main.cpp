#include <iostream>
#include "AVL.h"
#include <sstream>


using namespace std;

int main() {
	AVL tree; // create AVL instance tree
	string command; // initialize command to be a string to input in main method

	while (getline(cin, command)) {
		// while loop runs off commands until exited
		stringstream ss(command);
		string action, name;
		int id;

		ss >> action;
		/*-------------------Insert ACTION--------------------------------------- */
		if (action == "insert") {
			if (ss.peek() == ' ') ss.ignore(); // Ignore leading space
			if (ss.peek() != '"') {
				cout << "unsuccessful" << endl; // Ensure name starts with quote
				continue;
			}
			getline(ss, name, '"'); // get name & id with space as delimiter
			getline(ss, name, '"');
			ss >> id;
			tree.insert(name, id); // insert name and id into tree
		}

		else if (action == "remove") {  // remove node->id from tree

			ss >> id;
			tree.remove(id);
		}

		/*-------------------SEARCH ACTION--------------------------------------- */
		else if (action == "search") {
			if (!tree.isEmpty()) {
				if (ss.peek() == ' ') ss.ignore(); // Ignore leading space

				if (ss >> id) {  // Search by ID
					string result = tree.searchByID(id);
					if (result != "Not found") {
						cout << result << endl;
					}
					else {
						cout << "unsuccessful" << endl;
					}
				}

				else {  // Search by name
					ss.clear();
					if (ss.peek() == ' ') ss.ignore();
					if (ss.peek() == '"') {
						ss.ignore(); // Skip first quote
						getline(ss, name, '"'); // Extract name inside quotes

						vector<int> results = tree.searchByName(name);
						if (!results.empty()) {
							for (int i = 0; i < results.size(); i++) {
								cout << results[i];
								if (i < results.size() - 1) cout << endl; // Proper formatting
							}
							cout << endl;
						} else {
							cout << "unsuccessful" << endl;
						}
					} else {
						cout << "unsuccessful" << endl;
					}
				}
			} else {
				cout << "unsuccessful" << endl;
			}
		}
		/*-------------------printInorder--------------------------------------- */

		else if (action == "printInorder") { // store nodes in vector to fix commas
			vector<string> result = tree.getInorder();
			for (int i = 0; i < result.size(); i++) {
				cout << result[i];
				if (i < result.size() - 1) cout << ", ";
			}
			cout << endl;
		}
		/*-------------------removeInorder--------------------------------------- */
		else if (action == "removeInorder") {
			if (!tree.isEmpty()) {
				int n;
				if (ss >> n) {
					tree.removeInorder(n);
				} else {
					cout << "unsuccessful" << endl;
				}
			} else {
				cout << "unsuccessful" << endl;
			}
		}

		/*-------------------printPreorder--------------------------------------- */
		else if (action == "printPreorder") { // store nodes in vector to fix commas
			vector<string> result = tree.getPreorder();
			for (int i = 0; i < result.size(); i++) {
				cout << result[i];
				if (i < result.size() - 1) cout << ", ";
			}
			cout << endl;
		}

		/*-------------------printPostorder--------------------------------------- */
		else if (action == "printPostorder") { // store nodes in vector to fix commas
			vector<string> result = tree.getPostorder();
			for (int i = 0; i < result.size(); i++) {
				cout << result[i];
				if (i < result.size() - 1) cout << ", ";
			}
			cout << endl;
		}

		else if (action == "printLevelCount") {
			tree.printLevelCount();
		}

		else if (action == "exit") {
			return 0;
		}

		else {
			cout << "";
		}
	}
}
