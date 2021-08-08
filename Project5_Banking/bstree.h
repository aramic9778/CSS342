
#ifndef BSTREE_H
#define BSTREE_H

#include "account.h"
#include <iostream>
class Node {
  friend class BSTree;
  explicit Node(Account *acc);

private:
  Account *account;
  Node *left;
  Node *right;
};
class BSTree {

public:
  // Create BST
  BSTree();

  // Delete all nodes in BST
  ~BSTree();
  // copy not allowed
  BSTree(const BSTree &other) = delete; // to get rid of warnings

  // move not allowed
  BSTree(BSTree &&other) = delete; // to get rid of warnings

  // assignment not allowed
  BSTree &operator=(const BSTree &other) = delete;

  // move assignment not allowed
  BSTree &operator=(BSTree &&other) = delete;

  // Insert new account
  bool insert(Account *account);

  // Retrieve account
  // returns true if successful AND *Account points to account
  bool retrieve(const int &accountNumber, Account *&account) const;

  // Display information on all accounts
  void display() const;

  // delete all information in AccountTree
  void clear();

  // check if tree is empty
  bool insertHelper(Node *&root, Account *account);
  void displayHelper(Node *root) const;
  void clearHelper(Node *root);

private:
  Node *root;
};
#endif // BSTREE_H
