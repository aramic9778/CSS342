#include "bstree.h"
#include <string>

using namespace std;

Node::Node(Account *acc) : account{acc}, left{nullptr}, right{nullptr} {}

// Create BST
BSTree::BSTree() { root = nullptr; } // default constructor

// Delete all nodes in BST
BSTree::~BSTree() { clear(); } // destructor

// Insert new account
bool BSTree::insert(Account *account) {
  return insertHelper(root, account);
} // insert an acount to BSTree

// Insert recursive helper
bool BSTree::insertHelper(Node *&root, Account *account) {
  if (root == nullptr) {
    root = new Node(account);
    return true;
  }
  if (root->account->getID() ==
      account->getID()) { // if ID equals unable to insert
    return false;
  }

  if (root->account->getID() > account->getID()) { // sort all account by ID
    return insertHelper(root->left, account);
  }
  return insertHelper(root->right, account);
}

// Retrieve account
// returns true if successful AND *Account points to account
bool BSTree::retrieve(const int &accountNumber, Account *&account) const {
  Node *curr = root;
  while (curr != nullptr) {
    if (curr->account->ID == accountNumber) { // if ID equals retirve
      account = curr->account;
      return true;
    }
    if (curr->account->ID > accountNumber) { // follow the BSTree
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  return false;
}

// Display information on all accounts
void BSTree::display() const { displayHelper(root); } // display all acounts
// Display recursive helper
void BSTree::displayHelper(Node *root) const {
  if (root == nullptr) {
    return;
  } // if empty return
  displayHelper(root->left);
  cout << root->account->name << " Account ID: " << root->account->ID
       << endl;                  // first line with account ID
  for (int i = 0; i < 10; i++) { // print all fundtypes
    cout << "        " << root->account->getFundName(i) << ": $"
         << root->account->getFund(i) << endl;
    if (i == 9) {
      cout << endl;
    } // skipp the line after last fund
  }
  displayHelper(root->right);
}

// delete all information in AccountTree
void BSTree::clear() { clearHelper(root); } // clear all accounts
// clear recursive helper
void BSTree::clearHelper(Node *root) { // delete all nodes
  if (root != nullptr) {
    clearHelper(root->left);
    clearHelper(root->right);
    delete root->account;
    delete root;
  }
}