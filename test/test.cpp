/*
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "AVL.h"
#include "AVL.cpp"

//Jackson Turnbull 41914654
using namespace std;

TEST_CASE("Remove root when it's the only node", "[RemoveInorder]") {
    AVL tree;
    tree.insert("Zahara", 99);

    vector<string> inorderBefore = tree.getInorder();
    REQUIRE(inorderBefore == vector<string>{"Zahara"});

    tree.removeInorder(0); // Remove the root node

    vector<string> inorderAfter = tree.getInorder();
    REQUIRE(inorderAfter.empty()); // Tree should be empty
}

TEST_CASE("Remove an internal node with two children", "[2 Child Case]") {
    AVL tree;
    tree.insert("Drake", 50);
    tree.insert("Ela", 30);
    tree.insert("Frank", 70);
    tree.insert("Bobbie", 60);
    tree.insert("Hannah", 80);

    vector<string> inorderBefore = tree.getInorder();
    REQUIRE(inorderBefore == vector<string>{"Ela", "Drake", "Bobbie", "Frank", "Hannah"});

    tree.removeInorder(2); // Remove "Bobbie"

    vector<string> inorderAfter = tree.getInorder();
    REQUIRE(inorderAfter == vector<string>{"Ela", "Drake", "Frank", "Hannah"});
}

TEST_CASE("Verify Tree Balancing", "[Balancing]") {
    AVL tree;
    tree.insert("Hannah", 50);
    tree.insert("Ian", 30);
    tree.insert("Jane", 70);
    tree.insert("Kevin", 20);
    tree.insert("Lucy", 40);

    // Checking preorder to confirm tree balance
    vector<string> preorder = tree.getPreorder();
    REQUIRE(preorder == vector<string>{"Hannah", "Ian", "Kevin", "Lucy", "Jane"});
}

TEST_CASE("Search Non-Existent ID", "[Search]") {
    AVL tree;
    tree.insert("Frank", 33333);
    tree.insert("Ala", 44444);

    REQUIRE(tree.searchByID(99999) == "unsuccessful"); // 99999 is not in the tree
}

TEST_CASE("Check Empty Tree Behavior", "[EmptyTree]") {
    AVL tree;

    REQUIRE(tree.getInorder().empty());
    REQUIRE(tree.getPreorder().empty());
    REQUIRE(tree.getPostorder().empty());

    REQUIRE(tree.isEmpty() == true);
    REQUIRE(tree.searchByID(11111) == "unsuccessful");
}


*/

